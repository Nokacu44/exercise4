#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"
#include <iostream>

using namespace std;

int main() {
  ushort scelta = 0;

  cout << "Lasd Libraries 2022" << endl;
  cout << "[1] PER EFFETTUARE LASDTEST." << endl;
  cout << "[2] PER VISUALIZZARE LO SVOGLIMENTO DEL QUARTO ESERCIZIO." << endl;
  cout << "SCELTA: "; 
  cin >> scelta;

  switch(scelta) {
    case 1:
      lasdtest();
      break;
    case 2:
      startTest();
      break;
    default:
      cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
  }

  return 0;
}