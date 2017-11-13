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
private:
  QString fileUrl;
  part Part;

public:
  fileReader();
  void setPart(part Part);
  part getPart(void);
  void setFileUrl(QString fileUrl);
  std::vector<triangle> decodeFile();
  std::vector<triangle> decodeBinarySTL();
};

#endif // FILEREADER_H
