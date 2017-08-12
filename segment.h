#ifndef SEGMENT_H
#define SEGMENT_H

#include "datatypes.h"
#include "iostream"
#include "ostream"

class segment
{
public:
    segment();
    point p1;
    point p2;

    friend std::ostream& operator<<(std::ostream& os, const segment& seg);
};
#endif // SEGMENT_H
