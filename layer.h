#ifndef LAYER_H
#define LAYER_H

#include <vector>

#include "datatypes.h"
#include "triangle.h"
#include "segment.h"

class layer
{
public:
    layer();
    float width;
    float height;
    std::vector<segment> contours;

    segment getCrossingSegment(triangle);
    std::vector<segment> getContour(std::vector<triangle> triangles);

};

#endif // LAYER_H
