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
    auto rectangle = std::static_pointer_cast<RectangleShape>(data_storage_.scene_data.shapes.at(1));
    auto circle_1  = std::static_pointer_cast<CircleShape>   (data_storage_.scene_data.shapes.at(2));
    auto circle_2  = std::static_pointer_cast<CircleShape>   (data_storage_.scene_data.shapes.at(3));

    rectangle->set_position(sf::Vector2f{ window_.get_cursor_position() });

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

            if (shape_A->get_shape() == ShapeType::Rectangle)
            {
                if (shape_B->get_shape() == ShapeType::Rectangle)
                    collision = rectangles_collision(shape_A, shape_B);
                else if (shape_B->get_shape() == ShapeType::Circle)
                    collision = rectangle_circle_collision(shape_A, shape_B);
            }
            else if(shape_A->get_shape() == ShapeType::Circle)
            {
                if (shape_B->get_shape() == ShapeType::Rectangle)
                    collision = rectangle_circle_collision(shape_B, shape_A);
                else if (shape_B->get_shape() == ShapeType::Circle)
                    collision = circles_collision(shape_A, shape_B);
            }

            if (collision)
            {
                shape_A->move(-collision->collision_normal * collision->depth / 2.f);
                shape_B->move( collision->collision_normal * collision->depth / 2.f);

                shape_A->set_material_id(2);
                shape_B->set_material_id(2);
            }
        }
    }
    /*
    bool collided = false;
    if (auto collision = rectangle_circle_collision(rectangle, circle_1))
    {
        rectangle->set_material_id(2);
        collided = true;

        circle_1 ->move( collision->collision_normal * collision->depth / 2.f);
        rectangle->move(-collision->collision_normal * collision->depth / 2.f);
    }

    if (auto collision = circles_collision(circle_2, circle_1))
    {
        circle_2->set_material_id(2);
        collided = true;

        circle_1->move( collision->collision_normal * collision->depth / 2.f);
        circle_2->move(-collision->collision_normal * collision->depth / 2.f);
    }

    // --- //

    if (collided)
        circle_1->set_material_id(2);
    
    */
}
