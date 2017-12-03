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
  FILE* file;

public:
  fileReader();
  void run() override;

public:
  void setFileUrl(QString fileUrl);
private:
  std::vector<triangle> decodeFile(QString text);
  std::vector<triangle> decodeBinarySTL(QString fileURL);
};

#endif // FILEREADER_H
