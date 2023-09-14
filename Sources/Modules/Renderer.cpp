#include "../../Include/Modules/Renderer.h"


Renderer::Renderer(DataStorage& data_storage, DataLoader& data_loader, Window& window)
    : data_storage_(data_storage),
      data_loader_ (data_loader),
      window_      (window),
      painter_     (data_storage_, window)
{

}
Renderer::~Renderer()
{

}


void Renderer::update()
{
    
}

void Renderer::draw()
{
    
}
