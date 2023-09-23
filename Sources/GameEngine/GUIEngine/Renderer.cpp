#include <GameEngine/GUIEngine/Renderer.h>


namespace graphics
{
    Renderer::Renderer(DataStorage& data_storage, DataLoader& data_loader, graphics::Window& window)
        : data_storage_(data_storage),
          data_loader_ (data_loader),
          window_      (window),
          painter_     (window)
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
    }
} // namespace graphics
