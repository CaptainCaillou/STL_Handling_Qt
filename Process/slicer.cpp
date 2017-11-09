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
      //std::cout << triangles.size();
      lay.contours.clear();
      lay.getContour(triangles);
      layers.push_back(lay);
      if(lay.contours.size() > 3)
          contour_found = true;
      if((lay.height > 3*lay.width) && contour_found == false)
      {
        std::cerr << "No contour found at "<< lay.height <<" mm, have you selected the right layer width ?"  << std::endl;
        break;
      }
      lay.height += lay.width;
  }while(!contour_found || lay.contours.size() > 0);

  //we send back the layers detected to the part
  P->setLayers(layers);
}
