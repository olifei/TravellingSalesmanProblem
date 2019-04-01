#include "Individu.h"
#include <stdlib.h>
#include <time.h>

int& Individu::operator [] (int n)
{
    return chemin[n];
}

int Individu::operator [] (int n) const
{
    return chemin[n];
}

bool Individu::operator < (const Individu& unIndividu) const
{
    return fitness < unIndividu.fitness;
}

bool Individu::operator > (const Individu& unIndividu) const
{
    return fitness > unIndividu.fitness;
}

bool Individu::operator == (const Individu& unIndividu) const
{
    return fitness == unIndividu.fitness;
}

Individu& Individu::operator = (const Individu& unIndividu)
{
    fitness = unIndividu.fitness;
    for(int i=0 ; i<nbVilles ; i++)
        chemin[i] = unIndividu.chemin[i];
    return *this;
}

void Individu::calFitness()
{
    int sum_dis = 0;
    int get = getNbVilles()-1;
    for(int i = 0;i < get;i++)
    {
        sum_dis += plan[chemin[i]][chemin[i+1]];
    }
    sum_dis += plan[chemin[get]][chemin[0]];
    if(sum_dis == 0)
        cout << "sum_dis = "<<sum_dis<<endl;
    else
        setFitness(sum_dis);
}

int Individu::getFitness() const
{
    return fitness;
}

void Individu::setFitness(int newFitness)
{
    fitness = newFitness;
}

int Individu::getNbVilles()
{
    return nbVilles;
}

void Individu::showchemin() const
{
    cout <<"nbVilles:: "<<nbVilles<<endl;
    //int debug=-1;
    for(int i = 0;i<nbVilles-1;i++)
    {
        //cout << "jishu: "<<i<<endl;
        cout <<chemin[i]<<"->";
    }
    cout << chemin[nbVilles-1]<<endl;
}

void Individu::mute()
{
    int i = rand () % nbVilles;//range 0 to nbVilles-1
    int j = rand () % nbVilles;
    int temp = chemin[i];
    chemin[i] = chemin[j];
    chemin[j] = temp;
}

void Individu::croise(Individu& unIndividu)
{
    //srand(time(0));
    int minPos = rand() % nbVilles;
    int maxPos = rand() % nbVilles;
    while(maxPos < minPos){
            maxPos = rand() % nbVilles;
    }
    int seglen = maxPos - minPos + 1;
    int DNA1[seglen][2], DNA2[seglen][2];
    for(int i = 0;i < seglen;i++)
    {
        DNA1[i][0] = chemin[minPos + i];//this?
        DNA1[i][1] = 0;
        DNA2[i][0] = unIndividu.chemin[minPos + i];
        DNA2[i][1] = 0;
    }
    //check the duplication, flag 0 means non-duplication
    int nbdup = 0;
    for(int i = 0;i < seglen;i++)
    {
        for(int j = 0;j < seglen;j++)
        {
            if(DNA1[i][0] == DNA2[j][0])
            {
                nbdup++;
                DNA1[i][1] = 1;
                DNA2[j][1] = 1;
            }
        }
    }
    //note the position of dupliicated elements
    int nondup = seglen - nbdup;
    int DNA1dup[nondup][2], DNA2dup[nondup][2];
    int compt = -1;
    for(int i = 0;i < seglen;i++)
    {
        if(DNA1[i][1] == 0)//means distinct element
        {
            for(int j = 0;j < nbVilles;j++)
            {
                if(DNA1[i][0] == unIndividu.chemin[j])
                {
                    compt++;
                    DNA1dup[compt][0] = DNA1[i][0];
                    DNA1dup[compt][1] = j;
                }
            }
        }
    }
    compt = -1;
    for(int i = 0;i < seglen;i++)
    {
        if(DNA2[i][1] == 0)//means distinct element
        {
            for(int j = 0;j < nbVilles;j++)
            {
                if(DNA2[i][0] == chemin[j])//this?
                {
                    compt++;
                    DNA2dup[compt][0] = DNA2[i][0];
                    DNA2dup[compt][1] = j;
                }
            }
        }
    }
    for(int i = 0;i < nondup;i++)
    {
        chemin[DNA2dup[i][1]] = DNA1dup[i][0];
    }
    for(int i = 0;i < seglen;i++)
    {
        chemin[minPos + i] = DNA2[i][0];
    }
}

int* Individu::way_to_array()
{
    int nbcity = getNbVilles();
    int *shuzu = (int*)malloc(sizeof(int)*(1+nbcity));
    for(int i = 0;i < nbcity;i++)
    {
        shuzu[i] = chemin[i];
    }
    shuzu[nbcity] = chemin[0];
    return shuzu;
}
