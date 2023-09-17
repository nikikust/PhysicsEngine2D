#pragma once
#include "../../Include/Utils/Functions.h"


class Material
{
public:
	Material(const sf::Color& color = sf::Color::White, float elasticity = 0.6, const std::string& name = "");

	sf::Color get_color      ();
	float     get_elasticity ();
	
	int32_t     get_id   ();
	std::string get_name ();

	void set_color      (const sf::Color& color);
	void set_elasticity (float elasticity);
	void set_name       (const std::string& name);

private:
	sf::Color color_;
	float elasticity_;

	// --- //

	int32_t id_;
	std::string name_;
	static int32_t max_material_id_;
};
