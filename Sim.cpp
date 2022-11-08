#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Plane.h"
#include "PlaneHistory.h"
#include "Renderer.h"

inline constexpr Velocity2d g_wind = {20, 1};

int main()
{
    // Create the rendering subsystem
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(g_screensize, g_screensize), "Plane Sim", sf::Style::Default, settings);

    // Some planes for testing
    std::vector<Plane> planes;
    planes.push_back({
        {-10000, 0, 1524},
        {100, 0, 0.1}
    });
    planes.push_back({
        {5000, 2560, 1524},
        {100, 1.571, -0.1}
    });
    planes.push_back({
        {1000, 4500, 1524},
        {100, 3.142, 0}
    });
    planes.push_back({
        {-4000, -300, 1524},
        {100, 4.712, 0.03}
    });

    // Insert back-stepped previous positions for planes
    PlaneHistory history;
    for (const auto& p: planes) {
        history.addnew(p, g_wind);
    }

    Renderer renderer(window);
    using hrc = std::chrono::high_resolution_clock;

    while (window.isOpen()) {
        // Record frame time for sleeping later
        auto frame_start = hrc::now();

        // Read input
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Process state update
        for (size_t j = 0; j < planes.size(); ++j) {
            auto& p = planes[j];

            // Apply speed timestep
            p.step(g_wind);
            history.update(j, p.pos);
        }
        history.advance();

        // Draw screen
        {
            // RAII - make sure we draw when done
            auto txn = RenderTransaction(renderer);

            // Show the current position of each plane
            for (const auto& p: planes) {
                p.draw(renderer, g_wind);
            }

            // Sample history in 30-second steps to draw "trail"
            for (int i = 0; i < 5; i++) {
                const auto& line = history.past(i * 1800);
                line.draw(renderer);
            }
        }

        using namespace std::chrono_literals;
        std::this_thread::sleep_until(frame_start + 10ms);
    }
}
