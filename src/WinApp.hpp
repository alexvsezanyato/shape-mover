#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "App.hpp"
#include "WinSettings.hpp"

class WinApp : public App {
private:
    WinApp() = delete;

protected:
    WinSettings windowSettings;
    sf::RenderWindow window;
    sf::VideoMode getVideoMode();
    unsigned getWindowStyle();
    bool isWindowed();
    void setSettings(WinSettings);
    void render();
    sf::Vector2u getSize();
    WinApp(std::string name, WinSettings);
    WinApp(std::string name);
};
