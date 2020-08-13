#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

struct Osoba
{
    int id;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};

//funkcja szyfrujaca i deszfrujaca haslo administratora przed zapisaniem do pliku
string szyfrujHaslo(string hasloDoZaszyfrowania)
{
    char kluczSzyfrowania = 'K'; //klucz szyfrowania, mo¿e byæ jakikolwiek znak
    string hasloZaszyfrowane = hasloDoZaszyfrowania;

    for (int i = 0; i < hasloDoZaszyfrowania.size(); i++)
    {
        hasloZaszyfrowane[i] = hasloDoZaszyfrowania[i] ^ kluczSzyfrowania;
    }
    return hasloZaszyfrowane;
}


//funkcja zapisujaca dane z ksiazki adresowej do pliku
bool zapiszDaneDoPliku(vector<Osoba> ksiazkaAdresowa, string hasloAdmin)
{
    fstream plikDoZapisu;
    plikDoZapisu.open("ksazkaAdresowa.txt",ios::out);
    plikDoZapisu<<szyfrujHaslo(hasloAdmin)<<endl;

    vector<Osoba>::iterator osobaDoZapisu;
    vector<Osoba>::iterator koniecKsiazki = ksiazkaAdresowa.end() ;
    for (osobaDoZapisu=ksiazkaAdresowa.begin(); osobaDoZapisu!=koniecKsiazki; osobaDoZapisu++ )
    {

        plikDoZapisu<<(*osobaDoZapisu).id<<"|";
        plikDoZapisu<<(*osobaDoZapisu).imie<<"|";
        plikDoZapisu<<(*osobaDoZapisu).nazwisko<<"|";
        plikDoZapisu<<(*osobaDoZapisu).telefon<<"|";
        plikDoZapisu<<(*osobaDoZapisu).email<<"|";
        plikDoZapisu<<(*osobaDoZapisu).adres<<"|"<<endl;


    }
    plikDoZapisu.close();
    return true;
}

//funkcja wczytujaca dane do ksiazki adresowej z pliku
void wczytajDaneZPliku(vector<Osoba> &ksiazkaAdresowa, string *hasloAdmin)
{
    fstream plikDoWczytania;
    string aktualnaLiniaTekstu;
    string slowo;
    int poleDanych=0;
    Osoba wczytywanaOsoba;

    plikDoWczytania.open("ksazkaAdresowa.txt",ios::in);
    if(plikDoWczytania.good()==true)
    {
        getline(plikDoWczytania,aktualnaLiniaTekstu);
        *hasloAdmin=szyfrujHaslo(aktualnaLiniaTekstu);

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
                        wczytywanaOsoba.id = stoi(slowo);
                        break;

                    case 1 :
                        wczytywanaOsoba.imie = slowo;
                        break;

                    case 2 :
                        wczytywanaOsoba.nazwisko = slowo;
                        break;

                    case 3 :
                        wczytywanaOsoba.telefon = slowo;
                        break;

                    case 4 :
                        wczytywanaOsoba.email = slowo;
                        break;

                    case 5 :
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
            ksiazkaAdresowa.push_back(wczytywanaOsoba);
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

//funkcja wyznaczajaca najwysze id w ksiazce adresowej
int  znajdzAktualneId (vector<Osoba> ksiazkaAdresowa)
{
    int aktualneId;
    vector<Osoba>::iterator najwyzszeId;
    if (ksiazkaAdresowa.size()>0)
    {
        najwyzszeId= max_element(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(),[](const Osoba& lhs, const Osoba& rhs){return lhs.id < rhs.id;});
        aktualneId = (*najwyzszeId).id;
    }
    else
    {
        aktualneId=0;
    }
    return aktualneId;
}




//funkcja logowania na konto admistratora
bool zalogujJakoAdmin(string hasloAdmin)
{
    string podaneHaslo;
    int proby=0;
    cout<<endl;
    cout<<"Podaj haslo administratora:";
    while(cin>>podaneHaslo)
    {
        if(podaneHaslo==hasloAdmin)
        {
            cout<<endl;
            cout<<"Zalogowano na konto administratora.";
            Sleep(2000);
            return true;
        }
        else
        {
            cout<<"Haslo nieprawidlowe. Podaj ponownie haslo administratora:";
            proby++;
            if (proby>=3)
            {
                return false;
            }
        }
    }

}

//funkcja wylogowania z konta administratora
bool wylogujZAdmina()
{
    cout<<endl;
    cout<<"Wylogowano z konta administratora.";
    Sleep(2000);
    return false;
}

//funkcja dodawania nowej osoby do ksiazki adresowej
int dodajOsobe(vector<Osoba> &ksiazkaAdresowa, int aktualneId)
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
    osobaDoDodania.id = aktualneId;

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
    cout<<"Podaj id osoby do edycji:";
    cin>>id;
    cout<<endl;
    vector<Osoba>::iterator osobaDoEdycji;
    osobaDoEdycji = find_if(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), [id]( const Osoba &aktualnaOsoba){return aktualnaOsoba.id==id;});
    if (osobaDoEdycji != ksiazkaAdresowa.end())
    {

        cout<<"1. Imie."<<endl;
        cout<<"2. Nazwisko."<<endl;
        cout<<"3. Telefon."<<endl;
        cout<<"5. E-mail."<<endl;
        cout<<"5. Adres."<<endl;
        cout<<"Wybierz pole do edycji:"<<endl;
        cout<<endl;
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
    cout<<(*osobaDoWyswietlenia).id<<"|";
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
    osobaDoUsuniecia = find_if(ksiazkaAdresowa.begin(), ksiazkaAdresowa.end(), [id]( const Osoba &aktualnaOsoba){return aktualnaOsoba.id==id;});
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
string zmienHasloAdmina()
{
    string haslo1;
    string haslo2;


    while(true)
    {
        cout<<endl;
        cout<<"Podaj nowe haslo administratora:"<<endl;
        cin>>haslo1;
        cout<<"Powtorz nowe haslo administratora:"<<endl;
        cin>>haslo2;

        if (haslo1==haslo2)
        {
            cout<<endl;
            cout<<"Haslo administratora zostalo zmienione."<<endl;
            Sleep(3000);
            return haslo1;
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
    bool zalogowano=false;
    bool zapisDanychUdany=false;
    char wyborUzytkownika;
    string hasloAdmin="admin";
    int aktualneId;

    vector<Osoba> ksiazkaAdresowa;

//wczytanie danych z pliku tekstowego do struktury danych

    wczytajDaneZPliku(ksiazkaAdresowa, &hasloAdmin);
    aktualneId=znajdzAktualneId(ksiazkaAdresowa);

//menu uzytkownika

    while(true)
    {
        if(zalogowano==false)
        {
            system("cls");
            cout<< "*****       Ksiazka adresowa V1.3        *****"<<endl;
            cout<< "**********************************************"<<endl;
            cout<< "* 1. Wyszukiwanie osoby po imieniu.          *"<<endl;
            cout<< "* 2. Wyszukiwanie osoby po nazwisku.         *"<<endl;
            cout<< "* 3. Wypisanie wszystkich pozycji z ksiazki. *"<<endl;
            cout<< "* 4. Logowanie na konto administratora.      *"<<endl;
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
                zalogowano=zalogujJakoAdmin(hasloAdmin);
                break;

            case '9':
                zapisDanychUdany=zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin);
                if (zapisDanychUdany==true)
                {
                    cout<<"Dane zostaly pomyslnie zapisane"<<endl;
                }
                exit(0);
            default:
                break;
            }
        }
        else
        {
            system("cls");
            cout<< "*****       Ksiazka adresowa V1.3        *****"<<endl;
            cout<< "**********************************************"<<endl;
            cout<< "* 1. Wyszukiwanie osoby po imieniu.          *"<<endl;
            cout<< "* 2. Wyszukiwanie osoby po nazwisku.         *"<<endl;
            cout<< "* 3. Wypisanie wszystkich pozycji z ksiazki. *"<<endl;
            cout<< "* 4. Dodanie osoby.                          *"<<endl;
            cout<< "* 5. Edycja osoby.                           *"<<endl;
            cout<< "* 6. Usuniecie osoby.                        *"<<endl;
            cout<< "* 7. Zmiana hasla.                           *"<<endl;
            cout<< "* 8. Wylogowanie z konta administratora.     *"<<endl;
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

                aktualneId=dodajOsobe(ksiazkaAdresowa, aktualneId);
                zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin);
                break;

            case '5':
                edytujOsobe(ksiazkaAdresowa);
                zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin);
                break;

            case '6':
                usunOsobe(ksiazkaAdresowa);
                aktualneId=znajdzAktualneId(ksiazkaAdresowa);
                zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin);
                break;

            case '7':
                hasloAdmin=zmienHasloAdmina();
                break;

            case '8':
                zalogowano=wylogujZAdmina();
                break;

            case '9':
                zapisDanychUdany=zapiszDaneDoPliku(ksiazkaAdresowa, hasloAdmin);
                if (zapisDanychUdany==true)
                {
                    cout<<"Dane zostaly pomyslnie zapisane"<<endl;
                }

                exit(0);
            default:
                break;
            }
        }

    }

    return 0;
}
