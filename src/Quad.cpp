#include "../include/Quad.h"

inc::Quad::Quad(std::vector<sf::Vertex> vertices, sf::Vector2f origin) {
    polygon = vertices;
    this->origin = origin;
    sf::Vertex prev = polygon[polygon.size() - 1];
    for (int i = 0; i < vertices.size(); i++) {
        sf::Vertex curr = polygon[i];
        float x0 = prev.position.x;
        float y0 = prev.position.y;
        float x1 = curr.position.x;
        float y1 = curr.position.y;
        float a = (y1 - y0)/(x1 - x0);
        float b = y0 - a * x0;
        lineCoefficients.emplace_back(sf::Vector2f(a, b));
        float surfaceAngle = calculateSurfaceAngle(sf::Vector2f(a, b));
        surfaceAngles.emplace_back(surfaceAngle);
        prev = curr;
    }
    setColor(sf::Color(255, 255, 255));
}

void inc::Quad::draw(sf::RenderWindow* window) {
    window->draw(&polygon[0], polygon.size(), sf::Quads);
}

void inc::Quad::setColor(sf::Color color) {
    this->color = color;
    for (int i = 0; i < polygon.size(); i++)
        polygon[i].color = color;
}

sf::Color inc::Quad::getReflectedColor(sf::Color rayColor) {
    sf::Color reflectedColor;
    reflectedColor.r = rayColor.r > color.r ? color.r : rayColor.r;
    reflectedColor.g = rayColor.g > color.g ? color.g : rayColor.g;
    reflectedColor.b = rayColor.b > color.b ? color.b : rayColor.b;
    return reflectedColor;
}

bool inc::Quad::isCollision(sf::Vector2f point) {
    bool output = true;
    for(auto coeff : lineCoefficients) {
        if (!isLineCrossed(point, coeff.x, coeff.y))
            output = false;
    }
    return output;
}

bool inc::Quad::isLineCrossed(sf::Vector2f point, float a, float b) const {
    return (a * point.x + b - point.y) * (a * origin.x + b - origin.y) >= 0;
}

float inc::Quad::calculateSurfaceAngle(sf::Vector2f line) const {
    float a = -1 / line.x;
    float b = origin.y - a * origin.x;
    float w = -a + line.x;
    float wx = b - line.y;
    float wy = -a * line.y + b * line.x;
    sf::Vector2f point(wx/w, wy/w);
    float degrees = atan((origin.y - point.y) / (origin.x - point.x)) / M_PI * 180;
    if (degrees < 0)
        degrees += 360;
    return degrees;
}

float inc::Quad::getSurfaceAngle(sf::Vector2f prevPoint, sf::Vector2f point) {
    for (int i = 0; i < lineCoefficients.size(); i++) {
        if (isLineCrossed(prevPoint, lineCoefficients[i].x, lineCoefficients[i].y) != isLineCrossed(point, lineCoefficients[i].x, lineCoefficients[i].y))
            return surfaceAngles[i];
    }
}
