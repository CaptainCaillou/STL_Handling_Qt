#include "gcodegenerator.h"
 #include <QObject>
#include "Types/layer.h"
#include "Types/segment.h"
#include <stdio.h>
#include <QFile>
#include <QTextStream>

GCodeGenerator::GCodeGenerator() {}

void GCodeGenerator::run() {
    //printf("run !\n");
    int nbLayers = Part.getLayers().size();

    if(nbLayers < 1) {
        std::cerr << "Aucune couche à exporter !" << std::endl;
        state = -2;
        return;
    }

    QFile sortie(this->fileUrl);
    if (!sortie.open(QIODevice::WriteOnly))
    {
      std::cerr << "Could not open file, Error: "<< errno << " : " << strerror(errno) << std::endl;
      state = -2;
      return;
    }

    QTextStream sortieStream(&sortie);

    for(int il = 0; il < nbLayers; il++) {
        state = (il*100)/nbLayers;
        layer couche = Part.getLayer(il);
        int nbSeg = couche.contours.size();

        for(int is = 0; is < nbSeg; is++) {
            segment seg = couche.contours[is];
            toolPath path;
            path.z1 = path.z2 = couche.height;
            path.x1 = seg.p1.x;
            path.y1 = seg.p1.y;
            path.x2 = seg.p2.x;
            path.y2 = seg.p2.y;;
            //paths.push_back(path);

            //std::cout << "z1 :" << path.z1 << " z2 :" << path.z2 << " x1 :" << path.x1 << " x2 :" << path.x2 << "\n";
            //fflush(stdout);
            sortieStream << path.getGCodeBegin() << path.getGCodeEnd();
        }
    }
    sortie.close();
    if (state != -2) state = -1;
}

void GCodeGenerator::setFileUrl(QString fileUrl) {
    this->fileUrl = fileUrl;
}
