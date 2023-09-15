#include "../../../Include/Modules/Engine/Engine.h"


Engine::Engine(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage), window_(window)
{
}
Engine::~Engine()
{
}

void Engine::update()
{
    auto& circle = data_storage_.scene_objects.shapes.at(2);

    circle->set_position(sf::Vector2f{ window_.get_cursor_position() });
}
