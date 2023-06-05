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




vector<statistique> gestionnaire::RestaurerIndex(indexo*i)

{   vector<statistique> savedIndex;
    savedIndex=i->lecteurIndex();
    for(int unsigned j=0;j<savedIndex.size();j++)

        i->ajouter(savedIndex[j]);

    return savedIndex;
}
void gestionnaire::SauvergarderIndex(indexo*i)
{

    i->sauvegarderStat();
}

