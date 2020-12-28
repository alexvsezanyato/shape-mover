#include "WinApp.hpp"
#include <iostream>

sf::VideoMode WinApp::getVideoMode() { return windowSettings.videoMode; }
unsigned WinApp::getWindowStyle() { return windowSettings.windowStyle; }

void WinApp::render() {
    this->window.create(
        windowSettings.videoMode,
        this->getAppName(),
        windowSettings.windowStyle,
        windowSettings.contextSettings
    );
}

sf::Vector2u WinApp::getSize() {
    sf::VideoMode* videoMode = &windowSettings.videoMode;
    auto width = videoMode->width;
    auto height = videoMode->height;
    return {width, height};
}

void WinApp::setSettings(WinSettings settings) {
    this->windowSettings = settings;
    return;
}

bool WinApp::isWindowed() {
    auto style = windowSettings.windowStyle;
    using sf::Style::Fullscreen;
    if (style != Fullscreen) return true;
    else return false;
}

WinApp::WinApp(std::string name, WinSettings settings) :
App(name),
windowSettings(settings)
{ ; }

WinApp::WinApp(std::string name) :
App(name)
{ ; }
