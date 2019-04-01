//Qin ZHANG
#include "affiche_villes.h"
#include "Population.h"
#include "critere_arret.h"

#define PROB_MUTE 0.1
#define NUM_INDI 1000
list_of_points AfficheVilles::m_points;

int main (int argc, char *argv[])
{
    srand(time(0));
    critere_arret stop;
    pays monPays;
    monPays.charge("villes.htm","distances.htm");
    int nbindi = NUM_INDI;
    double prob_mute = PROB_MUTE;
    Population GA(nbindi,prob_mute);
    while(stop.continuer(GA))
    {
        GA.evolution();
        cout << "generation: " << GA.getgeneration() << endl;
        GA.showbest();
        cout << endl;
    }
    int* bestway;
    bestway = GA.showbest();
    list_of_points points;
    for(int i = 0;i < monPays.nbvilles()+1;i++)
    {
        coordinates a = monPays[bestway[i]].coordonnee();
        point b(a.x,a.y);
        points.push_back(b);
    }

    AfficheVilles::init(argv, argc);
    AfficheVilles::create(points);
    AfficheVilles::showAndWait();

    return 0;
}
