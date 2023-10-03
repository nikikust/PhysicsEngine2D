#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>
#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>
#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>


namespace physics
{
    class RigidBody;

    struct RigidBodyNodeData
    {
        RigidBodyNodeData(std::shared_ptr<RigidBody> body_in, const ShapeAABB& aabb_in, int32_t id_in);

        std::weak_ptr<RigidBody> body;
        int32_t id;

        ShapeAABB aabb;
        int32_t node_id;
    };

	class RigidBody
	{
	public:
		RigidBody();
        RigidBody(RigidBody&) = delete;
        RigidBody(RigidBody&&) noexcept;
        ~RigidBody();

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
        float get_inv_mmoi() const;

        std::pair<bool, bool> get_linear_fixation  ();
        bool                  get_angular_fixation ();

        // --- Dynamics
        RigidBody& move       (const sf::Vector2f& delta);
        RigidBody& accelerate (const sf::Vector2f& delta);
        RigidBody& rotate     (float angle);
        RigidBody& spin       (float angle);

        // --- //
        void update(float delta_time, const sf::Vector2f& gravity);

        void update_internal_AABB();
        void update_internal_AABB(const sf::Vector2f offset);

        ShapeAABB get_AABB() const;

        RigidBodyNodeData* get_node_data() const;
        void set_node_data(RigidBodyNodeData* data);

        // --- Shapes
        std::shared_ptr<physics::Fixture> add_shape (const physics::CircleShape&  circle );
        std::shared_ptr<physics::Fixture> add_shape (const physics::PolygonShape& polygon);

        std::shared_ptr<physics::Fixture> get_fixture    (uint32_t id) const;
        void                              remove_fixture (uint32_t id);

        const std::vector<std::shared_ptr<physics::Fixture>>& get_fixtures() const;

        const DAABBTree& get_tree() const;

        // --- //
		int32_t get_id() const;

	private:
        void update_physical_data();
        void update_physical_data_append(std::shared_ptr<physics::Fixture> fixture);
        void update_physical_data_remove(std::shared_ptr<physics::Fixture> fixture);

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
        DAABBTree internal_tree_;

        RigidBodyNodeData* node_data_;

        // --- //

        int32_t id_;

        static int32_t max_body_id_;
	};

    using RigidBodyPtrPair = std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>;
} // namespace physics
