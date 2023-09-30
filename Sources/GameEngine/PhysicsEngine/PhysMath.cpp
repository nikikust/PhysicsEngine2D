#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
	sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform)
	{
		auto shifted_point = point - transform.centroid;

		return transform.centroid + sf::Vector2f{
			shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
			shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
		};
	}

	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform)
	{
		auto shifted_point = point - transform.centroid;

		return transform.position + transform.centroid + sf::Vector2f {
			shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
			shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
		};
	}

	std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, float angle)
	{
		std::vector<sf::Vector2f> rotated_vertices = vertices;

		for (auto& vertex : rotated_vertices)
			vertex = utils::rotate_point(vertex + offset, angle);

		return rotated_vertices;
	}

	std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, const Transform& transform)
	{
		std::vector<sf::Vector2f> rotated_vertices = vertices;

		for (auto& vertex : rotated_vertices)
			vertex = physics::rotate_point(vertex + offset, transform);

		return rotated_vertices;
	}

	float triangle_area(const sf::Vector2f& A, const sf::Vector2f& B)
	{
		return utils::cross(A, B) / 2.f;
	}

	sf::Vector2f triangle_center(const sf::Vector2f& A, const sf::Vector2f& B)
	{
		return (A + B) / 3.f;
	}

	float triangle_mmoi(const sf::Vector2f& A, const sf::Vector2f& B, float triangle_mass)
	{
		return triangle_mass / 6.f * (utils::dot(A, A) + utils::dot(B, B) + utils::dot(A, B));
	}

	std::pair<float, sf::Vector2f> point_segment_distance_squared(const sf::Vector2f& p, const sf::Vector2f& A, const sf::Vector2f& B)
	{
		sf::Vector2f AB = B - A;
		sf::Vector2f Ap = p - A;

		float proj = utils::dot(Ap, AB);
		float AB_length_sqr = utils::length_squared(AB);
		float d = proj / AB_length_sqr;

		if (d <= 0.f)
			return { utils::distance_squared(p, A), A};
		else if (d >= 1.f)
			return { utils::distance_squared(p, B), B};
		else
			return { utils::distance_squared(p, A + AB * d), A + AB * d };
	}
	
	bool almost_equal(float A, float B, float precision)
	{
		return fabsf(B - A) < precision;
	}
	
	bool almost_equal(const sf::Vector2f& A, const sf::Vector2f& B, float precision)
	{
		return almost_equal(A.x, B.x) && almost_equal(A.y, B.y);
	}

	bool operator==(const Transform& left, const Transform& right)
	{
		return 
			physics::almost_equal(left.position,             right.position            ) &&
			physics::almost_equal(left.rotation.get_angle(), right.rotation.get_angle()) &&
			physics::almost_equal(left.centroid,             right.centroid            );
	}
	bool operator!=(const Transform& left, const Transform& right)
	{
		return 
			!physics::almost_equal(left.position,             right.position            ) ||
			!physics::almost_equal(left.rotation.get_angle(), right.rotation.get_angle()) ||
			!physics::almost_equal(left.centroid,             right.centroid            );
	}
	Transform& Transform::operator=(const Transform& b)
	{
		this->position = b.position;
		this->centroid = b.centroid;

		this->rotation.set_angle(b.rotation.get_angle());

		return *this;
	}
} // namespace physics
