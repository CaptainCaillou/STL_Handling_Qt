#ifndef PART_H
#define PART_H

#include "triangle.h"
#include "layer.h"

class part
{
private:
  std::vector<triangle> triangles;
  std::vector<layer> layers;
public:
  part();
  void setTriangles(std::vector<triangle>);
  std::vector<triangle> getTriangles(void);
  void setLayers(std::vector<layer>);
  std::vector<layer> getLayers(void);
};

#endif // PART_H
