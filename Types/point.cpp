#include "point.h"

point::point()
{

}

QVector3D point::to3dVector()
{
  return QVector3D(x, y, z);
}
