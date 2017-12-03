#ifndef PART_H
#define PART_H

#include "triangle.h"
#include "layer.h"

class part
{
private:
  std::vector<triangle> triangles;
  std::vector<layer> layers;
  double height;

public:
  part();
  void setTriangles(std::vector<triangle>);
  std::vector<triangle> getTriangles(void);
  void setLayers(std::vector<layer>);
  std::vector<layer> getLayers(void);
  void setHeight(double height);
  double getHeight(void);
  layer getLayer(int i);

  //translation
  void shift(float stepX, float stepY, float stepZ);
};

#endif // PART_H
