#include "../../Include/GUIEngine/Renderer.h"


namespace graphics
{
    Renderer::Renderer(DataStorage& data_storage, DataLoader& data_loader, graphics::Window& window)
        : data_storage_(data_storage),
          data_loader_ (data_loader),
          window_      (window),
          painter_     (data_storage_, window)
    {

    }
    Renderer::~Renderer()
    {

    }


    void Renderer::update()
    {
    
    }

    void Renderer::draw()
    {
        auto& shapes = data_storage_.scene_data.shapes;

        for (auto& shape_pair : shapes)
        {
            auto& shape = shape_pair.second;

            switch (shape->get_shape())
            {
            case physics::ShapeType::Rectangle: painter_.draw_polygon(std::static_pointer_cast<physics::PolygonShape>(shape)); break;
            case physics::ShapeType::Circle:    painter_.draw_circle (std::static_pointer_cast<physics::CircleShape> (shape)); break;
            default: break;
            }
        }
    }
} // namespace graphics
