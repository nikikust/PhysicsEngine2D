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

    return 0;
}
