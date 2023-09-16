#include "../../Include/DataOperations/DataLoader.h"
#include "../../Include/DataOperations/Shapes/PolygonShape.h"
#include "../../Include/DataOperations/Shapes/CircleShape.h"


DataLoader::DataLoader(DataStorage& data_storage)
    : data_storage_(data_storage) 
{
    auto& materials = data_storage_.scene_data.materials;
    auto& shapes    = data_storage_.scene_data.shapes;

    // --- Materials
    Material material_1{
        sf::Color::White,  // Color
        0.6f,              // Elasticity
        "Default material" // Name
    };

    Material material_2{
        sf::Color::Red,                 // Color
        0.6f,                           // Elasticity
        "'Collision detected' material" // Name
    };

    materials.insert({ material_1.get_id(), std::make_shared<Material>(material_1) });
    materials.insert({ material_2.get_id(), std::make_shared<Material>(material_2) });

    // --- Shapes
    PolygonShape polygon_1{
        { {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
        {200, 200}, // Position
        (float)PI4  // Rotation
    };

    CircleShape circle_1{
        50,         // Radius
        {400, 200}  // Position
    };

    CircleShape circle_2{
        50,         // Radius
        {600, 200}  // Position
    };

    PolygonShape polygon_2{
        { {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
        {800, 200}  // Position
    };

    polygon_1.set_material_id(material_1.get_id());
    circle_1   .set_material_id(material_1.get_id());
    circle_2   .set_material_id(material_1.get_id());
    polygon_2.set_material_id(material_1.get_id());

    shapes.insert({ polygon_1.get_id(), std::make_shared<PolygonShape>(polygon_1) });
    shapes.insert({ circle_1 .get_id(), std::make_shared<CircleShape> (circle_1)  });
    shapes.insert({ circle_2 .get_id(), std::make_shared<CircleShape> (circle_2)  });
    shapes.insert({ polygon_2.get_id(), std::make_shared<PolygonShape>(polygon_2) });
}
DataLoader::~DataLoader()
{
}
