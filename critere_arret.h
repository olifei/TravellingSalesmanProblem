#ifndef CRITERE_ARRET_H
#define CRITERE_ARRET_H

#include <iostream>
#include "Population.h"

#define num_cell 500
#define stop_condition 10
#define change_etape 250
#define MAX_GEN 10000
class critere_arret //Contrat qui definit les methodes exposees a l'algorithme
{
 private:
     int* record;
     int nbcell;
 public:
    critere_arret()
    {
        nbcell = num_cell;
        record = (int*)malloc(sizeof(int)*nbcell);
    };
    ~critere_arret(){};

    bool continuer(Population& GA)//rend 1 si l'on a pas atteint le critere d'arret, 0 sinon
    {
        int cur_gen = GA.getgeneration();
        cout <<"cur_gen: "<<cur_gen<<endl;
        record[cur_gen % nbcell] = GA.getbestvalue();
        if(cur_gen < nbcell - 1)
            return true;//generation too small, continue evolution
        int average = 0;
        for(int i = 0;i < nbcell;i++)
        {
            average += record[i];
        }
        average = average / nbcell;
        int variance = 0;
        for(int i = 0;i < nbcell;i++)
        {
            variance += (record[i] - average) * (record[i] - average);
        }
        variance = variance / nbcell;
        if(variance < stop_condition || GA.getgeneration() > MAX_GEN)
        {
            return false;//quit loop of evolution
        }
        else
        {
            if(variance < change_etape)
                GA.augprobmute();
            return true;//continue evolution
        }
    };
};

#endif
