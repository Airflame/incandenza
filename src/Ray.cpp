#include "../include/Ray.h"

inc::Ray::Ray() {

}

void inc::Ray::draw(sf::RenderWindow* window) {
    window->draw(&vertices[0], vertices.size(), sf::LineStrip);
}

void inc::Ray::calculate(sf::Vector2f point, float initialDegrees, std::vector<inc::Quad>* shapes) {
    vertices.clear();
    float angle = initialDegrees;
    std::vector<inc::Quad>* objects = shapes;
    float rad, dx, dy;
    sf::Vector2f prevPoint;
    vertices.emplace_back(point);
    for (int i = 0; i < 20; i++) {
        bool notCollided = true;
        rad = angle / 180.f * M_PI;
        dx = cos(rad) / 10;
        dy = sin(rad) / 10;
        prevPoint = point;
        point.x += dx;
        point.y += dy;
        while (notCollided) {
            for (auto & object : *objects) {
                if (object.isCollision(point)) {
                    float surfAngle = object.getSurfaceAngle(prevPoint, point);
                    angle += 2 * (surfAngle - angle);
                    if (angle < 0)
                        angle += 360;
                    else if (angle > 360)
                        angle -= 360;
                    angle += 180;
                    if (angle > 360)
                        angle -= 360;
                    notCollided = false;
                    vertices.emplace_back(point);
                    rad = angle / 180.f * M_PI;
                    dx = cos(rad) / 10;
                    dy = sin(rad) / 10;
                    while (object.isCollision(point)) {
                        prevPoint = point;
                        point.x += dx;
                        point.y += dy;
                    }
                    break;
                }
            }
            if (point.x <= 0 or point.x > 800 or point.y <= 0 or point.y > 800) {
                vertices.emplace_back(point);
                break;
            }
            prevPoint = point;
            point.x = point.x += dx;
            point.y = point.y += dy;
        }
    }
}
