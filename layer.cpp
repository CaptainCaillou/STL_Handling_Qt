#include <vector>
#include <algorithm>

#include "layer.h"

layer::layer()
{

}

segment layer::getCrossingSegment(triangle tri){
    segment s;
    //If the triangle is too high or to low in the Z direction
    if((tri.getMaxZ().z < height) || (tri.getMinZ().z > (height + width)))
    {
        /* DEBUG PART
        std::cout << "(getMaxZ().z < lay.height)" << (getMaxZ().z < lay.height) << std::endl;
        std::cout << "(getMinZ().z > (lay.height + lay.width))" << (getMinZ().z > (lay.height + lay.width)) << std::endl;

        std::cout << "min       \tlayHeight \tHeight + Width \tmax" << std::endl;
        std::cout << getMinZ().z << "\t" << lay.height << "\t\t" << lay.height+ lay.width << "\t\t" << getMaxZ().z << std::endl;
        */
        return s;
    }
    s.p1.z = (height + width) / 2;
    s.p2.z = s.p1.z;
    double a;

    //if the plan is between P1 and P2
    if((tri.p1.z > s.p1.z && tri.p2.z < s.p1.z) || (tri.p1.z < s.p1.z && tri.p2.z > s.p1.z))
    {
        if(tri.p1.x == tri.p2.x)
            s.p1.x = tri.p1.x;
        else {
        a = (tri.p1.z - tri.p2.z) / (tri.p1.x - tri.p2.x);
        s.p1.x = a / s.p1.z;
        }
        if(tri.p1.y == tri.p2.y)
            s.p1.y = tri.p1.y;
        else
        {
        a = (tri.p1.z - tri.p2.z) / (tri.p1.y - tri.p2.y);
        s.p1.y = a / s.p1.z;
        }
        //if the plan in between P2 and P3
        if((tri.p2.z > s.p1.z && tri.p3.z < s.p1.z) || (tri.p2.z < s.p1.z && tri.p3.z > s.p1.z))
        {
            if(tri.p2.x == tri.p3.x)
                s.p2.x = tri.p2.x;
            else
            {
                a = (tri.p2.z - tri.p3.z) / (tri.p2.x - tri.p3.x);
                s.p2.x = a / s.p1.z;
            }
            if(tri.p2.y == tri.p3.y)
                s.p2.y = tri.p1.y;
            else
            {
                a = (tri.p2.z - tri.p3.z) / (tri.p2.y - tri.p3.y);
                s.p2.y = a / s.p1.z;
            }
        } else
        //if the plan in between P1 and P3
        if((tri.p1.z > s.p1.z && tri.p3.z < s.p1.z) || (tri.p1.z < s.p1.z && tri.p3.z > s.p1.z))
        {
            if(tri.p1.x == tri.p3.x)
                s.p2.x = tri.p1.x;
            else
            {
                a = (tri.p1.z - tri.p3.z) / (tri.p1.x - tri.p3.x);
                s.p2.x = a / s.p1.z;
            }
            if(tri.p1.y == tri.p3.y)
                s.p2.y = tri.p1.y;
            else
            {
            a = (tri.p1.z - tri.p3.z) / (tri.p1.y - tri.p3.y);
            s.p2.y = a / s.p1.z;
            }
        }
    } else {
        //the plan is between P1 and P3 + P2 and P3
        if(tri.p2.x == tri.p3.x)
            s.p1.x = tri.p2.x;
        else
        {
        a = (tri.p2.z - tri.p3.z) / (tri.p2.x - tri.p3.x);
        s.p1.x = a / s.p1.z;
        }
        if(tri.p2.y == tri.p3.y)
            s.p1.y = tri.p2.y;
        else
        {
        a = (tri.p2.z - tri.p3.z) / (tri.p2.y - tri.p3.y);
        s.p1.y = a / s.p1.z;
        }
        if(tri.p1.x == tri.p3.x)
            s.p2.x = tri.p1.x;
        else {
        a = (tri.p1.z - tri.p3.z) / (tri.p1.x - tri.p3.x);
        s.p2.x = a / s.p1.z;
        }
        if(tri.p1.y == tri.p3.y)
            s.p2.y = tri.p3.y;
        else {
        a = (tri.p1.z - tri.p3.z) / (tri.p1.y - tri.p3.y);
        s.p2.y = a / s.p1.z;
        }
    }
    return s;
}

std::vector<segment> layer::getContour(std::vector<triangle> triangles){

    std::vector<triangle>::iterator tri;
    for (tri = triangles.begin(); tri < triangles.end(); tri++)
    {
        contours.push_back(getCrossingSegment(*(tri.base())));
    }
    std::vector<segment> test;
    return test;
}
