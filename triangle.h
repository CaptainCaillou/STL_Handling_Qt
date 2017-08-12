#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "datatypes.h"
#include "segment.h"
#include "layer.h"
class triangle
{
public:
    triangle();
    int id;
    point p1;
    point p2;
    point p3;
    point getMinX(void);
    point getMinY(void);
    point getMinZ(void);
    point getMaxX(void);
    point getMaxY(void);
    point getMaxZ(void);
    segment getCrossingSegment(layer);
};

#endif // TRIANGLE_H
