#ifndef MATRICE_COUT_H
#define MATRICE_COUT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

typedef unsigned ville_id_type;

class distances:
public std::vector<unsigned>
{
private:
    unsigned m_nombre_villes;
public:
    void setnb(unsigned leNombreDeVilles)
    {
        m_nombre_villes = leNombreDeVilles;
    }
    unsigned& distance(ville_id_type unDepart, ville_id_type uneArrivee)
    {
        return std::vector<unsigned>::operator[](unDepart * m_nombre_villes + uneArrivee);
    }

};


struct coordinates
{
    unsigned x;
    unsigned y;
};


class pays
{

private:
    static ville_id_type m_index_counter;
    static distances m_distances;

public:
    class ville
    {
        template<class charT, class traits>
        friend std::basic_istream<charT, traits>& operator >> (std::basic_istream<charT, traits>& unFlux, pays::ville& uneVille );
        friend class pays;
    private:
        string m_nom;
        coordinates m_coord;
        ville_id_type m_index;
    public:
        class assign_index {};

        ville()
        {
            //std::cout << "Creating Ville\n";
        }
        ville(assign_index): m_index(pays::m_index_counter ++)
        {
            //std::cout << "Ville " << pays::m_index_counter << "\n";
        }

        template<class charT, class traits>
        basic_istream<charT, traits>& litDistance(basic_istream<charT, traits>& unFlux);

    public:
        const coordinates& coordonnee() const
        { return m_coord; }
        coordinates& coordonnee()
        { return m_coord; }
        unsigned operator[] (ville_id_type uneVille) const
        { return pays::m_distances.distance(m_index, uneVille); }
        string nom() const
        { return m_nom;}
        int index() const
        { return m_index;}
    };

private:
    static std::map<string, ville> m_villes;
    static std::vector<ville*> m_villes_par_index;

public:
    pays() {}

    const ville& operator [] (ville_id_type uneVille) const
    { return *m_villes_par_index[uneVille]; }

    const ville& operator [] (string uneVille) const
    { return m_villes[uneVille]; }

    ville& operator [] (const string &uneVille)
    { return m_villes[uneVille]; }

    ville& at(const string &uneVille)
    { return m_villes[uneVille]; }

    int nbvilles(){return m_index_counter - 1;}//

    static void charge(const char* leFichierVille, const char* leFichierDistance);

};

template<class charT, class traits>
std::basic_istream<charT, traits>& operator >> (std::basic_istream<charT, traits>& unFlux,
						coordinates& desCoordonnees)
{
    unFlux >> desCoordonnees.x >> desCoordonnees.y;
    return unFlux;
}

template<class charT, class traits>
std::basic_istream<charT, traits>& operator >> (std::basic_istream<charT, traits>& unFlux,
						pays::ville& uneVille )
{
    unFlux >> uneVille.m_nom >> uneVille.coordonnee();
    return unFlux;
}


template<class charT, class traits>
basic_istream<charT, traits>& pays::ville::litDistance(basic_istream<charT, traits>& unFlux)
{
    string ville_destination;
    unsigned distance;
    unFlux >> ville_destination >> distance;
    if(unFlux.good())
    {
        m_distances.push_back(distance);
    }
    return unFlux;
}


#endif
