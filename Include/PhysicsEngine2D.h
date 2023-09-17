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
#include "../Include/DataCore/DataLoader.h"
#include "../Include/DataCore/DataEditor.h"

#include "../Include/PhysicsEngine/Engine.h"

#include "../Include/GUIEngine/Interface.h"
#include "../Include/GUIEngine/Renderer.h"
#include "../Include/GUIEngine/Window.h"


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
    void process_inputs();

    // --- Data
    
    DataStorage data_storage_;
    
    DataLoader  data_loader_;
    DataEditor  data_editor_;

    Interface   interface_;
    Engine      engine_;
    Renderer    renderer_;
    Window      window_;
};
