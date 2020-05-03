#include <SFML/Graphics.hpp>
#include "include/Ray.h"
#include "include/Source.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Incandenza", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    std::vector<sf::Vertex> v0;
    v0.emplace_back(sf::Vector2f(250, 200));
    v0.emplace_back(sf::Vector2f(300, 250));
    v0.emplace_back(sf::Vector2f(250, 300));
    v0.emplace_back(sf::Vector2f(200, 250));
    inc::Quad quad0(v0, sf::Vector2f(250, 250));
    std::vector<sf::Vertex> v1;
    v1.emplace_back(sf::Vector2f(550, 430));
    v1.emplace_back(sf::Vector2f(600, 550));
    v1.emplace_back(sf::Vector2f(550, 600));
    v1.emplace_back(sf::Vector2f(350, 550));
    inc::Quad quad1(v1, sf::Vector2f(550, 550));
    std::vector<sf::Vertex> v2;
    v2.emplace_back(sf::Vector2f(440, 230));
    v2.emplace_back(sf::Vector2f(510, 252));
    v2.emplace_back(sf::Vector2f(450, 310));
    v2.emplace_back(sf::Vector2f(403, 252));
    inc::Quad quad2(v2, sf::Vector2f(450, 250));
    std::vector<sf::Vertex> v3;
    v3.emplace_back(sf::Vector2f(261, 500));
    v3.emplace_back(sf::Vector2f(312, 550));
    v3.emplace_back(sf::Vector2f(233, 600));
    v3.emplace_back(sf::Vector2f(112, 550));
    inc::Quad quad3(v3, sf::Vector2f(250, 520));

    quad1.setColor(sf::Color::Magenta);
    quad2.setColor(sf::Color::Blue);
    quad3.setColor(sf::Color::Red);

    std::vector<inc::Quad> shapes;
    shapes.emplace_back(quad0);
    shapes.emplace_back(quad1);
    shapes.emplace_back(quad2);
    shapes.emplace_back(quad3);

    inc::Source source(sf::Vector2f(100, 100), 42);
    inc::Ray ray;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            source.move(sf::Vector2f(-1, 0));
            ray = source.getRay(&shapes);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            source.move(sf::Vector2f(1, 0));
            ray = source.getRay(&shapes);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            source.move(sf::Vector2f(0, -1));
            ray = source.getRay(&shapes);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            source.move(sf::Vector2f(0, 1));
            ray = source.getRay(&shapes);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            sf::Vector2f sourcePosition = source.getPosition();
            float angle = atan((mousePosition.y - sourcePosition.y) / (mousePosition.x - sourcePosition.x)) / M_PI * 180;
            if (mousePosition.x < sourcePosition.x)
                angle += 180;
            if (angle < 0)
                angle += 360;
            else if (angle >= 360)
                angle -= 360;
            source.setAngle(angle);
            ray = source.getRay(&shapes);
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        ray.draw(&window);
        for (auto s : shapes)
            s.draw(&window);
        window.display();
    }

    return 0;
}