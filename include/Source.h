#ifndef INCANDENZA_SOURCE_H
#define INCANDENZA_SOURCE_H

#include <SFML/System.hpp>
#include "Ray.h"

namespace inc {
    class Source {
    private:
        inc::Ray ray;
        sf::Vector2f position;
        float angle;

    public:
        Source(sf::Vector2f position, float angle);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void setAngle(float angle);
        void move(sf::Vector2f velocity);
        void rotate(float rotation);
        inc::Ray getRay(std::vector<inc::Quad>* objects);
    };
}


#endif //INCANDENZA_SOURCE_H
