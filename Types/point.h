#ifndef POINT_H
#define POINT_H

#include "QVector3D"

class point
{
public:
  point();
  double x;
  double y;
  double z;
  int where; //for debugging, we are searching where the point has been modified
  QVector3D to3dVector();
};

#endif // POINT_H
