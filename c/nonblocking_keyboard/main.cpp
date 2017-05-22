// @file main.cpp
// @author Jonas Solsvik
// @created 21.05.2017
// @brief Solving examen 2016 in a functional way

#include <functional.cpp> // Collection, map, filter, reduce, foreach
#include <les.cpp>

// INCLUDE:
#include <iostream> // cin, cout
#include <fstream>  // ifstream
#include <cstring>  // strcpy, strlen
#include <cctype>   // toupper

// CONST:
const int STRLEN = 80;
const int MINOPPGAVEDATO = 20160422;
const int MAXOPPGAVEDATO = 20291231;
const int MINOPPGAVETID = 15;
const int MAXOPPGAVETID = 600;

const int MAXOPPGAVER = 50;

class Oppgave : public TextElement  {
     private: // text = oppgavebeskrivelse
     int tid; // Ca. tid oppgaven tar (i minutter).
     bool ferdig; // Oppgaven utført/ferdig eller ei.
     public:
    Oppgave(char* t);
    Oppgave(char* t, ifstream & inn);
    void display();
    //  Oppgave 2C
    //  Oppgave 2G
    //  Oppgave 2B
    int hentTid() { return tid; } // |
    bool erFerdig() { return ferdig; } // | Ferdiglaget
    void settFerdig() { ferdig = true; } // |
};

//
// class Dato
//   Programmet holder styr på hvilke datoer det kommer EN ekstra-hjelp
//
struct Dato : public NumElement  {
    char* personNavn;                           // Ekstrahjelpens navn.
    Collection<Oppgave, MAXOPPGAVER>* oppgavene; // Liste med oppgaver på datoen.

    Dato(int dato); // Oppgave 2A Dato(int dato, ifstream & inn); // Oppgave 2G
    void display(); // Oppgave 2B og 2F
    // Ferdiglaget:
    void nyOppgave();
    void settFerdig();
    bool altFerdig();
    //  Oppgave 2C
    //  Oppgave 2D
    //  Oppgave 2E
};


int main() {
    return 0;
}
