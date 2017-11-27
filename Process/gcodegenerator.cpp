#include "gcodegenerator.h"
 #include <QObject>
#include "Types/layer.h"
#include "Types/segment.h"
#include <stdio.h>
#include <QFile>
#include <QTextStream>

GCodeGenerator::GCodeGenerator() {

}

void GCodeGenerator::run() {
    printf("run !\n");
    int nbLayers = Part.getLayers().size();

    QFile sortie(this->fileUrl);
    if (!sortie.open(QIODevice::WriteOnly))
    {
      std::cerr << "Could not open file, Error: "<< errno << " : " << strerror(errno) << std::endl;
    }
    QTextStream sortieStream(&sortie);

    for(int il = 0; il < nbLayers; il++) {

        state = (il*100)/nbLayers;

        layer couche = Part.getLayer(il);
        int nbSeg = couche.contours.size();

        for(int is = 0; is < nbSeg; is++) {
            segment seg = couche.contours[is];
            toolPath trajet;
            trajet.z1 = trajet.z2 = couche.height;
            trajet.x1 = seg.p1.x;
            trajet.y1 = seg.p1.y;
            trajet.x2 = seg.p2.x;
            trajet.y2 = seg.p2.y;;
            trajets.push_back(trajet);

            //std::cout << "z1 :" << trajet.z1 << " z2 :" << trajet.z2 << " x1 :" << trajet.x1 << " x2 :" << trajet.x2 << "\n";
            //fflush(stdout);
            sortieStream << trajet.getGCodeBegin() << trajet.getGCodeEnd();
        }
    }
    sortie.close();
}

int GCodeGenerator::getState() {
    return state;
}

void GCodeGenerator::setPart(part Part) {
    printf("setPart !\n");
    std::cout << Part.getLayers().size();
    this->Part = Part;
}

void GCodeGenerator::setFileUrl(QString fileUrl) {
    this->fileUrl = fileUrl;
}
