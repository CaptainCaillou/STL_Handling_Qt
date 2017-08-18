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
    float   width;
    float   height;
    std::vector<segment> contours;

    double getCrossingPointX(point p1, point p2, double yi);
    double getCrossingPointY(point p1, point p2, double yi);
    segment getCrossingSegment(triangle);
    void getContour(std::vector<triangle> triangles);
};

#endif // LAYER_H
