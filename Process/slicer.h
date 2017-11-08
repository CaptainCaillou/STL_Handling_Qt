#ifndef SLICER_H
#define SLICER_H

#include "process.h"
#include "Types/part.h"

class Slicer : public process
{

private:
  int state;
public:
  Slicer();
  void slice(part* P, double lay_width);
};

#endif // SLICER_H
