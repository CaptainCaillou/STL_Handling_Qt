#include "gcodegenerator.h"
 #include <QObject>
#include "Types/layer.h"
#include "Types/segment.h"
#include <stdio.h>

GCodeGenerator::GCodeGenerator() {

}

void GCodeGenerator::run() {
        printf("run !\n");
        std::cerr << Part.getLayers().size();
        for(int i = 0; i < Part.getLayers().size(); i++)
            std::cout << i << std::endl;
    /*for(std::vector<layer>::iterator itl = Part.getLayers().begin(); itl != Part.getLayers().end(); itl++) {

        for(std::vector<segment>::iterator its = itl->contours.begin(); its != itl->contours.end(); its++) {
            //toolPath trajet;
            //trajet.z1 = trajet.z2 = itl->height;
            /*trajet.x1 = its->p1.x;
            trajet.y1 = its->p1.y;
            trajet.x2 = its->p2.x;
            trajet.y2 = */
            //printf("Pouette");
           // printf("%lf\n", its->p2.y);
           // trajets.push_back(trajet);
           // std::cout << "BOOOOP" << std::endl;
            //printf("Trajet de %lf %lf %lf à %lf %lf %lf\n", trajet.x1, trajet.y1, trajet.z1, trajet.x2, trajet.y2, trajet.z2);
            //fflush(stdout);
     //   }
    //}
    for(int i = 0; i < 10; i++) printf("Boop !\n");
}

int GCodeGenerator::getState() {

    return 0;
}

void GCodeGenerator::setPart(part Part) {
    printf("setPart !\n");
    std::cout << Part.getLayers().size();
    this->Part = Part;
}

void GCodeGenerator::setFileUrl(QString fileUrl) {
    this->fileUrl = fileUrl;
}

void writeFile(QString text) {

}
