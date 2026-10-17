#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
struct Product
{
    string name;
    int cost;
};
class Automat
{
private:
    vector<pair<Product, int>> Produkty;



public:
    Automat(vector<pair<Product,int>> zawartość)
    {
        Produkty = zawartość;
    }
    void Wyświetl()
    {
        for(int i =0; i<Produkty.size(); i++)
        {
            if(Produkty[i].second > 0)
            {
            cout << i+1 << " - " << "Nazwa: " << Produkty[i].first.name << ", Koszt: " << Produkty[i].first.cost << ", Ilosc: " << Produkty[i].second << endl;
            }
        }
    }
    bool Sprawdz(int wyb)
    {
        if(Produkty[wyb].second>0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void Sprzedaj(int wyb)
    {
        Produkty[wyb].second --;
    }
    int ZwrocKoszt(int wyb)
    {
        return Produkty[wyb].first.cost;
    }

};
int temp = 1;
int moneta = 1;
int wybor=1;
int koszt;
int zapłacone;
bool powrot = false;
int main()
{

    Product Cola;
    Cola.name = "Cola";
    Cola.cost = 3;
    pair<Product,int> produkt = {Cola,3};
    vector<pair<Product,int>> vec;
    vec.emplace_back(produkt);
    Automat automat(vec);
    while(1)
    {
        cout << "Wybierz produkt" << endl;
        automat.Wyświetl();
        std::cin >> wybor;
        if(automat.Sprawdz(wybor-1))
        {
            auto start = chrono::steady_clock::now();
            zapłacone = 0;
            koszt = automat.ZwrocKoszt(wybor-1);
            while ((zapłacone<koszt)&&(powrot != true))
            {
                auto end = chrono::steady_clock::now();
                chrono::duration<double> elapsed = end - start;
                if(elapsed > chrono::seconds(15))
                {
                    powrot = true;
                }
                cout << "Prosze wlozyc monete lub nacisnac 9 zeby anulowac" << endl;
                cin >> temp;
                if(temp == 9)
                {
                    powrot = true;
                }
                else{
                    moneta = temp;
                    zapłacone = zapłacone + moneta;
                }
            }
            if(powrot == true)
            {
                powrot = false;
                cout << "Minal czas na zaplacenie lub transakcja zostala anulowana. " << "Zostana wydane pieniadze o wartosci: " << zapłacone << endl;
            }
            else
            {
            if((zapłacone - koszt>0)){
                cout << "Zwrot reszty: " << zapłacone - koszt << endl;}
            automat.Sprzedaj(wybor-1);
            }
        }
    }
    return 0;
}
