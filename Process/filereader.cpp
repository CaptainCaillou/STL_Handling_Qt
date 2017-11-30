#include "filereader.h"
#include <vector>
#include <QFile>
#include <QStringRef>

std::ostream& operator<<(std::ostream& str, const point& point){
  str << "x " << point.x << "\t y " << point.y << "\t z " << point.z << std::endl;
  return (str);
}
fileReader::fileReader()
{
  this->state = -1; //idle
}

void fileReader::setPart(part Part)
{
  this->Part = Part;
}

part fileReader::getPart(void)
{
  return this->Part;
}

void fileReader::setFileUrl(QString fileUrl)
{
  this->fileUrl = fileUrl;
}

std::vector<triangle> fileReader::decodeFile(QString text){
  std::vector<triangle> triangles;
  double highest_point = 0;
  QString word;
  int state = 0; //the state machine for decoding
  triangle tmp;
  int cpt = 0;

  for(int i = 0; i < text.length(); i++)
  {
    this->state = i*100 / text.length();
    word.push_back(text[i]);
    if((text[i] == ' ' || text[i] == '\n') && text[i-1] != ' ' )
    {
      switch (state) {
      case 0:
        if(word.mid(0, word.length()-2).toStdString() == std::string("loop"))
        {
          state ++;
        }
        break;
      case 1:
        state++; //nothing
        break;
      case 2:
        state++;
        break;
      case 3:
        tmp.p1.x = word.toDouble();
        state++;
        break;
      case 4:
        tmp.p1.y = word.toDouble();
        state++;
        break;
      case 5:
        tmp.p1.z = word.toDouble();
        if(highest_point < tmp.p1.z)
        {
          highest_point = tmp.p1.z;
          //std::cout << highest_point << std::endl;
        }
        state++;
      case 6:
        state++; //nothing
        break;
      case 7:
        state++;
        break;
      case 8:
        state++; //vertex
        break;
      case 9:
        tmp.p2.x = word.toDouble();
        state++;
        break;
      case 10:
        tmp.p2.y = word.toDouble();
        state++;
        break;
      case 11:
        tmp.p2.z = word.toDouble();
        if(highest_point < tmp.p2.z)
        {
          highest_point = tmp.p2.z;
          std::cout << highest_point << std::endl;
        }
        state++;
        break;
      case 12:
        state++; //nothing
        break;
      case 13:
        state++; //vertex
        break;
      case 14:
        tmp.p3.x = word.toDouble();
        state++;
        break;
      case 15:
        tmp.p3.y = word.toDouble();
        state++;
        break;
      case 16:
        tmp.p3.z = word.toDouble();
        if(highest_point < tmp.p3.z)
        {
          highest_point = tmp.p3.z;
          std::cout << highest_point << std::endl;
        }
        state = 0;
        tmp.id = cpt;
        triangles.push_back(tmp);
        cpt++;
        break;
      default:
        break;
      }
      word.clear();
    }
  }
  Part.setHeight(highest_point);

  //std::cout << "Nb of triangles: "  << cpt << std::endl;
  //std::cout << "Highest_point: "    << highest_point << std::endl;

  Part.setTriangles(triangles);
  return triangles;
}

QString toDebug(const QByteArray & line) {

  QString s;
  uchar c;

  for ( int i=0 ; i < line.size() ; i++ ){
    c = line[i];
    if ( c >= 0x20 and c <= 126 ) {
      s.append(c);
    } else {
      s.append(QString("%1").arg(c, 2, 10, QChar('0')));
    }
  }
  return s;
}
/*
std::vector<triangle> fileReader::decodeBinarySTL(QByteArray text) {

  std::cout << "length of the byte array : " << text.length() << std::endl;
  std::vector<triangle> triangles;

  //char bufferHeader[81] = {0};
  QByteArray BufferHeader;
  uint Ntriangles;

  std::cout << std::endl;
  BufferHeader = text.left(80);
  text.remove(0,80);
  Ntriangles = toDebug(text.left(1)).toUInt();
  text.remove(0,1);

  printf("STL Header : `%s`\nModel is supposed to have %d triangles\n", BufferHeader.toStdString().c_str(), Ntriangles);


  //      D:/Code/STL_Handler/TestFiles/cube10bin.STL

  //return triangles;
  //triangleChunk tempTriangle;
  for(unsigned int i = 0; i < Ntriangles; i++) {
    std::cout << "Triangle n " << triangles.size() << std::endl;
    triangle tmp;

    // 3 first floats are Normal vector coordinates. We ignore them.
    text.remove(0,3);

    // Vertex 1 x
    tmp.p1.x = toDebug(text.left(1)).toFloat();
    text.remove(0,1);

    // Vertex 1 y
    tmp.p1.y = toDebug(text.left(1)).toFloat();
    text.remove(0,1);
    // Vertex 1 z
    tmp.p1.z = toDebug(text.left(1)).toFloat();
    text.remove(0,1);

    // Vertex 2 x
    tmp.p2.x = toDebug(text.left(1)).toFloat();
    text.remove(0,1);

    // Vertex 2 y
    tmp.p2.y = toDebug(text.left(1)).toFloat();
    text.remove(0,1);

    // Vertex 2 z
    tmp.p2.z = toDebug(text.left(1)).toFloat();
    text.remove(0,1);

    // Vertex 3 x
    tmp.p3.x = toDebug(text.left(4)).toFloat();
    text.remove(0,4);

    // Vertex 3 y
    tmp.p3.y = toDebug(text.left(4)).toFloat();
    text.remove(0,4);

    // Vertex 3 z
    tmp.p3.z = toDebug(text.left(4)).toFloat();
    text.remove(0,4);

    std::cout << tmp.p1<< tmp.p2 << tmp.p3 << std::endl;
    std::cout << text.length() << std::endl;

    text.remove(0,2);
    triangles.push_back(tmp);
  }
  Part.setTriangles(triangles);
  return triangles;
}
*/

std::vector<triangle> fileReader::decodeBinarySTL(QString fileURL){

  std::vector<triangle> triangles;

  FILE* file = fopen(fileURL.toStdString().c_str(), "r");
  if (file == NULL) {
      std::cerr << "Could not open file, Error: "<< errno << " : " << strerror(errno) << std::endl;
      return triangles;
  }

  char bufferHeader[81] = {0};
  uint32_t Ntriangles;
  fread(bufferHeader, 80, 1, file);
  fread(&Ntriangles, 4, 1, file);
  printf("STL Header : `%s`\nModel is supposed to have %u triangles\n", bufferHeader, Ntriangles);


  //triangleChunk tempTriangle;
  for(unsigned int i = 0; i < Ntriangles; i++) {
      std::cout << "Triangle n " << triangles.size() << std::endl;
      float tempFloat;
      uint16_t tempInt;

      triangle tmp;

      // 3 first floats are Normal vector coordinates. We ignore them.
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      fread(&tempFloat, sizeof(tempFloat), 1, file);

      // Vertex 1 x
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p1.x = tempFloat;

      // Vertex 1 y
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p1.y = tempFloat;

      // Vertex 1 z
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p1.z = tempFloat;

      // Vertex 2 x
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p2.x = tempFloat;

      // Vertex 2 y
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p2.y = tempFloat;

      // Vertex 2 z
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p2.z = tempFloat;

      // Vertex 3 x
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p3.x = tempFloat;

      // Vertex 3 y
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p3.y = tempFloat;

      // Vertex 3 z
      fread(&tempFloat, sizeof(tempFloat), 1, file);
      tmp.p3.z = tempFloat;

      fread(&tempInt, sizeof(tempInt), 1, file);

      triangles.push_back(tmp);
  }
  Part.setTriangles(triangles);
  return triangles;
}


void fileReader::run()
{
  this->state = 0;
  //here we have to check if the file is binary or not
  bool isBinary = false;

  QFile input(this->fileUrl);
  if (!input.open(QIODevice::ReadOnly))
  {
    std::cerr << "Could not open file, Error: "<< errno << " : " << strerror(errno) << std::endl;
    this->state = -2;
  }

  QByteArray text = input.readAll();
  input.close();

  if(text.contains("facet") && text.contains("normal") && text.contains("endloop"))
    isBinary = false;
  else
    isBinary = true;


  if(isBinary) {
    this->decodeBinarySTL(this->fileUrl); // We should change this function to one more C++
  } else {
    this->decodeFile(text);
  }
  if (this->state != -2) this->state = -1;
}

int fileReader::getState()
{
  return this->state;
}
