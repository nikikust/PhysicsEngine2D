namespace utils
{
    inline sf::Vector2f convert_to_sf(const physics::Vector& right)
    {
        return sf::Vector2f(right.x, right.y);
    }
    inline physics::Vector convert_to_phys(const sf::Vector2f& right)
    {
        return physics::Vector(right.x, right.y);
    }

    inline std::vector<sf::Vector2f> convert_to_sf(const std::vector<physics::Vector>& right)
    {
        std::vector<sf::Vector2f> vec;
        vec.reserve(right.size());

        for (const auto& vertex : right)
            vec.push_back(utils::convert_to_sf(vertex));

        return vec;
    }

    inline sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fminf(A.x, B.x), fminf(A.y, B.y) };
    }
    inline sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fmaxf(A.x, B.x), fmaxf(A.y, B.y) };
    }

    inline sf::Vector2f abs(const sf::Vector2f& X)
    {
        return sf::Vector2f(fabsf(X.x), fabsf(X.y));
    }

    inline float length(const sf::Vector2f& x)
    {
        return sqrt(x.x * x.x + x.y * x.y);
    }
} // namespace utils
