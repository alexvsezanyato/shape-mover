#include "TshapeMover.hpp"


//
// ::TshapeMover::subwindow

bool TshapeMover::Subwindow::translate(sf::Vector2u translation) {
    if (translation.x + subwindowSize.x > windowSize.x) return false;
    if (translation.y + subwindowSize.y > windowSize.y) return false;
    this->translation = translation;
    return true;
}
sf::Vector2f TshapeMover::Subwindow::getPosition(sf::Vector2f coords) {
    float x, y;
    x = coords.x + (float) translation.x;
    y = coords.y + (float) translation.y;
    return {x, y};
}
bool TshapeMover::Subwindow::isOutside(sf::Vector2f coords) {
    // case 1
    sf::Vector2u max;
    max.x = subwindowSize.x + translation.x;
    max.y = subwindowSize.y + translation.y;
    if ((int) coords.x > max.x) return true;
    if ((int) coords.y > max.y) return true;
    // case 2
    sf::Vector2u min;
    min.x = translation.x;
    min.y = translation.y;
    if ((int) coords.x < min.x) return true;
    if ((int) coords.y < min.y) return true;
    // if not outside
    return false;
}
bool TshapeMover::Subwindow::setSize(sf::Vector2u size) {
    sf::Vector2u* windowSize = &this->windowSize;
    // if new size is larger than allowed
    if (size.x > windowSize->x) return false;
    if (size.y > windowSize->y) return false;
    // if new size is valid
    this->subwindowSize = size;
    return true;
}
sf::Vector2u TshapeMover::Subwindow::getSize(void) {
    sf::Vector2u* subwindowSize = &this->subwindowSize;
    unsigned width = subwindowSize->x;
    unsigned height = subwindowSize->y;
    return {width, height};
}
TshapeMover::Subwindow::Subwindow(sf::Vector2u windowSize) {
    // constructor be waiting of the real window size
    this->windowSize = windowSize;
    // as default, this constructor sets its own size = the real one
    this->subwindowSize = this->windowSize;
}


//
// ::TshapeMover

void TshapeMover::shutDown(void) {
    sf::Window* w = &this->window;
    w->close();
    return;
}

void TshapeMover::handleKeyboardEvent(sf::Event* event) {
    switch ((*event).key.code) {
        case sf::Keyboard::Escape: {
            this->shutDown();
            break;
        }
    }
}

void TshapeMover::handleEvent(sf::Event* event) {
    switch (event->type) {
        case sf::Event::Closed: {
            this->shutDown();
            break;
        }
        case sf::Event::KeyPressed: {
            this->handleKeyboardEvent(event);
            break;
        }
    }
}

void TshapeMover::checkEvents(void) {
    sf::Event event;
    sf::Window* w = &this->window;
    while (w->pollEvent(event)) this->handleEvent(&event);
    return;
}

bool TshapeMover::redraw(Subwindow* subwindow, float t) {
    // x must = y at the moment
    unsigned size = subwindow->getSize().x;
    // radius
    float r;
    r = size * 0.5f;
    // center (x0, y0)
    float x0, y0;
    x0 = subwindow->getPosition({r, r}).x;
    y0 = subwindow->getPosition({r, r}).y;
    // current position
    float x, y;
    x = x0 + r * cos(t);
    y = y0 + r * sin(t);

    sf::RenderWindow* w = &this->window;
    Tshape* shape = this->shape;
    w->clear(windowSettings.backgroundColor);
    shape->setRotation(t * 57.2958f + 90.f);
    shape->setPosition(x, y);
    shape->draw(w);
    w->display();
    return true;
}

void TshapeMover::run() {
    // prepare & render a window
    // there're default settings,
    // so from now on, you shouldn't care about setting this
    // but you can if you want
    this->setupSettings(this->settings);
    this->render();
    // shape has basic sfml shapes now,
    // it must create a sprite
    // a sprite has its own context settings,
    // so you must pass the settings to it
    // don't forget about building your shape, please!
    shape->build(windowSettings.contextSettings);
    sf::RenderWindow* w = &this->window;

    sf::Vector2u windowSize = this->getSize();
    Subwindow subwindow(windowSize);
    unsigned width, height;
    width = windowSize.x;
    height = windowSize.y;
    // take shape size into account
    // sf::Vector2u shapeSize = this->shape->getSize();
    // unsigned width, height;
    // width = windowSize.x - shapeSize.x;
    // height = windowSize.y - shapeSize.y;
    // square size for circle movement
    unsigned squaredSize;
    if (width > height) squaredSize = height;
    else squaredSize = width;
    subwindow.setSize({ squaredSize, squaredSize });
    // center subwindow
    unsigned translation = (windowSize.x - squaredSize) * 0.5f; // - shapeSize.x * 0.5f;
    subwindow.translate({ translation, 0 });
    sf::Clock clock;
    // warning! the speed does not change now
    // it wont do any speed change
    // your default speed value
    float speed = 0.5f;
    // if you wanna change the speed
    float maxSpeed = 2.f;
    // the angle changes by the step
    float step = .003f;

    while (w->isOpen()) {
        for (float i = -3.14f; i <= 3.14f; ) {
            // system checks
            if (!w->isOpen()) break;
            checkEvents();
            // time check
            sf::Time time = clock.getElapsedTime();
            if (time.asMicroseconds() < 5000.f) continue;
            // next step, redraw
            this->redraw(&subwindow, i);
            i += step;
            clock.restart();
        }
    }
}

void TshapeMover::handleSettings(TshapeMover::Settings* settings) {
    WinSettings* set = &this->windowSettings;
    set->backgroundColor = settings->backgroundColor;
    if (settings->isWindowed) set->windowStyle = sf::Style::Close;
    else set->windowStyle = sf::Style::Fullscreen;

    if (!settings->isWindowed) return;
    sf::Vector2u size = settings->windowSize;
    set->videoMode.width = size.x;
    set->videoMode.height = size.y;
    return;
}

void TshapeMover::setupSettings(TshapeMover::Settings* settings) {
    TshapeMover::setupSettings();
    handleSettings(settings);
    return;
}

void TshapeMover::setupSettings() {
    WinSettings* ws = &this->windowSettings;
    ws->contextSettings = sf::ContextSettings(0, 0, 16);
    return;
}

TshapeMover::TshapeMover(TshapeMover::Settings* settings, Tshape* shape) :
WinApp("Shape mover!"),
shape(shape),
settings(settings)
{ ; }
