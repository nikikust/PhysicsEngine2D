#include "../../Include/Modules/Renderer.h"


Renderer::Renderer(DataStorage& data_storage, DataLoader& data_loader, Window& window)
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
        case ShapeType::Rectangle: painter_.draw_rectangle(std::static_pointer_cast<RectangleShape>(shape)); break;
        case ShapeType::Circle:    painter_.draw_circle   (std::static_pointer_cast<CircleShape>   (shape)); break;
        default: break;
        }
    }
}
