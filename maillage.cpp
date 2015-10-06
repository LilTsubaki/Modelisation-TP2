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
        geom.append(QVector3D(a.x()+cos(angle)*rayon, a.y(), a.z()+sin(angle)*rayon));
        angle += 2*M_PI/nbMeridiens;
    }

    //deuxieme cercle
    for(int i = 0; i < nbMeridiens; i++)
    {
        geom.append(QVector3D(b.x()+cos(angle)*rayon, b.y(), b.z()+sin(angle)*rayon));
        angle += 2*M_PI/nbMeridiens;
    }

    /*****************************
     *    Génération topologie   *
     *****************************/
    //topo cercle bas + cercle haut
    for(int i =0; i < nbMeridiens; i++)
    {
        topo.append(nbMeridiens*2);topo.append(i);topo.append((i+1)%nbMeridiens);
        topo.append(nbMeridiens*2+1);topo.append((i+1)%nbMeridiens+nbMeridiens);topo.append(i+nbMeridiens);
    }

    //topo cylindre
    for(int i = 0; i < nbMeridiens; i++)
    {
        topo.append(i);topo.append(i+nbMeridiens);topo.append((i+1)%nbMeridiens);
        topo.append(nbMeridiens+i);topo.append((i+1)%nbMeridiens+nbMeridiens);topo.append((i+1)%nbMeridiens);
    }

    geom.append(a);
    geom.append(b);

    return Maillage(geom, topo, normales);
}

Maillage Maillage::cone(const QVector3D & a, const double & rayon, const  int & hauteur, const int & nbMeridiens)
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
        geom.append(QVector3D(a.x()+cos(angle)*rayon, a.y(), a.z()+sin(angle)*rayon));
        angle += 2*M_PI/nbMeridiens;
    }

    /*****************************
     *    Génération topologie   *
     *****************************/
    //topo cercle
    for(int i =0; i < nbMeridiens; i++)
    {
        topo.append(nbMeridiens);topo.append(i);topo.append((i+1)%nbMeridiens);
    }

    //topo cone
    for(int i =0; i < nbMeridiens; i++)
    {
        topo.append(i);topo.append(nbMeridiens+1);topo.append((i+1)%nbMeridiens);
    }

    geom.append(a);
    geom.append(b);

    return Maillage(geom, topo, normales);
}



Maillage Maillage::coneTronque(const QVector3D & a, const double & rayon, const double & rayon2,const  int & hauteur, const int & nbMeridiens)
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
        geom.append(QVector3D(a.x()+cos(angle)*rayon, a.y(), a.z()+sin(angle)*rayon));
        angle += 2*M_PI/nbMeridiens;
    }

    //deuxieme cercle
    for(int i = 0; i < nbMeridiens; i++)
    {
        geom.append(QVector3D(b.x()+cos(angle)*rayon2, b.y(), b.z()+sin(angle)*rayon2));
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



Maillage Maillage::sphere(QVector3D p, double radius, int points)
{
    //meme nombre de méridiens et de parallèles
    QVector<QVector3D> g;
    QVector<int> t;


    for (int i = 0; i < 2*points; i++) // Boucle pour la création des cercles
    {
        double phi = i*M_PI/points;
        for (int j = 1; j <= points-1; j++) // Boucle pour former la sphère
        {
            double theta = j*M_PI/points;
            qreal x = radius * cos(phi) * sin(theta) + p.x();
            qreal y = radius * sin(phi) * sin(theta) + p.y();
            qreal z = radius            * cos(theta) + p.z();
            g.append(QVector3D(x, y, z));
        }
    }

    // Faces
    for (int i = 0; i < (2*points-1)*(points-1)-1; i++)
    {
        if ( (i+1) % (points-1) != 0)
        {
            t.append(i);
            t.append(i+1);
            t.append(points+i);

            t.append(i);
            t.append(points+i);
            t.append(points-1+i);
        }
    }

    // Dernière bande
    for (int i = 0; i < points-2; i++)
    {
        t.append((2*points-1)*(points-1)+i);
        t.append((2*points-1)*(points-1)+1+i);
        t.append(i);

        t.append(i);
        t.append((2*points-1)*(points-1)+1+i);
        t.append(i+1);
    }

    // Poles
    double phi = 0;
    double theta = 0;
    qreal x = radius * cos(phi) * sin(theta) + p.x();
    qreal y = radius * sin(phi) * sin(theta) + p.y();
    qreal z = radius            * cos(theta) + p.z();
    g.append(QVector3D(x, y, z));

    theta = M_PI;
    x = radius * cos(phi) * sin(theta) + p.x();
    y = radius * sin(phi) * sin(theta) + p.y();
    z = radius            * cos(theta) + p.z();
    g.append(QVector3D(x, y, z));

    // Premier pole
    for (int i=0; i < 2*points-1; i++)
    {
        t.append((2*points)*(points-1));
        t.append((points-1)*i);
        t.append((points-1)*i+(points-1));
    }

    // Complétion du premier pole
    t.append((2*points)*(points-1));
    t.append((2*points-1)*(points-1));
    t.append(0);

    // Deuxième pole
    for (int i=0; i < 2*points-1; i++)
    {
        t.append((2*points)*(points-1)+1);
        t.append((points-2)+(points-1)+(points-1)*i);
        t.append((points-2)+(points-1)*i);
    }

    // Complétion du deuxième pole
    t.append((2*points)*(points-1)+1);
    t.append(points-2);
    t.append((points-2)+(points-1)+(points-1)*2*(points-1));

    return Maillage(g,t);
}

Maillage Maillage::tore(QVector3D v, int rayon, int epaisseur, int points)
{
    QVector<QVector3D> g;
    QVector<int> t;

    for(int i=1; i <= points; i++)
    {
        double angle = i*2*3.14159/points;
        QVector3D point(v.x()+cos(angle)*rayon, v.y()+sin(angle)*rayon, v.z());
        //g.append(point);
        QVector3D w = point - v;
        w.normalize();
        for (int j=1; j <= points; j++)
        {
            double angle = j*2*3.14159/points;
            double x = point.x() + epaisseur*(cos(angle)*w.x()+sin(angle)*0);
            double y = point.y() + epaisseur*(cos(angle)*w.y()+sin(angle)*0);
            double z = point.z() + epaisseur*(cos(angle)*w.z()+sin(angle)*1);
            g.append(QVector3D(x, y, z));
        }
    }

    // Faces
    for (int i=0; i <= (points-1)*points-1; i++)
    {
        if (i % (points) != (points-1))
        {
            t.append(i);
            t.append(points+i+1);
            t.append(i+1);

            t.append(i);
            t.append(points+i);
            t.append(points+i+1);
        } else
        {
            t.append(i);
            t.append(i+1);
            t.append(i+1-points);

            t.append(i);
            t.append(i+points);
            t.append(i+1);
        }
    }

    // Dernière bande
    for (int i=0; i < points-1; i++)
    {
        t.append(i);
        t.append(i+1);
        t.append((points-1)*points+i);

        t.append((points-1)*points+i);
        t.append(i+1);
        t.append((points-1)*points+i+1);
    }

    t.append(points-1);
    t.append(0);
    t.append((points-1)*points+points-1);

    t.append((points-1)*points+points-1);
    t.append(0);
    t.append((points-1)*points);

    return Maillage(g,t);
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

Maillage Maillage::lectureOff(std::string nom)
{
    QVector<QVector3D> geom;
    QVector<int> topo;

    std::ifstream fichier (nom);
    if(fichier)
    {
        int delimiterPos_1;
        int delimiterPos_2;
        int delimiterPos_3;
        int delimiterPos_4;
        std::string readLine;

        getline(fichier,readLine);
        if (readLine != "OFF")
        {
            std::cout << "The file to read is not in OFF format." << std::endl;
            return Maillage(geom, topo, normales);
        }

        getline(fichier,readLine);
        delimiterPos_1 = readLine.find(" ", 0);
        int nbSommets = atoi(readLine.substr(0,delimiterPos_1+1).c_str());
        delimiterPos_2 = readLine.find(" ", delimiterPos_1);
        int nbTriangles = atoi(readLine.substr(delimiterPos_1,delimiterPos_2 +1).c_str());

        std::cout << "nb sommets : " << nbSommets << std::endl;
        std::cout << "nb triangles : " << nbTriangles << std::endl;

        for (int n=0; n<nbSommets; n++)
        {
            QVector3D temp;
            getline(fichier,readLine);
            delimiterPos_1 = readLine.find(" ", 0);
            temp.setX(atof(readLine.substr(0,delimiterPos_1).c_str()));
            delimiterPos_2 = readLine.find(" ", delimiterPos_1+1);
            temp.setY(atof(readLine.substr(delimiterPos_1,delimiterPos_2 ).c_str()));
            delimiterPos_3 = readLine.find(" ", delimiterPos_2+1);
            temp.setZ(atof(readLine.substr(delimiterPos_2,delimiterPos_3 ).c_str()));
            geom.append(temp);
            //std::cout << temp.x() << "\t" << temp.y() << "\t" << temp.z() << "\t" << std::endl;
        }

        for (int n=0; n<nbTriangles; n++)
        {
            getline(fichier,readLine);
            delimiterPos_1 = readLine.find(" ", 0);
            delimiterPos_2 = readLine.find(" ", delimiterPos_1+1);
            topo.append(atoi(readLine.substr(delimiterPos_1,delimiterPos_2 ).c_str()));
            delimiterPos_3 = readLine.find(" ", delimiterPos_2+1);
            topo.append(atoi(readLine.substr(delimiterPos_2,delimiterPos_3 ).c_str()));
            delimiterPos_4 = readLine.find(" ", delimiterPos_3+1);
            topo.append(atoi(readLine.substr(delimiterPos_3,delimiterPos_4 ).c_str()));

            /*cout << facades[n].v1 << "\t" << facades[n].v2 << "\t" <<
            facades[n].v3 << "\t" << endl;*/
        }
        fichier.close();
    }
    else
    {
        std::cout << "erreur à l'ouverture du fichier" << std::endl;
    }
    return Maillage(geom, topo);
}



Maillage::~Maillage()
{

}
