#include "../../Include/DataOperations/DataEditor.h"


DataEditor::DataEditor(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage),
      window_      (window)
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
