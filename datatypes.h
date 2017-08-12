#ifndef DATATYPES_H
#define DATATYPES_H

struct point{
    double x;
    double y;
    double z;
};

struct vect3d{
    point origin;
    double cx;
    double cy;
    double cz;
};

struct reference{
    vect3d ux;
    vect3d uy;
    vect3d uz;
};

#endif // DATATYPES_H
