#include "segment.h"

//overwrite of operators to allow an easier printing
std::ostream& operator<<(std::ostream& str, const segment& seg){
  str << "p1: x " << seg.p1.x << "\t y " << seg.p1.y << "\t z " << seg.p1.z << std::endl;
  str << "p2: x " << seg.p2.x << "\t y " << seg.p2.y << "\t z " << seg.p2.z << std::endl;
  return (str);
}

/*std::ostream& operator<<(std::ostream& str, const point& point){
  str << "x " << point.x << "\t y " << point.y << "\t z " << point.z << std::endl;
  return (str);
}*/

segment::segment()
{
    isEmpty = true;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;
    p2.x = 0;
    p2.y = 0;
    p2.z = 0;

}
