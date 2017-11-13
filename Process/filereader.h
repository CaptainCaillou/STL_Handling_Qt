#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <QString>

#include "Types/datatypes.h"
#include "Types/triangle.h"
#include "Types/part.h"
#include "process.h"

class fileReader : public process
{
public:
  fileReader();
  std::vector<triangle> decodeFile(part* Part, QString fileURL);
  std::vector<triangle> decodeBinarySTL(part* Part,QString fileURL);
};

#endif // FILEREADER_H
