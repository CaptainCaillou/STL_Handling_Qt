#include "slicer.h"

Slicer::Slicer()
{

}
void Slicer::slice(part* P, double lay_width)
{
  layer lay;
  lay.width = lay_width;

  std::vector<layer> layers;
  bool contour_found = false;

  //We get the triangles from the part
  std::vector<triangle> triangles = P->getTriangles();

  //We search every layer
  do
  {
      lay.contours.clear();
      lay.getContour(triangles);
      layers.push_back(lay);
      lay.height += lay.width;
      if(lay.contours.size() > 3)
          contour_found = true;
  }while(!contour_found || lay.contours.size() > 0);

  //we send back the layers detected to the part
  P->setLayers(layers);
}
