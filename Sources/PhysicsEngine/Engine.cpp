#include "../../Include/PhysicsEngine/Engine.h"


namespace physics
{
    int32_t Engine::steps_amount = 16;


    Engine::Engine(DataStorage& data_storage, graphics::Window& window)
        : data_storage_(data_storage), window_(window), collision_solver_(data_storage_)
    {
    }
    Engine::~Engine()
    {
    }

    void Engine::update()
    {
        for (int step_cnt = 0; step_cnt < steps_amount; ++step_cnt)
            step();
    }

    void Engine::step()
    {
        auto& shapes = data_storage_.scene_data.shapes;
        for (auto& shape_pair_A : shapes)
        {
            auto& shape_A = shape_pair_A.second;

            for (auto& shape_pair_B : shapes)
            {
                auto& shape_B = shape_pair_B.second;

                if (shape_A->get_id() >= shape_B->get_id())
                    continue;

                std::optional<CollisionInfo> collision = std::nullopt;

                switch (shape_A->get_shape()) {
                case ShapeType::Rectangle:
                    switch (shape_B->get_shape()) {
                    case ShapeType::Rectangle: collision = collision_solver_.polygons_collision(shape_A, shape_B); break;
                    case ShapeType::Circle:    collision = collision_solver_.polygon_circle_collision(shape_A, shape_B); break;
                    default: break;
                    } break;
                case ShapeType::Circle:
                    switch (shape_B->get_shape()) {
                    case ShapeType::Rectangle: collision = collision_solver_.circle_polygon_collision(shape_A, shape_B); break;
                    case ShapeType::Circle:    collision = collision_solver_.circles_collision(shape_A, shape_B); break;
                    default: break;
                    } break;
                default: break;
                }

                if (collision)
                {
                    collision_solver_.resolve_collision(*collision, shape_A, shape_B);
                }
            }

            shape_A->update(data_storage_.status.delta_time / 1000.f / steps_amount);

            shape_A->wrap_to_screen(window_.get_render_area().getSize()); // to keep object inside screen
        }
    }
} // namespace physics
