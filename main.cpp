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
#include <chrono>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::vector;
using std::find;using std::multiset; using std::set;
using namespace std::chrono;




int main()
{

    lecteur l;
    traiterponc ponc;
    traitermaj maj;
    traitermotsvides mvides ;
    analyseurOccurence a;
    ordannanceurValeur o;
    indexvector   i;
    gestionnaire gest;
    Bibliotheque b;
    vector<traiteur*> total;
    total.push_back(&ponc);
    total.push_back(&maj);
    total.push_back(&mvides);

    moteurderecherche moteur (l, total,&i,& a,&o);


          cout<<"*********************MOTEUR DE RECHERCHE*********************"<<endl;
      cout<<endl;
      cout<<endl;
    vector<statistique> savedIndex;
    savedIndex=gest.RestaurerIndex(moteur.i);
    while(1)
    {
    cout<<"*************** Menu***************"<<endl;
    cout<<"1-Pour indexer un seul fichier tapez 1"<<endl;
    cout<<"2-Pour indexer une repertoire  tapez 2"<<endl;
    cout<<"3-Pour afficher votre index enregistré tapez 3"<<endl;
    cout<<"4-Pour afficher votre  nouveau index  tapez 4"<<endl;
    cout<<"5-Pour supprimer de votre index tapez 5"<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"6-Pour consulter votre Bibliotheque tapez 6"<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"7-Pour effectuer une recherche  tapez 7"<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"8-Pour changer la configuretion du moteur tapez 8"<<endl;
    cout<<"*****************************************"<<endl;
    cout<<"Pour enregistrer et quitter tapez 0"<<endl;
    cout<<"*****************************************"<<endl;
    char choix;
    cin>>choix;

    switch(choix)
        {
        case '1':
              {

                    cout<<"Entrer le chemin du fichier"<<endl;
                    while(getchar()!='\n');
                    string filePath;
                    getline(cin,filePath);
                    while( filePath.size()<5 || strcmp((filePath.substr(filePath.size()-4)).c_str(),".txt" )!=0)
                    {
                        cout << "chemin incorrect!" << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                        filePath.clear();
                        cin >> filePath;
                    }
                    auto start = high_resolution_clock::now();
                    bool existe;
                    existe=moteur.bib.ajouterFichiers(filePath);
                    if(existe==true)
                    {

                       cout<<"reindexation du fichier..."<<endl;

                        i.supprimerData(filePath);
                        moteur.indexerfichier(filePath);

                    }
                    else
                    {
                        cout<<" indexation du fichier..."<<endl;
                        moteur.indexerfichier(filePath);



                    }
                    auto stop = high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> float_ms = stop - start;
                    cout << "Temps pris par fonction: "<< float_ms.count() << " milliseconds" << endl;
                    break;
              }
         case '2':
              {
                    string path;
                    cout<<"Entrer le chemin du repertoire"<<endl;
                    while(getchar()!='\n');
                    getline(cin,path);
                    vector <string> fichiersAIndexer=moteur.filesDirectory(path);
                    auto start = std::chrono::high_resolution_clock::now();
                    if(!fichiersAIndexer.empty())
                    {
                            for(unsigned int k(0);k<fichiersAIndexer.size();++k)
                        {
                            bool existe;
                            existe=moteur.bib.ajouterFichiers(fichiersAIndexer[k]);
                            if(existe==true)
                            {
                                cout<<"file reindexing..."<<endl;
                                i.supprimerData(fichiersAIndexer[k]);
                                moteur.indexerfichier(fichiersAIndexer[k]);

                            }
                            else
                            {cout<<"file indexing..."<<endl;
                            moteur.indexerfichier(fichiersAIndexer[k]);
                            }


                        }
                    }

                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> float_ms = end - start;
                    std::cout << " temps d'indexation " << float_ms.count() << " milliseconds" << std::endl;

                    break;
              }

        case '3':
            {
                  moteur.afficherToutLesIndex();
                  break;
            }

        case '4':
            {
                  moteur.i->afficheData();
                  break;
            }
        case '5':
            {
                    cout<<"Entrer le chemin du fichier"<<endl;
                    string filePath;
                    getline(cin,filePath);
                    moteur.supprimerIndex(filePath);
                    break;
            }
        case '6':
            {
                cout<<moteur.bib;
                break;
            }
        case '7':
            {
                string motsRecherches;
                cout<<"Veuillez entrer votre requête de recherche "<<endl;
                while(getchar()!='\n');
                getline(cin,motsRecherches);

                vector <string> motCles;
                string mot;
                istringstream extraire( motsRecherches);
                while(extraire>>mot)
                {
                    motCles.push_back(mot);
                }
                vector<string>ord;
                auto start = high_resolution_clock::now();
                ord=moteur.rechercher(motCles);
                auto stop = high_resolution_clock::now();
                std::chrono::duration<double, std::milli> float_ms = stop - start;
                cout<<"les resultats du recherche :"<<endl;
                for(int unsigned j=0;j<ord.size();j++)
                    cout<<ord[j]<<endl;
                cout << "Temps de la recherche: "<< float_ms.count() << " milliseconds" << endl;
            break;
            }
        case '8':
            {

                char choix1,choix2,choix3,choix4,choix5,choix6,choix7;

                cout<<"Pour changer le type de traiteur tapez 1"<<endl;
                cout<< "Pour changer le type d'analyseur tapez 2"<<endl;
                cout<< "Pour changer le type de l'index tapez 3"<<endl;
                cout<< "Pour changer le type d'ordonnanceur tapez 4"<<endl;
                while(getchar()!='\n');
                cin>>choix1;
                switch(choix1)
                {
                case '1':
                {
                    cout<<" Pour effectuer un seul traitement tapez 1"<<endl;
                    cout<<" Pour effectuer plusieurs traitements tapez 2 "<< endl;
                    while(getchar()!='\n');
                    cin>>choix2;
                    switch(choix2)
                    {
                        case '1':
                        {
                            cout<<" Pour choisir traiteurPonctuation  tapez 1"<<endl;
                            cout<<" Pour choisir traiteurMajuscule tapez 2"<<endl;
                            cout<<" Pour choisir traiteurMotsvides  tapez 3"<<endl;
                            while(getchar()!='\n');
                            cin>>choix3;
                            switch(choix3)
                            {
                                case '1':
                                {
                                    moteur.tv.clear();
                                    traiterponc ponc ;
                                    moteur.tv.push_back(&ponc);


                                }
                                case '2' :
                                {
                                moteur.tv.clear();
                                traitermaj maj ;
                                moteur.tv.push_back(&maj);

                                }
                                case '3' :
                                {
                                    moteur.tv.clear();
                                    traitermotsvides motsvides ;
                                   moteur.tv.push_back(&motsvides);

                                }
                                default:
                                {   cout<<"invalid choice"<<endl;
                                    while(getchar()!='\n');
                                }
                                break;

                            }
                         break;
                        }

            case '2' :
                {
                    moteur.tv.clear();
                    cout<<" Pour ajouter un  traiteur de Ponctuation  tapez 1"<<endl;
                    cout<<" Pour ajouter un traiteur de Majuscule tapez 2"<<endl;
                    cout<<" Pour ajouter un traiteur de Motsvides  tapez 3"<<endl;
                    while(getchar()!='\n');
                    cin>>choix4;
                    switch(choix4)
                    {
                    case '1':
                        {
                            traiterponc ponc ;
                            moteur.tv.push_back(&ponc);
                            break;

                        }
                    case '2' :
                    {
                        traitermaj maj ;
                        moteur.tv.push_back(&maj);
                        break;
                    }
                    case '3' :
                    {
                        traitermotsvides motsvides ;
                        moteur.tv.push_back(&motsvides);
                        break;
                    }

                    }
                break;
                }

                }
            break;
            }


        case '2':
              {
                   cout<<"Choix d'analyseur"<<endl;

                   cout<<"Pour choisir un  Analyseur d'Occurence tapez 1"<<endl;

                   cout<<"Pour choisir un AnalyseurMap tapez 2"<<endl;
                   while(getchar()!='\n');
                  cin>>choix5;
                  switch(choix5)
                  {
                  case '1':
                        {
                            moteur.a=new analyseurOccurence ;
                            break;
                        }
                  case '2':
                        {
                            moteur.a=new AnalyseurMap ;
                            break;
                        }
                default:
                {

                cout<<"Choix invalide!"<<endl;
                while(getchar()!='\n');
                }
                }

         break;
              }

   case '3':
              {

                cout<<"Choix d 'index"<<endl;

                cout<<"Pour choisir un IndexVector tapez 1"<<endl;

                cout<<"Pour choisir un IndexMap tapez 2"<<endl;
                while(getchar()!='\n');
                cin>>choix6;
                switch(choix6)
                {
                case '1':
                    {
                        moteur.i=new indexvector;
                        savedIndex=gest.RestaurerIndex(moteur.i);
                        break;
                    }
                case '2':
                    {
                        moteur.i=new  indexmap;
                        savedIndex=gest.RestaurerIndex(moteur.i);
                        break;
                    }
                default:
                    {
                        cout<<"Choix invalide!"<<endl;
                        while(getchar()!='\n');
                    }
                  }
                break;
              }


case '4':
             {
                cout<<"Choix  d'Ordonnanceur"<<endl;
                cout<<"Pour choisir un OrdonnanceurBinaire tapez 1"<<endl;
                cout<<"Pour choisir un OrdonnanceurValeur tapez 2"<<endl;
                cin>>choix7;
                switch(choix7)
                {
                  case '1':
                        {
                              break;
                        }
                  case '2':
                        {

                          moteur.o=new  ordannanceurValeur;
                        break;
                        }
                         default:
                        {

                      cout<<"Choix invalide!"<<endl;
                      while(getchar()!='\n');
                               }
                  }
                  break;
             }

  default:
    {
        cout<<"Choix invalide!"<<endl;
        while(getchar()!='\n');
    }


}

break;
}

        case '0':
        {
            moteur.bib.saveDirectory();
            gest.SauvergarderIndex(moteur.i);

                    exit(0);
        }

         default:
        {
                cout<<"Choix invalide!"<<endl;


        }
    return 0;

}
        }
}
