#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <stdlib.h>
#include <time.h>
#include "matrice_cout.h"

class Individu  //A ameliorer en template
{
private:
    pays plan;
    int* chemin;
    int fitness;
    int nbVilles;// peut plutot a mettre en const et duplique

public:
    Individu()//Pour creer un individu aleatoire, il suffit de creer la matrice de cout a chaque fois elle est statique
    {
        //static int seed = 0;
        //srand(seed++);
        nbVilles = plan.nbvilles();
        chemin = (int*)malloc(sizeof(int)*nbVilles);
        //srand(time(0));
        //creer un chemin aleatoire de 0 a nbVilles-1
        int i = 0;
        while(i < nbVilles)
        {
            int j = 0;
            int flag = 0;
            chemin[i] = rand() % nbVilles;
            while(j < i)
            {
                if(chemin[i] == chemin[j])
                {
                    flag = 1;
                    break;
                }
                else
                    j++;
            }
            if(flag == 0)
                i++;
        }
        calFitness();
    }

    Individu(const Individu& unIndividu);

    ~Individu() {delete [] chemin;}
    void calFitness();
    int getFitness() const;
    void setFitness(int newFitness);
    int getNbVilles();
    void showchemin() const;

    int& operator [] (int n);
    int operator [] (int n) const;
    bool operator < (const Individu& unIndividu) const;
    bool operator > (const Individu& unIndividu) const;
    bool operator == (const Individu& unIndividu) const;
    Individu& operator = (const Individu& unIndividu);

    void mute();
    void croise(Individu& unIndividu);
    int *way_to_array();

};
#endif
