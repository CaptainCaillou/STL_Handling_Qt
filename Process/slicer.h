#ifndef SLICER_H
#define SLICER_H

#include "process.h"
#include "Types/part.h"
#include "Types/layer.h"

class Slicer : public process
{
public:
  Slicer();

private:
  double slicerWidth;

public:
  void run() override;
  void setSlicerWidth(double width);
};

#endif // SLICER_H
