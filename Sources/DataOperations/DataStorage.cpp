#include "../../Include/DataOperations/DataStorage.h"


DataStorage::DataStorage()
{
    status.last_time = utils::get_time_millisec();
    status.delta_time = 0;
}

DataStorage::~DataStorage()
{
    
}
