#ifndef POPULATION_H
#define POPULATION_H

#include "Individu.h"

class Population
{
private :

    int generation;
    Individu* famille;
    int taille_famille;
    Individu* meilleur;
    int best;
    double proba_mute;
    int RWselect();

public :

    Population(int n,double p_mute)
    {
        taille_famille = n;
        proba_mute = p_mute;
        generation = 0;
        famille = new Individu[taille_famille];
        for(int i = 0;i< taille_famille;i++)
        {
            cout << famille[i].getFitness()<<endl;
        }
        select_best();
    }

    ~Population(){delete [] famille;}

    Individu& operator [] (int n);

    void select_best();

    int getgeneration();

    void updatefitness();

    //int RWselect();

    void evolution();

    void show() const;

    int* showbest();

    int getbestvalue();

    void augprobmute();
};

#endif
