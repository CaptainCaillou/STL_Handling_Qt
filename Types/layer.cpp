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
        std::cerr << "Error: Try to find an intercection between to non crossing parts" << std::endl;
    } else {
        return p1.x + (yi - p1.z) / (p2.z - p1.z) * (p2.x - p1.x);
    }
}

double layer::getCrossingPointY(point p1, point p2, double yi) {
    if(p1.y == p2.y) {
        return p1.y;
    } else if(p1.z == p2.z){
        std::cerr << "Error: Try to find an intercection between to non crossing parts" << std::endl;
    } else {
        return p1.y + (yi - p1.z) / (p2.z - p1.z) * (p2.y - p1.y);
    }
}

segment layer::getCrossingSegment(triangle tri){
    segment s;
    segment sNull;

    //If the triangle is too high or to low in the Z direction
    if((tri.getMaxZ().z < height) || (tri.getMinZ().z > (height + width)))
        return s;

    //If we are here, we have a segment to found
    s.isEmpty = false;

    // We put our Z level between the top and the bottom reference
    s.p1.z = height;//(height + width) / 2;
    s.p2.z = s.p1.z;

    //now we check if one of the point is exacly on the layer
    if(tri.p1.z == s.p1.z) {
        s.p1 = tri.p1;
        s.p1.where = 5;
        if(tri.p2.z == s.p2.z) {
            s.p2 = tri.p2;
            s.p2.where = 6;
            return s;
        }
        if(tri.p3.z == s.p1.z) {
            s.p2.x = tri.p3.x;
            s.p2.y = tri.p3.y;
            s.p2.where = 7;
            return s;
        }
    } else if(tri.p2.z == s.p1.z) {
        s.p1 = tri.p2;
        s.p1.where = 8;
        if(tri.p3.z == s.p1.z) {
            s.p2.x = tri.p3.x;
            s.p2.y = tri.p3.y;
            s.p2.where = 9;
            return s;
        }
    }/* else if(tri.p3.z == s.p1.z) {
        s.p1 = tri. p3;
        s.p1.where = 10;
    }*/
    s.p1.where = -5;
    s.p2.where = -5;
    //We are now searching for a crossing between [p1,p2] and our z plan
    bool p1_upper_p2_lower = ((tri.p1.z > s.p1.z) && (tri.p2.z < s.p1.z));
    bool p2_upper_p1_lower = ((tri.p2.z > s.p1.z) && (tri.p1.z < s.p1.z));
    if((p1_upper_p2_lower || p2_upper_p1_lower)) {
        if(tri.p1.z == tri.p2.z)
            return {};
        s.p1.where = 1;
        s.p1.x = getCrossingPointX(tri.p1,tri.p2,s.p1.z);
        s.p1.y = getCrossingPointY(tri.p1,tri.p2,s.p1.z);
        //if the plan in between P2 and P3
        bool p2_upper_p3_lower = ((tri.p2.z > s.p1.z) && (tri.p3.z < s.p1.z));
        bool p3_upper_p2_lower = ((tri.p3.z > s.p1.z) && (tri.p2.z < s.p1.z));
        if(p2_upper_p3_lower || p3_upper_p2_lower) {
            if(tri.p3.z == tri.p2.z)
                return {};
            s.p2.where = 2;
            s.p2.x = getCrossingPointX(tri.p2,tri.p3,s.p1.z);
            s.p2.y = getCrossingPointY(tri.p2,tri.p3,s.p1.z);
        } else {
            //if the plan in between P1 and P3
            bool p1_upper_p3_lower = ((tri.p1.z > s.p1.z) && (tri.p3.z < s.p1.z));
            bool p3_upper_p1_lower = ((tri.p3.z > s.p1.z) && (tri.p1.z < s.p1.z));
            if(p1_upper_p3_lower || p3_upper_p1_lower) {
                if(tri.p1.z == tri.p3.z)
                    return {};
                s.p2.where = 3;
                s.p2.x = getCrossingPointX(tri.p1,tri.p3,s.p1.z);
                s.p2.y = getCrossingPointY(tri.p1,tri.p3,s.p1.z);
            }
        }
    } else {
        //the plan is between P1 and P3 + P2 and P3
        bool p2_upper_p3_lower = ((tri.p2.z > s.p1.z) && (tri.p3.z < s.p1.z));
        bool p3_upper_p2_lower = ((tri.p3.z > s.p1.z) && (tri.p2.z < s.p1.z));
        if(p2_upper_p3_lower || p3_upper_p2_lower) {
            if(tri.p2.z == tri.p3.z)
                return {};
            s.p1.where = 4;
            s.p1.x = getCrossingPointX(tri.p3,tri.p2,s.p1.z);
            s.p1.y = getCrossingPointY(tri.p3,tri.p2,s.p1.z);
        }
        bool p1_upper_p3_lower = ((tri.p1.z > s.p1.z) && (tri.p3.z < s.p1.z));
        bool p3_upper_p1_lower = ((tri.p3.z > s.p1.z) && (tri.p1.z < s.p1.z));
        if(p1_upper_p3_lower || p3_upper_p1_lower) {
            if(tri.p1.z == tri.p3.z)
                return {};
            s.p2.where = 4;
            s.p2.x = getCrossingPointX(tri.p1,tri.p3,s.p1.z);
            s.p2.y = getCrossingPointY(tri.p1,tri.p3,s.p1.z);
        }

        //somewhere, something went wrong, this segment is not valid
        if(s.p1.where == -5 || s.p2.where == -5)
            return{};
    }
    return s;
}

void layer::getContour(std::vector<triangle> triangles){
    //std::cout << "layer::getContour" << std::endl;

    for (unsigned int i = 0 ; i < triangles.size() ; i++) {
        segment seg = getCrossingSegment(triangles[i]);
        if(!seg.isEmpty)
        {
          /*
            printf("Triangle :\n1 : x %4.4g y %4.4g z %4.4g\n2 : x %4.4g y %4.4g z %4.4g\n3 : x %4.4g y %4.4g z %4.4g\nSegment :\n1 : x %4.4g y %4.4g z %4.4g w %4d\n2 : x %4.4g y %4.4g z %4.4g w %4d\n\n",
                  triangles[i].p1.x, triangles[i].p1.y, triangles[i].p1.z,
                  triangles[i].p2.x, triangles[i].p2.y, triangles[i].p2.z,
                  triangles[i].p3.x, triangles[i].p3.y, triangles[i].p3.z,
                  seg.p1.x, seg.p1.y, seg.p1.z, seg.p1.where,
                  seg.p2.x, seg.p2.y, seg.p2.z, seg.p2.where
                   );
          */
            contours.push_back(seg);
        }
    }
    //std::cout << contours.size() << std::endl;
}
