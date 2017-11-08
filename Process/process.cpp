#include "process.h"

process::process()
{
  this->state = -1;
}

int process::getState()
{
  return this->state;
}
