#ifndef INCANDENZA_RAY_H
#define INCANDENZA_RAY_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Quad.h"

namespace inc {
    class Ray {
    private:
        std::vector<sf::Vertex> vertices;

    public:
        Ray();
        void draw(sf::RenderWindow* window);
        void calculate(sf::Vector2f point, float initialDegrees, std::vector<inc::Quad>* shapes);
    };
}


#endif //INCANDENZA_RAY_H
