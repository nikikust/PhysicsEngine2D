#include "../../Include/GUIEngine/Interface.h"


namespace graphics
{
    Interface::Interface(DataStorage& data_storage, DataLoader& data_loader, graphics::Window& window)
        : data_storage_(data_storage),
          data_loader_ (data_loader),
          window_      (window)
    {
        init();
    }
    Interface::~Interface()
    {
        shutdown();
    }

    void Interface::update()
    {
        check_autosave();

        if (data_storage_.status.make_screenshot && data_storage_.settings.disable_interface_on_screenshot)
            return;


        show_cursor_message();

        show_exit_popup();
    }


    void Interface::init()
    {
        data_storage_.deltaClock.restart();
    }
    void Interface::shutdown()
    {
        ImGui::SFML::Shutdown();
    }

    void Interface::check_autosave()
    {
        if (data_storage_.settings.autosave == false)
            return;

        if (data_storage_.status.start_time_for_autosave + data_storage_.settings.autosave_interval_in_minutes * 60 <= time(0))
        {
            // TO DO: data_loader_.save_data();

            data_storage_.status.start_time_for_autosave = time(0);
        }
    }

    void Interface::show_cursor_message()
    {
        if (data_storage_.menus.CursorMessage == false)
            return;

        auto& fields = data_storage_.menus.fields.cursor_message;

        if (fields.elapse_at <= time(0))
        {
            fields.message = "";

            data_storage_.menus.CursorMessage = false;
        }

        ImVec2 position{
            (float)window_.get_cursor_position().x + 4,
            (float)window_.get_cursor_position().y + 4
        };

        ImGui::SetNextWindowPos(  position,  ImGuiCond_Always);
        ImGui::SetNextWindowSize({ 250, 0 }, ImGuiCond_Always);

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoTitleBar      |
            ImGuiWindowFlags_NoResize        |
            ImGuiWindowFlags_NoMove          |
            ImGuiWindowFlags_NoCollapse      |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoDecoration;

        ImGui::Begin("##Message", NULL, flags);

        ImGui::TextWrapped("%s", fields.message.c_str());

        ImGui::End();
    }

    void Interface::show_exit_popup()
    {
        if (data_storage_.menus.ConfirmExit.should_be_open == true &&
            data_storage_.menus.ConfirmExit.is_open        == false)
        {
            ImGui::OpenPopup("Exit", ImGuiPopupFlags_NoOpenOverExistingPopup);

            data_storage_.menus.ConfirmExit.is_open = true;
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("Exit", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("%s", "Are you sure?");
            ImGui::NewLine();
            ImGui::Separator();

            if (ImGui::Button("Quit and Save", ImVec2(120, 0)) || utils::key_pressed(sf::Keyboard::Enter))
            {
                data_storage_.menus.ConfirmExit.should_be_open = false;
                data_storage_.menus.ConfirmExit.is_open        = false;

                // TO DO: data_loader_.save_data();

                ImGui::CloseCurrentPopup();

                window_.close();
            }

            ImGui::SameLine();

            if (ImGui::Button("Quit and Don't Save", ImVec2(180, 0)))
            {
                data_storage_.menus.ConfirmExit.should_be_open = false;
                data_storage_.menus.ConfirmExit.is_open        = false;

                ImGui::CloseCurrentPopup();

                window_.close();
            }

            ImGui::SameLine();

            if (ImGui::Button("Stay", ImVec2(120, 0)) ||
                data_storage_.menus.ConfirmExit.should_be_open == false)
            {
                data_storage_.menus.ConfirmExit.should_be_open = false;
                data_storage_.menus.ConfirmExit.is_open = false;

                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    // --- //

    void Interface::create_message(const std::string& message, int timeout)
    {
        data_storage_.menus.CursorMessage = true;
        data_storage_.menus.fields.cursor_message.elapse_at = time(0) + timeout;
        data_storage_.menus.fields.cursor_message.message = message;
    }
} // namespace graphics
