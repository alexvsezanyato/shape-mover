#pragma once
#include <string>

class App {
public:
    std::string appName;
    void setAppName(std::string name);
    App() = delete;

protected:
    App(std::string name);

public:
    virtual void run() = 0;
    std::string getAppName();
};
