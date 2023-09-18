#pragma once
#include "../../Include/Utils/Functions.h"


namespace physics
{
	class Material
	{
	public:
		Material(const sf::Color& color = sf::Color::White, float elasticity = 0.6, const std::string& name = "");

		sf::Color get_color      () const;
		float     get_elasticity () const;

		int32_t     get_id   () const;
		std::string get_name () const;

		void set_color      (const sf::Color&   color     );
		void set_elasticity (float              elasticity);
		void set_name       (const std::string& name      );

	private:
		sf::Color color_;
		float     elasticity_;

		// --- //

		static int32_t max_material_id_;

		int32_t id_;
		std::string name_;
	};
} // namespace physics
