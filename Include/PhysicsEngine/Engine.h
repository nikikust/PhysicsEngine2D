#pragma once
#include "../../Include/DataCore/DataStorage.h"
#include "../../Include/GUIEngine/Window.h"

#include "CollisionSolver.h"

namespace physics
{
    class Engine
    {
    public:
        Engine(DataStorage& data_storage, graphics::Window& window);
        Engine() = delete;
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        ~Engine();

        // --- //

        void update();

        void add_circle   (const physics::CircleShape&  circle );
        void add_polygon  (const physics::PolygonShape& polygon);
        void add_material (const physics::Material&     material);

        std::shared_ptr<physics::Shape>    get_shape    (uint32_t id);
        std::shared_ptr<physics::Material> get_material (uint32_t id);

        const std::unordered_map<int32_t, std::shared_ptr<physics::Shape>>& get_shapes() const;

    private:
        void step();


        DataStorage& data_storage_;

        graphics::Window& window_;

        CollisionSolver collision_solver_;

        // Data
        struct SceneData
        {
            std::unordered_map<int32_t, std::shared_ptr<physics::Shape>>    shapes{};
            std::unordered_map<int32_t, std::shared_ptr<physics::Material>> materials{};
        } scene_data_;
        
        // Config
        static int32_t steps_amount;
    };
} // namespace physics
