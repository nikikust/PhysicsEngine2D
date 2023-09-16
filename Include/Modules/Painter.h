#pragma once
#include "../../Include/DataOperations/DataStorage.h"
#include "../../Include/DataOperations/Shapes/RectangleShape.h"
#include "../../Include/DataOperations/Shapes/CircleShape.h"

#include "Window.h"


class Painter
{
public:
    Painter(DataStorage& data_storage, Window& window);
    Painter() = delete;
    Painter(Painter&) = delete;
    Painter(Painter&&) = delete;
    ~Painter();

    // --- //

    void draw_rectangle (std::shared_ptr<RectangleShape> rectangle);
    void draw_circle    (std::shared_ptr<CircleShape>    circle   );

private:
    DataStorage& data_storage_;
    Window&      window_;

    sf::CircleShape    circle_brush;
    sf::RectangleShape rectangle_brush;
};
