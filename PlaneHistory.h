#ifndef SIM_PLANE_HISTORY_H
#define SIM_PLANE_HISTORY_H

#include <array>
#include <cstddef>
#include <vector>

#include "Util.h"
#include "Plane.h"

// Forward declarations
class Renderer;

struct PlaneHistory
{
    struct HistoryLine
    {
        std::vector<Position2d> positions;

        void draw(Renderer& r) const;
    };

    std::array<HistoryLine, 9000> lines;
    std::size_t next = 0;
    std::size_t nplanes = 0;

    void addnew(const Plane p, const Velocity2d wind)
    {
        for (std::size_t i = 0; i < 9000; ++i) {
            auto groundvel = p.vel.project() - wind;
            auto newpos = p.pos - groundvel * (g_timestep * (9000 - i));
            lines[i].positions.push_back(newpos);
        }
        ++nplanes;
    }

    void advance()
    {
        next = (next + 1) % 9000;
    }

    void update(size_t plane, Position2d pos)
    {
        lines[next].positions[plane] = pos;
    }

    const HistoryLine& past(std::size_t steps)
    {
        std::size_t index = steps > next ? 9000 + next - steps : next - steps;
        return lines[index];
    }
};

#endif
