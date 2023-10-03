#include <GameEngine/PhysicsEngine/DAABBTree.h>


namespace physics
{
#ifdef DEBUG
	std::vector<graphics::DebugDraw> DAABBTree::debug_entities{};
#endif // DEBUG

	DAABBTree::DAABBTree()
	{
		m_capacity = 32;
		m_size = 0;
		m_root_id = nullnode;

		m_nodes = (TreeNode*)malloc(sizeof(TreeNode) * m_capacity);

		if (m_nodes == nullptr)
			throw("Can't allocate tree in ctor!");

		memset(m_nodes, 0, sizeof(TreeNode) * m_capacity);

		for (int32_t i = 0; i < m_capacity - 1; ++i)
		{
			m_nodes[i].next = i + 1;
			m_nodes[i].height = -1;
		}
		m_nodes[m_capacity - 1].next = nullnode;
		m_nodes[m_capacity - 1].height = -1;

		m_free_node = 0;
	}

	DAABBTree::DAABBTree(DAABBTree&& tree) noexcept
		: m_nodes	  (std::move(tree.m_nodes	 )),
		  m_root_id	  (std::move(tree.m_root_id	 )),
		  m_free_node (std::move(tree.m_free_node)),
		  m_capacity  (std::move(tree.m_capacity )),
		  m_size	  (std::move(tree.m_size	 ))
	{}

	DAABBTree::~DAABBTree()
	{
		free(m_nodes);
	}

	int32_t DAABBTree::insert(const ShapeAABB& aabb, void* user_data)
	{
		int32_t node_id = allocate_node();

		m_nodes[node_id].aabb.min = aabb.min;
		m_nodes[node_id].aabb.max = aabb.max;
		m_nodes[node_id].user_data = user_data;
		m_nodes[node_id].height = 1;

		insert_leaf(node_id);

#ifdef DEBUGPrintTree
		std::cout << "Inserted node with id: " << node_id << std::endl;

		std::cout << "o" << std::endl;
		print_tree("", m_root_id);
#endif // DEBUGPrintTree

		return node_id;
	}

	void DAABBTree::remove(int32_t node_id)
	{
		remove_leaf(node_id);

		free_node(node_id);
	}

	bool DAABBTree::move(int32_t node_id, const ShapeAABB& aabb)
	{
		// Extend AABB
		ShapeAABB fat_AABB;
		sf::Vector2f r{ 5.f, 5.f };

		fat_AABB.min = aabb.min - r;
		fat_AABB.max = aabb.max + r;

		const ShapeAABB& tree_AABB = m_nodes[node_id].aabb;

		if (tree_AABB.contains(aabb))
		{
			return false;

			// The tree AABB still contains the object, but it might be too large.
			// Perhaps the object was moving fast but has since gone to sleep.
			// The huge AABB is larger than the new fat AABB.
			ShapeAABB huge_AABB{
				fat_AABB.min - 4.0f * r,
				fat_AABB.max + 4.0f * r
			};

			if (huge_AABB.contains(tree_AABB))
			{
				// The tree AABB contains the object AABB and the tree AABB is
				// not too large. No tree update needed.
				return false;
			}
			
			// Otherwise the tree AABB is huge and needs to be shrunk
		}

		remove_leaf(node_id);

		m_nodes[node_id].aabb = fat_AABB;

		insert_leaf(node_id);

		return true;
	}

	void DAABBTree::shift_origin(sf::Vector2f offset)
	{
		for (int32_t i = 0; i < m_capacity; ++i)
		{
			if (m_nodes[i].height == -1)
				continue;

			m_nodes[i].aabb.min += offset;
			m_nodes[i].aabb.max += offset;
		}
	}

	ShapeAABB DAABBTree::get_root_AABB() const
	{
		if (m_root_id != nullnode)
			return m_nodes[m_root_id].aabb;
		else
			return ShapeAABB();
	}

	void DAABBTree::reset()
	{
		free(m_nodes);

		m_capacity = 32;
		m_size = 0;
		m_root_id = nullnode;

		m_nodes = (TreeNode*)malloc(sizeof(TreeNode) * m_capacity);

		if (m_nodes == nullptr)
			throw("Can't reallocate tree in reset!");

		memset(m_nodes, 0, sizeof(TreeNode) * m_capacity);

		for (int32_t i = 0; i < m_capacity - 1; ++i)
		{
			m_nodes[i].next = i + 1;
			m_nodes[i].height = -1;
		}
		m_nodes[m_capacity - 1].next = nullnode;
		m_nodes[m_capacity - 1].height = -1;

		m_free_node = 0;
	}

#ifdef DEBUGPrintTree
	void DAABBTree::print_tree(const std::string& tree_part, int32_t id) const
	{
		if (id == nullnode)
			return;

#if 0
		if (tree_part.empty())
		{
			std::cout << "binary_tree = TreeNode()" << std::endl;

			if (m_nodes[id].is_leaf())
				return;

			print_tree("binary_tree.left", m_nodes[id].child_1);
			print_tree("binary_tree.right", m_nodes[id].child_2);
		}
		else
		{
			std::cout << "temp = TreeNode()" << std::endl;
			std::cout << tree_part << "= temp" << std::endl;

			if (m_nodes[id].is_leaf())
				return;

			print_tree(tree_part + ".left",  m_nodes[id].child_1);
			print_tree(tree_part + ".right", m_nodes[id].child_2);
		}
#else
		std::cout << tree_part << "`- " << id << " (p: " << m_nodes[id].aabb.get_perimeter() << ", h: " << m_nodes[id].height << "):" << std::endl;

		if (m_nodes[id].is_leaf())
			return;

		print_tree(tree_part + "   |", m_nodes[id].child_1);
		print_tree(tree_part + "    ", m_nodes[id].child_2);
#endif
	}
#endif // DEBUGPrintTree

#ifdef DEBUGTree
	void DAABBTree::draw_boxes() const
	{
		if (m_root_id == nullnode)
			return;

		std::stack<int32_t> stack;

		stack.push(m_root_id);

		while (!stack.empty())
		{
			auto& node = m_nodes[stack.top()]; stack.pop();

			auto corner{ node.aabb.max - node.aabb.min };

			debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Border, node.aabb.min, sf::Color(0, 55 + 24 * node.height, 0), 0, 0,
				{ { 0.f, 0.f }, { corner.x, 0.f }, { corner.x, corner.y }, { 0.f, corner.y } }, 2.f});

			if (node.is_leaf())
				continue;

			stack.push(node.child_1);
			stack.push(node.child_2);
		}
	}
#endif // DEBUGTree

	int32_t DAABBTree::allocate_node()
	{
		// Pool is full
		if (m_free_node == nullnode)
		{
			TreeNode* old_nodes = m_nodes;
			m_capacity *= 2;

			m_nodes = (TreeNode*)malloc(m_capacity * sizeof(TreeNode));

			if (m_nodes == nullptr)
				throw("Can't reallocate tree in allocate_node!");

			memcpy(m_nodes, old_nodes, m_size * sizeof(TreeNode));

			free(old_nodes);

			for (int32_t i = m_size; i < m_capacity - 1; ++i)
			{
				m_nodes[i].next = i + 1;
				m_nodes[i].height = -1;
			}
			m_nodes[m_capacity - 1].next = nullnode;
			m_nodes[m_capacity - 1].height = -1;

			m_free_node = m_size;
		}


		int32_t node_id = m_free_node;

		m_free_node = m_nodes[node_id].next;

		m_nodes[node_id].parent = nullnode;
		m_nodes[node_id].child_1 = nullnode;
		m_nodes[node_id].child_2 = nullnode;
		m_nodes[node_id].height = 0;
		m_nodes[node_id].user_data = nullptr;

		++m_size;

		return node_id;
	}

	void DAABBTree::free_node(int32_t node_id)
	{
		m_nodes[node_id].next = m_free_node;

		m_free_node = node_id;

		--m_size;
	}

	int32_t DAABBTree::balance(int32_t iA)
	{
		auto& A = m_nodes[iA];

		// Fast exit
		if (A.is_leaf() || A.height < 2)
		{
			return iA;
		}

		int32_t iB = A.child_1;
		int32_t iC = A.child_2;

		auto& B = m_nodes[iB];
		auto& C = m_nodes[iC];

		int32_t balance = C.height - B.height;

		// Rotate C up
		if (balance > 1)
		{
			int32_t iF = C.child_1;
			int32_t iG = C.child_2;

			auto& F = m_nodes[iF];
			auto& G = m_nodes[iG];

			// Swap A and C
			C.child_1 = iA;
			C.parent  = A.parent;
			A.parent  = iC;

			// A's old parent should point to C
			if (C.parent != nullnode)
			{
				if (m_nodes[C.parent].child_1 == iA)
				{
					m_nodes[C.parent].child_1 = iC;
				}
				else
				{
					m_nodes[C.parent].child_2 = iC;
				}
			}
			else
			{
				m_root_id = iC;
			}

			// Rotate
			if (F.height > G.height)
			{
				C.child_2 = iF;
				A.child_2 = iG;
				G.parent = iA;
				A.aabb = union_of(B.aabb, G.aabb);
				C.aabb = union_of(A.aabb, F.aabb);

				A.height = 1 + std::max(B.height, G.height);
				C.height = 1 + std::max(A.height, F.height);
			}
			else
			{
				C.child_2 = iG;
				A.child_2 = iF;
				F.parent = iA;
				A.aabb = union_of(B.aabb, F.aabb);
				C.aabb = union_of(A.aabb, G.aabb);

				A.height = 1 + std::max(B.height, F.height);
				C.height = 1 + std::max(A.height, G.height);
			}

			return iC;
		}

		// Rotate B up
		if (balance < -1)
		{
			int32_t iD = B.child_1;
			int32_t iE = B.child_2;
			auto& D = m_nodes[iD];
			auto& E = m_nodes[iE];

			// Swap A and B
			B.child_1 = iA;
			B.parent  = A.parent;
			A.parent  = iB;

			// A's old parent should point to B
			if (B.parent != nullnode)
			{
				if (m_nodes[B.parent].child_1 == iA)
				{
					m_nodes[B.parent].child_1 = iB;
				}
				else
				{
					m_nodes[B.parent].child_2 = iB;
				}
			}
			else
			{
				m_root_id = iB;
			}

			// Rotate
			if (D.height > E.height)
			{
				B.child_2 = iD;
				A.child_1 = iE;
				E.parent = iA;
				A.aabb = union_of(C.aabb, E.aabb);
				B.aabb = union_of(A.aabb, D.aabb);

				A.height = 1 + std::max(C.height, E.height);
				B.height = 1 + std::max(A.height, D.height);
			}
			else
			{
				B.child_2 = iE;
				A.child_1 = iD;
				D.parent = iA;
				A.aabb = union_of(C.aabb, D.aabb);
				B.aabb = union_of(A.aabb, E.aabb);

				A.height = 1 + std::max(C.height, D.height);
				B.height = 1 + std::max(A.height, E.height);
			}

			return iB;
		}

		return iA;
	}

	void DAABBTree::insert_leaf(int32_t node_id)
	{
		// Fast exit for empty tree
		if (m_root_id == nullnode)
		{
			m_root_id = node_id;
			m_nodes[m_root_id].parent = nullnode;

			return;
		}

		// Find the best sibling for this node
		auto& leaf_AABB = m_nodes[node_id].aabb;

		int32_t index = m_root_id;

		while (!m_nodes[index].is_leaf())
		{
			int32_t child_1 = m_nodes[index].child_1;
			int32_t child_2 = m_nodes[index].child_2;

			float area = m_nodes[index].aabb.get_perimeter();

			ShapeAABB combined_AABB{ union_of(m_nodes[index].aabb, leaf_AABB) };
			float combined_area = combined_AABB.get_perimeter();

			// Cost of creating a new parent for this node and the new leaf
			float cost = combined_area;

			// Minimum cost of pushing the leaf further down the tree
			float inheritance_cost = combined_area - area;


			// Cost of descending into child_1
			float cost_1;
			if (m_nodes[child_1].is_leaf())
			{
				ShapeAABB aabb{ union_of(leaf_AABB, m_nodes[child_1].aabb) };

				cost_1 = aabb.get_perimeter() + inheritance_cost;
			}
			else
			{
				ShapeAABB aabb{ union_of(leaf_AABB, m_nodes[child_1].aabb) };

				float oldArea = m_nodes[child_1].aabb.get_perimeter();
				float newArea = aabb.get_perimeter();

				cost_1 = (newArea - oldArea) + inheritance_cost;
			}

			// Cost of descending into child_2
			float cost_2;
			if (m_nodes[child_2].is_leaf())
			{
				ShapeAABB aabb{ union_of(leaf_AABB, m_nodes[child_2].aabb) };

				cost_2 = aabb.get_perimeter() + inheritance_cost;
			}
			else
			{
				ShapeAABB aabb{ union_of(leaf_AABB, m_nodes[child_2].aabb) };

				float oldArea = m_nodes[child_2].aabb.get_perimeter();
				float newArea = aabb.get_perimeter();

				cost_2 = (newArea - oldArea) + inheritance_cost;
			}

			// Descend according to the minimum cost.
			if (cost < cost_1 && cost < cost_2)
				break;

			// Descend
			if (cost_1 < cost_2)
				index = child_1;
			else
				index = child_2;
		}

		int32_t sibling = index;

		// Create a new parent.
		int32_t old_parent = m_nodes[sibling].parent;
		int32_t new_parent = allocate_node();

		m_nodes[new_parent].parent = old_parent;
		m_nodes[new_parent].user_data = nullptr;
		m_nodes[new_parent].aabb = union_of(leaf_AABB, m_nodes[sibling].aabb);
		m_nodes[new_parent].height = m_nodes[sibling].height + 1;


		if (old_parent != nullnode)
		{
			// The sibling was not the root.
			if (m_nodes[old_parent].child_1 == sibling)
			{
				m_nodes[old_parent].child_1 = new_parent;
			}
			else
			{
				m_nodes[old_parent].child_2 = new_parent;
			}

			m_nodes[new_parent].child_1 = sibling;
			m_nodes[new_parent].child_2 = node_id;
			m_nodes[sibling].parent = new_parent;
			m_nodes[node_id].parent = new_parent;
		}
		else
		{
			// The sibling was the root.
			m_nodes[new_parent].child_1 = sibling;
			m_nodes[new_parent].child_2 = node_id;
			m_nodes[sibling].parent = new_parent;
			m_nodes[node_id].parent = new_parent;
			m_root_id = new_parent;
		}

		// Walk back up the tree fixing heights and AABBs
		index = m_nodes[node_id].parent;
		while (index != nullnode)
		{
			//index = balance(index);

			int32_t child_1 = m_nodes[index].child_1;
			int32_t child_2 = m_nodes[index].child_2;

			m_nodes[index].height = 1 + std::max(m_nodes[child_1].height, m_nodes[child_2].height);
			m_nodes[index].aabb = union_of(m_nodes[child_1].aabb, m_nodes[child_2].aabb);

			index = m_nodes[index].parent;
		}
	}

	void DAABBTree::remove_leaf(int32_t node_id)
	{
		if (node_id == m_root_id)
		{
			m_root_id = nullnode;
			return;
		}

		int32_t parent = m_nodes[node_id].parent;
		int32_t grand_parent = m_nodes[parent].parent;
		int32_t sibling;

		if (m_nodes[parent].child_1 == node_id)
		{
			sibling = m_nodes[parent].child_2;
		}
		else
		{
			sibling = m_nodes[parent].child_1;
		}


		if (grand_parent != nullnode)
		{
			// Destroy parent and connect sibling to grand_parent.
			if (m_nodes[grand_parent].child_1 == parent)
			{
				m_nodes[grand_parent].child_1 = sibling;
			}
			else
			{
				m_nodes[grand_parent].child_2 = sibling;
			}

			m_nodes[sibling].parent = grand_parent;

			free_node(parent);

			// Adjust ancestor bounds.
			int32_t index = grand_parent;
			while (index != nullnode)
			{
				//index = balance(index);

				int32_t child_1 = m_nodes[index].child_1;
				int32_t child_2 = m_nodes[index].child_2;

				m_nodes[index].aabb = union_of(m_nodes[child_1].aabb, m_nodes[child_2].aabb);
				m_nodes[index].height = 1 + std::max(m_nodes[child_1].height, m_nodes[child_2].height);

				index = m_nodes[index].parent;
			}
		}
		else
		{
			m_root_id = sibling;
			m_nodes[sibling].parent = nullnode;

			free_node(parent);
		}
	}

} // namespace physics
