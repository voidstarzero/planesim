#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Util.h"
#include "Plane.h"
#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window)
: window{window}
{
    // Make static rings every 5 nm
    for (float rad = 10 * 1852.0; rad / 185.2 < g_screensize / std::sqrt(2); rad += 10 * 1852.0) {
        rings.emplace_back(rad / 185.2 + 1, rad / 185.2 + 1);
        sf::CircleShape& ring = rings.back();

        ring.setOutlineColor(sf::Color::White);
        ring.setOutlineThickness(1.f);
        ring.setFillColor(sf::Color::Transparent);
        ring.setOrigin(rad / 185.2 , rad / 185.2);
        ring.setPosition(g_screensize / 2, g_screensize / 2);
    }
}

void Renderer::begin()
{
    window.clear();

    // Draw the background rings
    for (auto& ring: rings) {
        window.draw(ring);
    }
}

void Renderer::drawPlane(const Plane& p, Velocity2d groundvel)
{
    sf::CircleShape circle(5.f);
    circle.setOutlineColor(sf::Color::Green);
    circle.setOutlineThickness(2.f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOrigin(5.f, 5.f);
    circle.setPosition((g_screensize / 2) + p.pos.x_m / 185.2, (g_screensize / 2) - p.pos.y_m / 185.2);
    window.draw(circle);

    sf::RectangleShape arrow({float(groundvel.speed_mps / 6.173), 0});
    arrow.setOutlineColor(sf::Color::Green);
    arrow.setOutlineThickness(1.f);
    arrow.setFillColor(sf::Color::Transparent);
    arrow.setPosition((g_screensize / 2) + p.pos.x_m / 185.2, (g_screensize / 2) - p.pos.y_m / 185.2);
    arrow.setRotation(groundvel.course_rad * (180 / M_PI) - 90);
    window.draw(arrow);
}

void Renderer::drawSmallCircle(Position2d pos)
{
    sf::CircleShape circle(1.f);
    circle.setOutlineColor(sf::Color::Green);
    circle.setOutlineThickness(1.f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOrigin(1.f, 1.f);
    circle.setPosition((g_screensize / 2) + pos.x_m / 185.2, (g_screensize / 2) - pos.y_m / 185.2);
    window.draw(circle);
}

void Renderer::commit()
{
    window.display();
}
