#include "maillage.h"
#include <math.h>
#define M_PI           3.14159265358979323846

Maillage::Maillage()
{

}

Maillage Maillage::cylindre(const QVector3D & a, const double & rayon, const  int & hauteur, const int & nbMeridiens)
{
    QVector<QVector3D> geom;
    QVector<int> topo;
    QVector<QVector3D> normales;
    float angle = 0;
    QVector3D b(a.x(), a.y() + hauteur, a.z());


    /*****************************
     *    Génération géométrie   *
     *****************************/
    //premier cercle
    for(int i = 0; i < nbMeridiens; i++)
    {
        geom.append(QVector3D(a.x()+cos(angle), a.y(), a.z()+sin(angle)));
        angle += 2*M_PI/nbMeridiens;
    }

    //deuxieme cercle
    for(int i = 0; i < nbMeridiens; i++)
    {
        geom.append(QVector3D(b.x()+cos(angle), b.y(), b.z()+sin(angle)));
        angle += 2*M_PI/nbMeridiens;
    }

    /*****************************
     *    Génération topologie   *
     *****************************/
    for(int i =0; i < nbMeridiens; i++)
    {
        topo.append(nbMeridiens*2);topo.append(i);topo.append((i+1)%nbMeridiens);
        topo.append(nbMeridiens*2+1);topo.append((i+1)%nbMeridiens+nbMeridiens);topo.append(i+nbMeridiens);
    }

    for(int i = 0; i < nbMeridiens; i++)
    {
        topo.append(i);topo.append(i+nbMeridiens);topo.append((i+1)%nbMeridiens);

        topo.append(nbMeridiens+i);topo.append((i+1)%nbMeridiens+nbMeridiens);topo.append((i+1)%nbMeridiens);
    }

    geom.append(a);
    geom.append(b);

    return Maillage(geom, topo, normales);
}







void Maillage::Merge(Maillage figure2)
{
    QVector<int> changement;
    int temp;
    //on parcours la liste des points de la seconde figure
    //on vérifie si il y a des points communs entre les deux figures
    for(int p1 = 0; p1 < figure2.geom.size(); p1++)
    {
//        temp = this->ComparePoint(figure2.geom.at(p1));
//        si le point n'existe pas deja alors on l'ajoute à la geométrie de la premiere figure
//        on stock également le nouvel indice de ce point
//        if(temp == -1)
//        {
            this->geom.append(figure2.geom.at(p1));
            temp = this->geom.size()-1;
        //}
        //std::cout << "l'indice " << p1 << "est maintenant l'indice " << temp << std::endl;
        changement.append(temp);
    }

    //on ajoute a la premiere topo la seconde en mettant a jour les indices
    for(int i = 0; i < figure2.topo.size(); i++)
    {
        this->topo.append(changement.at(figure2.topo.at(i)));
    }
}

int Maillage::ComparePoint(const QVector3D & p1)
{
    for(int p2 = 0; p2 < this->geom.size(); p2++)
    {
        //si il y a un point en commun alors je ne le rajoute pas à la liste
        //mais je change les indices au sein de la topo
        if(this->geom.at(p2) == p1)
        {
            //std::cout << "point en commun  !!!" << std::endl;
            return p2;
        }
    }
    return -1;
}

void Maillage::Ecriture(std::string nom)
{
    std::ofstream fichier(nom, std::ios::out | std::ios::trunc);
    if(fichier)
    {
        fichier << "o " << nom << std::endl;
        fichier << std::endl;
        QVector3D temp;
        for (int i = 0; i < geom.size(); ++i)
        {
             temp = geom.at(i);
             fichier << "v " << temp.x() << " " << temp.y() << " " << temp.z() << std::endl;
        }
        fichier << std::endl;
        for (int i = 0; i < normales.size(); ++i)
        {
             temp = normales.at(i);
             fichier << "vn " << temp.x() << " " << temp.y() << " " << temp.z() << std::endl;
        }
        fichier << std::endl;
        for (int i = 0; i < topo.size(); i+=3)
        {
             fichier << "f " << topo.at(i)+1 << " " << topo.at(i+1)+1 << " " << topo.at(i+2)+1 << std::endl;
        }
        fichier.close();  // on referme le fichier
    }
    else
    {
        std::cerr << "Erreur à l'ouverture !" << std::endl;
    }
}

Maillage Maillage::Rotation(const double matrice[3][3])
{
    QVector<QVector3D> geom2;
    QVector3D temp;
    for (int i = 0; i < geom.size(); ++i)
    {
         temp = geom.at(i);
         temp.setX(temp.x() * matrice[0][0] + temp.y() * matrice[0][1] + temp.z() * matrice[0][2]);
         temp.setY(temp.x() * matrice[2][0] + temp.y() * matrice[2][1] + temp.z() * matrice[2][2]);
         temp.setZ(temp.x() * matrice[1][0] + temp.y() * matrice[1][1] + temp.z() * matrice[1][2]);
         geom2.append(temp);
    }

    Maillage * sphere = new Maillage(geom2, topo, normales);
    return *sphere;
}

Maillage::~Maillage()
{

}
