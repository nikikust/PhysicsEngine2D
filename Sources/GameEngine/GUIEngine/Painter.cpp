#include <GameEngine/GUIEngine/Painter.h>
#include <GameEngine/GUIEngine/Window.h>


namespace graphics
{
    Painter::Painter(graphics::Window& window)
        : window_ (window)
    {
        circle_brush.setOutlineThickness(0.f);
        circle_angle_brush.setOrigin({ 0.f, 1.f });
        circle_angle_brush.setFillColor(sf::Color::White);
    }
    Painter::~Painter()
    {
    }


    void Painter::draw_polygon(const sf::Vector2f& position, const std::vector<sf::Vector2f>& vertices, const sf::Color& color)
    {
        polygon_brush.setPointCount(vertices.size());
        
        int32_t cnt = 0;
        for (auto& vertex : vertices)
            polygon_brush.setPoint(cnt++, vertex);
        
        polygon_brush.setPosition(position);
        
        polygon_brush.setFillColor(color);
        
        window_.get_render_area().draw(polygon_brush);
    }
    void Painter::draw_circle(const sf::Vector2f& position, float radius, float angle, const sf::Color& color)
    {
        circle_brush.setRadius(radius);
        circle_brush.setOrigin(radius, radius);
        circle_brush.setPosition(position);
        circle_brush.setRotation(angle * 180.f / (float)PI);
        
        circle_brush.setFillColor(color);
        circle_brush.setOutlineColor(color);
        
        circle_angle_brush.setPosition(position);
        circle_angle_brush.setSize({ radius, 2.f });
        circle_angle_brush.setRotation(angle * 180.f / (float)PI);

        window_.get_render_area().draw(circle_brush);
        window_.get_render_area().draw(circle_angle_brush);
    }
    
} // namespace graphics
