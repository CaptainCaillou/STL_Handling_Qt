#include "slicer.h"

Slicer::Slicer()
{
  this->state = -1; //idle
}
void Slicer::run()
{
  // We set the new state
  this->state = 0;
  layer lay;
  lay.width = this->slicerWidth;
  if(lay.width <= 0)
  {
    std::cerr << "Seriously, want to slice with layer height <= 0 ?!" << std::endl;
    if(state != -2) this->state = -1;
    return;
  }

  std::vector<layer> layers;
  bool contour_found = false;

  //We get the triangles from the part
  std::vector<triangle> triangles = this->Part.getTriangles();

  //We search every layer
  do
  {
    lay.contours.clear();
    lay.getContour(triangles);

    layers.push_back(lay);
    if(lay.contours.size() > 3)
      contour_found = true;

    if((lay.height > 3*lay.width) && contour_found == false)
    {
      //We set an error into the state variable
      this->state = -2; // error
      std::cerr << "No contour found at "<< lay.height <<" mm, have you selected the right layer width ?"  << std::endl;
      break;
    }
    lay.height += lay.width;
    this->state = lay.height/Part.getHeight()*100;
  }while(!contour_found || lay.contours.size() > 0);

  //we send back the layers detected to the part
  this->Part.setLayers(layers);

  //We are now on idle
  if(state != -2) this->state = -1;
}

void Slicer::setPart(part Part)
{
  this->Part = Part;
}

part Slicer::getPart(void)
{
  return (this->Part);
}

void Slicer::setSlicerWidth(double width)
{
  this->slicerWidth = width;
}

int Slicer::getState()
{
  return this->state;
}

/*
void Slicer::slice(part* P, double lay_width)
{z
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
*/
