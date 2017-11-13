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
  //int state;
  part Part;
  double slicerWidth;

public:
  void run() override;
  void setPart(part Part);
  part getPart(void);
  void setSlicerWidth(double width);
  int  getState(void);
};

#endif // SLICER_H
