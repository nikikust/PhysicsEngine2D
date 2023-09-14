#include "../../Include/Modules/Painter.h"


Painter::Painter(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage),
      window_      (window)
{
    point_brush.setPointCount(8);
}
Painter::~Painter()
{

}


void Painter::draw_point(sf::Vector2i position, float rad)
{
    point_brush.setPosition((float)position.x, (float)position.y);
    point_brush.setRadius(rad);
    point_brush.setOrigin(rad, rad);

    point_brush.setFillColor(brush_color);
    point_brush.setOutlineColor(sf::Color::White);
    point_brush.setOutlineThickness(1);

    window_.get_render_area().draw(point_brush);
}
void Painter::draw_line(sf::Vector2i A, sf::Vector2i B, float width)
{
    auto  diff = B - A;
    float lens = utils::pif(diff);
    float ang  = atan2((float)diff.y, (float)diff.x);

    A.x += lround(width / 2 * sin(ang));
    A.y -= lround(width / 2 * cos(ang));

    line_brush.setSize(sf::Vector2f(lens, width));
    line_brush.setPosition(sf::Vector2f((float)A.x, (float)A.y));
    line_brush.setRotation(float(ang / PI * 180.f));

    line_brush.setFillColor(brush_color);

    window_.get_render_area().draw(line_brush);
}

void Painter::set_color(sf::Color color)
{
    brush_color = color;
}
