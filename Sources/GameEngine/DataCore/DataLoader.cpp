#include <GameEngine/DataCore/DataLoader.h>


DataLoader::DataLoader(DataStorage& data_storage, graphics::Window& window, physics::Engine& engine)
    : data_storage_(data_storage), window_(window), engine_(engine)
{
}
DataLoader::~DataLoader()
{
}

int DataLoader::init()
{
    srand((unsigned int)time(NULL));

    load_scene_1();

    return 0;
}

void DataLoader::load_scene_1()
{
    game::ComplexEntity complex_1{ engine_.get_world(), {500, 500} , 0 };
    game::PolygonEntity polygon_1{ engine_.get_world(), {100, 100} , 0 };
    game::CircleEntity  circle_1 { engine_.get_world(), {300, 100} , 0 };
    game::CircleEntity  circle_2 { engine_.get_world(), {100, 300} , 0 };
    game::PolygonEntity polygon_2{ engine_.get_world(), {300, 300} , 0 };

    data_storage_.entities_storage.add_entity(complex_1);
    data_storage_.entities_storage.add_entity(polygon_1);
    data_storage_.entities_storage.add_entity(circle_1 );
    data_storage_.entities_storage.add_entity(circle_2 );
    data_storage_.entities_storage.add_entity(polygon_2);

    // std::cout << std::endl << 1.f / std::dynamic_pointer_cast<game::ComplexEntity>(data_storage_.entities_storage.add_entity(complex_1))->get_body()->get_inv_mass();
    // std::cout << std::endl << 1.f / std::dynamic_pointer_cast<game::PolygonEntity>(data_storage_.entities_storage.add_entity(polygon_1))->get_body()->get_inv_mass();
    // std::cout << std::endl << 1.f / std::dynamic_pointer_cast<game::CircleEntity> (data_storage_.entities_storage.add_entity(circle_1 ))->get_body()->get_inv_mass();
    // std::cout << std::endl << 1.f / std::dynamic_pointer_cast<game::CircleEntity> (data_storage_.entities_storage.add_entity(circle_2 ))->get_body()->get_inv_mass();
    // std::cout << std::endl << 1.f / std::dynamic_pointer_cast<game::PolygonEntity>(data_storage_.entities_storage.add_entity(polygon_2))->get_body()->get_inv_mass();
    // std::cout << std::endl;
}
void DataLoader::load_scene_2()
{
    // auto& materials = data_storage_.scene_data.materials;
    // auto& shapes = data_storage_.scene_data.shapes;
    // 
    // // --- Materials
    // sf::Color colors[7] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow, sf::Color::White };
    // 
    // for (uint32_t i = 0; i < 7; ++i)
    // {
    //     // Elasticity
    //     int el_start = 10, el_end = 90;
    // 
    //     float elasticity = float(rand() % (el_end - el_start + 1) + el_start) / 100.f;
    // 
    //     // Creation
    //     physics::Material material{ colors[i], elasticity, "material_" + std::to_string(i) };
    // 
    //     materials.insert({ material.get_id(), std::make_shared<physics::Material>(material) });
    // }
    // 
    // // --- Shapes
    // 
    // int col_start = 1, col_end = 7;
    // 
    // for (uint32_t i = 0; i < 20; ++i)
    // {
    //     physics::PolygonShape polygon = physics::PolygonShape::generate_rectangle(window_.get_render_area().getSize());
    // 
    //     int material = rand() % (col_end - col_start + 1) + col_start;
    // 
    //     polygon.set_material_id(materials.at(material)->get_id());
    // 
    //     shapes.insert({ polygon.get_id(), std::make_shared<physics::PolygonShape>(polygon) });
    // }
    // 
    // for (uint32_t i = 0; i < 20; ++i)
    // {
    //     physics::CircleShape circle = physics::CircleShape::generate_circle(window_.get_render_area().getSize());
    // 
    //     int material = rand() % (col_end - col_start + 1) + col_start;
    // 
    //     circle.set_material_id(materials.at(material)->get_id());
    // 
    //     shapes.insert({ circle.get_id(), std::make_shared<physics::CircleShape>(circle) });
    // }
}
void DataLoader::load_scene_3()
{
    // auto& materials = data_storage_.scene_data.materials;
    // auto& shapes    = data_storage_.scene_data.shapes;
    // 
    // // --- Materials
    // physics::Material material{
    //     sf::Color::White,  // Color
    //     1.0f,              // Elasticity
    //     "Default material" // Name
    // };
    // 
    // materials.insert({ material.get_id(), std::make_shared<physics::Material>(material) });
    // 
    // // --- Shapes
    // physics::PolygonShape ground{
    //     { {-1000, 20}, {1000, 20}, {1000, -20}, {-1000, -20} }, // Vertices
    //     {1280, 1300}, // Position
    //     0.f,        // Rotation
    //     1000.f      // Mass
    // };
    // 
    // ground.set_linear_fixation(true, true);
    // 
    // physics::PolygonShape polygon{
    //     { {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
    //     {1280, 200}, // Position
    //     0.f,         // Rotation
    //     1000.f       // Mass
    // };
    // 
    // ground .set_material_id(material.get_id());
    // polygon.set_material_id(material.get_id());
    // 
    // shapes.insert({ ground .get_id(), std::make_shared<physics::PolygonShape>(ground ) });
    // shapes.insert({ polygon.get_id(), std::make_shared<physics::PolygonShape>(polygon) });
}
void DataLoader::load_scene_4()
{
    // auto& materials = data_storage_.scene_data.materials;
    // auto& shapes    = data_storage_.scene_data.shapes;
    // 
    // // --- Materials
    // sf::Color colors[7] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Yellow, sf::Color::White };
    // 
    // for (uint32_t i = 0; i < 7; ++i)
    // {
    //     // Elasticity
    //     int el_start = 10, el_end = 90;
    // 
    //     float elasticity = float(rand() % (el_end - el_start + 1) + el_start) / 100.f;
    // 
    //     // Creation
    //     physics::Material material{ colors[i], elasticity, "material_" + std::to_string(i) };
    // 
    //     materials.insert({ material.get_id(), std::make_shared<physics::Material>(material) });
    // }
    // 
    // // --- Shapes
    // physics::PolygonShape ground{
    //     { {-1000, 20}, {1000, 20}, {1000, -20}, {-1000, -20} }, // Vertices
    //     {1280, 1300}, // Position
    //     0.f,          // Rotation
    //     1000.f        // Mass
    // };
    // 
    // ground.set_linear_fixation(true, true);
    // ground.set_material_id(1);
    // 
    // shapes.insert({ ground.get_id(), std::make_shared<physics::PolygonShape>(ground) });
    // 
    // for (int i = 0; i < 25; ++i)
    // {
    //     physics::PolygonShape polygon{
    //         { {-25, -25}, {25, -25}, {25, 25}, {-25, 25} }, // Vertices
    //         {1280 + i * 10.f, 100 + i * 60.f}, // Position
    //         0.f,         // Rotation
    //         1000.f       // Mass
    //     };
    // 
    //     polygon.set_material_id(i % 7 + 1);
    // 
    //     shapes.insert({ polygon.get_id(), std::make_shared<physics::PolygonShape>(polygon) });
    // }
}
