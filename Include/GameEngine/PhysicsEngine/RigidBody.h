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
        RigidBody& set_position             (const sf::Vector2f& position            );
        RigidBody& set_angle                (float               angle               );
        RigidBody& set_linear_speed         (const sf::Vector2f& linear_speed        );
        RigidBody& set_angular_speed        (float               angular_speed       );
        RigidBody& set_linear_acceleration  (const sf::Vector2f& linear_acceleration );
        RigidBody& set_angular_acceleration (float               angular_acceleration);
        RigidBody& set_force                (const sf::Vector2f& force               );

        RigidBody& set_linear_fixation  (bool x, bool y);
        RigidBody& set_angular_fixation (bool a);

        const sf::Vector2f& get_position             () const;
        float               get_angle                () const;
        const Transform&    get_transform            () const;
        const sf::Vector2f& get_linear_speed         () const;
        float               get_angular_speed        () const;
        const sf::Vector2f& get_linear_acceleration  () const;
        float               get_angular_acceleration () const;
        const sf::Vector2f& get_force                () const;

        float get_inv_mass() const;

        std::pair<bool, bool> get_linear_fixation  ();
        bool                  get_angular_fixation ();

        // --- Dynamics
        RigidBody& move       (const sf::Vector2f& delta);
        RigidBody& accelerate (const sf::Vector2f& delta);
        RigidBody& rotate     (float angle);
        RigidBody& spin       (float angle);

        // --- //
        void update(float delta_time, const sf::Vector2f& gravity);

        void update_AABB();
        void update_AABB(const sf::Vector2f offset);
        const ShapeAABB& get_AABB() const;

        // --- Shapes
        std::shared_ptr<physics::Fixture> add_shape (const physics::CircleShape&  circle );
        std::shared_ptr<physics::Fixture> add_shape (const physics::PolygonShape& polygon);

        std::shared_ptr<physics::Fixture> get_fixture    (uint32_t id) const;
        void                              remove_fixture (uint32_t id);

        

        const std::vector<std::shared_ptr<physics::Fixture>>& get_fixtures() const;

        // --- //
		int32_t get_id() const;

	private:
        void update_physical_data();
        void update_physical_data_append(physics::Fixture& fixture);
        void update_physical_data_remove(physics::Fixture& fixture);

        // --- Data
        Transform    transform_             = {};

        sf::Vector2f linear_speed_          = {};
        float        angular_speed_         = 0;

        sf::Vector2f linear_acceleration_   = {};
        float        angular_acceleration_  = 0;

        sf::Vector2f force_                 = {};

        PhysicalData physical_data_         = {};

        // --- Flags
        std::pair<bool, bool> fixed_linear_ = {}; // x and y
        bool                  fixed_angle_  = false;
		
        // --- Shapes
        std::vector<std::shared_ptr<physics::Fixture>> fixtures_;
        ShapeAABB aabb_;

        // --- //

        int32_t id_;

        static int32_t max_body_id_;
	};
} // namespace physics
