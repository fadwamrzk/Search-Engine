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





vector<string> traiterponc::traiter(vector<string> mots)
{
    vector<string> t ;
    for(int unsigned i=0;i<mots.size();i++)
    {
        string text =mots[i];
        text.erase(std::remove_if(text.begin(), text.end(), ::ispunct), text.end());

        t.push_back(text);
    }
    return t;
}
vector<string>traitermotsvides::traiter(vector<string> mots)
{
    lecteur l ;
    vector<string> m ;
    vector<string> motsvides=l.lire("/Users/Cyrinelounissi/Desktop/motsvides1.txt");
    int k=1;
    for(int unsigned j=0;j<mots.size();j++)
    {
        string ch=mots[j];
        for(int unsigned i=0;i<motsvides.size();i++)
            {
                if(ch == motsvides[i])
                {
                    k=k+1;
                }
            }
        if(k==1)
            m.push_back(ch);
        k=1;
    }
    return m ;
}
vector<string>traitermaj::traiter(vector<string> mots)
{
for(int i=0;i<mots.size();i++)
{
        for (int j=0;j<mots[i].length();j++)
            if ((mots[i][j]>='A') && (mots[i][j]<='Z'))
        {
                mots[i][j]=mots[i][j]+32;
        }
}
return mots;
}
