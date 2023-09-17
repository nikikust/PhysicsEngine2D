#pragma once
#include "../../Include/DataCore/DataStorage.h"
#include "../../Include/DataCore/DataLoader.h"

#include "Window.h"


namespace graphics
{
    class Interface
    {
    public:
        Interface(DataStorage& data_storage, DataLoader& data_loader, Window& window);
        Interface() = delete;
        Interface(Interface&) = delete;
        Interface(Interface&&) = delete;

        ~Interface();

        // --- //

        void update();

    private:
        void init();
        void shutdown();

        void check_autosave();

        void show_cursor_message();

        void show_exit_popup();


        // --- Utils

        void create_message(const std::string& message, int timeout = 5);


        // --- Data

        DataStorage& data_storage_;
        DataLoader&  data_loader_;

        graphics::Window& window_;
    };
} // namespace graphics
