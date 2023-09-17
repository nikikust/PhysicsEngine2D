#pragma once
#include "../../Include/DataCore/DataStorage.h"

#include "../../Include/PhysicsEngine/Shapes/PolygonShape.h"
#include "../../Include/PhysicsEngine/Shapes/CircleShape.h"

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

    void draw_rectangle (std::shared_ptr<PolygonShape> rectangle);
    void draw_circle    (std::shared_ptr<CircleShape>    circle   );

private:
    DataStorage& data_storage_;
    Window&      window_;

    sf::CircleShape circle_brush;
    sf::ConvexShape polygon_brush;
};
