#include <GameEngine/GUIEngine/Renderer.h>


namespace graphics
{
    Renderer::Renderer(DataStorage& data_storage, DataLoader& data_loader, graphics::Window& window)
        : data_storage_(data_storage),
          data_loader_ (data_loader),
          window_      (window),
          painter_     (window, data_storage)
    {
    }
    Renderer::~Renderer()
    {
    }


    void Renderer::update()
    {
        // auto& body = std::dynamic_pointer_cast<game::ComplexEntity>(data_storage_.entities_storage.get_entity(1))->get_body();
        // 
        // body->set_transform({ sf::Vector2f{window_.get_cursor_position() }, body->get_transform().angle });
    }

    void Renderer::draw()
    {
        auto& entities = data_storage_.entities_storage.get_entities();
        
        for (auto& [k, entity] : entities)
            entity->render(painter_);

        auto& ray_cast_data = data_storage_.status.ray_cast_section;

        painter_.draw_line(ray_cast_data.origin, ray_cast_data.target, sf::Color::White, 2);

        if (ray_cast_data.is_hit)
        {
            painter_.draw_circle(ray_cast_data.target, 4.f, 0.f, sf::Color::Yellow, false);

            painter_.draw_line(ray_cast_data.target, ray_cast_data.target + ray_cast_data.normal * 25.f, sf::Color::White, 2);
        }
    }

#ifdef DEBUG
    void Renderer::draw_debug(const std::vector<DebugDraw>& debug_entities)
    {
        painter_.draw_debug(debug_entities);
    }
#endif // DEBUG
} // namespace graphics
