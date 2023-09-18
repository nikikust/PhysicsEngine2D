#include "../../Include/PhysicsEngine/Material.h"


namespace physics
{
	int32_t Material::max_material_id_ = 0;


	Material::Material(const sf::Color& color, float elasticity, const std::string& name)
		: color_(color), elasticity_(elasticity), name_(name)
	{
		id_ = ++max_material_id_;
	}

	// --- //

	sf::Color Material::get_color() const
	{
		return color_;
	}
	float Material::get_elasticity() const
	{
		return elasticity_;
	}

	int32_t Material::get_id() const
	{
		return id_;
	}
	std::string Material::get_name() const
	{
		return name_;
	}

	void Material::set_color(const sf::Color& color)
	{
		color_ = color;
	}
	void Material::set_elasticity(float elasticity)
	{
		elasticity_ = elasticity;
	}
	void Material::set_name(const std::string& name)
	{
		name_ = name;
	}
} // namespace physics