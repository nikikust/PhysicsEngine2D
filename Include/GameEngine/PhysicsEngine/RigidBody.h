#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>
#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>


namespace physics
{
	class RigidBody
	{
	public:
		RigidBody();


        // --- Physics
        RigidBody& set_transform            (const Transform&    transform           );
        RigidBody& set_mass                 (float               mass                );
        RigidBody& set_linear_speed         (const sf::Vector2f& linear_speed        );
        RigidBody& set_angular_speed        (float               angular_speed       );
        RigidBody& set_linear_acceleration  (const sf::Vector2f& linear_acceleration );
        RigidBody& set_angular_acceleration (float               angular_acceleration);
        RigidBody& set_force                (const sf::Vector2f& force               );

        RigidBody& set_linear_fixation  (bool x, bool y);
        RigidBody& set_angular_fixation (bool a);

        const Transform&    get_transform            () const;
        float               get_mass                 () const;
        const sf::Vector2f& get_linear_speed         () const;
        float               get_angular_speed        () const;
        const sf::Vector2f& get_linear_acceleration  () const;
        float               get_angular_acceleration () const;
        const sf::Vector2f& get_force                () const;

        std::pair<bool, bool> get_linear_fixation  ();
        bool                  get_angular_fixation ();

        // --- Dynamics
        RigidBody& move       (const sf::Vector2f& delta);
        RigidBody& accelerate (const sf::Vector2f& delta);
        RigidBody& rotate     (float angle);
        RigidBody& spin       (float angle);
        
        sf::Vector2f get_center_of_mass   () const;
        float        get_moment_of_inertia() const;

        // --- //
        void update(float delta_time, const sf::Vector2f& gravity);
        void wrap_to_screen(const sf::Vector2u& window_size);

        // --- Shapes
        std::shared_ptr<physics::Fixture> add_shape (const physics::CircleShape&  circle );
        std::shared_ptr<physics::Fixture> add_shape (const physics::PolygonShape& polygon);

        std::shared_ptr<physics::Fixture> get_fixture    (uint32_t id) const;
        void                              remove_fixture (uint32_t id);

        const std::vector<std::shared_ptr<physics::Fixture>>& get_fixtures() const;

        // --- //
		int32_t get_id() const;

	private:
        // --- Data
        physics::Transform transform_;

        sf::Vector2f linear_speed_          = {};
        float        angular_speed_         = 0;

        sf::Vector2f linear_acceleration_   = {};
        float        angular_acceleration_  = 0;

        sf::Vector2f force_                 = {};

        float        mass_                  = 1;

        // --- Calculated values
        float        moment_of_inertia_     = 1;

        // --- Flags
        std::pair<bool, bool> fixed_linear_ = {}; // x and y
        bool                  fixed_angle_  = false;
		
        // --- Shapes
        std::vector<std::shared_ptr<physics::Fixture>> fixtures_;

        // --- //

        int32_t id_;

        static int32_t max_body_id_;
	};
} // namespace physics
