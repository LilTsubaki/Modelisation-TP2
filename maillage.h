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


        // Utilitaires

        Maillage Rotation(const double matrice[3][3]);
        int ComparePoint(const QVector3D & p1);
        void Merge(Maillage figure2);
        void Ecriture(std::string nom);

        ~Maillage();
};


#endif // MAILLAGE_H
