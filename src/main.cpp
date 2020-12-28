#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Tshape.hpp"
#include "TshapeMover.hpp"
#include <iostream>

using sf::Color;
// shapes available
using Rectangle = sf::RectangleShape;
using Circle = sf::CircleShape;
using Convex = sf::ConvexShape;

int main(void) {
    Tshape shape({
        [] {
            auto rectangle = new Rectangle({100.f, 40.f});
            rectangle->setFillColor(Color(34, 167, 240));
            rectangle->setPosition(0.f, 0.f);
            return rectangle;
        },

        [] {
            auto rectangle = new Rectangle({100.f, 40.f});
            rectangle->setFillColor(Color(34, 167, 240));
            rectangle->setPosition(0.f, 110.f);
            return rectangle;
        },

        [] {
            auto circle = new Circle(60.f, 300);
            circle->setFillColor(Color(228, 241, 254));
            circle->setPosition(80.f, 15.f);
            return circle;
        },

        [] {
            auto triangle = new Convex(3);
            triangle->setFillColor(Color(197, 239, 247));
            triangle->setPoint(0, { 0.f, 0.f });
            triangle->setPoint(1, { 0.f, 150.f });
            triangle->setPoint(2, { 80.f, 0.5f * 150.f });
            triangle->setPosition(200.f, 0.f);
            return triangle;
        },
    });

    TshapeMover::Settings set;
    set.backgroundColor = Color(1, 50, 67, 1); // rgba
    set.isWindowed = true;
    set.windowSize = {800, 600};

    TshapeMover app(&set, &shape);
    app.run();
    return 0;
}
