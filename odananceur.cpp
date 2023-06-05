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
#include<unordered_set>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::vector;
using std::string;using std::multiset; using std::set;


vector<string> ordannanceurValeur::ordannancer(vector<string> req,indexo* i)
{
    vector<statistique>v2;
    vector<statistique>v1;

    vector<string>v3;
    vector<string> v4;


    /*for(int y=0;y<reqt.size();y++)
    {
        v1=i->getIndexmot(reqt[y]);

        for(int l=0;l<v1.size();l++)
        {

             v2.push_back(v1[l]);
        }

    }
    sort(v2.begin(),v2.end(),statistique::comparestat);

    for(int k=0;k<v2.size();k++)
    {
        v3.push_back(v2[k].chemin);

    }
return v3;*/


    for(int y=0;y<req.size();y++)
    {
        v1=i->getIndexmot(req[y]);
        for(int l=0;l<v1.size();l++)
             v2.push_back(v1[l]);

    }

    sort(v2.begin(),v2.end(),statistique::comparestat);


    unordered_set<string> s;
    unordered_set<string>::iterator itr;
    for(int k=0;k<v2.size();k++)
    {
        v3.push_back(v2[k].chemin);

    }
    for(int i=0;i<v3.size();i++)
    {
        s.insert(v3[i]);
    }
    for(itr=s.begin(); itr!=s.end(); itr++)
    {
        v4.push_back(*itr);
    }
return v4;

}

