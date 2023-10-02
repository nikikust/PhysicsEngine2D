#include <GameEngine/PhysicsEngine/DAABBTree.h>


namespace physics
{
	DAABBTree::DAABBTree()
	{
		m_capacity = 2;
		m_size = 0;
		m_root_id = nullnode;

		m_nodes = (node*)malloc(sizeof(node) * m_capacity);
		memset(m_nodes, 0, sizeof(node) * m_capacity);

		for (int32_t i = 0; i < m_capacity - 1; ++i)
		{
			m_nodes[i].next = i + 1;
		}
		m_nodes[m_capacity - 1].next = nullnode;

		m_free_node = 0;

		std::cout << "Constructed with capacity: " << m_capacity << std::endl << std::endl;
	}

	DAABBTree::~DAABBTree()
	{
		free(m_nodes);

		std::cout << std::endl << "Deconstructed with capacity: " << m_capacity << std::endl;
	}

	int32_t DAABBTree::insert(const ShapeAABB& aabb)
	{
		int32_t node_id = allocate_node();

		m_nodes[node_id].aabb.min = aabb.min;
		m_nodes[node_id].aabb.max = aabb.max;

		insert_leaf(node_id);

		return node_id;
	}

	void DAABBTree::remove(int32_t node_id)
	{
		remove_leaf(node_id);

		free_node(node_id);
	}

	bool DAABBTree::move(int32_t node_id, const ShapeAABB& aabb)
	{
		return false;
	}

	int32_t DAABBTree::allocate_node()
	{
		// Pool is full
		if (m_free_node == nullnode)
		{
			node* old_nodes = m_nodes;
			m_capacity *= 2;

			m_nodes = (node*)malloc(m_capacity * sizeof(node));
			memcpy(m_nodes, old_nodes, m_size * sizeof(node));

			free(old_nodes);

			for (int32_t i = m_size; i < m_capacity - 1; ++i)
			{
				m_nodes[i].next = i + 1;
			}
			m_nodes[m_capacity - 1].next = nullnode;

			m_free_node = m_size;

			std::cout << std::endl << "Increased capacity to: " << m_capacity << std::endl;
		}


		int32_t node_id = m_free_node;

		m_free_node = m_nodes[node_id].next;

		m_nodes[node_id].parent = nullnode;
		m_nodes[node_id].child_1 = nullnode;
		m_nodes[node_id].child_2 = nullnode;

		++m_size;

		std::cout << "Allocated id: " << node_id << std::endl;

		return node_id;
	}

	void DAABBTree::free_node(int32_t node_id)
	{
		m_nodes[node_id].next = m_free_node;

		m_free_node = node_id;

		--m_size;

		std::cout << "Deallocated id: " << node_id << std::endl;
	}

	void DAABBTree::insert_leaf(int32_t node_id)
	{
	}

	void DAABBTree::remove_leaf(int32_t node_id)
	{
	}

} // namespace physics
