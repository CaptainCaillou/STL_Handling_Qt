#include "triangle.h"

#include "segment.h"
#include "layer.h"

#include <iostream>
triangle::triangle()
{
    id = 0;
}

point triangle::getMinX(void){
    if(p1.x < p2.x && p1.x < p3.x)
        return p1;
    else if(p2.x < p3.x)
        return p2;
    else
        return p3;
}

point triangle::getMinY(void){
    if(p1.y < p2.y && p1.y < p3.y)
        return p1;
    else if(p2.y < p3.y)
        return p2;
    else
        return p3;
}

point triangle::getMinZ(void){
    if(p1.z < p2.z && p1.z < p3.z)
        return p1;
    else if(p2.z < p3.z)
        return p2;
    else
        return p3;
}
point triangle::getMaxX(void){
    if(p1.x > p2.x && p1.x > p3.x)
        return p1;
    else if(p2.x < p3.x)
        return p2;
    else
        return p3;
}

point triangle::getMaxY(void){
    if(p1.y > p2.y && p1.y > p3.y)
        return p1;
    else if(p2.y > p3.y)
        return p2;
    else
        return p3;
}

point triangle::getMaxZ(void){
    if(p1.z > p2.z && p1.z > p3.z)
        return p1;
    else if(p2.z > p3.z)
        return p2;
    else
        return p3;
}
