#include "PlaneHistory.h"
#include "Renderer.h"

void PlaneHistory::HistoryLine::draw(Renderer& r) const
{
    for (const auto& pos: positions) {
        r.drawSmallCircle(pos);
    }
}
