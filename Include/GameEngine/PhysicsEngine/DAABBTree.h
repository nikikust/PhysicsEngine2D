#pragma once
#include <stack>

#include <GameEngine/PhysicsEngine/ShapeAABB.h>

#ifdef DEBUGTree
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUGTree


namespace physics
{
#define nullnode -1

    struct TreeNode
    {
        union
        {
            int32_t parent;
            int32_t next;
        };

        int32_t child_1;
        int32_t child_2;

        ShapeAABB aabb;

        void* user_data;

        int32_t height;

        bool is_leaf() const
        {
            return child_1 == nullnode;
        }
    };

    class DAABBTree
    {
    public:
        DAABBTree();
        DAABBTree(DAABBTree&&) noexcept;
        ~DAABBTree();


        int32_t insert(const ShapeAABB& aabb, void* user_data);

        void remove(int32_t node_id);

        bool move(int32_t node_id, const ShapeAABB& aabb);

        template <typename Callback>
        void query(Callback* callback, const ShapeAABB& aabb) const;

        template <typename Callback>
        void query(Callback* callback, const DAABBTree& tree) const;

        void shift_origin(sf::Vector2f offset);

        ShapeAABB get_root_AABB() const;

        void reset();

#ifdef DEBUGPrintTree
        void print_tree(const std::string& tree_part, int32_t id = nullnode) const;
#endif // DEBUGPrintTree

#ifdef DEBUGTree
        void draw_boxes() const;

        static std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUGTree

    private:
        int32_t allocate_node();
        void free_node(int32_t node_id);

        int32_t balance(int32_t iA);

        void insert_leaf(int32_t node_id);
        void remove_leaf(int32_t node_id);

        TreeNode* m_nodes;
        int32_t m_root_id;
        int32_t m_free_node;

        int32_t m_capacity;
        int32_t m_size;
    };


    template<typename Callback>
    inline void DAABBTree::query(Callback* callback, const ShapeAABB& aabb) const
    {
        std::stack<int32_t> stack;

        stack.push(m_root_id);

        while (!stack.empty())
        {
            int32_t node_id = stack.top(); stack.pop();

            if (node_id == nullnode)
                continue;

            auto& node = m_nodes[node_id];

            if (node.aabb.collides(aabb))
            {
                if (node.is_leaf())
                {
                    callback->add_contact(node.user_data);
                }
                else
                {
                    stack.push(node.child_1);
                    stack.push(node.child_2);
                }
            }
        }
    }

    template<typename Callback>
    inline void DAABBTree::query(Callback* callback, const DAABBTree& tree) const
    {
        std::stack<std::pair<int32_t, int32_t>> stack;

        stack.push({ m_root_id, tree.m_root_id });

        while (!stack.empty())
        {
            auto [node_id_1, node_id_2] = stack.top(); stack.pop();

            if (node_id_1 == nullnode || node_id_2 == nullnode)
                continue;

            auto& node_1 = this->m_nodes[node_id_1];
            auto& node_2 = tree .m_nodes[node_id_2];

            if (node_1.aabb.collides(node_2.aabb))
            {
                if (node_1.is_leaf() && node_2.is_leaf())
                {
                    callback->add_contact(node_1.user_data, node_2.user_data);
                }
                else if (node_1.is_leaf())
                {
                    stack.push({ node_id_1, node_2.child_1 });
                    stack.push({ node_id_1, node_2.child_2 });
                }
                else if (node_2.is_leaf())
                {
                    stack.push({ node_1.child_1, node_id_2 });
                    stack.push({ node_1.child_2, node_id_2 });
                }
                else
                {
                    stack.push({ node_1.child_1, node_2.child_1 });
                    stack.push({ node_1.child_1, node_2.child_2 });
                    stack.push({ node_1.child_2, node_2.child_1 });
                    stack.push({ node_1.child_2, node_2.child_2 });
                }
            }
        }
    }
} // namespace physics
