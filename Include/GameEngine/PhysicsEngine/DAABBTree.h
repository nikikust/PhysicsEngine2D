#pragma once
#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
#define nullnode -1

    struct node
    {
        union
        {
            int32_t parent;
            int32_t next;
        };

        int32_t child_1;
        int32_t child_2;

        ShapeAABB aabb;

        bool is_leaf() const
        {
            return child_1 == nullnode;
        }
    };

    class DAABBTree
    {
    public:
        DAABBTree();
        ~DAABBTree();


        int32_t insert(const ShapeAABB& aabb);

        void remove(int32_t node_id);

        bool move(int32_t node_id, const ShapeAABB& aabb);

    private:
        int32_t allocate_node();
        void free_node(int32_t node_id);

        void insert_leaf(int32_t node_id);
        void remove_leaf(int32_t node_id);

        node* m_nodes;
        int32_t m_root_id;
        int32_t m_free_node;

        int32_t m_capacity;
        int32_t m_size;
    };
} // namespace physics
