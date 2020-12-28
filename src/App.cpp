#include "App.hpp"

void App::setAppName(std::string name) { this->appName = name; }
std::string App::getAppName() { return this->appName; }
App::App(std::string name) { this->setAppName(name); }
