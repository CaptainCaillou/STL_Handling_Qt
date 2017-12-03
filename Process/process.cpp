#include "process.h"

void process::run(){}

int process::getState()
{
  return this->state;
}

void process::setPart(part Part)
{
  this->Part = Part;
}

part process::getPart(void)
{
  return this->Part;
}
