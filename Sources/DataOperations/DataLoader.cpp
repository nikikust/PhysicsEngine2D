#include "../../Include/DataOperations/DataLoader.h"
#include "../../Include/DataOperations/Shapes/RectangleShape.h"
#include "../../Include/DataOperations/Shapes/CircleShape.h"


DataLoader::DataLoader(DataStorage& data_storage)
    : data_storage_(data_storage) 
{
    auto& shapes = data_storage_.scene_objects.shapes;

    RectangleShape rectangle_1{
        {100, 100}, // Size
        {200, 200}  // Position
    };

    CircleShape circle_1{
        50,         // Radius
        {400, 200}  // Position
    };

    shapes.push_back(std::make_shared<RectangleShape>(rectangle_1));
    shapes.push_back(std::make_shared<CircleShape>   (circle_1));
}
DataLoader::~DataLoader()
{
}
