#include <GameEngine/DataCore/DataEditor.h>


DataEditor::DataEditor(DataStorage& data_storage, graphics::Window& window, physics::Engine& engine)
    : data_storage_(data_storage),
      window_      (window),
      engine_      (engine)
{

}

DataEditor::~DataEditor()
{

}

// --- //

void DataEditor::save_mouse_position_on_click()
{
    data_storage_.status.mouse_position_on_click = window_.get_cursor_position();
}
bool DataEditor::mouse_kept_position()
{
    return data_storage_.status.mouse_position_on_click == window_.get_cursor_position();
}

sf::Vector2f DataEditor::get_world_mouse_position()
{
    return (window_.get_cursor_position() - data_storage_.screen_size_halved) / data_storage_.camera.scale_modifier +
        data_storage_.camera.position;
}

void DataEditor::save_camera_position()
{
    data_storage_.status.camera_position_on_click = data_storage_.camera.position;
}
void DataEditor::restore_camera_position()
{
    data_storage_.camera.position = data_storage_.status.camera_position_on_click;

    data_storage_.status.movement_mode = DataStorage::Status::MovementMode::IDLE;
}
void DataEditor::start_moving_camera()
{
    save_camera_position();

    data_storage_.status.movement_mode = DataStorage::Status::MovementMode::MovingCamera;
}
void DataEditor::stop_moving_camera()
{
    data_storage_.status.movement_mode = DataStorage::Status::MovementMode::IDLE;
}
void DataEditor::move_camera(sf::Vector2f delta)
{
    data_storage_.camera.position = data_storage_.status.camera_position_on_click - delta;
}

bool DataEditor::mouse_io_is_released()
{
    return !data_storage_.status.mouse_captured;
}
bool DataEditor::keyboard_io_is_released()
{
    return !data_storage_.status.keyboard_captured;
}

bool DataEditor::is_idle_mode()
{
    return data_storage_.status.movement_mode == DataStorage::Status::MovementMode::IDLE;
}
bool DataEditor::is_camera_moving_mode()
{
    return data_storage_.status.movement_mode == DataStorage::Status::MovementMode::MovingCamera;
}

void DataEditor::create_message(const std::string& message, int timeout)
{
    data_storage_.menus.CursorMessage = true;
    data_storage_.menus.fields.cursor_message.elapse_at = time(0) + timeout;
    data_storage_.menus.fields.cursor_message.message = message;
}
bool DataEditor::message_is_opened()
{
    return data_storage_.menus.CursorMessage == true;
}
void DataEditor::close_message()
{
    data_storage_.menus.fields.cursor_message.elapse_at = time(0);
}

void DataEditor::zoom(float delta)
{
    if (data_storage_.camera.scale_modifier < 0.0001f && delta < 1.f)
        return;

    data_storage_.camera.scale_modifier *= delta;
}

void DataEditor::screenshot_with_interface()
{
    data_storage_.status.make_screenshot         = true;
    data_storage_.status.screenshot_frames_delay = 0;
}
void DataEditor::screenshot_without_interface()
{
    data_storage_.status.make_screenshot         = true;
    data_storage_.status.screenshot_frames_delay = 2;
}
void DataEditor::check_screenshot_status()
{
    if (data_storage_.status.make_screenshot == false)
        return;

    if (data_storage_.status.screenshot_frames_delay > 0)
    {
        data_storage_.status.screenshot_frames_delay--;

        return;
    }

    make_screenshot();

    data_storage_.status.make_screenshot = false;
}
void DataEditor::make_screenshot()
{
    bool result;
    auto& render_window = window_.get_render_area();

    sf::Texture texture;
    result = texture.create(render_window.getSize().x, render_window.getSize().y);
    texture.update(render_window);

    result = texture.copyToImage().saveToFile("Data/screenshots/" + utils::get_time_string() + ".png");
}

void DataEditor::flip_exit_popup_state()
{
    data_storage_.menus.ConfirmExit.should_be_open = !data_storage_.menus.ConfirmExit.is_open;
}

void DataEditor::load_scene(int32_t id)
{
    auto  world   = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    storage.clear();
    world->clear();

    engine_.set_pause(true);

    switch (id)
    {
    case 1: load_scene_1(); break;
    case 2: load_scene_2(); break;
    case 3: load_scene_3(); break;
    case 4: load_scene_4(); break;
    default:                break;
    }

    data_storage_.status.paused = engine_.get_pause_state();
}

void DataEditor::create_entity(const sf::Vector2f& position)
{
    auto  world   = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    auto entity = std::make_shared<game::PolygonEntity>(world, position, 0.f);

    storage.add_entity(entity);

    storage.select_entity(entity);
}

void DataEditor::load_scene_1()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    auto complex_1 = std::make_shared<game::ComplexEntity>(world, sf::Vector2f{  250,  500 }, 0.f);
    auto polygon_1 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{ -150,  100 }, 0.f);
    auto circle_1  = std::make_shared<game::CircleEntity >(world, sf::Vector2f{  150,  100 }, 0.f);
    auto circle_2  = std::make_shared<game::CircleEntity >(world, sf::Vector2f{ -150,  300 }, 0.f);
    auto polygon_2 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{  150,  300 }, 0.f);

    storage.add_entity(complex_1);
    storage.add_entity(polygon_1);
    storage.add_entity(circle_1 );
    storage.add_entity(circle_2 );
    storage.add_entity(polygon_2);

    storage.select_entity(complex_1);
}

void DataEditor::load_scene_2()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    world->set_gravity({ 0.f, 980.f });

    std::shared_ptr<game::Entity> entity;

    for (int32_t i = 0; i < 2; ++i)
    {
        auto ship = std::make_shared<game::ShipEntity>(world, sf::Vector2f{ -500.f + i * 1050.f, 10.f }, 0.f, 75, 75);

        if (entity == nullptr)
            entity = ship;
        
        storage.add_entity(ship);
    }

    auto ground_1 = std::make_shared<game::GroundEntity>(world, sf::Vector2f{ 0, 1200 }, 0.f);

    storage.add_entity(ground_1);

    storage.select_entity(entity);
}

void DataEditor::load_scene_3()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    world->set_gravity({ 0.f, 980.f });

    auto complex_1 = std::make_shared<game::ComplexEntity>(world, sf::Vector2f{  800,  500 }, 0.f);
    auto polygon_1 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{  400,  100 }, 0.f);
    auto circle_1  = std::make_shared<game::CircleEntity >(world, sf::Vector2f{  700,  100 }, 0.f);
    auto circle_2  = std::make_shared<game::CircleEntity >(world, sf::Vector2f{  400,  300 }, 0.f);
    auto polygon_2 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{  700,  300 }, 0.f);
    auto ground_1  = std::make_shared<game::GroundEntity >(world, sf::Vector2f{    0, 1200 }, 0.f);

    storage.add_entity(complex_1);
    storage.add_entity(polygon_1);
    storage.add_entity(circle_1 );
    storage.add_entity(circle_2 );
    storage.add_entity(polygon_2);
    storage.add_entity(ground_1 );

    
    for (int32_t i = 0; i < 50; ++i)
    {
        auto position = sf::Vector2f{ utils::randf(-1200, 1200, 2400), utils::randf(150, 1000, 850) };
        auto rotation = utils::randf(0.f, PIf * 2.f, 360);

        auto circle  = std::make_shared<game::CircleEntity >(world, position, rotation);

        position = sf::Vector2f{ utils::randf(-1200, 1200, 2400), utils::randf(150, 1000, 850) };
        rotation = utils::randf(0.f, PIf * 2.f, 360);

        auto polygon = std::make_shared<game::PolygonEntity>(world, position, rotation);

        storage.add_entity(circle);
        storage.add_entity(polygon);
    }

    storage.select_entity(complex_1);
}

void DataEditor::load_scene_4()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    auto polygon_1 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{   10,  600 }, 0.f);
    auto polygon_2 = std::make_shared<game::PolygonEntity>(world, sf::Vector2f{ 1550,  600 }, 0.f);

    polygon_1->set_color(sf::Color::Green);
    polygon_1->get_main_body()->accelerate({ 10000.f, 0.f });

    storage.add_entity(polygon_1);
    storage.add_entity(polygon_2);
}
