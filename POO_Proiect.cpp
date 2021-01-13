#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <regex>
#include <iterator>
#include <vector>

using namespace std;
class Scrisoare //Am construit clasa de baza
{
private:
    string nume;
    string prenume;
    int varsta;
    string oras;
    string culoare;

public:
    ~Scrisoare(); //Destructor
    string wishlist[3];
    //setters
    void setNume(string numeC)
    {
        nume = numeC;
    }
    void setPrenume(string prenumeC)
    {
        prenume = prenumeC;
    }
    void setVarsta(int varstaC)
    {
        varsta = varstaC;
    }
    void setOras(string orasC)
    {
        oras = orasC;
    }
    void setWishlist(string wishlistC[])
    {
        int i, dim;
        dim = sizeof(wishlist) / sizeof(wishlist[0]);

        for (i = 0; i < dim; i++)
            wishlist[i] = wishlistC[i];
    }
    void setCuloare(string culoareC)
    {
        culoare = culoareC;
    }
    void setScrisoare(string numeC, string prenumeC, int varstaC, string orasC, string culoareC, string wishlistC[])
    {
        nume = numeC;
        prenume = prenumeC;
        varsta = varstaC;
        oras = orasC;
        culoare = culoareC;
        int i, dim;
        dim = sizeof(wishlist) / sizeof(wishlist[0]);

        for (i = 0; i < dim; i++)
            wishlist[i] = wishlistC[i];
    }
    //getters
    string getNume()
    {
        return nume;
    }
    string getPrenume()
    {
        return prenume;
    }
    int getVarsta()
    {
        return varsta;
    }
    string getOras()
    {
        return oras;
    }
    string *getWishlist()
    {
        cout << endl;
        return wishlist;
    }
    string getCuloare()
    {
        return culoare;
    }
};
Scrisoare ::~Scrisoare(void)
{
    cout << "Obiectul a fost sters!" << endl;
}
class Copil //Clasa copil pentru a putea verifica conditiile copiilor
{
protected:
    string nume, prenume;
    string status;
    int buget;

public:
    ~Copil(); //destructor copil
    void setNume(string name)
    {
        nume = name;
    }
    void setPrenume(string prename)
    {
        nume = prename;
    }
    void setBuget(int bug)
    {
        buget = bug;
    }
    void setStatus(string stat)
    {
        status = stat;
    }
    int getBuget()
    {
        return buget;
    }
    string getStatus()
    {
        return status;
    }
    string getNume()
    {
        return nume;
    }
    string getPrenume()
    {
        return prenume;
    }
};
Copil ::~Copil(void)
{
    cout << "Obiectul a fost sters!" << endl;
}

class Elfi : public Scrisoare, public Copil // Clasa elf mosteneste ambele clase (mostenire multipla)
{

public:
    void verificareCopil(Copil *cop, Scrisoare *scris);
    void alegereCadou(Copil *cop, Scrisoare *scris);
    ~Elfi();
};
Elfi ::~Elfi(void)
{
    cout << "Obiectul a fost sters!" << endl;
}
void Elfi ::verificareCopil(Copil *cop, Scrisoare *scris) //Veriicam statusul fiecarui copil(ne ajutam de un fisier in care am retinut statusul fiecaruia)
{

    string fisier = "statusCopil.txt";
    ifstream readFile(fisier);
    string nume;
    string prenume;
    string status;
    int buget;
    string separator = " ";
    int nr = 0;
    int i = 0;
    try
    {
        if (readFile.is_open())
        {
            while (getline(readFile, separator))
            {
                stringstream iss(separator);
                iss >> nume >> prenume >> status >> buget;
                cop[i].setStatus(status);
                cop[i].setBuget(buget);
                cop[i].setNume(nume);
                cop[i].setPrenume(prenume);
                i++;
            }
        }

        else
        {
            throw fisier;
        }
    }
    catch (string fisier)
    {
        cout << "Nu exista fisierul " << fisier << endl;
        exit(404);
    }
}

void Elfi ::alegereCadou(Copil *cop, Scrisoare *scris)
{
    string fisier = "jucariiAtelier.txt";
    ifstream readFile(fisier);
    string jucarie;
    int pret;
    vector<string> cadou;
    vector<float> money;
    int suma = 0;
    string separator = " ";
    try
    {
        if (readFile.is_open())
        {
            while (getline(readFile, separator))
            {
                stringstream iss(separator);
                iss >> jucarie >> pret;

                money.push_back(pret);
                cadou.push_back(jucarie);
            }
        }

        else
        {
            throw fisier;
        }
    }
    catch (string fisier)
    {
        cout << "Nu exista fisierul " << fisier << endl;
        exit(404);
    }

    for (int i = 0; i < 8; i++)
    {
        cout << scris[i].getNume() << " " << scris[i].getPrenume() << " primeste: ";
        if (cop[i].getStatus() == "cuminte")
        {
            int bani = 100;
            for (int j = 0; j < 3; j++)
            {

                for (int k = 0; k < cadou.size(); ++k)
                {

                    if (cadou.at(k) == scris[i].wishlist[j])
                    {
                        if (bani >= money.at(k))
                        {
                            cout << scris[i].wishlist[j] << " ";
                            bani = bani - money.at(k);
                        }
                    }
                }
            }
            if (bani == 100)
                cout << "Cadoua default special!\n";
            else if (bani > 0)
            {
                cout << bani << " acadele\n";
                suma += bani;
            }
        }
        else if (cop[i].getStatus() == "rau")
        {
            int bani = 10;
            for (int j = 0; j < 3; j++)
            {

                for (int k = 0; k < cadou.size(); ++k)
                {

                    if (cadou.at(k) == scris[i].wishlist[j])
                    {
                        if (bani >= money.at(k))
                        {
                            cout << scris[i].wishlist[j] << " ";
                            bani = bani - money.at(k);
                        }
                    }
                }
            }
            if (bani > 0)
                cout << "Cadou default!\n";
        }

        cout << endl;
    }
    cout << "Suma cheltuita pe acadele este de " << suma * 0.5 << " dolari" << endl;
}
class Troli : public Elfi
{
public:
    void invelireCadouri(Scrisoare *s, Copil *c);
};
void Troli ::invelireCadouri(Scrisoare *s, Copil *c)
{
    int i;
    int ambalajRoz = 0, ambalajBlue = 0; //calculul de ambalaje necesare

    for (i = 0; i < 8; i++)
    {
        if (c[i].getStatus() == "cuminte")
            if (s[i].getCuloare() == "pink")
                ambalajRoz++;
            else
            {
                if (s[i].getCuloare() == "blue")
                    ambalajBlue++;
            }
        else
        {
            if (c[i].getStatus() == "rau")
            {
                if (s[i].getCuloare() == "pink")
                {
                    ambalajRoz++;
                }
                else
                {
                    if (s[i].getCuloare() == "blue")
                    {
                        ambalajBlue++;
                    }
                }
            }
        }
    }
    cout << "Numarul de  ambalaje folosit pentru fete:" << ambalajRoz << endl;
    cout << "Numarul ambalaje folosit pentru baieti:" << ambalajBlue << endl;
}
class DoamnaCraciun
{
protected:
    int nrCarbuni;

public:
    vector<string> plecare, sosire;
    friend class Troli;
    void setCarbuni(int nrC)
    {
        nrCarbuni = nrC;
    }

    void pretCarbuni(Scrisoare *s, Copil *cop);
};
void DoamnaCraciun ::pretCarbuni(Scrisoare *s, Copil *cop) //Am calculat pretul carbunilor folositi
{
    int i, nr = 0;
    float sumaTotala = 0;
    for (i = 0; i < 8; i++)
        if (cop[i].getStatus() == "rau")
            nr++;
    setCarbuni(nr);
    sumaTotala = 0.5 * nr;
    cout << "Suma toatla pentru carbuni este de " << sumaTotala << " dolari";
}
#define edge pair<int, int>
class MosCraciun //Aici facem traseul lui Mos Craciun, distanta optima pe care acesta trb sa o parcurga astfel incat nr de km sa fie minim
{
private:
    vector<pair<float, edge>> G;
    vector<pair<float, edge>> T;
    int *parinte;
    int V;

public:
    friend class DoamnaCraciun; //Pentru a afla si doamna Craciun traseul lui Mos Craciun
    MosCraciun(int V);
    void Adaugare(int u, int v, float w); //Adauga coordonatele si costul
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal(); //Afla drumul minim(arborele de cost minim)
    void print(DoamnaCraciun *a, DoamnaCraciun *b);
    void print(); //Afisarea traseului fara sa l imparta cu Doamna Craciun
};
MosCraciun::MosCraciun(int V)
{
    parinte = new int[V];

    for (int i = 0; i < V; i++)
        parinte[i] = i;

    G.clear();
    T.clear();
}
void MosCraciun::Adaugare(int u, int v, float w)
{
    G.push_back(make_pair(w, edge(u, v)));
}
int MosCraciun::find_set(int i) //functie ce returneaza tatal unui nod, se incheie cand tatal nodului curent este chiar nodul curent
{

    if (i == parinte[i])
        return i;
    else

        return find_set(parinte[i]);
}

void MosCraciun::union_set(int u, int v) //functie care uneste noduriile
{
    parinte[u] = parinte[v];
}
void MosCraciun::kruskal()
{
    int i;
    float uRep, vRep;
    sort(G.begin(), G.end()); //se sorteaza muchiile crescator
    for (i = 0; i < G.size(); i++)
    {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep)
        {
            T.push_back(G[i]);
            union_set(uRep, vRep);
        }
    }
}
void MosCraciun::print(DoamnaCraciun *a, DoamnaCraciun *b) //afisarea traseului si impartasirea lui cu Doamna Craciun
{
    string orase[10] = {"Suwon", "Seoul", "Busan", "Deagu", "Dajeon", "Suwon"};
    cout << "Lista oraselor este:" << endl;
    float distTot = 0;
    float distLaponiaCoreaSud = 4157.77; //Am calculat distanta minima din Laponia pana in cel mai apropiat oras din Corea de Sud
    for (int i = 0; i < T.size(); i++)
    {
        a->plecare.push_back(orase[T[i].second.first]);
        b->sosire.push_back(orase[T[i].second.second]);
        cout << orase[T[i].second.first] << " - " << orase[T[i].second.second] << " : "
             << T[i].first;
        distTot += T[i].first;

        cout << endl;
    }
    cout << "Distanta totala parcusra de Mos Craciun este de " << (distTot + distLaponiaCoreaSud) << " mile" << endl;
}
void MosCraciun ::print() //Afisarea traseului fara impartasirea cu Doamna Craciun
{

    string orase[10] = {"Suwon", "Seoul", "Busan", "Deagu", "Dajeon", "Suwon"};
    cout << "Lista oraselor este:" << endl;
    float distTot = 0;
    float distLaponiaCoreaSud = 4157.77;
    for (int i = 0; i < T.size(); i++)
    {
        cout << orase[T[i].second.first] << " - " << orase[T[i].second.second] << " : "
             << T[i].first;
        distTot += T[i].first;

        cout << endl;
    }
    cout << "Distanta totala parcusra de Mos Craciun este de " << (distTot + distLaponiaCoreaSud) << " mile" << endl;
}

int main()
{

    Scrisoare *scrisoare = new Scrisoare[10];
    string *temp = new string[10];
    Copil *copil = new Copil[10];
    DoamnaCraciun *sos = new DoamnaCraciun[10];
    DoamnaCraciun *plec = new DoamnaCraciun[10];

    int n = 5, i, nr = 0;
    string nume[10] = {"Kyu", "Myung", "Nam", "Sang", "Kyung", "Mi", "Mi", "Young"};
    string prenume[10] = {"Bok", "Hee", "Kyu", "Hun", "Mi", "Ok", "Young", "Nam"};
    int varsta[10] = {8, 9, 12, 13, 10, 12, 7, 8};
    string oras[10] = {"SEOUOL", "BUSAN", "Deagu", "Dajeon", "Suwon", "Busan", "Deagu", "Deagu"};
    string dorinte[10][3] = {{"Chocolate", "Jenga", "Harry_Potter's_movie"}, {"Yamms", "Puzzle", "Play_Doh"}, {"Puzzle", "Iphone", "CS-GO"}, {"Oranges", "The_Witcher", "PUBG"}, {"Barbie", "Minni_Mouse", "Candy_Land"}, {"Puzzle", "Benefit_makeup", "Monapoly"}, {"Dior_makeup", "LOL", "Poker"}, {"Hat", "PC", "Converse"}};
    string culoare[10] = {"blue", "pink", "pink", "blue", "pink", "pink", "pink", "blue"};

    for (i = 0; i < 8; i++)
    {
        scrisoare[i].setScrisoare(nume[i], prenume[i], varsta[i], oras[i], culoare[i], dorinte[i]);
    }
    Elfi e;
    e.verificareCopil(copil, scrisoare);
    cout << copil[i].getStatus() << " " << copil[i].getBuget() << endl;
    e.alegereCadou(copil, scrisoare);
    Troli t;
    t.invelireCadouri(scrisoare, copil);
    DoamnaCraciun d;
    d.pretCarbuni(scrisoare, copil);
    cout << endl;

    MosCraciun g(6);

    cout << "Orasele vizitate pentru a optine drumul minim sunt:" << endl;
    g.Adaugare(1, 5, 21.33);
    g.Adaugare(5, 4, 68.1);
    g.Adaugare(4, 3, 73.31);
    g.Adaugare(3, 2, 57.94);
    g.Adaugare(2, 1, 204.13);
    g.Adaugare(2, 5, 186.43);
    g.Adaugare(2, 4, 123.17);
    g.Adaugare(1, 3, 147.35);
    g.kruskal();
    g.print();

    g.print(sos, plec);
    cout << "Drumul pe care Mos Craciun il impartateste cu Doamna Craciun!" << endl;
    for (int i = 0; i < sos->plecare.size(); i++)
        cout << sos->plecare.at(i) << "-" << plec->sosire.at(i) << endl;
}
