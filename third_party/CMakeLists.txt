include(FetchContent)


FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        823a1385a269d923d35b82b2f470f3ae1fa8b5a3
)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG        de565ac8f2b795dedc0307b60830cb006afd2ecd
)

FetchContent_Declare(
    nlohmann-json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d
)

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


message("Installing nlohmann-json")
FetchContent_MakeAvailable(nlohmann-json)
message("nlohmann-json installed")
