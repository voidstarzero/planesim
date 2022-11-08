#ifndef SIM_RENDERER_H
#define SIM_RENDERER_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Util.h"

// Forward declarations
struct Plane;

class Renderer
{
public:
    explicit Renderer(sf::RenderWindow& window);

    void begin();

    void drawPlane(const Plane& p, Velocity2d groundvel);
    void drawSmallCircle(Position2d pos);

    void commit();

private:
    sf::RenderWindow& window;
    std::vector<sf::CircleShape> rings;
};

class RenderTransaction
{
public:
    explicit RenderTransaction(Renderer& r)
    : guarded{r}
    {
        guarded.begin();
    }

    ~RenderTransaction()
    {
        guarded.commit();
    }

private:
    Renderer& guarded;
};

#endif
