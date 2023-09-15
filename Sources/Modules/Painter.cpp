#include "../../Include/Modules/Painter.h"


Painter::Painter(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage),
      window_      (window)
{
}
Painter::~Painter()
{

}


void Painter::draw_rectangle(std::shared_ptr<RectangleShape> rectangle)
{
    rectangle_brush.setSize  (rectangle->get_size());
    rectangle_brush.setOrigin(rectangle->get_size() / 2.f);

    rectangle_brush.setPosition(rectangle->get_position());
    rectangle_brush.setRotation(rectangle->get_angle());

    window_.get_render_area().draw(rectangle_brush);
}
void Painter::draw_circle(std::shared_ptr<CircleShape> circle)
{
    float radius = circle->get_radius();

    circle_brush.setRadius(radius);
    circle_brush.setOrigin(radius, radius);
    circle_brush.setPosition(circle->get_position());

    window_.get_render_area().draw(circle_brush);
}

void Painter::set_color(sf::Color color)
{
    brush_color = color;

    rectangle_brush.setFillColor(brush_color);

    circle_brush.setFillColor(brush_color);
    circle_brush.setOutlineColor(brush_color);
    circle_brush.setOutlineThickness(1);
}
