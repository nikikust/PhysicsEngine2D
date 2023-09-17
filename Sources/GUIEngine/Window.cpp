#include "../../Include/Modules/Window.h"


Window::Window(DataStorage& data_storage, const std::string window_title)
    : data_storage_(data_storage)
{
    sf::VideoMode size{ sf::VideoMode::getDesktopMode() };

    size.height -= 40;

    window_.create(size, window_title);
    window_.setPosition(sf::Vector2i(-10, 0));

    // window.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(400);
    window_.setKeyRepeatEnabled(false);

    data_storage_.screen_size = sf::Vector2i(window_.getSize());

    bool result = ImGui::SFML::Init(window_);

    imgui_io_ = &ImGui::GetIO();
    imgui_io_->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}
Window::~Window()
{

}

void Window::close()
{
    window_.close();
}

void Window::on_resize(sf::Event& event)
{
    sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);

    window_.setView(sf::View(visibleArea));

    data_storage_.screen_size = sf::Vector2i(window_.getSize());
}
bool Window::poll_event(sf::Event& event)
{
    return window_.pollEvent(event);
}

bool Window::has_focus()
{
    return window_.hasFocus();
}
bool Window::is_open()
{
    return window_.isOpen();
}

sf::Vector2i Window::get_cursor_position()
{
    return sf::Mouse::getPosition(window_);
}

void Window::set_cursor_position(sf::Vector2i position)
{
    sf::Mouse::setPosition(position, window_);
}
void Window::hide_mouse()
{
    window_.setMouseCursorVisible(false);
}
void Window::show_mouse()
{
    window_.setMouseCursorVisible(true);
}

void Window::update()
{
    ImGui::SFML::Update(window_, data_storage_.deltaClock.restart());

    data_storage_.status.mouse_captured    = imgui_io_->WantCaptureMouse;
    data_storage_.status.keyboard_captured = imgui_io_->WantCaptureKeyboard;
}
void Window::cls()
{
    window_.clear(data_storage_.settings.background_color);
}
void Window::flip()
{
    ImGui::SFML::Render(window_);

    window_.display();
}

sf::RenderWindow& Window::get_render_area()
{
    return window_;
}
