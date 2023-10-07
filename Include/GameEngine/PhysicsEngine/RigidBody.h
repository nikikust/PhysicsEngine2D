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

        void set_active_fixture(uint32_t id, bool flag);

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
        std::vector<std::shared_ptr<physics::Fixture>> active_fixtures_;
        DAABBTree internal_tree_;

        RigidBodyNodeData* node_data_;

        // --- //

        int32_t id_;

        static int32_t max_body_id_;
	};

    using RigidBodyPtrPair = std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>;


    // Inline section
    inline RigidBody& RigidBody::set_position(const sf::Vector2f& position)
    {
        auto delta = position - transform_.position;

        transform_.position = position;

        update_internal_AABB(delta);

        return *this;
    }

    inline RigidBody& RigidBody::set_angle(float angle)
    {
        transform_.rotation.set_angle(angle);

        update_internal_AABB();

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_speed(const sf::Vector2f& linear_speed)
    {
        linear_speed_ = linear_speed;

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_speed(float angular_speed)
    {
        angular_speed_ = angular_speed;

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_acceleration(const sf::Vector2f& linear_acceleration)
    {
        linear_acceleration_ = linear_acceleration;

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_acceleration(float angular_acceleration)
    {
        angular_acceleration_ = angular_acceleration;

        return *this;
    }

    inline RigidBody& RigidBody::set_force(const sf::Vector2f& force)
    {
        force_ = force;

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_fixation(bool x, bool y)
    {
        fixed_linear_ = { x, y };

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_fixation(bool a)
    {
        fixed_angle_ = a;

        return *this;
    }

    inline const sf::Vector2f& RigidBody::get_position() const
    {
        return transform_.position;
    }

    inline float RigidBody::get_angle() const
    {
        return transform_.rotation.get_angle();
    }

    inline const Transform& RigidBody::get_transform() const
    {
        return transform_;
    }

    inline const sf::Vector2f& RigidBody::get_linear_speed() const
    {
        return linear_speed_;
    }

    inline float RigidBody::get_angular_speed() const
    {
        return angular_speed_;
    }

    inline const sf::Vector2f& RigidBody::get_linear_acceleration() const
    {
        return linear_acceleration_;
    }

    inline float RigidBody::get_angular_acceleration() const
    {
        return angular_acceleration_;
    }

    inline const sf::Vector2f& RigidBody::get_force() const
    {
        return force_;
    }

    inline float RigidBody::get_inv_mass() const
    {
        return physical_data_.inv_mass;
    }

    inline float RigidBody::get_inv_mmoi() const
    {
        return physical_data_.inv_mmoi;
    }

    inline std::pair<bool, bool> RigidBody::get_linear_fixation()
    {
        return fixed_linear_;
    }

    inline bool RigidBody::get_angular_fixation()
    {
        return fixed_angle_;
    }

    inline RigidBody& RigidBody::move(const sf::Vector2f& delta)
    {
        transform_.position += delta;

        //update_internal_AABB(delta);

        return *this;
    }

    inline RigidBody& RigidBody::accelerate(const sf::Vector2f& delta)
    {
        linear_speed_ += delta;

        return *this;
    }

    inline RigidBody& RigidBody::rotate(float angle)
    {
        transform_.rotation.rotate(angle);

        update_internal_AABB();

        return *this;
    }

    inline RigidBody& RigidBody::spin(float angle)
    {
        angular_speed_ += angle;

        return *this;
    }

    inline ShapeAABB RigidBody::get_AABB() const
    {
        return internal_tree_.get_root_AABB();
    }

    inline RigidBodyNodeData* RigidBody::get_node_data() const
    {
        return node_data_;
    }

    inline void RigidBody::set_node_data(RigidBodyNodeData* data)
    {
        node_data_ = data;
    }

    inline std::shared_ptr<physics::Fixture> RigidBody::get_fixture(uint32_t id) const
    {
        for (auto& fixture : fixtures_)
            if (fixture->get_id() == id)
                return fixture;

        return nullptr;
    }

    inline const std::vector<std::shared_ptr<physics::Fixture>>& RigidBody::get_fixtures() const
    {
        return fixtures_;
    }

    inline const DAABBTree& RigidBody::get_tree() const
    {
        return internal_tree_;
    }

    inline int32_t RigidBody::get_id() const
    {
        return id_;
    }

} // namespace physics
