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

    load_scene_2();

    return 0;
}

void DataLoader::load_scene_1()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    game::ComplexEntity complex_1{ world, {1500, 1000}, 0 };
    game::PolygonEntity polygon_1{ world, {1100,  600}, 0 };
    game::CircleEntity  circle_1 { world, {1400,  600}, 0 };
    game::CircleEntity  circle_2 { world, {1100,  800}, 0 };
    game::PolygonEntity polygon_2{ world, {1400,  800}, 0 };

    storage.add_entity(std::move(complex_1));
    storage.add_entity(std::move(polygon_1));
    storage.add_entity(std::move(circle_1 ));
    storage.add_entity(std::move(circle_2 ));
    storage.add_entity(std::move(polygon_2));
}
void DataLoader::load_scene_2()
{
    auto  world = engine_.get_world();
    auto& storage = data_storage_.entities_storage;

    for (int32_t i = 0; i < 5; ++i)
    {
        game::ShipEntity ship{ world, { 100.f + i * 350.f, 100.f }, 0 };

        storage.add_entity(std::move(ship));
    }

    //game::GroundEntity ground_1{ world, {1280, 1200}, 0 };
    //
    //storage.add_entity(std::move(ground_1));
}
void DataLoader::load_scene_3()
{
    auto  world   = engine_.get_world();
    auto& storage = data_storage_.entities_storage;
    
    game::ComplexEntity complex_1 { world, { 800,  500}, 0 };
    game::PolygonEntity polygon_1 { world, { 400,  100}, 0 };
    game::CircleEntity  circle_1  { world, { 700,  100}, 0 };
    game::CircleEntity  circle_2  { world, { 400,  300}, 0 };
    game::PolygonEntity polygon_2 { world, { 700,  300}, 0 };
    game::GroundEntity  ground_1  { world, {1280, 1200}, 0 };
    
    storage.add_entity(std::move(complex_1));
    storage.add_entity(std::move(polygon_1));
    storage.add_entity(std::move(circle_1 ));
    storage.add_entity(std::move(circle_2 ));
    storage.add_entity(std::move(polygon_2));
    storage.add_entity(std::move(ground_1 ));


    for (int32_t i = 0; i < 50; ++i)
    {
        game::CircleEntity  circle { world, { utils::randf(200, 2360, 2160), utils::randf(150, 1000, 850) }, utils::randf(0.f, (float)PI * 2.f, 360)};
        game::PolygonEntity polygon{ world, { utils::randf(200, 2360, 2160), utils::randf(150, 1000, 850) }, utils::randf(0.f, (float)PI * 2.f, 360)};

        storage.add_entity(std::move(circle ));
        storage.add_entity(std::move(polygon));
    }
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
