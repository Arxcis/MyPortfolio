// @file les.cpp
// @author Jonas Solsvik
// @created 21.05.2017
// @brief Frodes les() library
#include <cstring>  // strcpy, strlen

const size_t STRLEN = 80;

char les(const char* txt) { // Leser og upcaser ett tegn:
    std::cout << txt;
    char ch;   std::cin >> ch;   std::cin.ignore();   return (toupper(ch));
}

int les(const char* txt, const int MIN, const int MAX)  {
    int n;
    do {
        std::cout << '\t' << txt << " (" << MIN << '-' << MAX << "): ";
        std::cin >> n;  std::cin.ignore();
    } while (n < MIN || n > MAX);
    return n;
 }
  //  Leser inn en tekst:
 void les(const char* txt, char* string, const int LEN)  {
     do {
         std::cout << '\t' << txt << ": "; // Skriver ledetekst.
         std::cin.getline(string, LEN); // Leser inn tekst.
     } while (strlen(string) == 0); // Sjekker at tekstlengden er ulik 0.
 }

char* lesString(const char* txt) {

    char  lesString[STRLEN];
    les(txt, lesString, STRLEN);

    char* string = new char[strlen(lesString)+1];
    strcpy(string, lesString);
    return string;
}
