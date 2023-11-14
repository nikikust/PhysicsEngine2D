#pragma once
#include <stack>

#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/ShapeAABB.h>
#include <GameEngine/PhysicsEngine/Ray.h>

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
        void cast_ray(Callback* callback, const Ray& ray);

        template <typename Callback>
        void query(Callback* callback, const ShapeAABB& aabb);

        template <typename Callback>
        void query(Callback* callback, const DAABBTree& tree);

        void shift_origin(Vector offset);

        ShapeAABB get_root_AABB() const;
        int32_t get_height() const;

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


        std::vector<int32_t> m_stack_;
        std::vector<int32_t> m_raycast_stack_;
        std::vector<std::pair<int32_t, int32_t>> m_pairs_stack_;
    };
} // namespace physics

#include "DAABBTree.inl"
