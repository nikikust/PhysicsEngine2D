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

    Sources/DataOperations/DataEditor.cpp
    Sources/DataOperations/DataLoader.cpp
    Sources/DataOperations/DataStorage.cpp

    Sources/DataOperations/Shapes/Shape.cpp
    Sources/DataOperations/Shapes/PolygonShape.cpp
    Sources/DataOperations/Shapes/CircleShape.cpp

    Sources/Modules/Interface.cpp
    Sources/Modules/Painter.cpp
    Sources/Modules/Renderer.cpp
    Sources/Modules/Window.cpp
    
    Sources/Modules/Engine/Engine.cpp
    Sources/Modules/Engine/Material.cpp
    Sources/Modules/Engine/CollisionSolver.cpp
)
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
    functions
)

# string(REGEX REPLACE "/W4" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")
