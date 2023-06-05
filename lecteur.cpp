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








vector<string> lecteur::lire(string cheminFichier)
{
    vector<string> mots;
    string mot;

    ifstream fichier(cheminFichier);//ouvrir le fichier en mode lecture
    if (!fichier.is_open()) {
        cerr << "impossible d'ouvrir le fichier " << cheminFichier << endl;// pour afficher le message dÕerreur immŽdiatement et ne stocke pas le message dÕerreur ˆ afficher plus tard dans un tompon

    }
    else
        while (fichier >> mot) {
            mots.push_back(mot);
        }
        fichier.close();

    return mots;
}
