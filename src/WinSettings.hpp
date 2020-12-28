#pragma once

#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>

struct WinSettings {
public:
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::ContextSettings contextSettings = sf::ContextSettings(0, 0, 4);
    unsigned windowStyle = sf::Style::Fullscreen;
    sf::Color backgroundColor = sf::Color::Black;
};
