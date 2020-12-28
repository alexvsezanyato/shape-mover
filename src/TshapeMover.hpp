#pragma once

#include "WinApp.hpp"
#include "WinSettings.hpp"
#include "Tshape.hpp"
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>


//
// ::TshapeMover

class TshapeMover : public WinApp {
public:
    class Subwindow;
    struct Settings;

private:
    Tshape* shape;
    // bool isMoving = true;
    TshapeMover();
    Settings* settings;
    void setupSettings();
    void setupSettings(Settings*);

public:
    void handleKeyboardEvent(sf::Event* event);
    void handleEvent(sf::Event* event);
    void handleSettings(Settings*);
    void checkEvents();
    bool redraw(Subwindow* subwindow, float t);
    void run() override;
    void shutDown(void);
    TshapeMover(Settings* settings, Tshape* shape);
};


//
// ::TshapeMover::Settings

struct TshapeMover::Settings {
public:
    sf::Color backgroundColor = sf::Color::Black;
    sf::Vector2u windowSize = {800, 600};
    bool isWindowed = false;
};


//
// ::TshapeMover::Subwindow

class TshapeMover::Subwindow {
private:
    sf::Vector2u subwindowSize;
    sf::Vector2u windowSize;
    sf::Vector2u translation = {0, 0};

public:
    Subwindow(sf::Vector2u windowSize);
    bool translate(sf::Vector2u translation);
    sf::Vector2f getPosition(sf::Vector2f coords);
    bool isOutside(sf::Vector2f coords);
    bool setSize(sf::Vector2u size);
    sf::Vector2u getSize(void);
};
