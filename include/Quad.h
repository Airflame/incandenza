#ifndef INCANDENZA_QUAD_H
#define INCANDENZA_QUAD_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace inc {
    class Quad {
    private:
        std::vector<sf::Vertex> polygon;
        std::vector<sf::Vector2f> lineCoefficients;
        std::vector<float> surfaceAngles;
        sf::Vector2f origin;
        bool isLineCrossed(sf::Vector2f point, float a, float b) const;
        float calculateSurfaceAngle(sf::Vector2f line) const;

    public:
        Quad(std::vector<sf::Vertex> vertices, sf::Vector2f origin);
        void draw(sf::RenderWindow* window);
        bool isCollision(sf::Vector2f point);
        float getSurfaceAngle(sf::Vector2f prevPoint, sf::Vector2f point);
    };
}

#endif //INCANDENZA_QUAD_H
