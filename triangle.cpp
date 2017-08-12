#include "triangle.h"
#include "segment.h"

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

segment triangle::getCrossingSegment(layer lay){
    segment s;
    //If the triangle is too high or to low in the Z direction
    if((getMaxZ().z < lay.height) || (getMinZ().z > (lay.height + lay.width)))
    {
        /* DEBUG PART
        std::cout << "(getMaxZ().z < lay.height)" << (getMaxZ().z < lay.height) << std::endl;
        std::cout << "(getMinZ().z > (lay.height + lay.width))" << (getMinZ().z > (lay.height + lay.width)) << std::endl;

        std::cout << "min       \tlayHeight \tHeight + Width \tmax" << std::endl;
        std::cout << getMinZ().z << "\t" << lay.height << "\t\t" << lay.height+ lay.width << "\t\t" << getMaxZ().z << std::endl;
        */
        return s;
    }
    s.p1.z = (lay.height + lay.width) / 2;
    s.p2.z = s.p1.z;
    double a;

    //if the plan is between P1 and P2
    if((p1.z > s.p1.z && p2.z < s.p1.z) || (p1.z < s.p1.z && p2.z > s.p1.z))
    {
        if(p1.x == p2.x)
            s.p1.x = p1.x;
        else {
        a = (p1.z - p2.z) / (p1.x - p2.x);
        s.p1.x = a / s.p1.z;
        }
        if(p1.y == p2.y)
            s.p1.y = p1.y;
        else
        {
        a = (p1.z - p2.z) / (p1.y - p2.y);
        s.p1.y = a / s.p1.z;
        }
        //if the plan in between P2 and P3
        if((p2.z > s.p1.z && p3.z < s.p1.z) || (p2.z < s.p1.z && p3.z > s.p1.z))
        {
            if(p2.x == p3.x)
                s.p2.x = p2.x;
            else
            {
                a = (p2.z - p3.z) / (p2.x - p3.x);
                s.p2.x = a / s.p1.z;
            }
            if(p2.y == p3.y)
                s.p2.y = p1.y;
            else
            {
                a = (p2.z - p3.z) / (p2.y - p3.y);
                s.p2.y = a / s.p1.z;
            }
        } else
        //if the plan in between P1 and P3
        if((p1.z > s.p1.z && p3.z < s.p1.z) || (p1.z < s.p1.z && p3.z > s.p1.z))
        {
            if(p1.x == p3.x)
                s.p2.x = p1.x;
            else
            {
                a = (p1.z - p3.z) / (p1.x - p3.x);
                s.p2.x = a / s.p1.z;
            }
            if(p1.y == p3.y)
                s.p2.y = p1.y;
            else
            {
            a = (p1.z - p3.z) / (p1.y - p3.y);
            s.p2.y = a / s.p1.z;
            }
        }
    } else {
        //the plan is between P1 and P3 + P2 and P3
        if(p2.x == p3.x)
            s.p1.x = p2.x;
        else
        {
        a = (p2.z - p3.z) / (p2.x - p3.x);
        s.p1.x = a / s.p1.z;
        }
        if(p2.y == p3.y)
            s.p1.y = p2.y;
        else
        {
        a = (p2.z - p3.z) / (p2.y - p3.y);
        s.p1.y = a / s.p1.z;
        }
        if(p1.x == p3.x)
            s.p2.x = p1.x;
        else {
        a = (p1.z - p3.z) / (p1.x - p3.x);
        s.p2.x = a / s.p1.z;
        }
        if(p1.y == p3.y)
            s.p2.y = p3.y;
        else {
        a = (p1.z - p3.z) / (p1.y - p3.y);
        s.p2.y = a / s.p1.z;
        }
    }
    return s;
}
