#include "filereader.h"
#include <vector>
#include <QFile>

fileReader::fileReader()
{

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

std::vector<triangle> fileReader::decodeFile(){
    std::vector<triangle> triangles;
    QFile input(this->fileUrl);
    double highest_point = 0;
    if (!input.open(QIODevice::ReadOnly))
    {
        std::cerr << "Could not open file, Error: "<< errno << " : " << strerror(errno) << std::endl;
        return triangles;
    }

    QString word;
    std::string text = input.readAll().toStdString();
    int state = 0; //the state machine for decoding
    triangle tmp;
    int cpt = 0;
    for(unsigned int i = 0; i < text.length(); i++)
    {
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
                  std::cout << highest_point << std::endl;
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

    std::cout << "Nb of triangles: "  << cpt << std::endl;
    std::cout << "Highest_point: "    << highest_point << std::endl;

    input.close();
    Part.setTriangles(triangles);
    return triangles;
}


std::vector<triangle> fileReader::decodeBinarySTL() {

    std::vector<triangle> triangles;
    std::cout << "Opening file `" << this->fileUrl.toStdString() << "` as binary STL.\n" << std::endl;
    FILE* file = fopen(this->fileUrl.toStdString().c_str(), "r");
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
