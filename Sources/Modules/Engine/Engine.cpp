#include "../../../Include/Modules/Engine/Engine.h"


Engine::Engine(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage), window_(window)
{
}
Engine::~Engine()
{
}

void Engine::update()
{
    auto rectangle_1 = std::static_pointer_cast<PolygonShape>(data_storage_.scene_data.shapes.at(1));
    auto circle_1    = std::static_pointer_cast<CircleShape> (data_storage_.scene_data.shapes.at(2));
    auto circle_2    = std::static_pointer_cast<CircleShape> (data_storage_.scene_data.shapes.at(3));
    auto rectangle_2 = std::static_pointer_cast<PolygonShape>(data_storage_.scene_data.shapes.at(4));

    rectangle_1->set_position(sf::Vector2f{ window_.get_cursor_position() });

    // rectangle_1->rotate( (float)PI / 1000);
    // rectangle_2->rotate(-(float)PI / 2000);

    // --- //

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
                case ShapeType::Rectangle: collision = polygons_collision       (shape_A, shape_B); break;
                case ShapeType::Circle:    collision = polygon_circle_collision (shape_A, shape_B); break;
                default: break; } break;
            case ShapeType::Circle:
                switch (shape_B->get_shape()) {
                case ShapeType::Rectangle: collision = circle_polygon_collision (shape_A, shape_B); break;
                case ShapeType::Circle:    collision = circles_collision        (shape_A, shape_B); break;
                default: break; } break;
            default: break; }

            if (collision)
            {
                shape_A->move(-collision->collision_normal * collision->depth / 2.f);
                shape_B->move( collision->collision_normal * collision->depth / 2.f);

                shape_A->set_material_id(2);
                shape_B->set_material_id(2);
            }
        }
    }
}
