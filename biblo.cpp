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
#include <cstdio>
#include <cstring>
using namespace std;
const string Bibliotheque::files="repertoire.txt";
///*************class Bibliotheque********
Bibliotheque::Bibliotheque(){

      ifstream fichier(files.c_str());
            string mot;
                  while (fichier >>mot)
                  {
                        fichiers.push_back(mot);
                  }
      }

bool Bibliotheque::ajouterFichiers(string cheminFichier)
{
    bool existe;
    if(find(fichiers.begin(), fichiers.end(), cheminFichier)==fichiers.end())
    {
        fichiers.push_back(cheminFichier);

        existe=false;
        saveDirectory();
    }
else
{
      existe=true;
      cout<<"le fichier existe "<<endl;
}
   return existe;
}


std::ostream& operator<<(std::ostream& flux,Bibliotheque const& bib)
{
      bib.affichageFichiers(flux);
      return flux;
}

void  Bibliotheque::affichageFichiers(std::ostream& flux)const{
    if(!fichiers.empty())
    {

        for(unsigned int i(0);i<fichiers.size();++i)
        {
            flux<<fichiers[i]<<endl;
        }
    }
    else
    {
        cout<<"aucun fichier trouve"<<endl;
    }


}

void Bibliotheque::saveDirectory()
{
      ofstream ecrire(files.c_str());

        if (ecrire)
        {
              for (unsigned int i(0);i<fichiers.size();i++)
              ecrire<<fichiers[i]<<endl;
        }
}

bool Bibliotheque::supprimerFichier(string cheminFichier)
{   bool existe;
    vector<string>::iterator it;
    it=find(fichiers.begin(), fichiers.end(), cheminFichier);
    if(it!=fichiers.end())
    {
        fichiers.erase(it);
        existe=true;
        saveDirectory();
     }
     else
    {
        cout<<"fichier n'existe pas"<<endl;
        existe=false;
    }
    return existe;
}



