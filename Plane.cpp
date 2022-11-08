#include "Plane.h"
#include "Renderer.h"

void Plane::draw(Renderer& r, Velocity2d wind) const
{
    r.drawPlane(*this, vel.project() - wind);
}
