// Zwierzątko.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <time.h>

class Rodzaj {
public:
    std::string nazwy; 
    std::string separator;
    Rodzaj(std::string _separator) : separator(_separator) {    };
    Rodzaj(std::string _nazwy, std::string _separator) : nazwy(_nazwy), separator(_separator) {    }
    void pobierzNazwy(std::string zrodlo) {
        this->nazwy = zrodlo;
    }
    void wypiszZwierzeta() {
        std::cout << this->nazwy << std::endl;
    }
    std::string getNazwy() {
        return this->nazwy;
    }
    std::string operator[](int ktore) {
        std::string bufor = this->nazwy;
        std::string token;
        size_t pos = 0;
        while ((pos = bufor.find(this->separator)) != std::string::npos) {
            token = bufor.substr(0, pos);
            if (ktore == 0) {
                break;
            }
            bufor.erase(0, pos + this->separator.length());
            ktore--;
        }
        return token;
    }
    friend std::ostream& operator<<(std::ostream& out, Rodzaj& rodzaj) {
        std::string bufor = rodzaj.nazwy;
        std::string token;
        int ktore = 0;
        size_t pos = 0;
        while ((pos = bufor.find(rodzaj.separator)) != std::string::npos) {
            token = bufor.substr(0, pos);
            out << ktore << ". " << token << " " << std::endl;
            bufor.erase(0, pos + rodzaj.separator.length());
            ktore++;
        }
        return out;
    }
    friend std::ifstream& operator>>(std::ifstream& fstr, Rodzaj& rodzaj) {
        std::getline(fstr, rodzaj.nazwy);
        return fstr;
    }
};



class Zwierze;

class Przedmiot {
    int cena;
    std::string nazwa;
    int skutecznosc;
public:
    Przedmiot(int _cena, std::string _nazwa, int _skutecznosc)
        : cena(_cena), nazwa(_nazwa), skutecznosc(_skutecznosc) {   }
    int getCena() {
        return this->cena;
    }
    std::string getNazwa() {
        return this->nazwa;
    }
    int getSkutecznosc() {
        return this->skutecznosc;
    }
    virtual ~Przedmiot() {
        std::cout << "Aktywowano destruktor przedmiotu" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& out, Przedmiot& przedmiot) {
        out << przedmiot.nazwa;
        out << " [" << przedmiot.skutecznosc << "pkt]";
        out << " [" << przedmiot.cena << "g]";
        return out;
    }
};

class Zabawka : public Przedmiot {
public:
    Zabawka(int _cena, std::string _nazwa, int _skutecznosc)
        : Przedmiot(_cena, _nazwa, _skutecznosc) {  }
    ~Zabawka() {
        Przedmiot::~Przedmiot();
    }
};

class Jedzenie : public Przedmiot {
public:
    Jedzenie(int _cena, std::string _nazwa, int _skutecznosc)
        : Przedmiot(_cena, _nazwa, _skutecznosc) {  }
    ~Jedzenie() {

    }
};

class Lekarstwo : public Przedmiot {
public:
    Lekarstwo(int _cena, std::string _nazwa, int _skutecznosc)
        : Przedmiot(_cena, _nazwa, _skutecznosc) {  }
    ~Lekarstwo() {

    }
};

class Zwierze {
private:
    std::string nazwa;
    std::string rodzaj;
    int jedzenie;
    int milosc;
    int zdrowie;
public:
    Zwierze() { jedzenie = 0; milosc = 0; zdrowie = 0; }
    Zwierze(std::string _nazwa, std::string _rodzaj, int _jedzenie, int _milosc, int _zdrowie) :
        nazwa(_nazwa), rodzaj(_rodzaj), jedzenie(_jedzenie), milosc(_milosc), zdrowie(_zdrowie) {   }
    void setNazwa(std::string _nazwa) {
        this->nazwa = _nazwa;
    }
    void setRodzaj(std::string _rodzaj) {
        this->rodzaj = _rodzaj;
    }
    std::string getNazwa() {
        return this->nazwa;
    }
    std::string getRodzaj() {
        return this->rodzaj;
    }
    void uzyjPrzedmiotu(Przedmiot* _przedmiot) {
        Zabawka* zabawka = dynamic_cast<Zabawka*>(_przedmiot);
        Jedzenie* jedzenie = dynamic_cast<Jedzenie*>(_przedmiot);
        Lekarstwo* lekarstwo = dynamic_cast<Lekarstwo*>(_przedmiot);
        if (zabawka) {
            std::cout << "Przedmiot typu Zabawka zostal wykorzystany by dac zwierzatku " << _przedmiot->getSkutecznosc() << " punktow milosci" << std::endl;;
            this->milosc += _przedmiot->getSkutecznosc();
            if (this->milosc > 99) {
                std::cout << "Przekroczono gorny limit milosci, ustawiono milosc na 99" << std::endl;
                this->milosc = 99;
            }
        }
        else if (jedzenie) {
            std::cout << "Przedmiot typu Jedzenie zostal wykorzystany by dac zwierzatku " << _przedmiot->getSkutecznosc() << " punktow najedzenia" << std::endl;;
            this->jedzenie += _przedmiot->getSkutecznosc();
            if (this->jedzenie > 99) {
                std::cout << "Przekroczono gorny limit jedzenia, ustawiono jedzenie na 99" << std::endl;
                this->jedzenie = 99;
            }
        }
        else if (lekarstwo) {
            std::cout << "Przedmiot typu Lekarstwo zostal wykorzystany by dac zwierzatku " << _przedmiot->getSkutecznosc() << " punktow zdrowia" << std::endl;;
            this->zdrowie += _przedmiot->getSkutecznosc();
            if (this->zdrowie > 99) {
                std::cout << "Przekroczono gorny limit zdrowia, ustawiono zdrowie na 99" << std::endl;
                this->zdrowie = 99;
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& out, Zwierze& zwierze) {
        out << "Imie: " << zwierze.nazwa << std::endl;
        out << "Rodzaj: " << zwierze.rodzaj << std::endl;
        out << "Stan: ";
        if (zwierze.milosc < 40 && zwierze.jedzenie < 40 && zwierze.zdrowie < 40) {
            out << "zaniedbanie, uwazaj, twoje zwierze moze zaraz zginac!!" << std::endl;
        }
        else {
            if (zwierze.milosc > 40 && zwierze.jedzenie > 40 && zwierze.zdrowie > 40) {
                out << "szczescie";
            }
            else {
                if (zwierze.milosc < 40) {
                    out << " smutek";
                }
                if (zwierze.zdrowie < 40) {
                    out << " choroba";
                }
                if (zwierze.jedzenie < 40) {
                    out << " glod";
                }
            }

        }
        out << std::endl;
        out << std::endl;
        out << "Milosc: " << zwierze.milosc << std::endl;
        out << "Jedzenie: " << zwierze.jedzenie << std::endl;
        out << "Zdrowie: " << zwierze.zdrowie << std::endl;
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Zwierze& zwierze) {
        std::string nazwa;
        std::cout << "Podaj nazwe zwierzatka: " << std::endl;
        in >> nazwa;
        zwierze.setNazwa(nazwa);
        std::cout << "Wybierz rodzaj zwierzatka: " << std::endl;
        Rodzaj rodzajeZwierzat(";");
        std::ifstream plik;
        plik.open("rodzaje.txt");
        plik >> rodzajeZwierzat;
        std::cout << rodzajeZwierzat << "Wybrany rodzaj zwierzecia: ";
        int i;
        in >> i;
        zwierze.setRodzaj(rodzajeZwierzat.operator[](i));
        zwierze.milosc = 99;
        zwierze.jedzenie = 99;
        zwierze.zdrowie = 99;
        return in;
    }
    int getJedzenie() {
        return this->jedzenie;
    }
    int getMilosc() {
        return this->milosc;
    }
    int getZdrowie() {
        return this->zdrowie;
    }
    void setJedzenie(int _jedzenie) {
        this->jedzenie = _jedzenie;
    }void setMilosc(int _milosc) {
        this->milosc = _milosc;
    }void setZdrowie(int _zdrowie) {
        this->zdrowie = _zdrowie;
    }
};



class ElementListyPrzedmiotow {
public:
    Przedmiot* przedmiot;
    ElementListyPrzedmiotow* nastepny;
    ElementListyPrzedmiotow() {
        this->przedmiot = nullptr;
        this->nastepny = nullptr;
    }
    void operator+=(Przedmiot* _przedmiot) {
        ElementListyPrzedmiotow* element = this;
        if (!(element->przedmiot)) {
            element->przedmiot = _przedmiot;
            element->nastepny = nullptr;
        }
        else {
            while (element->nastepny) {
                element = element->nastepny;
            }
            element->nastepny = new ElementListyPrzedmiotow();
            element = element->nastepny;
            element->przedmiot = _przedmiot;
            element->nastepny = nullptr;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, ElementListyPrzedmiotow& element) {
        ElementListyPrzedmiotow* bufor = &element;
        while (bufor) {
            if (bufor->przedmiot) {
                out << *(bufor->przedmiot) << std::endl;
            }
            bufor = bufor->nastepny;
        }
        return out;
    }
    int policzWpisyWLiscie() {
        ElementListyPrzedmiotow* element = this;
        int licznik = 0;
        if (element) {
            if (element->przedmiot) {
                licznik++;
            }
            while (element->nastepny) {
                element = element->nastepny;
                licznik++;
            }
        }
        return licznik;
    }
    std::string znajdzNtaNazweElementu(int _ktory) {
        ElementListyPrzedmiotow* element = this;
        std::string nazwa = "uzyj ";
        int licznik = _ktory;
        if (element->przedmiot) {
            while (licznik > 0) {
                element = element->nastepny;
                licznik--;
            }
            nazwa += element->przedmiot->getNazwa();
        }
        return nazwa;
    }
};

enum Akcja {
    MenuGlowne = 0,
    PodejrzyjZwierzatko = 1,
    IdzDoSklepu = 2,
    PodejrzyjPlecak = 3,
    SklepZJedzeniem = 4,
    SklepZZabawkami = 5,
    SklepZLekarstwami = 6,
    WyjscieZGry = 7,
    kupOwoc = 8,
    kupWarzywo = 9,
    kupMieso = 10,
    kupGryzak = 11,
    kupPluszak = 12,
    kupDrapak = 13,
    kupLekPrzeciwbolowy = 14,
    kupWitamineC = 15,
    kupAspiryne = 16,
    uzyjSlot1 = 17,
    uzyjSlot2 = 18,
    uzyjSlot3 = 19,
    uzyjSlot4 = 20,
    uzyjSlot5 = 21,
    uzyjSlot6 = 22,
    uzyjSlot7 = 23,
    uzyjSlot8 = 24,
    uzyjSlot9 = 25
};

class Gra;

class ListaPrzedmiotow {
public:
    ElementListyPrzedmiotow* glowa;
    ListaPrzedmiotow* nastepny;
    ListaPrzedmiotow() {
        this->glowa = nullptr;
        this->nastepny = nullptr;
    }
    ListaPrzedmiotow* operator+=(Przedmiot* _przedmiot) {
        ListaPrzedmiotow* lista = this;
        Zabawka* zabawka = dynamic_cast<Zabawka*>(_przedmiot);
        Jedzenie* jedzenie = dynamic_cast<Jedzenie*>(_przedmiot);
        Lekarstwo* lekarstwo = dynamic_cast<Lekarstwo*>(_przedmiot);
        if (zabawka) {
        }else if (jedzenie) {
            lista = lista->nastepny;
        }else if (lekarstwo) {
            lista = lista->nastepny->nastepny;
        }
        lista->glowa->operator+=(_przedmiot);
        return this;
    }
    friend std::ostream& operator<<(std::ostream& out, ListaPrzedmiotow& lista) {
        ListaPrzedmiotow* bufor = &lista;
        while (bufor) {
            out << "Przegrodka plecaka" << std::endl;
            out << *(bufor->glowa) << std::endl;
            bufor = bufor->nastepny;
        }
        return out;
    }
    int policzWpisyWListach() {
        int i = 0;
        int suma = 0;
        ListaPrzedmiotow* lista = this;
        while (i < 3) {
            if (lista->glowa) {
                suma += lista->glowa->policzWpisyWLiscie();
            }
            if (lista->nastepny) {
                lista = lista->nastepny;
            }
            i++;
        }
        return suma;
    }
    std::string zwrocNazwePrzedmiotuWListach(int _ktory) {
        std::string nazwa = "";
        int indeks = 0;
        int i = 0;
        int ktory = _ktory;
        int pierwsza, druga, trzecia;
        ListaPrzedmiotow* lista = this;
        while (i < 3) {
            indeks += lista->glowa->policzWpisyWLiscie();
            switch (i) {
            case 0:
                pierwsza = lista->glowa->policzWpisyWLiscie();
                break;
            case 1:
                druga = lista->glowa->policzWpisyWLiscie();
                break;
            case 2:
                trzecia = lista->glowa->policzWpisyWLiscie();
                break;
            }
            if (lista->nastepny) {
                lista = lista->nastepny;
            }
            i++;
        }
        i = 0;
        int flaga = 0;

        if (ktory > pierwsza) {
            ktory -= pierwsza;
            flaga++;
        } 
        if (ktory > druga) {
            ktory -= druga;
            flaga++;
        }

        lista = this;
        while (i < flaga) {
            
            if (lista) {
                if (lista->nastepny) {
                    lista = lista->nastepny;
                }
            }
            i++;
        }
        nazwa = lista->glowa->znajdzNtaNazweElementu(ktory-1);
        return nazwa;
    }
    void usunNtyPrzedmiot(int _ktory) {
        std::string nazwa = "";
        int indeks = 0;
        int i = 0;
        int ktory = _ktory;
        int pierwsza, druga, trzecia;
        ListaPrzedmiotow* lista = this;
        while (i < 3) {
            indeks += lista->glowa->policzWpisyWLiscie();
            switch (i) {
            case 0:
                pierwsza = lista->glowa->policzWpisyWLiscie();
                break;
            case 1:
                druga = lista->glowa->policzWpisyWLiscie();
                break;
            case 2:
                trzecia = lista->glowa->policzWpisyWLiscie();
                break;
            }
            if (lista->nastepny) {
                lista = lista->nastepny;
            }
            i++;
        }
        
        i = 0;
        int flaga = 0;

        if (ktory > pierwsza) {
            ktory -= pierwsza;
            flaga++;
        }
        if (ktory > druga) {
            ktory -= druga;
            flaga++;
        }

        lista = this;
        while (i < flaga) {

            if (lista) {
                if (lista->nastepny) {
                    lista = lista->nastepny;
                }
            }
            i++;
        }
        ElementListyPrzedmiotow* przedmiot = lista->glowa;
        i = 0;
        ElementListyPrzedmiotow* bufor;
        if (ktory == 1 && !(przedmiot->nastepny)) {
            lista->glowa = new ElementListyPrzedmiotow();
            lista->glowa->nastepny = nullptr;
            lista->glowa->przedmiot = nullptr;
            return;
        }
        if (ktory == 1 && przedmiot->nastepny) {
            lista->glowa = przedmiot->nastepny;
            return;
        }
        while (i < ktory - 2) {
            przedmiot = przedmiot->nastepny;
            i++;
        }
        if(przedmiot->nastepny) {
            if (przedmiot->nastepny->nastepny) {
                bufor = przedmiot;
                przedmiot = przedmiot->nastepny;
                przedmiot = przedmiot->nastepny;
                bufor->nastepny = przedmiot;
            }
        }
        else if (przedmiot->nastepny) {
            przedmiot->nastepny = nullptr;
        }
        
    }
    int zwrocNazweAkcjiDlaPrzedmiotuWListach(int _ktory) {
        return _ktory + 17;
    }
};

class Wlasciciel {
private:
    int pieniadze;
    ListaPrzedmiotow* plecak;
public:
    Wlasciciel(int _pieniadze) : pieniadze(_pieniadze) {    
        this->plecak = nullptr;
    }
    void Zainicjuj_Plecak(int _przegrodki) {
        int przegrodki = _przegrodki;
        this->plecak = new ListaPrzedmiotow();
        ListaPrzedmiotow* bufor = this->plecak;
        while (przegrodki > 0) {
            bufor->glowa = new ElementListyPrzedmiotow();
            przegrodki--;
            if (przegrodki == 0) {
                bufor->nastepny = nullptr;
            }
            else {
                bufor->nastepny = new ListaPrzedmiotow();
                bufor = bufor->nastepny;
            }
        }
    }
    ListaPrzedmiotow* operator+=(Przedmiot* _przedmiot) {
        this->plecak->operator+=(_przedmiot);
        return this->plecak;
    }
    void opiszPlecak() {
        std::cout << *plecak;
    }
    int getPieniadze() {
        return this->pieniadze;
    }
    void setPieniadze(int _pieniadze) {
        this->pieniadze = _pieniadze;
        if (this->pieniadze > 99999) {
            this->pieniadze = 99999;
        }
    }
    int policzWpisyWPlecaku() {
        return this->plecak->policzWpisyWListach();
    }
    std::string zwrocNazwePrzedmiotuWPlecaku(int _ktory) {
        return this->plecak->zwrocNazwePrzedmiotuWListach(_ktory);
    }
    int zwrocNazweAkcjiDlaPrzedmiotuWPlecaku(int _ktory) {
        return this->plecak->zwrocNazweAkcjiDlaPrzedmiotuWListach(_ktory);
    }
    void usunZPlecaka(int _ktore) {
        this->plecak->usunNtyPrzedmiot(_ktore);
    }
};

class Przycisk {
    std::string tresc;
    int cel;
public:
    Przycisk() {}
    Przycisk(std::string _tresc, int _cel) : tresc(_tresc), cel(_cel) {  }
    std::string getTresc() {
        return this->tresc;
    }
    int getCel() {
        return this->cel;
    }
};

class ElementListyPrzyciskow {
public:
    Przycisk* przycisk;
    ElementListyPrzyciskow* nastepny;
    ElementListyPrzyciskow& operator[](int ktory) {
        int pomocnicza = ktory;
        ElementListyPrzyciskow* element = this;
        while (pomocnicza > 0 && element->nastepny) {
            element = element->nastepny;
            pomocnicza--;
        }
        return *element;
    }
};

class Kursor {
    int pozycja;
    int granica;
public:
    Kursor(int _pozycja, int _granica) : pozycja(_pozycja), granica(_granica) {  }
    void poruszDoGory() {
        this->pozycja--;
        if (this->pozycja < 0) {
            this->pozycja = this->granica-1;
        }
    }
    void poruszWDol() {
        this->pozycja++;
        if (this->pozycja >= this->granica) {
            this->pozycja = 0;
        }
    }
    int getPozycja() {
        return this->pozycja;
    }
    int getGranica() {
        return this->granica;
    }
    void setGranica(int _granica) {
        this->granica = _granica;
    }
};

class Menu {
    std::string tytul;
    ElementListyPrzyciskow* listaPrzyciskow;
    Kursor* kursor;
public:
    Menu(std::string _tytul) : tytul(_tytul) {
        this->listaPrzyciskow = new ElementListyPrzyciskow();
        this->listaPrzyciskow->przycisk = nullptr;
        this->listaPrzyciskow->nastepny = nullptr;
        this->kursor = new Kursor(0,0);
    }
    void dodajPrzyciskDoMenu(Przycisk* _przycisk) {
        ElementListyPrzyciskow* bufor = this->listaPrzyciskow;
        if (!(bufor->przycisk)) {
            bufor->przycisk = _przycisk;
        }
        else {
            while (bufor->nastepny) {
                bufor = bufor->nastepny;
            }
            bufor->nastepny = new ElementListyPrzyciskow();
            bufor = bufor->nastepny;
            bufor->przycisk = _przycisk;
            bufor->nastepny = nullptr;
        }
        this->kursor->setGranica(this->kursor->getGranica() + 1);
    }
    friend std::ostream& operator<<(std::ostream& out, Menu& menu) {
        out << menu.tytul << std::endl;
        ElementListyPrzyciskow* bufor = menu.listaPrzyciskow;
        int pozycja = 0;
        while (bufor) {
            if (menu.kursor->getPozycja() == pozycja) {
                out << "> ";
            }
            else {
                out << "  ";
            }
            if (bufor->przycisk) {
                out << bufor->przycisk->getTresc() << std::endl;
            }
            bufor = bufor->nastepny;
            pozycja++;
        }
        return out;
    }
    int obsluzZachowanieKursora(char _wejscie, int _aktywne) {
        switch (_wejscie) {
        case 72:
            this->kursor->poruszDoGory();
            break;
        case 80:
            this->kursor->poruszWDol();
            break;
        case 13:
            int slot = this->kursor->getPozycja();
            Przycisk* przycisk = this->listaPrzyciskow->operator[](slot).przycisk;
            return przycisk->getCel();
            break;
        }
        return _aktywne;
    }
};

void dodajPrzyciskiDoSklepu(Menu* _menu, Przycisk** _przyciski, int ilosc) {
    //int ilosc = sizeof(_przyciski) / sizeof(_przyciski[0]);
    for (int i = 0; i < ilosc; i++) {
        _menu->dodajPrzyciskDoMenu(_przyciski[i]);
    }
}

void wypelnijMenuPrzyciskami(Menu *_menu, std::string *_lancuchy, int* _cele, int ilosc) {
    Przycisk** przyciski = new Przycisk *[ilosc];

    for (int i = 0; i < ilosc; i++) {
        przyciski[i] = new Przycisk(_lancuchy[i], _cele[i]);
    }

    dodajPrzyciskiDoSklepu(_menu, (Przycisk**) przyciski, ilosc);
}

std::string nazwyMenuGry[] = {
    "Menu Glowne",
    "Podejrzyj Zwierzatko",
    "Idz do sklepu",
    "Podejrzyj plecak",
    "Sklep z jedzeniem",
    "Sklep z zabawkami",
    "Sklep z lekarstwami" };

std::string nazwyPrzyciskow[] = {
    "Podejrzyj zwierzatko", "Idz do sklepu", "Podejrzyj plecak", "Wyjdz z gry",
    "Wroc do Menu Glownego",
    "Kup jedzenie", "Kup zabawki", "Kup Lekarstwa", "Wroc do Menu Glownego",
    "Wroc do Menu Glownego",
    "Kup Owoc", "Kup Warzywo", "Kup Mieso",
    "Kup Lek Przeciwbolowy", "Kup Witamina C", "Kup Aspiryna", "Wroc do Wyboru Sklepow",
    "Kup Gryzak", "Kup Pluszak", "Kup Drapak", "Wroc do Wyboru Sklepow",
};

std::string** ustawNazwyPrzyciskow(std::string* _staraTablica) {
    std::string** nazwyPrzyciskow;
    int num = 0;
    nazwyPrzyciskow = new std::string*[7];
    int i = 0;
    while (i++ < 8) {
        int j = 0;
        int max;
        if (i == 1 || i == 3) {
            max = 1;
        }
        else {
            max = 4;
        }
        nazwyPrzyciskow[i] = new std::string[max];
        while (j < max) {
            nazwyPrzyciskow[i][j] = _staraTablica[i][j];
            j++;
        }
    }
    return nazwyPrzyciskow;
}

int iloscPrzyciskowMenu[] = { 4, 1, 4, 1, 4, 4, 4 };

int ktoreCeleMenu[] = { 1,2,3,-1,0,5,6,7,0,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0 };

int** zwrocKtoreCeleNalezaDoKtoregoPrzycisku(int* ktorecele) {
    int licznik = 0;
    int ile;
    int** ktore = new int*[7];
    for (int i = 0; i < 7; i++) {
        if (i != 1 && i!= 3) {
            ile = 4;
        }
        else {
            ile = 1;
        }
        ktore[i] = new int[ile];
        for (int j = 0; j < ile; j++) {
            ktore[i][j] = ktorecele[licznik];
            licznik++;
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < 7; i++) {
        int max = 0;
        if (i == 1 || i == 3) {
            max = 1;
        }
        else {
            max = 4;
        }
        for (int j = 0; j < max; j++) {
            std::cout << ktore[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return ktore;
}

class Gra {
    Zwierze *zwierze;
    Wlasciciel *wlasciciel;
public:
    Menu** menuGry;
    Gra() {};
    void zainicjujZwierze() {
        zwierze = new Zwierze();
        std::cin >> *zwierze;
    }
    void zainicjujWlasciciela() {
        wlasciciel = new Wlasciciel(0);
        wlasciciel->Zainicjuj_Plecak(3);
    }
    void opiszPlecak() {
        this->wlasciciel->opiszPlecak();
    }
    void opiszZwierzatko() {
        std::cout << *(this->zwierze);
    }
    void zaladujMenuGry(std::string *_nazwyMenuGry, int _iloscNazwMenu) {
        int i = 0;
        this->menuGry = new Menu* [_iloscNazwMenu];
        Menu** bufor = this->menuGry;
        while (i < _iloscNazwMenu) {
            bufor[i] = new Menu(_nazwyMenuGry[i]);
            i++;
        }
    }
    void wyswietlGlowneMenu() {
        system("cls");
        std::cout << menuGry[0];
    }
    void wyswietlMenuPodejrzyjZwierzatko() {
        system("cls");
        std::cout << menuGry[1];
    }
    int wyswietlajMenu(int _menu) {
        system("cls");
        if (_menu == Akcja::PodejrzyjZwierzatko) {
            this->opiszZwierzatko();
            std::cout << std::endl;
        }
        if (_menu > 3 && _menu < 7) {
            this->wypiszSrodki();
        }
        if (_menu < 7) {
            std::cout << *(this->menuGry[_menu]);
        }
        char c = _getch();
        int ktore = this->menuGry[_menu]->obsluzZachowanieKursora(c, _menu);
        return ktore;
    }
    int obliczWynik() {
        int sumaStatusowZwierzaka = this->zwierze->getJedzenie() + this->zwierze->getMilosc() + this->zwierze->getZdrowie();
        return sumaStatusowZwierzaka + this->wlasciciel->getPieniadze();
    }
    void Zakup(Przedmiot& przedmiot) {
        if (this->wlasciciel->getPieniadze() >= przedmiot.getCena()) {
            this->wlasciciel->operator+=(&przedmiot);
            this->wlasciciel->setPieniadze((this->wlasciciel->getPieniadze() - przedmiot.getCena()));
        }
        else {
            std::cout << "Nie udalo sie zakupic przedmiotu! Powod: zbyt malo srodkow" << std::endl;
            std::cout << "[Kliknij cokolwiek aby potwierdzic]" << std::endl;
            char c = _getch();
        }
    }
    void losowoDodajSrodki() {
        srand(time(NULL));
        int ilosc = rand() % 5;
        int tick = rand() % 300;
        int pieniadze = wlasciciel->getPieniadze();
        if (tick > pieniadze*300/99999) {
            this->wlasciciel->setPieniadze(this->wlasciciel->getPieniadze() + ilosc);
        }
    }
    void wypiszSrodki() {
        std::cout << "Srodki: " << this->wlasciciel->getPieniadze() << "g" << std::endl;
    }
    int policzObiektyWPlecaku() {
        return this->wlasciciel->policzWpisyWPlecaku();
    }
    std::string zwrocNazwePrzedmiotuWPlecaku(int _ktory) {
        return this->wlasciciel->zwrocNazwePrzedmiotuWPlecaku(_ktory);
    }
    int zwrocNazweAkcjiDlaPrzedmiotuWPlecaku(int _ktory) {
        return this->wlasciciel->zwrocNazweAkcjiDlaPrzedmiotuWPlecaku(_ktory);
    }
    void losowoManipulujStatystykami() {
        srand(time(NULL));
        int ktora = rand() % 3;
        int tick = rand() % 99;
        int ilosc = 1;
        int statystyka;
        if (ktora == 0) {
            statystyka = this->zwierze->getJedzenie();
        }
        else if (ktora == 1) {
            statystyka = this->zwierze->getMilosc();
        }
        else if (ktora == 2) {
            statystyka = this->zwierze->getZdrowie();
        }
        if (tick < statystyka) {
            if (ktora == 0) {
                if (statystyka - ilosc >= 0) {
                    this->zwierze->setJedzenie(statystyka - ilosc);
                    if (statystyka - ilosc == 40) {
                        std::cout << "Twoje zwierzatko jest glodne!" << std::endl;
                        char c = _getch();
                    }
                }
            }
            else if (ktora == 1) {
                if (statystyka - ilosc >= 0) {
                    this->zwierze->setMilosc(statystyka - ilosc);
                    if (statystyka - ilosc == 40) {
                        std::cout << "Twoje zwierzatko jest smutne!" << std::endl;
                        char c = _getch();
                    }
                }
            }
            else if (ktora == 2) {
                if (statystyka - ilosc >= 0) {
                    this->zwierze->setZdrowie(statystyka - ilosc);
                    if (statystyka - ilosc == 40) {
                        std::cout << "Twoje zwierzatko jest chore!" << std::endl;
                        char c = _getch();
                    }
                }
            }
        }
        if (zwierze->getJedzenie() == 0 && zwierze->getMilosc() == 0 && zwierze->getZdrowie() == 0) {
            std::cout << "Koniec gry! Twoje zwierze umarlo!" << std::endl;
            std::cout << "R. I. P. " << this->zwierze->getNazwa() << std::endl;
            std::cout << "Byles dobrym " << this->zwierze->getRodzaj() << std::endl;
        }

    }
    void Uzyj(Przedmiot& przedmiot) {
        this->zwierze->uzyjPrzedmiotu(&przedmiot);
    }
    void usunZPlecaka(int _ktore) {
        this->wlasciciel->usunZPlecaka(_ktore);
    }
};

int main()
{
    Gra* tamagotchi = new Gra();
    tamagotchi->zainicjujZwierze();
    tamagotchi->zainicjujWlasciciela();
    tamagotchi->zaladujMenuGry(nazwyMenuGry, 7);

    Przedmiot* przedmiotyZeSklepu[] = {
        new Jedzenie(25, "Owoc", 10),
        new Jedzenie(35, "Warzywo", 20),
        new Jedzenie(55, "Mieso", 40),
        new Zabawka(225, "Gryzak", 40),
        new Zabawka(375, "Pluszak", 50),
        new Zabawka(505, "Drapak", 70),
        new Lekarstwo(75, "Lek przeciwbolowy", 5),
        new Lekarstwo(105, "Witamina C", 10),
        new Lekarstwo(130, "Aspiryna", 15)
    };

    Menu* menuGlowne = new Menu("Menu Glowne");
    Menu* menuPodejrzyjZwierzatko = new Menu("Podejrzyj Zwierzatko");
    Menu* menuIdzDoSklepu = new Menu("Idz do sklepu");
    Menu* menuPodejrzyjPlecak = new Menu("Podejrzyj plecak");
    Menu* menuUzywaniaPrzedmiotu = new Menu("Uzywanie przedmiotu");

    Menu* menuSklepuZJedzeniem = new Menu("Sklep z jedzeniem");
    Menu* menuSklepuZZabawkami = new Menu("Sklep z zabawkami");
    Menu* menuSklepuZLekarstwami = new Menu("Sklep z lekarstwami");

    std::string nazwyPrzyciskowMenuGlownego[] = { "Podejrzyj zwierzatko", "Idz do sklepu", "Podejrzyj plecak", "Wyjdz z gry" };
    std::string nazwyPodejrzyjZwierzatko[] = {"Wroc do Menu Glownego"};
    std::string nazwyIdzDoSklepu[] = { "Kup jedzenie", "Kup zabawki", "Kup Lekarstwa", "Wroc do Menu Glownego" };
    std::string nazwyPodejrzyjPlecak[] = { "Wroc do Menu Glownego" } ;
    std::string nazwySklepuZJedzeniem[] = { "Kup Owoc [10pkt] [25g] ", "Kup Warzywo [20pkt] [35g]", "Kup Mieso [40pkt] [55g]", "Wroc do Menu Sklepow" };
    std::string nazwySklepuZZabawkami[] = { "Kup Gryzak [40pkt] [225g]", "Kup Pluszak [50pkt] [375g]", "Kup Drapak [70pkt] [505g]", "Wroc do Menu Sklepow" };
    std::string nazwySklepuZLekarstwami[] = { "Kup Lek Przeciwbolowy [5pkt] [75g]", "Kup Witamina C [10pkt] [105g]", "Kup Aspiryna [15pkt] [130g]", "Wroc do Menu Sklepow" };

    int menuDoKtorychKierujaPrzyciskiMenuGlownego[] = {
        Akcja::PodejrzyjZwierzatko,
        Akcja::IdzDoSklepu,
        Akcja::PodejrzyjPlecak,
        Akcja::WyjscieZGry
    };

    int menuDoKtorychKierujaPrzyciskiPodejrzyjZwierzatko[] = {
        Akcja::MenuGlowne
    };

    int menuDoKtorychKierujaPrzyciskiMenuIdzDoSklepu[] = {
        Akcja::SklepZJedzeniem,
        Akcja::SklepZZabawkami,
        Akcja::SklepZLekarstwami,
        Akcja::MenuGlowne
    };

    int menuDoKtorychKierujaPrzyciskiPodejrzyjPlecak[] = {
        Akcja::MenuGlowne
    };

    int menuDoKtorychKierujaPrzyciskiSklepuZJedzeniem[] = {
        Akcja::kupOwoc,
        Akcja::kupWarzywo,
        Akcja::kupMieso,
        Akcja::IdzDoSklepu
    };

    int menuDoKtorychKierujaPrzyciskiSklepuZZabawkami[] = {
        Akcja::kupGryzak,
        Akcja::kupPluszak,
        Akcja::kupDrapak,
        Akcja::IdzDoSklepu
    };

    int menuDoKtorychKierujaPrzyciskiSklepuZLekarstwami[] = {
        Akcja::kupLekPrzeciwbolowy,
        Akcja::kupWitamineC,
        Akcja::kupAspiryne,
        Akcja::IdzDoSklepu
    };

    wypelnijMenuPrzyciskami(tamagotchi->menuGry[0], nazwyPrzyciskowMenuGlownego, menuDoKtorychKierujaPrzyciskiMenuGlownego, 4);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[1], nazwyPodejrzyjZwierzatko, menuDoKtorychKierujaPrzyciskiPodejrzyjZwierzatko, 1);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[2], nazwyIdzDoSklepu, menuDoKtorychKierujaPrzyciskiMenuIdzDoSklepu, 4);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[3], nazwyPodejrzyjPlecak, menuDoKtorychKierujaPrzyciskiPodejrzyjPlecak, 1);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[4], nazwySklepuZJedzeniem, menuDoKtorychKierujaPrzyciskiSklepuZJedzeniem, 4);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[5], nazwySklepuZZabawkami, menuDoKtorychKierujaPrzyciskiSklepuZZabawkami, 4);
    wypelnijMenuPrzyciskami(tamagotchi->menuGry[6], nazwySklepuZLekarstwami, menuDoKtorychKierujaPrzyciskiSklepuZLekarstwami, 4);

    std::string *noweNazwyPodejrzyjPlecak;
    int iloscObiektowWPlecaku;
    int *menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak;

    bool koniec = false;
    int aktywne = Akcja::MenuGlowne;
    int poprzednie;
    while (!koniec) {
        poprzednie = aktywne;
        
        aktywne = tamagotchi->wyswietlajMenu(aktywne);
        if (aktywne > 7 && aktywne < 17) {
            tamagotchi->Zakup(*(przedmiotyZeSklepu[aktywne-8]));
            iloscObiektowWPlecaku = tamagotchi->policzObiektyWPlecaku();
            noweNazwyPodejrzyjPlecak = new std::string[iloscObiektowWPlecaku + 1];
            for (int i = 0; i < iloscObiektowWPlecaku; i++) {
                noweNazwyPodejrzyjPlecak[i] = tamagotchi->zwrocNazwePrzedmiotuWPlecaku(i+1);
            }
            noweNazwyPodejrzyjPlecak[iloscObiektowWPlecaku] = "Wroc do Menu Glownego";
            menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak = new int[iloscObiektowWPlecaku + 1];
            for (int i = 0; i < iloscObiektowWPlecaku; i++) {
                menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak[i] = tamagotchi->zwrocNazweAkcjiDlaPrzedmiotuWPlecaku(i+1);
            }
            menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak[iloscObiektowWPlecaku] = Akcja::MenuGlowne;
            aktywne = poprzednie;
            menuPodejrzyjPlecak = new Menu("Podejrzyj plecak");
            tamagotchi->zaladujMenuGry(nazwyMenuGry, 7);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[0], nazwyPrzyciskowMenuGlownego, menuDoKtorychKierujaPrzyciskiMenuGlownego, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[1], nazwyPodejrzyjZwierzatko, menuDoKtorychKierujaPrzyciskiPodejrzyjZwierzatko, 1);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[2], nazwyIdzDoSklepu, menuDoKtorychKierujaPrzyciskiMenuIdzDoSklepu, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[3], noweNazwyPodejrzyjPlecak, menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak, iloscObiektowWPlecaku + 1);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[4], nazwySklepuZJedzeniem, menuDoKtorychKierujaPrzyciskiSklepuZJedzeniem, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[5], nazwySklepuZZabawkami, menuDoKtorychKierujaPrzyciskiSklepuZZabawkami, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[6], nazwySklepuZLekarstwami, menuDoKtorychKierujaPrzyciskiSklepuZLekarstwami, 4);
        }
        else if (aktywne == Akcja::WyjscieZGry) {
            break;
        }
        if (aktywne >= 17) {
            tamagotchi->Uzyj(*(przedmiotyZeSklepu[aktywne - 18]));
            tamagotchi->usunZPlecaka(aktywne-17);
            iloscObiektowWPlecaku = tamagotchi->policzObiektyWPlecaku();
            noweNazwyPodejrzyjPlecak = new std::string[iloscObiektowWPlecaku + 1];
            for (int i = 0; i < iloscObiektowWPlecaku; i++) {
                noweNazwyPodejrzyjPlecak[i] = tamagotchi->zwrocNazwePrzedmiotuWPlecaku(i + 1);
            }
            noweNazwyPodejrzyjPlecak[iloscObiektowWPlecaku] = "Wroc do Menu Glownego";
            menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak = new int[iloscObiektowWPlecaku + 1];
            for (int i = 0; i < iloscObiektowWPlecaku; i++) {
                menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak[i] = tamagotchi->zwrocNazweAkcjiDlaPrzedmiotuWPlecaku(i + 1);
            }
            menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak[iloscObiektowWPlecaku] = Akcja::MenuGlowne;
            aktywne = poprzednie;
            menuPodejrzyjPlecak = new Menu("Podejrzyj plecak");
            tamagotchi->zaladujMenuGry(nazwyMenuGry, 7);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[0], nazwyPrzyciskowMenuGlownego, menuDoKtorychKierujaPrzyciskiMenuGlownego, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[1], nazwyPodejrzyjZwierzatko, menuDoKtorychKierujaPrzyciskiPodejrzyjZwierzatko, 1);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[2], nazwyIdzDoSklepu, menuDoKtorychKierujaPrzyciskiMenuIdzDoSklepu, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[3], noweNazwyPodejrzyjPlecak, menuDoKtorychKierujaNowePrzyciskiPodejrzyjPlecak, iloscObiektowWPlecaku + 1);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[4], nazwySklepuZJedzeniem, menuDoKtorychKierujaPrzyciskiSklepuZJedzeniem, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[5], nazwySklepuZZabawkami, menuDoKtorychKierujaPrzyciskiSklepuZZabawkami, 4);
            wypelnijMenuPrzyciskami(tamagotchi->menuGry[6], nazwySklepuZLekarstwami, menuDoKtorychKierujaPrzyciskiSklepuZLekarstwami, 4);
            aktywne = poprzednie;
        }
        tamagotchi->losowoDodajSrodki();
        tamagotchi->losowoManipulujStatystykami();
    }
    std::cout << "Nastapilo zakonczenie rozgrywki" << std::endl;
    std::cout << "Oto twoj wynik: " << tamagotchi->obliczWynik() << std::endl;

}