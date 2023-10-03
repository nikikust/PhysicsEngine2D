#pragma once
#include <stack>

#include <GameEngine/PhysicsEngine/ShapeAABB.h>

#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


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
        void query(Callback* callback, const ShapeAABB& aabb);

        void shift_origin(sf::Vector2f offset);

        ShapeAABB get_root_AABB() const;

        void reset();

#ifdef DEBUGTree
        void print_tree(const std::string& tree_part, int32_t id = nullnode) const;
#endif // DEBUGTree

#ifdef DEBUG
        void draw_boxes() const;

        static std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUG

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
    inline void DAABBTree::query(Callback* callback, const ShapeAABB& aabb)
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
} // namespace physics
