#include "stlfileobject.h"
#include "datatypes.h"

#include <QApplication>
#include <QString>

#include <iostream>
#include <vector>

StlFileObject::StlFileObject(){}

std::vector<triangle> StlFileObject::decodeFile(QString stl_data_brut){
    QString word;
    std::string text = stl_data_brut.toStdString();
    int state = 0; //the state machine for decoding
    std::vector<triangle> triangles;
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
    std::cout << "Nb of triangles: " << cpt << std::endl;
    return triangles;
}
