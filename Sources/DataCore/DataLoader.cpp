#include "../../Include/DataCore/DataLoader.h"
#include "../../Include/PhysicsEngine/Shapes/PolygonShape.h"
#include "../../Include/PhysicsEngine/Shapes/CircleShape.h"


DataLoader::DataLoader(DataStorage& data_storage, Window& window)
    : data_storage_(data_storage), window_(window)
{
}
DataLoader::~DataLoader()
{
}

int DataLoader::init()
{
    srand((unsigned int)time(NULL));

    load_scene_2();

    return 0;
}

void DataLoader::load_scene_1()
{
    auto& materials = data_storage_.scene_data.materials;
    auto& shapes = data_storage_.scene_data.shapes;

    // --- Materials
    physics::Material material_1{
        sf::Color::White,  // Color
        0.6f,              // Elasticity
        "Default material" // Name
    };

    physics::Material material_2{
        sf::Color::Red,                 // Color
        0.6f,                           // Elasticity
        "'Collision detected' material" // Name
    };

    materials.insert({ material_1.get_id(), std::make_shared<physics::Material>(material_1) });
    materials.insert({ material_2.get_id(), std::make_shared<physics::Material>(material_2) });

    // --- Shapes
    physics::PolygonShape polygon_1{
        { {-150, 0}, {-100, -50}, {100, -50}, {150, 0}, {100, 50}, {-100, 50} }, // Vertices
        {200, 200}, // Position
        0.f,        // Rotation
        1500.f      // Mass
    };

    physics::CircleShape circle_1{
        50,         // Radius
        {400, 200}, // Position
        0.f,        // Rotation
        1500.f      // Mass
    };

    physics::CircleShape circle_2{
        50,         // Radius
        {600, 200}, // Position
        0.f,        // Rotation
        1500.f      // Mass
    };

    physics::PolygonShape polygon_2{
        { {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
        {800, 200}, // Position
        0.f,        // Rotation
        1500.f      // Mass
    };

    polygon_1.set_material_id(material_1.get_id());
    circle_1 .set_material_id(material_1.get_id());
    circle_2 .set_material_id(material_1.get_id());
    polygon_2.set_material_id(material_1.get_id());

    shapes.insert({ polygon_1.get_id(), std::make_shared<physics::PolygonShape>(polygon_1) });
    shapes.insert({ circle_1.get_id(),  std::make_shared<physics::CircleShape> (circle_1)  });
    shapes.insert({ circle_2.get_id(),  std::make_shared<physics::CircleShape> (circle_2)  });
    shapes.insert({ polygon_2.get_id(), std::make_shared<physics::PolygonShape>(polygon_2) });
}
void DataLoader::load_scene_2()
{
    auto& materials = data_storage_.scene_data.materials;
    auto& shapes = data_storage_.scene_data.shapes;

    // --- Materials
    sf::Color colors[7] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow, sf::Color::White };

    for (uint32_t i = 0; i < 7; ++i)
    {
        // Elasticity
        int el_start = 10, el_end = 90;

        float elasticity = float(rand() % (el_end - el_start + 1) + el_start) / 100.f;

        // Creation
        physics::Material material{ colors[i], elasticity, "material_" + std::to_string(i) };

        materials.insert({ material.get_id(), std::make_shared<physics::Material>(material) });
    }

    // --- Shapes

    int col_start = 1, col_end = 7;

    for (uint32_t i = 0; i < 20; ++i)
    {
        physics::PolygonShape polygon = physics::PolygonShape::generate_rectangle(window_.get_render_area().getSize());

        int material = rand() % (col_end - col_start + 1) + col_start;

        polygon.set_material_id(materials.at(material)->get_id());

        shapes.insert({ polygon.get_id(), std::make_shared<physics::PolygonShape>(polygon) });
    }

    for (uint32_t i = 0; i < 20; ++i)
    {
        physics::CircleShape circle = physics::CircleShape::generate_circle(window_.get_render_area().getSize());

        int material = rand() % (col_end - col_start + 1) + col_start;

        circle.set_material_id(materials.at(material)->get_id());

        shapes.insert({ circle.get_id(), std::make_shared<physics::CircleShape>(circle) });
    }
}
void DataLoader::load_scene_3()
{
    auto& materials = data_storage_.scene_data.materials;
    auto& shapes    = data_storage_.scene_data.shapes;

    // --- Materials
    physics::Material material{
        sf::Color::White,  // Color
        1.0f,              // Elasticity
        "Default material" // Name
    };

    materials.insert({ material.get_id(), std::make_shared<physics::Material>(material) });

    // --- Shapes
    physics::PolygonShape ground{
        { {-1000, 20}, {1000, 20}, {1000, -20}, {-1000, -20} }, // Vertices
        {1280, 1300}, // Position
        0.f,        // Rotation
        1000.f      // Mass
    };

    ground.set_linear_fixation(true, true);

    physics::PolygonShape polygon{
        { {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
        {1280, 200}, // Position
        0.f,         // Rotation
        1000.f       // Mass
    };

    ground .set_material_id(material.get_id());
    polygon.set_material_id(material.get_id());

    shapes.insert({ ground .get_id(), std::make_shared<physics::PolygonShape>(ground ) });
    shapes.insert({ polygon.get_id(), std::make_shared<physics::PolygonShape>(polygon) });
}
