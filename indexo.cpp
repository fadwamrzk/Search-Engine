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




///***********toutes les methodes de l'indexo*********************
const string indexo::fileSave="index.txt";

vector<statistique> indexvector::getIndexmot(string m)
{
    vector<statistique>s;
    for (unsigned p=0; p<indexData.size(); p++){
        if (indexData[p].mot==m){
            s.push_back(indexData[p]);
        }}
    return s;
}

void indexvector::ajouter(statistique s)
{
    indexData.push_back(s);
}
///************methode sauvegarderStat***************
void  indexvector::afficheData()
{
     for (unsigned p=0; p<indexData.size(); p++)
        {
            cout<<"Mot:"<<indexData[p].mot << " valeur:" << indexData[p].valeur << " chemin:" << indexData[p].chemin<<endl;
        }
}

void  indexmap::afficheData()
{
    map<string, vector<statmap> >::iterator it;
    for (it = indexData.begin(); it != indexData.end(); it++)
    {
        for (unsigned p=0; p<it->second.size(); p++)
        {
            cout<<"Mot:"<<it->first << " valeur:" << it->second[p].valeur << " chemin:" <<  it->second[p].chemin<<endl;

        }

    }
}
void indexvector::sauvegarderStat ()
{

       ofstream ecrire(fileSave.c_str());
        if (ecrire)
        {
              for (unsigned int j(0);j<indexData.size();j++)
              ecrire<<indexData[j].mot<<" "<<indexData[j].valeur<<" "<<indexData[j].chemin<<endl;
        }
}
void indexmap::sauvegarderStat ()
{

       ofstream ecrire(fileSave.c_str());
        if (ecrire)
        {
             map<string, vector<statmap> >::iterator it;
            for (it = indexData.begin(); it != indexData.end(); it++)
            {
                for (unsigned p=0; p<it->second.size(); p++)
                {
                    ecrire<<it->first<<" "<<it->second[p].valeur<<" "<<it->second[p].chemin<<endl;
                }
            }
        }
}
///************methode lecteurIndex**************
//**********class IndexVector*************
vector <statistique >  indexvector:: lecteurIndex ()
{

    vector<statistique >savedIndex;
    vector <string> texteIndex;

    ifstream lire(indexo::fileSave.c_str());
    if(lire)
    {
        istream_iterator<string> it(lire);

        istream_iterator<string> fin;
           //Le signal de fin
        back_insert_iterator<vector<string> > it2(texteIndex);

        copy(it, fin, it2);

        int nbrOcc;
        unsigned int i(0);

        while(i<texteIndex.size()-2)
        {

            istringstream iss;
            iss.str(texteIndex[i+1].c_str());
            iss>>nbrOcc;

            savedIndex.push_back (statistique(texteIndex[i],nbrOcc,texteIndex[i+2]));
            fichiersDejaIndexes.insert(texteIndex[i+1]);
            i+=3;
        }
    }

    return savedIndex;//retour d'un vector contenant les statistiques lues à partir de fichier de sauvegarde
}


vector<statmap> make_vector(int valeur, string chemin) {
  vector<statmap> result;
  statmap c(valeur,chemin);
  result.push_back(c);

  return result;
}
///************methode lecteurIndex**************
//**********class IndexMultimap*************

void indexmap::ajouter(statistique s)
{

    statmap c (s.valeur,s.chemin);
    int j =0;
    map<string, vector<statmap> >::iterator it;
    if(false==indexData.empty())
    {
        for (it = indexData.begin(); it != indexData.end(); it++)
        {
            if  (it->first==s.mot)
            {
                indexData[it->first].push_back(c);
                j=j+1;
            }
        }
        if(j==0)
        {
            indexData.insert(std::make_pair(s.mot,make_vector(s.valeur,s.chemin) ));
        }

    }
    else
    {
       indexData.insert(std::make_pair(s.mot,make_vector(s.valeur,s.chemin) )) ;

    }

}

void indexvector::supprimerData( string filePath)
{
    vector<statistique > ::iterator it =indexData.begin();
    while(it!=indexData.end())
    {
        if((*it).chemin==filePath)    //suppression de l'ancien index
        {
            it=indexData.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
void indexmap::supprimerData( string filepath)
{
    map<string, vector<statmap> >::iterator it;
    for (it = indexData.begin(); it != indexData.end(); it++)
    {
        for (auto j = it->second.begin(); j!= it->second.end(); ++j)
        {
            if (j->chemin==filepath)
            {
                if(it->second.size()>1)
                {   it->second.erase(j);
                }


                else
                {
                    indexData.erase(it);
                }
            }
        }
    }
}

vector<statistique> indexmap::getIndexmot(string m)
{
    vector<statistique>s;

    map<string, vector<statmap> >::iterator it;
    for (it = indexData.begin(); it != indexData.end(); it++)
    {
        if  (it->first==m)
            {
                for (unsigned p=0; p<it->second.size(); p++){
                statistique su(it->first,it->second[p].valeur,it->second[p].chemin);
                s.push_back(su);
                }


            }
    }
    return s;
}
vector<statistique > indexmap:: lecteurIndex ()
{
    vector<statistique > savedIndex;
    ifstream lire (fileSave.c_str());
    if(lire)
    {
        string ligne,mot,nomFichier;
        int nbrOcc;
        istringstream iss;
        while(getline(lire,ligne))
        {
                    iss.clear();
                    iss.str(ligne);
                    iss>> mot>>nbrOcc>>nomFichier;
                    savedIndex.push_back (statistique(mot,nbrOcc,nomFichier));
                    fichiersDejaIndexes.insert(nomFichier);
                    mot.erase();
                    nomFichier.erase();
                    nbrOcc=0;
        }

    }
    return savedIndex;
}


