#include "stlfileobject.h"
#include "datatypes.h"

#include <QApplication>
#include <QString>

#include <iostream>
#include <vector>

StlFileObject::StlFileObject(){}

int StlFileObject::decodeFile(QString stl_data_brut){
    QString word;
    std::string text = stl_data_brut.toStdString();
    int state = 0; //the state machine for decoding
    std::vector<triangle> triangles;
    triangle tmp;
    int cpt = 1;
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
                state++; //rien
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
                state++; //vertex
                break;
            case 7:
                tmp.p2.x = word.toDouble();
                state++;
                break;
            case 8:
                tmp.p2.y = word.toDouble();
                state++;
                break;
            case 9:
                tmp.p2.z = word.toDouble();
                state++;
                break;
            case 10:
                state++; //vertex
                break;
            case 11:
                tmp.p3.x = word.toDouble();
                state++;
                break;
            case 12:
                tmp.p3.y = word.toDouble();
                state++;
                break;
            case 13:
                tmp.p3.z = word.toDouble();
                state++;
                std::cout << cpt << std::endl;
                std::cout << "P1: " << tmp.p1.x << " " << tmp.p1.y << " " << tmp.p1.z << std::endl;
                std::cout << "P2: " << tmp.p2.x << " " << tmp.p2.y << " " << tmp.p2.z << std::endl;
                std::cout << "P3: " << tmp.p3.x << " " << tmp.p3.y << " " << tmp.p3.z << std::endl << std::endl;
                state = 0;
                cpt++;
                break;
            default:
                break;
            }
            triangles.push_back(tmp);
            word.clear();
        }
    }
    std::cout << "Nb of coordinates: " << triangles.size() << std::endl;
    return 1;
}
