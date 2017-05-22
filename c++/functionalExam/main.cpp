//
// @file main.cpp
// @author Jonas Solsvik
// @created 21.05.2017
// @brief Solving examen 2016 in a functional way
//

#include "functional.cpp" // Collection, map, filter, reduce, foreach
#include "les.cpp"       // les(), les(txt, min, max), les(txt, str, LEN)

// INCLUDE:
#include <iostream> // cin, cout
#include <fstream>  // ifstream
#include <cctype>   // toupper

// CONST:
const int MINOPPGAVEDATO = 20160422;
const int MAXOPPGAVEDATO = 20291231;
const int MINOPPGAVETID  = 15;
const int MAXOPPGAVETID  = 600;
const int MAXOPPGAVER    = 50;
const int MAXDATOER      = 200;

struct Oppgave {
     char* beskrivelse;
     int   beregnetTid;
     bool  ferdig = false;
};

struct Dato {
    unsigned int      dato;                 //dato (ÅÅÅÅMMDD)
    char*             ekstrahjelpNavn;
    Collection<Oppgave, MAXOPPGAVER> oppgaver;

    bool altFerdig();
};

using DatoCollection = Collection<Dato, MAXDATOER>;
void slettFerdigeDatoer(DatoCollection& datoene);
void settFerdig(DatoCollection& datoene);
void nyOppgave(DatoCollection& datoene);
void nyDato(DatoCollection& datoene);

void displayDato(const Dato& x);
void displayOppgave(const Oppgave& x);
void displayDatoer(DatoCollection& datoene);
void displayPrettyDato(int dato);
void displayMenu();

int main() {
    char valg;
    DatoCollection datoene;
    //lesFraFil();

    displayMenu();
    valg = les("\n\n\nKommando: ");
    while (valg != 'Q')  {
        switch (valg)  {
            case 'D': nyDato(datoene);             break;
            case 'S': displayDatoer(datoene);      break;
            case 'O': nyOppgave(datoene);          break;
            case 'F': settFerdig(datoene);         break;
            case 'R': slettFerdigeDatoer(datoene); break;
            default:  displayMenu();
                break;
        }
        valg = les("\n\n\nKommando: ");
    }

    std::cout << "\n\n";
    return 0;
}

void slettFerdigeDatoer(DatoCollection& datoene) {
    datoene = filter(datoene, [](const auto& x) {
        if (x.oppgaver.count == countIf(x.oppgaver,
                [](const auto& x){ return x.ferdig; })) {
            displayDato(x);
            return false;
        }
        return true;
    });
}

void settFerdig(DatoCollection& datoene) {
    unsigned int lovligDato = les("Dato: ", MINOPPGAVEDATO, MAXOPPGAVEDATO);

    findThenElse(datoene,
        [lovligDato](const auto& x) { return x.dato == lovligDato; },
        [](auto& x) {

            filterThenElse(x.oppgaver,
                [](const auto& x){ return !x.ferdig; },
                [](auto& x) {
                    displayOppgave(x);
                    char svar = les("Onsker du å sette den til ferdig?(J/N): ");
                    if (svar == 'J') x.ferdig = true;
                },
                [](){ std::cout << "Alle er ferdig.."; }
            );
        },
        [](){ std::cout << "Dato finnes ikke...\n"; }
    );
}

void displayPrettyDato(int dato) {
    unsigned int day   = dato % 100;  dato /= 100;  //dato (ÅÅÅÅMMDD)
    unsigned int month = dato % 100;  dato /= 100;
    unsigned int year  = dato;
    std::cout << day << "/" << month << "-" << year << '\n';
}

void displayOppgave(const Oppgave& x) {
    std::cout << "   --- Oppgave --- \n"
              << "   Beskrivelse: " << x.beskrivelse << '\n'
              << "   BergnetTid:  " << x.beregnetTid    << '\n'
              << "   Ferdig:      " << ((x.ferdig)? "FERDIG" : " --- ") << "\n\n";
}

void displayDato(const Dato& x){
    std::cout << x.dato << "   " << x.ekstrahjelpNavn << '\n';
    if (x.oppgaver.count == 0) {
        std::cout << "Det finnes ingen oppgaver";
    } else { foreach(x.oppgaver, [](const auto& x){ displayOppgave(x); }); }
}

void displayDatoer(DatoCollection& datoene) {
    if(datoene.count == 0) {
        std::cout << "Det finnes ingen datoer...\n";
    } else { foreach(datoene, [](const auto& x){ displayDato(x); }); }
}

void displayMenu() { // Skriver alle mulige menyvalg:
    std::cout << "\n\nFØ LGENDE KOMMANDOER ER TILGJENGELIGE:"
                << "\n   D  - ny Dato"
                << "\n   S  - Skriv dato"
                << "\n   O  - ny Oppgave"
                << "\n   F  - sett Ferdig"
                << "\n   R  - Rens/slett ferdige datoer"
                << "\n   Q  - Quit / avslutt";
}

void nyOppgave(DatoCollection& datoene) {

    unsigned int lovligDato = les("Dato: ", MINOPPGAVEDATO, MAXOPPGAVEDATO);

    findThenElse(datoene,
        [lovligDato](const auto& x) { return x.dato == lovligDato; },

        [](auto& x){
            add(x.oppgaver, Oppgave{
                lesString("Beskrivelse(max 80 tegn)"),
                les("Beregnet tid: ", MINOPPGAVETID, MAXOPPGAVETID)
            });
        },

        []() { std::cout << "Dato finnes ikke...\n"; }
    );
}

void nyDato(DatoCollection& datoene) {
    unsigned int lovligDato = les("Dato: ", MINOPPGAVEDATO, MAXOPPGAVEDATO);

    findThenElse(datoene,
        [lovligDato](const auto& x) { return x.dato == lovligDato; },

        [](auto&) { std::cout << "Dato finnes allerede...\n"; },

        [&datoene, lovligDato]() {
            add(datoene, Dato{ lovligDato, lesString("Navn"), {} });
        }
    );
}
