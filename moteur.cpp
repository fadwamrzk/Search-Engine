#include <fstream>
#include <iostream>
#include "moteur.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include<cstdlib>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <dirent.h>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::vector;
using std::string;using std::multiset; using std::set;



void moteurderecherche::indexerfichier(string cheminf)
{

    vector<string>propre;
    vector<string>traite;
    vector<statistique> resultatsIndex;
    vector<string>tmp;
    traite=l.lire(cheminf);
    for(int unsigned j=0;j<tv.size();j++)
    {   tmp=tv[j]->traiter(traite);
        traite=tmp;
        tmp.clear();
    }
    resultatsIndex =a->analyser(traite,cheminf);
    for(int unsigned j=0;j<resultatsIndex.size();j++)
        i->ajouter(resultatsIndex[j]);
}


vector<string>  moteurderecherche::filesDirectory (std::string pathDirectory)
{
    vector<string> fichiersAIndexer;

    struct dirent *entry;
    DIR *dir = opendir(pathDirectory.c_str());

    if (dir == NULL)
    {
        cout<<"can't open directory"<<endl;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        string path(entry->d_name);

        if(path.size()>=5 && strcmp((path.substr(path.size()-4)).c_str(),".txt")==0)
        {

                fichiersAIndexer.push_back(pathDirectory+'/'+path);
        }
       path.clear();
    }
    closedir(dir);

    return fichiersAIndexer;
}



///**************supprimerIndex********
void moteurderecherche::supprimerIndex(string cheminFichier)
{
    bool existe;
    existe=bib.supprimerFichier(cheminFichier);
    vector<statistique >  savedIndex=i->lecteurIndex();
    vector<statistique > ::iterator it =savedIndex.begin();
    if(existe==true)

    {
        while(it!=savedIndex.end())
    {

        if((*it).chemin==cheminFichier)    //suppression de l'ancien index
        {
            it=savedIndex.erase(it);
        }
        else
        {
            ++it;
        }
    }
    }
    i->sauvegarderStat();

}
///********************affcherToutLesIndex*********
void moteurderecherche::afficherToutLesIndex()
{
    vector<statistique >  savedIndex;
    savedIndex=i->lecteurIndex();



    for(unsigned int k(0) ;k<savedIndex.size();k++)
    {

        cout<< '<'<<savedIndex[k].mot<<";"<<savedIndex[k].valeur<<";"<<savedIndex[k].chemin<<'>'<<endl;
    }




}



vector<string>moteurderecherche::rechercher(vector<string >req)
{

    vector<string>ord ;
    vector<string>tmp;
    for(int unsigned j=0;j<tv.size();j++)
    {   tmp=tv[j]->traiter(req);
        req=tmp;
        tmp.clear();
    }

    ord=o->ordannancer(req,i);

    return ord;



}
