#include "../../Include/Modules/Painter.h"


Painter::Painter(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage),
      window_      (window)
{
    circle_brush.setOutlineThickness(0);
}
Painter::~Painter()
{

}


void Painter::draw_rectangle(std::shared_ptr<RectangleShape> rectangle)
{
    auto& materials = data_storage_.scene_data.materials;
    auto  color     = sf::Color::White;

    if (materials.contains(rectangle->get_material_id()))
        color = materials.at(rectangle->get_material_id())->get_color();
    
    // --- //

    rectangle_brush.setSize  (rectangle->get_size());
    rectangle_brush.setOrigin(rectangle->get_size() / 2.f);

    rectangle_brush.setPosition(rectangle->get_position());
    rectangle_brush.setRotation(rectangle->get_angle());

    rectangle_brush.setFillColor(color);

    window_.get_render_area().draw(rectangle_brush);

    rectangle->set_material_id(1);
}
void Painter::draw_circle(std::shared_ptr<CircleShape> circle)
{
    auto& materials = data_storage_.scene_data.materials;
    auto  color = sf::Color::White;

    if (materials.contains(circle->get_material_id()))
        color = materials.at(circle->get_material_id())->get_color();

    // --- //

    float radius = circle->get_radius();

    circle_brush.setRadius(radius);
    circle_brush.setOrigin(radius, radius);
    circle_brush.setPosition(circle->get_position());

    circle_brush.setFillColor(color);
    circle_brush.setOutlineColor(color);

    window_.get_render_area().draw(circle_brush);

    circle->set_material_id(1);
}
