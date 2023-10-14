#include <GameEngine/GUIEngine/Painter.h>
#include <GameEngine/GUIEngine/Window.h>
#include <GameEngine/DataCore/DataStorage.h>


namespace graphics
{
    Painter::Painter(graphics::Window& window, DataStorage& data_storage)
        : window_ (window), data_storage_(data_storage)
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
            polygon_brush.setPoint(cnt++, vertex * data_storage_.camera.scale_modifier);
        
        polygon_brush.setPosition(data_storage_.screen_size_halved + (position - data_storage_.camera.position ) * data_storage_.camera.scale_modifier);
        
        polygon_brush.setOutlineThickness(0.f);
        polygon_brush.setOutlineColor(color);
        polygon_brush.setFillColor(color);
        
        window_.get_render_area().draw(polygon_brush);
    }
    void Painter::draw_circle(const sf::Vector2f& position, float radius, float angle, const sf::Color& color, bool draw_rotation_line)
    {
        float scaled_radius  = radius * data_storage_.camera.scale_modifier;
        auto scaled_position = (position - data_storage_.camera.position) * data_storage_.camera.scale_modifier;

        circle_brush.setRadius(scaled_radius);
        circle_brush.setOrigin(scaled_radius, scaled_radius);
        circle_brush.setPosition(data_storage_.screen_size_halved + scaled_position);
        circle_brush.setRotation(angle * 180.f / (float)PI);

        circle_brush.setFillColor(color);
        circle_brush.setOutlineColor(color);

        window_.get_render_area().draw(circle_brush);

        if (draw_rotation_line)
        {
            circle_angle_brush.setPosition(data_storage_.screen_size_halved + scaled_position);
            circle_angle_brush.setSize({ scaled_radius, 2.f });
            circle_angle_brush.setRotation(angle * 180.f / (float)PI);

            window_.get_render_area().draw(circle_angle_brush);
        }
    }

    void Painter::draw_border(const sf::Vector2f& position, const std::vector<sf::Vector2f>& vertices, const sf::Color& color, float outline_thickness)
    {
        polygon_brush.setPointCount(vertices.size());

        int32_t cnt = 0;
        for (auto& vertex : vertices)
            polygon_brush.setPoint(cnt++, vertex * data_storage_.camera.scale_modifier);

        polygon_brush.setPosition(data_storage_.screen_size_halved + (position - data_storage_.camera.position) * data_storage_.camera.scale_modifier);

        polygon_brush.setOutlineThickness(outline_thickness);
        polygon_brush.setOutlineColor(color);
        polygon_brush.setFillColor({ 0, 0, 0, 0 });

        window_.get_render_area().draw(polygon_brush);
    }

#ifdef DEBUG
    void Painter::draw_debug(const std::vector<DebugDraw>& debug_entities)
    {
        for (auto& entity : debug_entities)
        {
            switch (entity.type)
            {
            case DebugDraw::Circle:  draw_circle  (entity.position, entity.radius, entity.angle, entity.color, false);                    break;
            case DebugDraw::Polygon: draw_polygon (entity.position, entity.vertices,             entity.color);                           break;
            case DebugDraw::Border:  draw_border  (entity.position, entity.vertices,             entity.color, entity.outline_thickness); break;
            default: break;
            }
        }
    }
#endif // DEBUG
    
} // namespace graphics
