#include <fstream>
#include <iostream>
#include "moteur.h"
#include <vector>
#include <string>
#include <sstream>
#include<cstdlib>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <dirent.h>
#include <cstdio>
#include <cstring>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::vector;
using std::string;using std::multiset; using std::set;



vector< statistique> analyseurOccurence::analyser( vector <string>  vect , string cheminfichier)
{
    vector <statistique> v;
    for(int unsigned i=0;i<vect.size();i++)
    {
        int k=0;
        for(int unsigned j=0;j<vect.size();j++) //je recherche le nombre d'occ de chaque mot avec incrementation du entier k
        {
            if(vect[i]==vect[j])
                {
                    k=k+1;
                }
        }
        statistique s(vect[i],k,cheminfichier); // creation d une instance de la classe statistique conteant mot,nombre d'occu et le chemin fichier
        int t=0 ;
        for(int unsigned h=0;h<v.size();h++)
            if(v[h].mot==s.mot)
                t=t+1;
        if(t==0)
            v.push_back(s);
    }
    return v;
}

vector<statistique > AnalyseurMap::analyser(vector <string> texteAAnalyser,string chemin_fichier)
{
    cout<<" using analyseur map"<<endl;
    map <string,statmap>Occurence;
    for(unsigned int i=0;i<texteAAnalyser.size();++i)
    {
        ++Occurence[texteAAnalyser[i]].valeur;
        Occurence[texteAAnalyser[i]].chemin= chemin_fichier ;//incrémenter le nombre d'occurrence  du mot ( texte[i])
    }
    vector <statistique > statistics;
    for(map<string,statmap> ::const_iterator it=Occurence.begin();it!=Occurence.end();++it)
    {
        statistique p(it->first,it->second.valeur,it->second.chemin);
        statistics.push_back(p);
    }

    return statistics;
}

