namespace physics
{
    inline Vector operator+(const Vector& left)
    {
        Vector out{ left.x, left.y };

        return out;
    }
    inline Vector operator-(const Vector& left)
    {
        Vector out{ -left.x, -left.y };

        return out;
    }

    inline Vector operator+(const Vector& left, float right)
    {
        Vector out{ left };

        out.x += right;
        out.y += right;

        return out;
    }
    inline Vector operator-(const Vector& left, float right)
    {
        Vector out{ left };

        out.x -= right;
        out.y -= right;

        return out;
    }
    inline Vector operator*(const Vector& left, float right)
    {
        Vector out{ left };

        out.x *= right;
        out.y *= right;

        return out;
    }
    inline Vector operator/(const Vector& left, float right)
    {
        Vector out{ left };

        out.x /= right;
        out.y /= right;

        return out;
    }

    inline Vector operator+(float left, const Vector& right)
    {
        Vector out{ right };

        out.x += left;
        out.y += left;

        return out;
    }
    inline Vector operator*(float left, const Vector& right)
    {
        Vector out{ right };

        out.x *= left;
        out.y *= left;

        return out;
    }

    inline Vector operator+(const Vector& left, const Vector& right)
    {
        Vector out{ left };

        out.x += right.x;
        out.y += right.y;

        return out;
    }
    inline Vector operator-(const Vector& left, const Vector& right)
    {
        Vector out{ left };

        out.x -= right.x;
        out.y -= right.y;

        return out;
    }

    inline Vector& operator+=(Vector& left, float right)
    {
        left.x += right;
        left.y += right;

        return left;
    }
    inline Vector& operator-=(Vector& left, float right)
    {
        left.x -= right;
        left.y -= right;

        return left;
    }

    inline Vector& operator+=(Vector& left, const Vector& right)
    {
        left.x += right.x;
        left.y += right.y;

        return left;
    }
    inline Vector& operator-=(Vector& left, const Vector& right)
    {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    inline Vector min(const Vector& A, const Vector& B)
    {
        return { fminf(A.x, B.x), fminf(A.y, B.y) };
    }
    inline Vector max(const Vector& A, const Vector& B)
    {
        return { fmaxf(A.x, B.x), fmaxf(A.y, B.y) };
    }

    inline Vector abs(const Vector& X)
    {
        return Vector(fabsf(X.x), fabsf(X.y));
    }

    inline bool inf(float a, float num, float b)
    {
        return (num >= a && num <= b);
    }

    template<typename T>
    inline void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    inline float length(const Vector& x)
    {
        return sqrtf(x.x * x.x + x.y * x.y);
    }
    inline float distance(const Vector& A, const Vector& B)
    {
        Vector diff = B - A;

        return sqrtf(diff.x * diff.x + diff.y * diff.y);
    }

    inline float length_squared(const Vector& x)
    {
        return x.x * x.x + x.y * x.y;
    }
    inline float distance_squared(const Vector& A, const Vector& B)
    {
        Vector diff = B - A;

        return diff.x * diff.x + diff.y * diff.y;
    }

    inline Vector normalize(const Vector& vector)
    {
        auto length = physics::length(vector);

        if (length == 0.f)
            return { 1.f, 0.f };

        return vector / length;
    }

    inline float dot(const Vector& A, const Vector& B)
    {
        return A.x * B.x + A.y * B.y;
    }
    inline float cross(const Vector& A, const Vector& B)
    {
        return A.x * B.y - B.x * A.y;
    }

    inline Vector rotate_point(const Vector& point, float angle)
    {
        return {
            point.x * cosf(angle) - point.y * sinf(angle),
            point.x * sinf(angle) + point.y * cosf(angle)
        };
    }

    inline std::vector<Vector> rotate_polygon(const std::vector<Vector>& vertices, const Vector& offset, float angle)
    {
        std::vector<Vector> rotated_vertices = vertices;

        for (auto& vertex : rotated_vertices)
            vertex = rotate_point(vertex + offset, angle);

        return rotated_vertices;
    }

    inline std::vector<Vector> rotate_polygon(const std::vector<Vector>& vertices, const Vector& offset, const Transform& transform)
    {
        std::vector<Vector> rotated_vertices = vertices;

        for (auto& vertex : rotated_vertices)
            vertex = physics::rotate_point(vertex + offset, transform);

        return rotated_vertices;
    }


    /// @brief Rotate point around centroid provided in transform
    inline Vector rotate_point(const Vector& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.centroid + Vector{
            shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
            shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    /// @brief Inverse rotate point around centroid provided in transform
    inline Vector rotate_point_T(const Vector& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.centroid + Vector{
             shifted_point.x * transform.rotation.get_cos() + shifted_point.y * transform.rotation.get_sin(),
            -shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    /// @brief Rotate point by matrix constructed from provided rotation
    inline Vector rotate_point(const Vector& point, const Rotation& rotation)
    {
        return Vector{
            point.x * rotation.get_cos() - point.y * rotation.get_sin(),
            point.x * rotation.get_sin() + point.y * rotation.get_cos()
        };
    }


    /// @brief Inverse rotate point by matrix constructed from provided rotation
    inline Vector rotate_point_T(const Vector& point, const Rotation& rotation)
    {
        return Vector{
             point.x * rotation.get_cos() + point.y * rotation.get_sin(),
            -point.x * rotation.get_sin() + point.y * rotation.get_cos()
        };
    }


    /// @brief Rotate point around centroid provided in transform and shift it
    inline Vector rotate_and_move_point(const Vector& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.position + transform.centroid + Vector{
            shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
            shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    inline float triangle_area(const Vector& A, const Vector& B)
    {
        return cross(A, B) / 2.f;
    }

    inline Vector triangle_center(const Vector& A, const Vector& B)
    {
        return (A + B) / 3.f;
    }

    inline float triangle_mmoi(const Vector& A, const Vector& B, float triangle_mass)
    {
        return triangle_mass / 6.f * (dot(A, A) + dot(B, B) + dot(A, B));
    }

    inline std::pair<float, Vector> point_segment_distance_squared(const Vector& p, const Vector& A, const Vector& B)
    {
        Vector AB = B - A;
        Vector Ap = p - A;

        float proj = dot(Ap, AB);
        float AB_length_sqr = length_squared(AB);
        float d = proj / AB_length_sqr;

        if (d <= 0.f)
            return { distance_squared(p, A), A };
        else if (d >= 1.f)
            return { distance_squared(p, B), B };
        else
            return { distance_squared(p, A + AB * d), A + AB * d };
    }

    inline bool almost_equal(float A, float B, float precision)
    {
        return fabsf(B - A) < precision;
    }

    inline bool almost_equal(const Vector& A, const Vector& B, float precision)
    {
        return almost_equal(A.x, B.x) && almost_equal(A.y, B.y);
    }
} // namespace physics
