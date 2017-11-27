#include "part.h"

part::part()
{

}


void part::setTriangles(std::vector<triangle> triangles_set) {
  this->triangles = triangles_set;
}


std::vector<triangle> part::getTriangles(void){
  return this->triangles;
}

void part::setLayers(std::vector<layer> layer_set) {
  this->layers = layer_set;
}


std::vector<layer> part::getLayers(){
  return this->layers;
}

layer part::getLayer(int i){
  return this->layers[i];
}

void part::setHeight(double height)
{
  this->height = height;
}

double part::getHeight()
{
  return this->height;
}
