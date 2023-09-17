#pragma once
#include "../../Include/DataCore/DataStorage.h"
#include "../../Include/DataCore/DataLoader.h"

#include "Painter.h"


namespace graphics
{
    class Renderer
    {
    public:
        Renderer(DataStorage& data_storage, DataLoader& data_loader, graphics::Window& window);
        Renderer() = delete;
        Renderer(Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        ~Renderer();

        // --- //

        void update();
        void draw();

    private:
        DataStorage& data_storage_;
        DataLoader&  data_loader_;

        graphics::Window& window_;

        graphics::Painter painter_;
    };
} // namespace graphics
