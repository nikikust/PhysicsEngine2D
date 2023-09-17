cmake_minimum_required(VERSION 3.5)
project(Physics_Engine_2D LANGUAGES CXX)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_STANDARD 20)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR})

find_package(Threads REQUIRED)

add_subdirectory(third_party)

include_directories(
	Include/
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/misc/cpp/
    ${CMAKE_BINARY_DIR}/_deps/imgui-sfml-src/
    ${CMAKE_BINARY_DIR}/_deps/sfml-src/include/
    # ${CMAKE_BINARY_DIR}/_deps/nlohmann-json-src/include/
)


add_library(functions STATIC
    Sources/Utils/Functions.cpp
)
target_link_libraries(functions
    ImGui-SFML::ImGui-SFML
)

add_executable(${PROJECT_NAME}
    Main.cpp

    Sources/PhysicsEngine2D.cpp

    Sources/DataCore/DataEditor.cpp
    Sources/DataCore/DataLoader.cpp
    Sources/DataCore/DataStorage.cpp

    Sources/GUIEngine/Interface.cpp
    Sources/GUIEngine/Painter.cpp
    Sources/GUIEngine/Renderer.cpp
    Sources/GUIEngine/Window.cpp
    
    Sources/PhysicsEngine/Engine.cpp
    Sources/PhysicsEngine/Material.cpp
    Sources/PhysicsEngine/CollisionSolver.cpp

    Sources/PhysicsEngine/Shapes/Shape.cpp
    Sources/PhysicsEngine/Shapes/PolygonShape.cpp
    Sources/PhysicsEngine/Shapes/CircleShape.cpp
)
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
    functions
)

# string(REGEX REPLACE "/W4" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")
