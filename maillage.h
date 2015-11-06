#ifndef MAILLAGE_H
#define MAILLAGE_H
#include <QVector>
#include <QVector3D>
#include <iostream>
#include <fstream>


class Maillage
{
    QVector<QVector3D> geom; //contient les points du maillage
    QVector<int> topo; //contient des triplets d'indice pour chaque triangle du maillage
    QVector<QVector3D> normales; //contient les normales au point

    public:
        Maillage();
        Maillage(QVector<QVector3D> geo, QVector<int> top, QVector<QVector3D> norm) : geom(geo), topo(top), normales(norm) {}
        Maillage(QVector<QVector3D> geo, QVector<int> top) : geom(geo), topo(top) {}

        // Maillages simples

        static Maillage cylindre(const QVector3D & a, const double & rayon, const  int & hauteur, const int & nbMeridiens);
        static Maillage cone(const QVector3D & a, const double & rayon,const int & hauteur, const int & nbMeridiens);
        static Maillage coneTronque(const QVector3D & a, const double & rayon, const double & rayon2,const  int & hauteur, const int & nbMeridiens);
        static Maillage sphere(QVector3D p, double radius, int points);
        static Maillage tore(QVector3D v, int rayon, int epaisseur, int points);

        // Utilitaires
        static Maillage lectureOff(const std::string nom);
        void Ecriture(std::string nom);
        ~Maillage();
        QVector<QVector3D> getGeom() const;
        void setGeom(const QVector<QVector3D> &value);
        QVector<int> getTopo() const;
        void setTopo(const QVector<int> &value);
        QVector<QVector3D> getNormales() const;
        void setNormales(const QVector<QVector3D> &value);
};


#endif // MAILLAGE_H
