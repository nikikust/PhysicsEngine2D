/**
 * Copyright 2023 Glazunov Nikita <lis291@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../Include/PhysicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(const std::string& app_title)
    : window_      (data_storage_, app_title),
      data_loader_ (data_storage_),
      data_editor_ (data_storage_, window_),
      engine_      (data_storage_, window_),
      renderer_    (data_storage_, data_loader_, window_),
      interface_   (data_storage_, data_loader_, window_)
{
    
}
PhysicsEngine2D::~PhysicsEngine2D()
{
    
}


int PhysicsEngine2D::run()
{
    int result = load_data();

    if (result != 0)
        return result;

    return main_loop();
}

int PhysicsEngine2D::load_data()
{
    return 0;
}
int PhysicsEngine2D::main_loop()
{
    while (window_.is_open())
    {
        // --- Poll
        poll_events   ();
        process_inputs();

        // --- Update
        window_   .update();
        engine_   .update();
        renderer_ .update();
        interface_.update();

        // --- Draw
        window_.cls();
        renderer_.draw();
        window_.flip();

        data_editor_.check_screenshot_status();
    }

    return 0;
}

void PhysicsEngine2D::poll_events()
{
    sf::Event event {};

    while (window_.poll_event(event))
    {
        ImGui::SFML::ProcessEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::Resized:
            window_.on_resize(event);
            break;
        case sf::Event::MouseButtonPressed:
            if (utils::in(0, event.mouseButton.button, sf::Mouse::ButtonCount - 1))
                utils::mouse_states[event.mouseButton.button] = utils::ButtonState::Pressed;
            break;
        case sf::Event::MouseButtonReleased:
            if (utils::in(0, event.mouseButton.button, sf::Mouse::ButtonCount - 1))
                utils::mouse_states[event.mouseButton.button] = utils::ButtonState::Released;
            break;
        case sf::Event::KeyPressed:
            if (utils::in(0, event.key.code, sf::Keyboard::KeyCount - 1))
                utils::key_states[event.key.code] = utils::ButtonState::Pressed;
            break;
        case sf::Event::KeyReleased:
            if (utils::in(0, event.key.code, sf::Keyboard::KeyCount - 1))
                utils::key_states[event.key.code] = utils::ButtonState::Released;
            break;
        default:
            break;
        }
    }
}
void PhysicsEngine2D::process_inputs()
{
    // --- Camera movement

    if (utils::mouse_pressed  (sf::Mouse::Left)  && data_editor_.mouse_io_is_released())
    {
        data_editor_.save_mouse_position_on_click();

        data_editor_.start_moving_camera();
    }
    if (utils::mouse_down     (sf::Mouse::Left))
    {
        auto mouse_diff = window_.get_cursor_position() - data_storage_.status.mouse_position_on_click;

        mouse_diff.x = int(mouse_diff.x / data_storage_.camera.scale_modifier_as_pow2);
        mouse_diff.y = int(mouse_diff.y / data_storage_.camera.scale_modifier_as_pow2);

        if (data_editor_.is_camera_moving_mode())
        {
            data_editor_.move_camera(mouse_diff);

            if (!data_editor_.mouse_io_is_released())
                data_editor_.restore_camera_position();
        }
    }
    if (utils::mouse_released (sf::Mouse::Left)  && data_editor_.mouse_io_is_released())
    {
        if (data_editor_.is_camera_moving_mode())
        {
            data_editor_.stop_moving_camera();
        }
    }
                              
    if (utils::mouse_pressed  (sf::Mouse::Right) && data_editor_.mouse_io_is_released())
    {

    }
    if (utils::mouse_down     (sf::Mouse::Right))
    {

    }
    if (utils::mouse_released (sf::Mouse::Right) && data_editor_.mouse_io_is_released())
    {

    }

    if (utils::key_pressed(sf::Keyboard::Left ) && data_editor_.keyboard_io_is_released())
    {
        if (data_editor_.is_idle_mode())
            data_storage_.camera.position.x -= int(data_storage_.screen_size.x / data_storage_.camera.scale_modifier_as_pow2);
    }
    if (utils::key_pressed(sf::Keyboard::Right) && data_editor_.keyboard_io_is_released())
    {
        if (data_editor_.is_idle_mode())
            data_storage_.camera.position.x += int(data_storage_.screen_size.x / data_storage_.camera.scale_modifier_as_pow2);
    }
    if (utils::key_pressed(sf::Keyboard::Up)    && data_editor_.keyboard_io_is_released())
    {
        if (data_editor_.is_idle_mode())
            data_storage_.camera.position.y -= int(data_storage_.screen_size.y / data_storage_.camera.scale_modifier_as_pow2);
    }
    if (utils::key_pressed(sf::Keyboard::Down)  && data_editor_.keyboard_io_is_released())
    {
        if (data_editor_.is_idle_mode())
            data_storage_.camera.position.y += int(data_storage_.screen_size.y / data_storage_.camera.scale_modifier_as_pow2);
    }

    // --- Zooming
    if (utils::key_pressed(sf::Keyboard::Subtract))
    {
        if (data_editor_.keyboard_io_is_released())
            data_editor_.zoom_out();
    }
    if (utils::key_pressed(sf::Keyboard::Add))
    {
        if (data_editor_.keyboard_io_is_released())
            data_editor_.zoom_in();
    }
    if (utils::key_pressed(sf::Keyboard::LBracket))
    {
        if (data_editor_.keyboard_io_is_released())
            data_editor_.zoom_out();
    }
    if (utils::key_pressed(sf::Keyboard::RBracket))
    {
        if (data_editor_.keyboard_io_is_released())
            data_editor_.zoom_in();
    }

    // --- Hotkeys
    if (utils::key_pressed(sf::Keyboard::P))
    {
        if (data_editor_.keyboard_io_is_released())
            if (data_storage_.settings.disable_interface_on_screenshot)
                data_editor_.screenshot_without_interface();
            else
                data_editor_.screenshot_with_interface();
    }

    if (utils::key_pressed(sf::Keyboard::Escape))
    {
        if (data_editor_.message_is_opened())
            data_editor_.close_message();
        else if (utils::mouse_down(sf::Mouse::Left))
        {
            if (data_editor_.is_camera_moving_mode())
                data_editor_.restore_camera_position();
        }
        else
            data_editor_.flip_exit_popup_state();
    }

    if (utils::key_down(sf::Keyboard::LControl))
    {
        if (data_editor_.keyboard_io_is_released())
        {
            if (utils::key_pressed(sf::Keyboard::S)) 
            {
                // TO DO: data_loader_.save_data();
            }
        }
    }

    if (utils::key_down(sf::Keyboard::A))
        if (data_editor_.keyboard_io_is_released())
            data_storage_.scene_data.shapes.at(1)->rotate(-(float)PI / 1000.f);

    if (utils::key_down(sf::Keyboard::D))
        if (data_editor_.keyboard_io_is_released())
            data_storage_.scene_data.shapes.at(1)->rotate((float)PI / 1000.f);

    // --- //
}
