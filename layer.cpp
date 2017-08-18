#include <vector>
#include <algorithm>

#include "layer.h"

layer::layer() {
    height = 0;
}

double layer::getCrossingPointX(point p1, point p2, double yi) {
    if(p1.x == p2.x) {
        return p1.x;
    } else if(p1.z == p2.z){
        return p1.x;
    } else {
        return yi * ((p2.x - p1.x) / (p2.z - p1.z));
    }
}

double layer::getCrossingPointY(point p1, point p2, double yi) {
    if(p1.y == p2.y) {
        return p1.y;
    } else if(p1.z == p2.z){
        return p1.y;
    } else {
        return yi * ((p2.y - p1.y) / (p2.z - p1.z));
    }
}

segment layer::getCrossingSegment(triangle tri){
    segment s;
    //If the triangle is too high or to low in the Z direction
    if((tri.getMaxZ().z < height) || (tri.getMinZ().z > (height + width)))
        return s;

    //If we are here, we have a segment to found
    s.isEmpty = false;

    // We put our Z level between the top and the bottom reference
    s.p1.z = height;//(height + width) / 2;
    s.p2.z = s.p1.z;

    //We are now searching for a crossing between [p1,p2] and our z plan
    bool p1_upper_p2_lower = ((tri.p1.z > s.p1.z) && (tri.p2.z < s.p1.z));
    bool p2_upper_p1_lower = ((tri.p2.z > s.p1.z) && (tri.p1.z < s.p1.z));
    if(p1_upper_p2_lower || p2_upper_p1_lower) {
        s.p1.x = getCrossingPointX(tri.p1,tri.p2,s.p1.z);
        s.p1.y = getCrossingPointY(tri.p1,tri.p2,s.p1.z);
        //if the plan in between P2 and P3
        bool p2_upper_p3_lower = ((tri.p2.z > s.p1.z) && (tri.p3.z < s.p1.z));
        bool p3_upper_p2_lower = ((tri.p3.z > s.p1.z) && (tri.p2.z < s.p1.z));
        if(p2_upper_p3_lower || p3_upper_p2_lower) {
            s.p2.x = getCrossingPointX(tri.p2,tri.p3,s.p1.z);
            s.p2.y = getCrossingPointY(tri.p2,tri.p3,s.p1.z);
        } else {
            //if the plan in between P1 and P3
            bool p1_upper_p3_lower = ((tri.p1.z > s.p1.z) && (tri.p3.z < s.p1.z));
            bool p3_upper_p1_lower = ((tri.p3.z > s.p1.z) && (tri.p1.z < s.p1.z));
            if(p1_upper_p3_lower || p3_upper_p1_lower) {
                s.p2.x = getCrossingPointX(tri.p1,tri.p3,s.p1.z);
                s.p2.y = getCrossingPointY(tri.p1,tri.p3,s.p1.z);
            }
        }
    } else {
        //the plan is between P1 and P3 + P2 and P3
        s.p1.x = getCrossingPointX(tri.p2,tri.p3,s.p1.z);
        s.p1.y = getCrossingPointY(tri.p2,tri.p3,s.p1.z);

        s.p2.x = getCrossingPointX(tri.p1,tri.p3,s.p1.z);
        s.p2.y = getCrossingPointY(tri.p1,tri.p3,s.p1.z);
    }
    return s;
}

void layer::getContour(std::vector<triangle> triangles){
    std::cout << "layer::getContour" << std::endl;
    for (unsigned int i = 0 ; i < triangles.size() ; i++) {
        segment seg = getCrossingSegment(triangles[i]);
        if(!seg.isEmpty)
        {
            std::cout << "x "  << seg.p1.x;
            std::cout << " y " << seg.p1.y;
            std::cout << " z " << seg.p1.z  << std::endl;
            std::cout << "x "  << seg.p2.x;
            std::cout << " y " << seg.p2.y;
            std::cout << " z " << seg.p2.z  << std::endl;
            contours.push_back(seg);
        }
    }
    std::cout << contours.size() << std::endl;
}
