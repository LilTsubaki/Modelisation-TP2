#include <QCoreApplication>
#include "maillage.h"

int main(int argc, char *argv[])
{
    QCoreApplication z(argc, argv);

    QVector3D a(1,1,1);



    std::cout << "Generation cylindre..." << std::endl;
    Maillage cylindre = Maillage::cylindre(a,2,5,20);
    cylindre.Ecriture("monCylindre.obj");

    std::cout << "Generation cone..." << std::endl;
    Maillage cone = Maillage::cone(a,2,5,20);
    cone.Ecriture("monCone.obj");

    std::cout << "Generation cone tronque..." << std::endl;
    Maillage coneTronque = Maillage::coneTronque(a,2,1,5,20);
    coneTronque.Ecriture("monConeTronque.obj");

    std::cout << "Generation sphere..." << std::endl;
    Maillage sphere = Maillage::sphere(a,1,20);
    sphere.Ecriture("sphere.obj");

    std::cout << "Generation tore..." << std::endl;
    Maillage tore = Maillage::tore(a,2,1,20);
    tore.Ecriture("tore.obj");

    /*Maillage bunny = Maillage::lectureOff("C:/Users/etu/Desktop/bunny.off");
    bunny.Ecriture("bunny.obj");*/

}

