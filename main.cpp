#include <QCoreApplication>
#include "maillage.h"

int main(int argc, char *argv[])
{
    QCoreApplication z(argc, argv);

    QVector3D a(1,1,1);
    QVector3D b(3,3,3);



    std::cout << "Generation cylindre..." << std::endl;
    Maillage cylindre2 = Maillage::cylindre(a,2,10, 10);
    cylindre2.Ecriture("monCylindre.obj");

}

