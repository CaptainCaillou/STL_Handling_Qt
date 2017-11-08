#ifndef DATATYPES_H
#define DATATYPES_H
#include "iostream"

struct point{
    double x;
    double y;
    double z;
    int where; //for debugging, we are searching where the point has been modified
};

struct vect3d{
    point origin;
    double cx;
    double cy;
    double cz;
};


#endif // DATATYPES_H
