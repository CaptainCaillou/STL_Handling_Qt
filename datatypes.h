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

#endif // DATATYPES_H
