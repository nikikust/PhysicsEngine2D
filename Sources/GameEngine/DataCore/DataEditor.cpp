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
void DataEditor::move_camera(sf::Vector2i delta)
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

void DataEditor::zoom_out()
{
    data_storage_.camera.scale_modifier = utils::minmax(
        -2.f,
            round(data_storage_.camera.scale_modifier) - 1,
            3.f
    );

    data_storage_.camera.scale_modifier_as_pow2 = powf(2, data_storage_.camera.scale_modifier);
}
void DataEditor::zoom_in()
{
    data_storage_.camera.scale_modifier = utils::minmax(
        -2.f,
        round(data_storage_.camera.scale_modifier) + 1,
        3.f
    );

    data_storage_.camera.scale_modifier_as_pow2 = powf(2, data_storage_.camera.scale_modifier);
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
    case 1: load_scene_1(); return;
    case 2: load_scene_2(); return;
    case 3: load_scene_3(); return;
    case 4: load_scene_4(); return;
    default:                return;
    }
}

void DataEditor::load_scene_1()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    game::ComplexEntity complex_1{ world, {1500, 1000}, 0 };
    game::PolygonEntity polygon_1{ world, {1100,  600}, 0 };
    game::CircleEntity  circle_1{ world, {1400,  600}, 0 };
    game::CircleEntity  circle_2{ world, {1100,  800}, 0 };
    game::PolygonEntity polygon_2{ world, {1400,  800}, 0 };

    auto entity = storage.add_entity(std::move(complex_1));
    storage.add_entity(std::move(polygon_1));
    storage.add_entity(std::move(circle_1));
    storage.add_entity(std::move(circle_2));
    storage.add_entity(std::move(polygon_2));

    storage.select_entity(entity);
}

void DataEditor::load_scene_2()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    world->set_gravity({ 0.f, 980.f });

    std::shared_ptr<game::Entity> entity;

    for (int32_t i = 0; i < 2; ++i)
    {
        game::ShipEntity ship{ world, { 100.f + i * 1050.f, 10.f }, 0 };

        if (entity == nullptr)
            entity = storage.add_entity(std::move(ship));
        else
            storage.add_entity(std::move(ship));
    }

    game::GroundEntity ground_1{ world, {1280, 1200}, 0 };

    storage.add_entity(std::move(ground_1));

    storage.select_entity(entity);
}

void DataEditor::load_scene_3()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    world->set_gravity({ 0.f, 980.f });

    game::ComplexEntity complex_1{ world, { 800,  500}, 0 };
    game::PolygonEntity polygon_1{ world, { 400,  100}, 0 };
    game::CircleEntity  circle_1{ world, { 700,  100}, 0 };
    game::CircleEntity  circle_2{ world, { 400,  300}, 0 };
    game::PolygonEntity polygon_2{ world, { 700,  300}, 0 };
    game::GroundEntity  ground_1{ world, {1280, 1200}, 0 };

    auto entity = storage.add_entity(std::move(complex_1));
    storage.add_entity(std::move(polygon_1));
    storage.add_entity(std::move(circle_1));
    storage.add_entity(std::move(circle_2));
    storage.add_entity(std::move(polygon_2));
    storage.add_entity(std::move(ground_1));


    for (int32_t i = 0; i < 50; ++i)
    {
        game::CircleEntity  circle{ world, { utils::randf(200, 2360, 2160), utils::randf(150, 1000, 850) }, utils::randf(0.f, (float)PI * 2.f, 360) };
        game::PolygonEntity polygon{ world, { utils::randf(200, 2360, 2160), utils::randf(150, 1000, 850) }, utils::randf(0.f, (float)PI * 2.f, 360) };

        storage.add_entity(std::move(circle));
        storage.add_entity(std::move(polygon));
    }

    storage.select_entity(entity);
}

void DataEditor::load_scene_4()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    game::PolygonEntity polygon_1{ world, {  10,  600}, 0 };
    game::PolygonEntity polygon_2{ world, {1550,  600}, 0 };

    polygon_1.set_color(sf::Color::Green);
    polygon_1.get_main_body()->accelerate({ 10000.f, 0.f });

    storage.add_entity(std::move(polygon_1));
    storage.add_entity(std::move(polygon_2));
}
