#pragma once
#include <GameEngine/PhysicsEngine/World.h>

#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


namespace physics
{
    class Engine
    {
    public:
        Engine();
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        ~Engine();

        // --- //

        void update(float delta_time, const sf::Vector2i& window_size);

        physics::RigidBody* get_body(int32_t id) const;
        physics::RigidBody* get_body(int32_t id, int32_t world_id) const;

        void add_body(physics::RigidBody* body);

        std::shared_ptr<World> get_world();

        void set_pause(bool flag);
        bool get_pause_state();
        void do_step();

#ifdef DEBUG
        const std::vector<graphics::DebugDraw>& get_debug_entities();
#endif // DEBUG

    private:
        void wrap_to_screen(RigidBody* body, const sf::Vector2i& window_size);


        std::shared_ptr<World> selected_world_{};

        // Config
        static int32_t steps_amount;

        bool paused_;
        bool do_step_;
    };
} // namespace physics
