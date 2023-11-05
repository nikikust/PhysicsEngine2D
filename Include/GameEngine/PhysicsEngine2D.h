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

#pragma once
#include <GameEngine/DataCore/DataLoader.h>
#include <GameEngine/DataCore/DataEditor.h>

#include <GameEngine/Game/Callbacks/ClosestRayHit.h>

#include <GameEngine/PhysicsEngine/Engine.h>

#include <GameEngine/GUIEngine/Interface.h>
#include <GameEngine/GUIEngine/Renderer.h>
#include <GameEngine/GUIEngine/Window.h>


class PhysicsEngine2D
{
public:
    PhysicsEngine2D(const std::string& app_title);
    ~PhysicsEngine2D();

    // --- //

    int run();

private:
    int load_data();
    int main_loop();

    void poll_events();
    void update_timers();
    void process_inputs();

    void ray_cast_test();

    // --- Data
    
    DataStorage data_storage_;
    DataLoader  data_loader_;
    DataEditor  data_editor_;

    graphics::Interface   interface_;
    graphics::Renderer    renderer_;
    graphics::Window      window_;

    physics::Engine      engine_;
};
