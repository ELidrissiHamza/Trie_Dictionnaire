#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include<algorithm>
using namespace std;


/**  Trier les mots par nombre de lettres (utilisation d'une fonction lamda) **/
vector<string> trier_nbr_lettre(const string &file_src, vector<string> &v)
{
    fstream file;
    string word;
    ///ouverture de fichier
    file.open(file_src.c_str());
    ///lecture mot par mot
    while(file >> word)
    {
        v.push_back(word);
    }
    /// fermeture de fichier
    file.close();
    ///fonction lamda
    auto lambda = [](const string & a, const string & b) -> bool
    {
        ///si les deux mots ont la meme taille on retourne true
        if(a<b&& a.length()==b.length()) return true; // meme taille mais different chiane
        return a.length() < b.length();
    };
    sort(v.begin(),v.end(),lambda);
    return v;
}



/** Fonction de trie alphabetiquement des mots de dictionnaire  **/
vector<string> & trier_dictionnaire(const string &file_src,const string &file_dest,vector<string> &vec )
{
    fstream file;
    string word;
    file.open(file_src.c_str());
    while(file >> word)
    {
        vec.push_back(word);
    }
    file.close();
    std::sort(vec.begin(), vec.end());

    ofstream TriFile(file_dest);
    for(auto & i : vec)
    {
        TriFile<<i<<endl;
    }
    TriFile.close();
    return vec;
}


/** Fonction pour generer un mot d'une maniere random **/
string gen_random(const int len)
{
    static const char alphanum[] ="abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}
/** Fonction pour generer un ensemble de mots d'une maniere random   **/
void garbage_data(const string &file_name,int nbr_Mots)
{
    ofstream myFile(file_name);

    for(int i=0; i<nbr_Mots; i++)
    {
        string mot=gen_random(rand()%10);
        myFile<<mot<<" ";
    }
    myFile.close();
}

/** Fonction pour chercher un mot dans un dictionnaire (Vecteur)  **/

void chercher_mot(vector<string>v,string mot)
{
    vector<string>::iterator it;
    it=find(v.begin(),v.end(),mot);
    if(it!=v.end())
        cout<<"\n\n"<<mot<<"    Exist XD \n";
    else
        cout<<"\n\n"<<mot<<"  N'existe pas !!\n";
}

/** Surcharge de l'operateur << pour le vecteur des entiers **/


ostream& operator<<(ostream& o, vector<int> v)
{
    o<<"{";
    for(auto var:v)
        o<<var<<"     ";
    o<<"}";
    o<<endl;
    return o;
}

/*
bool paire(int i)
{
    return i>20;
}*/

int main()
{
    vector<string> vec{};
    srand(NULL);
    garbage_data("dictionaire.txt",100);
    vec=trier_dictionnaire("dictionaire.txt","tried_Dic.txt",vec);
    vec=trier_nbr_lettre("dictionaire.txt",vec);
    for(auto & i : vec)
    {
        cout<<i<<endl;
    }


    chercher_mot(vec,"dmcp");

    return 0;
}
