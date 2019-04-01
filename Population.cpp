#include <stdlib.h>
#include <time.h>
#include "Population.h"

void Population::augprobmute()
{
    proba_mute = proba_mute * 10;
}

Individu& Population::operator[](int n)
{
    return famille[n];
}

void Population::select_best()
{
    int bestnb = 0;
    int bestfit = famille[0].getFitness();
    for(int i = 0;i < taille_famille;i++)
    {
        if(bestfit > famille[i].getFitness())
        {
            bestfit = famille[i].getFitness();
            bestnb = i;
        }
    }
    meilleur = &famille[bestnb];
    best = bestnb;
}

int Population::getgeneration()
{
    return generation;
}

void Population::updatefitness()
{
    //static int nbup = 0;
    //cout <<"taille_famille: "<<taille_famille<<endl;
    for(int i = 0;i < taille_famille;i++)
    {
        //cout <<"update nb: "<<nbup++<<endl;
        famille[i].calFitness();
    }
}

int Population::RWselect()
{
    //srand(time(0));
    double sum_fitness = 0.000000;
    //int t = taille_famille;
    for(int i = 0;i < taille_famille;i++)
    {
        sum_fitness = sum_fitness + 10000/famille[i].getFitness();
    }
    double pointeur = (double)(rand()%10)/11*sum_fitness;
    sum_fitness = 0.0000000;
    int nbselect;
    for(nbselect = 0;nbselect < taille_famille;nbselect++)
    {
        sum_fitness += 10000/famille[nbselect].getFitness();
        if(sum_fitness > pointeur)
            break;
    }
    return nbselect;
}

void Population::evolution()
{
    updatefitness();
    Individu son[taille_famille];
    //croisement
    for(int i = 0;i < taille_famille;i++)
    {
        int a,b;
        a = RWselect();
        b = RWselect();
        while(a == b)
        {
            b = RWselect();
        }
        son[i] = famille[b];
        son[i].croise(famille[a]);
        son[i].calFitness();
    }
    for(int i = 0;i < taille_famille;i++)
    {
        if(son[i].getFitness() < famille[i].getFitness())//
            famille[i] = son[i];
    }
    //mutation
    double nbmute;
    for(int i = 0;i < taille_famille;i++)
    {
        //srand(time(0));
        //double pb = proba_mute;
        Individu temp;
        nbmute = (double)(rand()%11)/10;
        if(nbmute < proba_mute)
        {
            temp = famille[i];
            famille[i].calFitness();
            temp.mute();
            temp.calFitness();
            if(temp.getFitness() < famille[i].getFitness())
                famille[i] = temp;
        }
    }
    updatefitness();
    select_best();
    //show();
    generation++;
}

void Population::show() const
{
    for(int i = 0;i < taille_famille;i++)
    {
        cout << i << " : ";
        famille[i].showchemin();
    }
}

int* Population::showbest()
{
    famille[best].showchemin();
    cout << "value: "<< famille[best].getFitness()<<endl;
    return famille[best].way_to_array();
}

int Population::getbestvalue()
{
    return famille[best].getFitness();
}

