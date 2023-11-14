namespace physics
{
    inline void PolygonShape::set_vertices(const std::vector<Vector>& vertices)
    {
        vertices_ = vertices;

        // Precalculate normals
        normals_.clear();

        int32_t count = (int32_t)vertices_.size();
        for (int32_t i = 0; i < count; ++i)
        {
            int32_t i_and_one = (i + 1 == count) ? 0 : i + 1;

            const auto& point_A = vertices_.at(i);
            const auto& point_B = vertices_.at(i_and_one);

            const auto edge = point_B - point_A;
            const auto axis = physics::normalize(Vector(edge.y, -edge.x));

            normals_.push_back(axis);
        }
    }

    inline const std::vector<Vector>& PolygonShape::get_vertices() const
    {
        return vertices_;
    }

    inline const std::vector<Vector>& PolygonShape::get_normals() const
    {
        return normals_;
    }
} // namespace physics
