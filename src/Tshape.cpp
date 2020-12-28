#include "Tshape.hpp"
#include <iostream>

sf::Vector2u Tshape::computeSize(void) {
    sf::Vector2u size{0, 0};
    // ..
    for (auto i : this->basicShapes) {
        for (int j = i->getPointCount(); j >= 0; --j) {
            sf::Vector2f point = i->getPoint(j);
            sf::Vector2f position = i->getPosition();
            float width = point.x + position.x;
            float height = point.y + position.y;

            if (size.x < width) size.x = point.x + position.x;
            if (size.y < height) size.y = point.y + position.y;
        }
    }
    return size;
}
void Tshape::draw(sf::RenderWindow* w) {
    w->draw(this->sprite);
    return;
}
void Tshape::setPosition(float x, float y) {
    sf::Sprite* sprite = &this->sprite;
    sprite->setPosition(x, y);
    return;
}
void Tshape::setRotation(float angle) {
    sf::Sprite* sprite = &this->sprite;
    sprite->setRotation(angle);
    return;
}
sf::Vector2u Tshape::getSize() {
    sf::Vector2u textureSize = this->texture.getSize();
    unsigned width = textureSize.x;
    unsigned height = textureSize.y;
    return {width, height};
}
void Tshape::build(sf::ContextSettings contextSettings) {
    // texture size = combined shape size
    sf::Vector2u* size = &this->size;
    this->texture.create(size->x, size->y, contextSettings);
    // ..
    this->texture.clear(sf::Color::Transparent);
    for (auto i : this->basicShapes) this->texture.draw(*i);
    this->texture.display();
    this->texture.setSmooth(true);
    this->sprite.setTexture(this->texture.getTexture());
    return;
}
Tshape::Tshape(std::vector<TcreateShape> createShapes) {
    // from now on the class contains basic shapes
    std::vector<sf::Shape*> shapes = this->basicShapes;
    for (auto createShape : createShapes) shapes.push_back(createShape());
    // check basic shapes count
    // if (!shapes->size()) return;
    // compute combined shape size
    this->basicShapes = shapes;
    this->size = this->computeSize();
}
Tshape::~Tshape() {
    for (auto i : basicShapes) delete i;
    return;
}
