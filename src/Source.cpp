#include "../include/Source.h"

inc::Source::Source(sf::Vector2f position, float angle) {
    this->position = position;
    this->angle = angle;
}

void inc::Source::setPosition(sf::Vector2f position) {
    this->position = position;
}

void inc::Source::setAngle(float angle) {
    this->angle = angle;
}

sf::Vector2f inc::Source::getPosition() {
    return position;
}

void inc::Source::move(sf::Vector2f velocity) {
    position = sf::Vector2f(position.x + velocity.x, position.y + velocity.y);
}

void inc::Source::rotate(float rotation) {
    angle += rotation;
    if (angle < 0)
        angle += 360;
    else if (angle >= 360)
        angle -= 360;
}

inc::Ray inc::Source::getRay(std::vector<inc::Quad> *objects) {
    ray.calculate(position, angle, objects);
    return ray;
}




