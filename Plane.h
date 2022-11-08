#ifndef SIM_PLANE_H
#define SIM_PLANE_H

#include <cstddef>

#include "Globals.h"
#include "Util.h"

// Forward declaration
class Renderer;

struct Plane
{
    Position3d pos;
    Velocity3d vel;

    void step(Velocity2d wind)
    {
        auto groundvel = vel.project() - wind;
        pos.x_m += groundvel.x_mps() * g_timestep;
        pos.y_m += groundvel.y_mps() * g_timestep;
        pos.z_m += vel.z_mps() * g_timestep; // Assume no vertical winds
    }

    void draw(Renderer& r, Velocity2d wind) const;
};

#endif
