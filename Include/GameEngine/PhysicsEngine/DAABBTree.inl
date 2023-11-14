namespace physics
{
    template<typename Callback>
    inline void DAABBTree::cast_ray(Callback* callback, const Ray& ray)
    {
        m_raycast_stack_.emplace_back(m_root_id);

        RayHitInfo result;

        while (!m_raycast_stack_.empty())
        {
            int32_t node_id = m_raycast_stack_.back(); m_raycast_stack_.pop_back();

            if (node_id == nullnode)
                continue;

            auto& node = m_nodes[node_id];

            if (node.aabb.cast_ray(ray, result))
            {
                if (node.is_leaf())
                {
                    callback->raycast_callback(node.user_data);
                }
                else
                {
                    m_raycast_stack_.emplace_back(node.child_1);
                    m_raycast_stack_.emplace_back(node.child_2);
                }
            }
        }
    }

    template<typename Callback>
    inline void DAABBTree::query(Callback* callback, const ShapeAABB& aabb)
    {
        m_stack_.emplace_back(m_root_id);

        while (!m_stack_.empty())
        {
            int32_t node_id = m_stack_.back(); m_stack_.pop_back();

            if (node_id == nullnode)
                continue;

            auto& node = m_nodes[node_id];

            if (node.aabb.collides(aabb))
            {
                if (node.is_leaf())
                {
                    callback->add_contact_bodies(node.user_data);
                }
                else
                {
                    m_stack_.emplace_back(node.child_1);
                    m_stack_.emplace_back(node.child_2);
                }
            }
        }
    }

    template<typename Callback>
    inline void DAABBTree::query(Callback* callback, const DAABBTree& tree)
    {
        m_pairs_stack_.emplace_back(m_root_id, tree.m_root_id);

        while (!m_pairs_stack_.empty())
        {
            auto& [node_id_1, node_id_2] = m_pairs_stack_.back();

            if (node_id_1 == nullnode || node_id_2 == nullnode)
            {
                m_pairs_stack_.pop_back();
                continue;
            }

            auto& node_1 = this->m_nodes[node_id_1];
            auto& node_2 = tree.m_nodes[node_id_2];

            m_pairs_stack_.pop_back();

            if (node_1.aabb.collides(node_2.aabb))
            {
                if (node_1.is_leaf() && node_2.is_leaf())
                {
                    callback->add_contact_fixtures(node_1.user_data, node_2.user_data);
                }
                else if (node_1.is_leaf())
                {
                    m_pairs_stack_.emplace_back(node_id_1, node_2.child_1);
                    m_pairs_stack_.emplace_back(node_id_1, node_2.child_2);
                }
                else if (node_2.is_leaf())
                {
                    m_pairs_stack_.emplace_back(node_1.child_1, node_id_2);
                    m_pairs_stack_.emplace_back(node_1.child_2, node_id_2);
                }
                else
                {
                    m_pairs_stack_.emplace_back(node_1.child_1, node_2.child_1);
                    m_pairs_stack_.emplace_back(node_1.child_1, node_2.child_2);
                    m_pairs_stack_.emplace_back(node_1.child_2, node_2.child_1);
                    m_pairs_stack_.emplace_back(node_1.child_2, node_2.child_2);
                }
            }
        }
    }

    inline int32_t DAABBTree::get_height() const
    {
        if (m_root_id == nullnode)
            return 0;

        return m_nodes[m_root_id].height;
    }
} // namespace physics
