#ifndef SIM_UTIL_H
#define SIM_UTIL_H

#include <cmath>

// Forces double-type arguments
inline double sind(double theta)
{
    return std::sin(theta);
}

inline double cosd(double theta)
{
    return std::cos(theta);
}

inline double atan2d(double y, double x)
{
    return std::atan2(y, x);
}

inline double sqrtd(double val)
{
    return std::sqrt(val);
}

struct Position2d {
    float x_m;
    float y_m;
};

struct Position3d {
    float x_m;
    float y_m;
    float z_m;

    operator Position2d() const
    {
        return {x_m, y_m};
    }

    Position2d operator-(Position2d other) const
    {
        return {x_m - other.x_m, y_m - other.y_m};
    }
};

struct Velocity2d {
    float speed_mps;
    float course_rad;

    float x_mps() const
    {
        return speed_mps * sind(course_rad);
    }

    float y_mps() const
    {
        return speed_mps * cosd(course_rad);
    }

    Position2d operator*(double timestep) const
    {
        return {
            float(x_mps() * timestep),
            float(y_mps() * timestep)};
    }
};


inline Velocity2d operator-(Velocity2d x, Velocity2d y)
{
    float speed_mps = sqrtd(
        x.speed_mps * x.speed_mps
        + y.speed_mps * y.speed_mps
        - 2 * x.speed_mps * y.speed_mps * cosd(y.course_rad - x.course_rad)
    );
    float course_rad = x.course_rad + atan2d(
        -y.speed_mps * sind(
            y.course_rad - x.course_rad),
        x.speed_mps - y.speed_mps * cosd(
            y.course_rad - x.course_rad)
    );

    return {speed_mps, course_rad};
}

struct Velocity3d {
    float speed_mps;
    float course_rad;
    float pitch_rad;

    float z_mps() const
    {
        return speed_mps * sind(pitch_rad);
    }

    Velocity2d project() const
    {
        return {float(speed_mps * cosd(pitch_rad)), course_rad};
    }
};

#endif
