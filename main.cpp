#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>


using namespace std;

struct Osoba
{
    int idOsoby;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa;
    string haslo;
};



//funkcja zapisujaca dane uzytkownikow do pliku
bool zapiszDaneUzytkownikow(vector<Uzytkownik> uzytkownicy)
{
    fstream plikDoZapisu;
    plikDoZapisu.open("uzytkownicy.txt",ios::out);

    vector<Uzytkownik>::iterator uzytkownikDoZapisu;
    vector<Uzytkownik>::iterator koniecUzytkownikow = uzytkownicy.end() ;
    for (uzytkownikDoZapisu=uzytkownicy.begin(); uzytkownikDoZapisu!=koniecUzytkownikow ; uzytkownikDoZapisu++ )
    {

        plikDoZapisu<<(*uzytkownikDoZapisu).idUzytkownika<<"|";
        plikDoZapisu<<(*uzytkownikDoZapisu).nazwa<<"|";
        plikDoZapisu<<(*uzytkownikDoZapisu).haslo<<"|"<<endl;


    }
    plikDoZapisu.close();
    return true;
}

//funkcja zapisujaca dane z ksiazki adresowej do pliku
int zapiszDaneDoPliku(vector<Osoba> ksiazkaAdresowa, string hasloAdmin, int idZalogowanegoUzytkownika)
{
    fstream plikKsiazkaAdresowa;
    fstream plikTymczasowy;
    string aktualnaLiniaTekstu;
    string slowo;
    int poleDanych;
    int aktualneId=0;
    Osoba wczytywanaOsoba;

    plikKsiazkaAdresowa.open("ksiazkaAdresowa.txt",ios::in);
    plikTymczasowy.open("ksiazkaAdresowa_tmp.txt",ios::out);

    vector<Osoba>::iterator osobaDoZapisu;
    vector<Osoba>::iterator koniecKsiazki = ksiazkaAdresowa.end() ;
    for (osobaDoZapisu=ksiazkaAdresowa.begin(); osobaDoZapisu!=koniecKsiazki; osobaDoZapisu++ )
    {

        plikTymczasowy<<(*osobaDoZapisu).idOsoby<<"|";
        plikTymczasowy<< idZalogowanegoUzytkownika << "|";
        plikTymczasowy<<(*osobaDoZapisu).imie<<"|";
        plikTymczasowy<<(*osobaDoZapisu).nazwisko<<"|";
        plikTymczasowy<<(*osobaDoZapisu).telefon<<"|";
        plikTymczasowy<<(*osobaDoZapisu).email<<"|";
        plikTymczasowy<<(*osobaDoZapisu).adres<<"|"<<endl;
        if ((*osobaDoZapisu).idOsoby > aktualneId)
        {
            aktualneId=(*osobaDoZapisu).idOsoby;
        }
    }

    if(plikKsiazkaAdresowa.good()==true)
    {


        while(getline(plikKsiazkaAdresowa,aktualnaLiniaTekstu))
        {


            for(int i = 0; i<aktualnaLiniaTekstu.length(); i++)
            {
                switch(aktualnaLiniaTekstu[i])
                {

                case '|' :

                    switch(poleDanych)
                    {
                    case 0 :
                        wczytywanaOsoba.idOsoby = stoi(slowo);
                        break;

                    case 1 :
                        wczytywanaOsoba.idUzytkownika = stoi(slowo);
                        break;

                    case 2 :
                        wczytywanaOsoba.imie  = slowo;
                        break;

                    case 3 :
                        wczytywanaOsoba.nazwisko = slowo;
                        break;

                    case 4 :
                        wczytywanaOsoba.telefon = slowo;
                        break;

                    case 5 :
                        wczytywanaOsoba.email = slowo;
                        break;

                    case 6 :
                        wczytywanaOsoba.adres = slowo;
                        break;
                    }


                    poleDanych++;

                    slowo.clear();
                    break;

                default:
                    slowo += aktualnaLiniaTekstu[i];
                    break;
                }

            }

            if(wczytywanaOsoba.idUzytkownika != idZalogowanegoUzytkownika)
            {
                plikTymczasowy<<wczytywanaOsoba.idOsoby<<"|";
                plikTymczasowy<< wczytywanaOsoba.idUzytkownika << "|";
                plikTymczasowy<<wczytywanaOsoba.imie<<"|";
                plikTymczasowy<<wczytywanaOsoba.nazwisko<<"|";
                plikTymczasowy<<wczytywanaOsoba.telefon<<"|";
                plikTymczasowy<<wczytywanaOsoba.email<<"|";
                plikTymczasowy<<wczytywanaOsoba.adres<<"|"<<endl;
                poleDanych=0;

                if (wczytywanaOsoba.idOsoby > aktualneId)
                {
                aktualneId=wczytywanaOsoba.idOsoby;
                }
            }
            else
            {
                poleDanych=0;
            }

        }

    }

    plikTymczasowy.close();
    plikKsiazkaAdresowa.close();
    remove( "ksiazkaAdresowa.txt" );
    rename("ksiazkaAdresowa_tmp.txt", "ksiazkaAdresowa.txt");
    return aktualneId;
}

//funkcja wczytujaca dane uzytkownikow  z pliku
void wczytajDaneUzytkownikow(vector<Uzytkownik> &uzytkownicy)
{
    fstream plikDoWczytania;
    string aktualnaLiniaTekstu;
    string slowo;
    int poleDanych=0;
    Uzytkownik wczytywanyUzytkownik;

    plikDoWczytania.open("uzytkownicy.txt",ios::in);
    if(plikDoWczytania.good()==true)
    {

        while(getline(plikDoWczytania,aktualnaLiniaTekstu))
        {


            for(int i = 0; i<aktualnaLiniaTekstu.length(); i++)
            {
                switch(aktualnaLiniaTekstu[i])
                {

                case '|' :

                    switch(poleDanych)
                    {
                    case 0 :
                        wczytywanyUzytkownik.idUzytkownika = stoi(slowo);
                        break;

                    case 1 :
                        wczytywanyUzytkownik.nazwa = slowo;
                        break;

                    case 2 :
                        wczytywanyUzytkownik.haslo = slowo;
                        break;

                    }


                    poleDanych++;

                    slowo.clear();
                    break;

                default:
                    slowo += aktualnaLiniaTekstu[i];
                    break;
                }

            }
            uzytkownicy.push_back(wczytywanyUzytkownik);
            poleDanych=0;
        }


        plikDoWczytania.close();
        return;
    }
    else
    {
       return;
    }
}
//funkcja wczytujaca dane do ksiazki adresowej z pliku
int wczytajDaneZPliku(vector<Osoba> &ksiazkaAdresowa, int idZalogowanegoUzytkownika)
{
    fstream plikDoWczytania;
    string aktualnaLiniaTekstu;
    string slowo;
    int poleDanych=0;
    int aktualneId=0;
    Osoba wczytywanaOsoba;

    plikDoWczytania.open("ksiazkaAdresowa.txt",ios::in);
    if(plikDoWczytania.good()==true)
    {


        while(getline(plikDoWczytania,aktualnaLiniaTekstu))
        {


            for(int i = 0; i<aktualnaLiniaTekstu.length(); i++)
            {
                switch(aktualnaLiniaTekstu[i])
                {

                case '|' :

                    switch(poleDanych)
                    {
                    case 0 :
                        wczytywanaOsoba.idOsoby = stoi(slowo);
                        break;

                    case 1 :
                        wczytywanaOsoba.idUzytkownika = stoi(slowo);
                        break;

                    case 2 :
                        wczytywanaOsoba.imie  = slowo;
                        break;

                    case 3 :
                        wczytywanaOsoba.nazwisko = slowo;
                        break;

                    case 4 :
                        wczytywanaOsoba.telefon = slowo;
                        break;

                    case 5 :
                        wczytywanaOsoba.email = slowo;
                        break;

                    case 6 :
                        wczytywanaOsoba.adres = slowo;
                        break;
                    }


                    poleDanych++;

                    slowo.clear();
                    break;

                default:
                    slowo += aktualnaLiniaTekstu[i];
                    break;
                }

            }
            if (wczytywanaOsoba.idOsoby > aktualneId)
            {
                aktualneId=wczytywanaOsoba.idOsoby;
            }

            if(wczytywanaOsoba.idUzytkownika == idZalogowanegoUzytkownika)
            {
                ksiazkaAdresowa.push_back(wczytywanaOsoba);
                poleDanych=0;
            }
            else
            {
                poleDanych=0;
            }

        }


        plikDoWczytania.close();
        return aktualneId;
    }
    else
    {
       return 0;
    }




}

//funkcja wyznaczajaca najwysze id w ksiazce adresowej
int  znajdzAktualneId (vector<Osoba> ksiazkaAdresowa)
{
    int aktualneId;
    vector<Osoba>::iterator najwyzszeId;
    if (ksiazkaAdresowa.size()>0)
    {
        najwyzszeId= max_element(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(),[](const Osoba& lhs, const Osoba& rhs){return lhs.idOsoby < rhs.idOsoby;});
        aktualneId = (*najwyzszeId).idOsoby;
    }
    else
    {
        aktualneId=0;
    }
    return aktualneId;
}

//funkcja wyznaczajaca najwysze id w ksiazce adresowej
int  znajdzAktualneIdUzytkownika (vector<Uzytkownik> uzytkownicy)
{
    int aktualneIdUzytkownika;
    vector<Uzytkownik>::iterator najwyzszeId;
    if (uzytkownicy.size()>0)
    {
        najwyzszeId= max_element(uzytkownicy.begin(), uzytkownicy.end(),[](const Uzytkownik& lhs, const Uzytkownik& rhs){return lhs.idUzytkownika < rhs.idUzytkownika;});
        aktualneIdUzytkownika = (*najwyzszeId).idUzytkownika;
    }
    else
    {
        aktualneIdUzytkownika=0;
    }
    return aktualneIdUzytkownika;
}


//funkcja logowania na konto uzytkownika
int zalogujUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    string podaneHaslo;
    string nazwaUzytkownika;
    int proby=0;
    cout<<endl;
    cout<<"Podaj nazwe uzytkownika:";
    cin>>nazwaUzytkownika;
    vector<Uzytkownik>::iterator uzytkownik;
    uzytkownik = find_if(uzytkownicy.begin(), uzytkownicy.end(), [nazwaUzytkownika]( const Uzytkownik &aktualnyUzytkownik){return aktualnyUzytkownik.nazwa==nazwaUzytkownika;});
    if (uzytkownik != uzytkownicy.end())
    {
        cout<<endl;
        cout<<"Podaj haslo:";
        while(cin>>podaneHaslo)
        {
            if(podaneHaslo==(*uzytkownik).haslo)
            {
                cout<<endl;
                cout<<"Zalogowano na konto uzytkownika.";
                Sleep(2000);
                return (*uzytkownik).idUzytkownika;
            }
            else
            {
                cout<<endl;
                cout<<"Haslo nieprawidlowe. Podaj ponownie haslo.";
                cout<<endl;
                proby++;
                if (proby>=3)
                {
                    return 0;
                }
            }
        }

    }
    else
    {
        cout<<endl;
        cout<<"Brak podanej nazwy uzytkownika w ksiazce adresowej.";
        Sleep(2000);
        return 0;
    }

}

//funkcja wylogowania z konta uzytkownika
int wylogujUzytkownika()
{
    cout<<endl;
    cout<<"Wylogowano z konta uzytkownika.";
    Sleep(2000);
    return 0;
}


//funkcja rejestracji uzytkownika
int zarejestrujUzytkownika(vector<Uzytkownik> &uzytkownicy, int aktualneId)
{
    Uzytkownik uzytkownikDoDodania;
    cout<<endl;
    cout<<"Podaj nazwe uzytkownika:"<<endl;
    cin>>uzytkownikDoDodania.nazwa;
    cout<<"Podaj haslo:"<<endl;
    cin>>uzytkownikDoDodania.haslo;

    int i =0;
    while (i<uzytkownicy.size())
    {

        if (uzytkownikDoDodania.nazwa==uzytkownicy[i].nazwa)
        {
            cout<<endl;
            cout << "Taki uzytkownik jest juz zarejestrowany. Podaj ponownie nazwe."<<endl;
            cout<<endl;
            cin>>uzytkownikDoDodania.nazwa;
            i=0;
        }
        else
        {
            i++;
        }
    }

    aktualneId+=1;
    uzytkownikDoDodania.idUzytkownika = aktualneId;

    uzytkownicy.push_back(uzytkownikDoDodania);

    cout<<endl;
    cout<<"Uzytkownik zostal pomyslnie dodany do ksiazki adresowej.";
    Sleep(3000);
    return aktualneId;

}


//funkcja dodawania nowej osoby do ksiazki adresowej
int dodajOsobe(vector<Osoba> &ksiazkaAdresowa, int aktualneId, int idZalogowanegoUzytkownika )
{
    Osoba osobaDoDodania;
    cout<<endl;
    cout<<"Podaj imie:"<<endl;
    cin>>osobaDoDodania.imie;
    cout<<"Podaj nazwisko:"<<endl;
    cin>>osobaDoDodania.nazwisko;

    int i =0;
    while (i<ksiazkaAdresowa.size())
    {

        if ((osobaDoDodania.imie==ksiazkaAdresowa[i].imie)&&(osobaDoDodania.nazwisko==ksiazkaAdresowa[i].nazwisko))
        {
            cout<<endl;
            cout << "Osoba jest juz w ksiazce adresowej. Podaj ponownie dane."<<endl;
            cout<<endl;
            cout<<"Podaj imie:"<<endl;
            cin>>osobaDoDodania.imie;
            cout<<"Podaj nazwisko:"<<endl;
            cin>>osobaDoDodania.nazwisko;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj telefon:"<<endl;
    cin>>osobaDoDodania.telefon;
    cout<<"Podaj e-mail:"<<endl;
    cin>>osobaDoDodania.email;
    cout<<"Podaj adres:"<<endl;
    cin.sync();
    getline(cin,osobaDoDodania.adres);
    aktualneId+=1;
    osobaDoDodania.idOsoby = aktualneId;
    osobaDoDodania.idUzytkownika = idZalogowanegoUzytkownika;

    ksiazkaAdresowa.push_back(osobaDoDodania);

    cout<<endl;
    cout<<"Osoba zostala pomyslnie dodana do ksiazki adresowej.";
    Sleep(3000);
    return aktualneId;

}

//funkcja edycji osoby z ksiazki adresowej
void edytujOsobe(vector<Osoba> &ksiazkaAdresowa)
{
    int id;
    char wyborUzytkownika;
    string poleDoEdycji;
    cout<<endl;
    cout<<"Podaj id osoby do edycji:"<<endl;
    cin>>id;
    cout<<endl;
    vector<Osoba>::iterator osobaDoEdycji;
    osobaDoEdycji = find_if(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), [id]( const Osoba &aktualnaOsoba){return aktualnaOsoba.idOsoby==id;});
    if (osobaDoEdycji != ksiazkaAdresowa.end())
    {

        cout<<"1. Imie."<<endl;
        cout<<"2. Nazwisko."<<endl;
        cout<<"3. Telefon."<<endl;
        cout<<"5. E-mail."<<endl;
        cout<<"5. Adres."<<endl;
        cout<<endl;
        cout<<"Wybierz pole do edycji:"<<endl;

        cin>>wyborUzytkownika;
        switch (wyborUzytkownika)
        {
        case '1':
            cout<<endl;
            cout<<"Podaj nowe imie:"<<endl;
            cin>>poleDoEdycji;
            (*osobaDoEdycji).imie=poleDoEdycji;

            break;

        case '2':
            cout<<endl;
            cout<<"Podaj nowe nazwisko:"<<endl;
            cin>>poleDoEdycji;
            (*osobaDoEdycji).nazwisko=poleDoEdycji;

            break;

        case '3':
            cout<<endl;
            cout<<"Podaj nowy numer telefonu:"<<endl;
            cin>>poleDoEdycji;
            (*osobaDoEdycji).telefon=poleDoEdycji;
            break;

        case '4':
            cout<<endl;
            cout<<"Podaj nowy numer telefonu:"<<endl;
            cin>>poleDoEdycji;
            (*osobaDoEdycji).email=poleDoEdycji;
            break;

        case '5':
            cout<<endl;
            cout<<"Podaj nowy numer telefonu:"<<endl;
            cin>>poleDoEdycji;
            (*osobaDoEdycji).adres=poleDoEdycji;
            break;

        default:
            break;
        }


        cout<<endl;
        cout<<"Dane zmienione poprawnie"<<endl;
        Sleep(3000);
        return;
    }

    else
    {
        cout<<endl;
        cout<<"Osoba z podanym id nie istnieje w ksiazce adresowej.";
        Sleep(3000);
        return;
    }
}

//fukcja wyswietlania danych osoby z ksiazki adresowej
void wyswietlOsobe(vector<Osoba>::iterator osobaDoWyswietlenia )
{
    cout<<(*osobaDoWyswietlenia).idOsoby<<"|";
    cout<<(*osobaDoWyswietlenia).imie<<" ";
    cout<<(*osobaDoWyswietlenia).nazwisko<<"|";
    cout<<(*osobaDoWyswietlenia).telefon<<"|";
    cout<<(*osobaDoWyswietlenia).email<<"|";
    cout<<(*osobaDoWyswietlenia).adres<<endl;
}

//funkcja usuwania osoby z ksiazki adresowej po podanym id
void usunOsobe(vector<Osoba> &ksiazkaAdresowa)
{
    int id;
    char wyborUzytkownika;
    cout<<endl;
    cout<<"Podaj id osoby do usuniecia:";
    cin>>id;

    vector<Osoba>::iterator osobaDoUsuniecia;
    osobaDoUsuniecia = find_if(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), [id]( const Osoba &aktualnaOsoba){return aktualnaOsoba.idOsoby==id;});
    if (osobaDoUsuniecia != ksiazkaAdresowa.end())
    {
        cout<<endl;
        cout<<"Czy na pewno chcesz usunac:"<<endl;
        cout<<endl;
        wyswietlOsobe(osobaDoUsuniecia);
        cout<<endl;
        cout<<"Potwierdz naciskajac klawisz 't'."<<endl;
        cin>> wyborUzytkownika;
        if(wyborUzytkownika=='t')
        {
            ksiazkaAdresowa.erase(osobaDoUsuniecia);
            cout<<endl;
            cout<<"Osoba zostala pomyslnie usunieta z ksiazki adresowej.";
            Sleep(3000);
            return;
        }
        else
        {
            return;
        }

    }
    else
    {
        cout<<endl;
        cout<<"Osoba z podanym id nie istnieje w ksiazce adresowej.";
        Sleep(3000);
        return;

    }

}

//funkcja wypisujaca wszystkie osoby z ksiazki adresowej
void wypiszWszystkieOsoby(vector<Osoba> ksiazkaAdresowa)
{
    cout<<endl;

    if(ksiazkaAdresowa.size()==0)
    {
        cout<<endl;
        cout<<"Brak osob w ksiazce adresowej."<<endl;
    }

    else
    {
        vector<Osoba>::iterator osobaDoWyswietlenia;
        vector<Osoba>::iterator koniecKsiazki = ksiazkaAdresowa.end() ;
        for (osobaDoWyswietlenia=ksiazkaAdresowa.begin(); osobaDoWyswietlenia!=koniecKsiazki; osobaDoWyswietlenia++ )
        {

            wyswietlOsobe(osobaDoWyswietlenia);

        }
    }
    cout<<endl;
    cout<<"Nacisnij dowolny klawisz aby kontynuowac."<<endl;
    cin.sync();
    cin.get();
}


//funkcja wypisujaca wszystkie osoby z ksiazki adresowej o podanym imieniu
void wyszukajImie(vector<Osoba> ksiazkaAdresowa)
{
    int liczbaZnalezionychOsob=0;
    string imie;
    cout<<endl;
    cout<<"Podaj imie:"<<endl;
    cin>>imie;
    cout<<endl;

    vector<Osoba>::iterator osobaDoWyswietlenia  = ksiazkaAdresowa.begin();

    while (osobaDoWyswietlenia != ksiazkaAdresowa.end())
    {

        osobaDoWyswietlenia = find_if(osobaDoWyswietlenia, ksiazkaAdresowa.end(), [imie]( const Osoba &aktualnaOsoba)
        {
            return aktualnaOsoba.imie==imie;
        });
        if(osobaDoWyswietlenia != ksiazkaAdresowa.end())
        {
            wyswietlOsobe(osobaDoWyswietlenia);
            osobaDoWyswietlenia++;
            liczbaZnalezionychOsob++;
        }
        else
        {
            break;
        }


    }
    if (liczbaZnalezionychOsob==0)
    {
        cout<<endl;
        cout<<"Brak osob o podanym nazwisku w ksiazce adresowej."<<endl;
    }
    cout<<endl;
    cout<<"Nacisnij dowolny klawisz aby kontynuowac."<<endl;
    cin.sync();
    cin.get();
}

//funkcja wypisujaca wszystkie osoby z ksiazki adresowej o podanym nazwisku
void wyszukajNazwisko(vector<Osoba> ksiazkaAdresowa)
{
    int liczbaZnalezionychOsob=0;
    string nazwisko;
    cout<<endl;
    cout<<"Podaj nazwisko:"<<endl;
    cin>>nazwisko;
    cout<<endl;
    vector<Osoba>::iterator osobaDoWyswietlenia  = ksiazkaAdresowa.begin();

    while (osobaDoWyswietlenia != ksiazkaAdresowa.end())
    {

        osobaDoWyswietlenia = find_if(osobaDoWyswietlenia, ksiazkaAdresowa.end(), [nazwisko]( const Osoba &aktualnaOsoba)
        {
            return aktualnaOsoba.nazwisko==nazwisko;
        });
        if(osobaDoWyswietlenia != ksiazkaAdresowa.end())
        {
            wyswietlOsobe(osobaDoWyswietlenia);
            osobaDoWyswietlenia++;
            liczbaZnalezionychOsob++;
        }
        else
        {

            break;
        }


    }
    if (liczbaZnalezionychOsob==0)
    {
        cout<<endl;
        cout<<"Brak osob o podanym nazwisku w ksiazce adresowej."<<endl;
    }

    cout<<endl;
    cout<<"Nacisnij dowolny klawisz aby kontynuowac."<<endl;
    cin.sync();
    cin.get();
}

//funkcja zmieniajaca haslo administratora
void zmienHasloUzytkownika(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo1;
    string haslo2;


    while(true)
    {
        cout<<endl;
        cout<<"Podaj nowe haslo uzytkownika:"<<endl;
        cin>>haslo1;
        cout<<"Powtorz nowe haslo uzytkownika:"<<endl;
        cin>>haslo2;

        if (haslo1==haslo2)
        {
            cout<<endl;
            vector<Uzytkownik>::iterator uzytkownik;
            uzytkownik = find_if(uzytkownicy.begin(), uzytkownicy.end(), [idZalogowanegoUzytkownika]( const Uzytkownik &aktualnyUzytkownik){return aktualnyUzytkownik.idUzytkownika==idZalogowanegoUzytkownika;});
             if (uzytkownik != uzytkownicy.end())
             {
                 (*uzytkownik).haslo = haslo1;
                 cout<<"Haslo uzytkownika zostalo zmienione."<<endl;
                 Sleep(3000);
                 return;
             }


        }
        else
        {
            cout<<endl;
            cout<<"Podane hasla roznia sie."<<endl;
            Sleep(3000);
        }
    }
}


int main()
{
    int idZalogowanegoUzytkownika=0;
    char wyborUzytkownika;
    string hasloAdmin="admin";
    int aktualneIdUzytkownika;
    int aktualneIdOsoby;

    vector<Osoba> ksiazkaAdresowa;
    vector<Uzytkownik> uzytkownicy;

//wczytanie danychuzytkownikow z pliku tekstowego do struktury danych

    wczytajDaneUzytkownikow(uzytkownicy);


//menu uzytkownika

    while(true)
    {
        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout<< "*****       Ksiazka adresowa V1.4        *****"<<endl;
            cout<< "**********************************************"<<endl;
            cout<< "* 1. Logowanie.                              *"<<endl;
            cout<< "* 2. Rejestracja.                            *"<<endl;
            cout<< "* 9. Wyjscie z programu.                     *"<<endl;
            cout<< "**********************************************"<<endl;
            cout<<endl;
            cout<< "Wybierz numer:"<<endl;

            cin>>wyborUzytkownika;

            switch (wyborUzytkownika)
            {
            case '1':
                idZalogowanegoUzytkownika=zalogujUzytkownika(uzytkownicy);
                aktualneIdOsoby=wczytajDaneZPliku(ksiazkaAdresowa, idZalogowanegoUzytkownika);
                break;

            case '2':
                aktualneIdUzytkownika=znajdzAktualneIdUzytkownika(uzytkownicy);
                aktualneIdUzytkownika=zarejestrujUzytkownika(uzytkownicy,aktualneIdUzytkownika);
                zapiszDaneUzytkownikow(uzytkownicy);
                break;

            case '9':
                zapiszDaneUzytkownikow(uzytkownicy);

                exit(0);
            default:
                break;
            }
        }
        else
        {




            system("cls");
            cout<< "*****       Ksiazka adresowa V1.4        *****"<<endl;
            cout<< "**********************************************"<<endl;
            cout<< "* 1. Wyszukiwanie osoby po imieniu.          *"<<endl;
            cout<< "* 2. Wyszukiwanie osoby po nazwisku.         *"<<endl;
            cout<< "* 3. Wypisanie wszystkich pozycji z ksiazki. *"<<endl;
            cout<< "* 4. Dodanie osoby.                          *"<<endl;
            cout<< "* 5. Edycja osoby.                           *"<<endl;
            cout<< "* 6. Usuniecie osoby.                        *"<<endl;
            cout<< "* 7. Zmiana hasla.                           *"<<endl;
            cout<< "* 8. Wylogowanie z konta uzytkownika.        *"<<endl;
            cout<< "* 9. Wyjscie z programu.                     *"<<endl;
            cout<< "**********************************************"<<endl;
            cout<<endl;
            cout<< "Wybierz numer:"<<endl;

            cin>>wyborUzytkownika;

            switch (wyborUzytkownika)
            {
            case '1':
                wyszukajImie(ksiazkaAdresowa);
                break;

            case '2':
                wyszukajNazwisko(ksiazkaAdresowa);
                break;

            case '3':
                wypiszWszystkieOsoby(ksiazkaAdresowa);
                break;

            case '4':

                dodajOsobe(ksiazkaAdresowa, aktualneIdOsoby, idZalogowanegoUzytkownika);
                aktualneIdOsoby=zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin, idZalogowanegoUzytkownika);
                break;

            case '5':
                edytujOsobe(ksiazkaAdresowa);
                zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin, idZalogowanegoUzytkownika);
                break;

            case '6':
                usunOsobe(ksiazkaAdresowa);
                aktualneIdOsoby=zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin, idZalogowanegoUzytkownika);
                break;

            case '7':
                zmienHasloUzytkownika(uzytkownicy, idZalogowanegoUzytkownika);
                zapiszDaneUzytkownikow(uzytkownicy);
                break;

            case '8':
                idZalogowanegoUzytkownika=wylogujUzytkownika();
                ksiazkaAdresowa.clear();
                break;

            case '9':
                zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin, idZalogowanegoUzytkownika);

                exit(0);
            default:
                break;
            }
        }

    }

    return 0;
}
