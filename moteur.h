
#include <iostream>
#include <set>
#include <vector>
#include<map>
#include <cstdio>
#include <cstring>
using namespace std;
using std::set;
class lecteur
{
public:

    ~lecteur(){};
    vector<string> lire (string chemin_fichier);

};


class traiteur
{
 public:

     virtual ~traiteur(){};
     virtual vector<string>traiter (vector<string>)=0;//sans implémentation
};
class traiterponc : public traiteur
{
public:
    virtual ~traiterponc(){};
    vector<string>  traiter(vector<string>);
};

class traitermaj : public traiteur
{
public:
     virtual ~traitermaj (){};
    vector<string>  traiter(vector<string>);
};

class traitermotsvides : public traiteur
{
public:
     virtual ~traitermotsvides(){};
    vector<string> traiter(vector<string>  );
};
class statistique
{
public:

    string mot ;
    double valeur ;
    string chemin;
    statistique(){}
    ~statistique(){};
    statistique(string m,int occu,string chemfich)
    {
        mot=m;
        valeur=occu;
        chemin=chemfich;
    }
    static bool comparestat(statistique &a,statistique &b)
    {
        return a.valeur>b.valeur;
    }

};
class statmap
{
public:
    double valeur ;
    string chemin;
    statmap(){}
    statmap(int occu,string chemfich)
    {

        valeur=occu;
        chemin=chemfich;
    }
};
class analyseur
{
public:

    virtual ~analyseur(){};
    virtual vector< statistique>analyser (vector <string> const,string emplacement)=0;// une méthode virtuelle pure sans implémentation
};


class analyseurOccurence : public analyseur
{
public:

    virtual ~analyseurOccurence(){};
    vector< statistique> analyser(vector <string>, string chemin_fichier);//prend un vecteur de mots et retourne un vecteur contenant des tuples (mot,occurence de cette mot,nom du fichier)
};

class  AnalyseurMap : public analyseur
{
public:
    virtual ~AnalyseurMap(){};
    vector<statistique > analyser(vector <string> texteAAnalyser,string chemin_fichier );
};
class indexo
{

public:
    static const string  fileSave;//="statistics.txt";
    std::set<string> fichiersDejaIndexes;
public:
    virtual ~indexo(){};
    virtual void sauvegarderStat ()=0;
    virtual void ajouter(statistique)=0;
    virtual vector<statistique>  getIndexmot(string mot)=0;
    virtual void  afficheData()=0;
    virtual vector<statistique>  lecteurIndex () =0;
    virtual void supprimerData( string filepath)=0;
};
class indexvector:public indexo
{
    public:
        vector<statistique > indexData ;
        vector<statistique>  getIndexmot(string mot);
        void sauvegarderStat ();
        void supprimerData( string filepath);
        void ajouter(statistique s);
        void afficheData();
        virtual ~indexvector(){};
        virtual vector<statistique >  lecteurIndex ();

};

class indexmap:public indexo
{
public:
    map <string,vector<statmap> >indexData ;
    vector<statistique>  getIndexmot(string mot);
    void sauvegarderStat ();
    void supprimerData( string filepath);
    void ajouter(statistique s);
    void  afficheData();
    virtual ~indexmap(){};
    virtual vector<statistique>  lecteurIndex ();
};
class Bibliotheque //la classe Bibliotheque va retourner un vector qui contient les noms des fichiers qu'on va les analyser
{
public:
      Bibliotheque();
      bool ajouterFichiers(string cheminFichier);
      bool supprimerFichier(string cheminFichier);
      void affichageFichiers(std::ostream& flux)const;
      void saveDirectory();
      friend std::ostream& operator<<(std::ostream& flux,Bibliotheque const& bib);
      vector <string> fichiers;
      static const string  files;//"repertoire.txt";


};
class gestionnaire
{
public:

    void SauvergarderIndex(indexo*i);
    vector<statistique> RestaurerIndex(indexo*i);
};
class ordannanceur
{
public:

    virtual ~ordannanceur(){};
    virtual vector<string> ordannancer (vector<string>,indexo*i )=0;// prend un vecteur contenant les statistiques des mots de notre requette apres analyse et retourne le vecteur contenant les statistiques de ces mots aprés ordonnancement
};
class ordannanceurValeur:public ordannanceur
{
public:

    virtual ~ordannanceurValeur(){};
    vector<string> ordannancer (vector<string>,indexo*i );
};


class moteurderecherche
{

public:
        lecteur l;
        vector<traiteur* > tv ;
        indexo* i ;
        analyseur* a;
        ordannanceur* o;
        Bibliotheque bib;
        gestionnaire gest;
        ~moteurderecherche()
      {


            delete a ;
            tv.clear();
            delete i;
            delete o;
      }

        void indexerfichier (string cheminf);
        vector<string>  filesDirectory (std::string pathDirectory);
        vector<string >  rechercher (vector<string> req);
        void supprimerIndex(string cheminFichier);

        void afficherToutLesIndex();
        moteurderecherche(lecteur lec , vector<traiteur* > tr,indexo* id,analyseur* an,ordannanceur* ord)
        {
            l=lec;
            tv=tr;
            i=id;
            a=an;
            o=ord;

        }
};
// MINI_PROJET_C++_H_INCLUDED
