#pragma once

#include <vector>
#include <utility>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>

class Tshape {
    using TcreateShape = std::function <sf::Shape*()>;
    using BasicShape = sf::Shape;

private:
    sf::RenderTexture texture;
    sf::Sprite sprite;
    sf::Vector2u size = {0, 0};
    std::vector<BasicShape*> basicShapes;
    sf::Vector2u computeSize();

public:
    sf::Vector2u getSize();
    void draw(sf::RenderWindow* w);
    void setPosition(float x, float y);
    void setRotation(float angle);
    void build(sf::ContextSettings);
    Tshape(std::vector<TcreateShape>);
    ~Tshape();
};
