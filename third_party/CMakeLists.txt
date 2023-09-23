include(FetchContent)


FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        a1b60fc1f5589d498ab1080c2572da725fcbd0e3
)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG        6bd43671d3fab76f94b1f0877d943d8cc3b34c3b
)

# FetchContent_Declare(
#     nlohmann-json
#     GIT_REPOSITORY https://github.com/nlohmann/json.git
#     GIT_TAG        bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d
# )

message("Installing imgui")
FetchContent_MakeAvailable(imgui)
message("imgui installed")


message("Installing SFML")
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)

FetchContent_MakeAvailable(SFML)
message("SFML installed")


set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

message("Installing imgui-sfml")
FetchContent_MakeAvailable(imgui-sfml)
message("imgui-sfml installed")


# message("Installing nlohmann-json")
# FetchContent_MakeAvailable(nlohmann-json)
# message("nlohmann-json installed")
