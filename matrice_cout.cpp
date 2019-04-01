#include "matrice_cout.h"

distances pays::m_distances;
ville_id_type pays::m_index_counter = 0;
map<string,pays::ville> pays::m_villes;
vector<pays::ville*> pays::m_villes_par_index;

void pays::charge(const char* leFichierVille, const char* leFichierDistance)
{
    m_distances.clear();
    m_villes.clear();
    m_villes_par_index.clear();

    ifstream input(leFichierVille);
    while(input.good())
    {
        pays::ville villeCourante = pays::ville(pays::ville::assign_index());//???
        input >> villeCourante;
        if(input.good())
        {
            m_villes[villeCourante.nom()] = villeCourante;
        }
    }
    input.close();

    m_distances.setnb((unsigned)m_villes.size());
    input.open(leFichierDistance);
    while(input.good())
    {
        string villeCourante;
        input >> villeCourante;
        if(input.good() && villeCourante.length() > 0)
            m_villes[villeCourante].litDistance(input);
    }
    input.close();

    m_villes_par_index.resize(m_villes.size());
    for(std::map<string, ville>::iterator courant = m_villes.begin();
        courant != m_villes.end(); courant ++)
        m_villes_par_index[courant->second.index()] = &(courant->second);
}

