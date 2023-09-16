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


void Painter::draw_rectangle(std::shared_ptr<PolygonShape> polygon)
{
    auto& materials = data_storage_.scene_data.materials;
    auto  color     = sf::Color::White;
    auto  position  = polygon->get_position();

    if (materials.contains(polygon->get_material_id()))
        color = materials.at(polygon->get_material_id())->get_color();
    
    // --- //

    polygon_brush.setPointCount(polygon->get_vertices().size());

    int32_t cnt = 0;
    for (auto& vertex : polygon->get_vertices())
        polygon_brush.setPoint(cnt++, vertex + position);

    polygon_brush.setOrigin(position);

    polygon_brush.setPosition(position);
    polygon_brush.setRotation(polygon->get_angle() * 180.f / (float)PI);

    polygon_brush.setFillColor(color);

    window_.get_render_area().draw(polygon_brush);

    polygon->set_material_id(1);
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
