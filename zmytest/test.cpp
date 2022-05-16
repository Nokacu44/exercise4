#include "test.hpp"
#include <random>
#include <iostream>

using namespace std;
using namespace lasd;

BST<int> bstint;

// AUXILIARY FUNCTIONS
int generateRandomInteger() {
    default_random_engine generator( random_device{}() );
    uniform_int_distribution<int> distribution(-100, 100);
    return distribution(generator); 
}

int getStructureSize() {
    int dim = 0;
    while (cout << endl << "DIGITARE LA DIMENSIONE DELLA STRUTTURA: " && !(cin >> dim)) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
    }
    return dim;
}

// MAP FUNCTIONS
void visualizeBSTInt(int& value, void* other_par) { 
    cout << "[" << value << "] "; 
}

// FOLD FUNCTIONS
void foldBSTInt(const int& value, const void* limit, void* accumulator) {
    if(value < *((int*) limit)) {
        *((int*) accumulator) = *((int*) accumulator) * value; 
        std::cout << "ACCUMULATORE: " << *((int*) accumulator) << std::endl; 
    } else {
        *((int*) accumulator) = *((int*) accumulator) * 1;
    }
}

// MENU
void menuBSTInteger(BST<int>& bst) {
    ushort choice = 0;
    cout << endl << "[1] (MAP) PER VISUALIZZAZIONE ALBERO IN AMPIEZZA, PRE-ORDER, POST-ORDER, IN-ORDER." << endl;
    cout << "[2] PER CONTROLLO DI ESISTENZA DI UN VALORE." << endl;
    cout << "[3] (FOLD) PER APPLICAZIONE FUNZIONE PRODOTTO PER GLI INTERI MINORI DI N." << endl;
    cout << "SCELTA: "; 
    cin >> choice;

    switch(choice) {
        case 1: {
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTInt, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTInt, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTInt, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTInt, nullptr);

            cout << endl;
            menuBSTInteger(bst);
            break;
        }
        case 2: {
            int elem = 0;
            while (cout << endl << "DIGITARE IL NUMERO DI CUI VERIFICARE LA PRESENZA: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(elem)) {
                cout << endl << "RISULTATO RICERCA: TRUE" << endl;
            } else {
                cout << endl << "RISULTATO RICERCA: FALSE" << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 3: {
            int n = 0; 
            while (cout << endl << "DIGITARE IL VALORE SECONDO CUI APPLICARE LA FUNZIONE: " && !(cin >> n)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }
            
            cout << endl;

            const int lim = n;
            int start = 1;

            cout << endl << "APPLICAZIONE FOLD IN AMPIEZZA: " << endl;
            bst.FoldBreadth(foldBSTInt, &lim, &start);
    
            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN PRE-ORDER: " << endl;
            bst.FoldPreOrder(foldBSTInt, &lim, &start);
    
            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN POST-ORDER: " << endl;
            bst.FoldPostOrder(foldBSTInt, &lim, &start);

            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN IN-ORDER: " << endl;
            bst.FoldInOrder(foldBSTInt, &lim, &start);

            cout << endl;
            menuBSTInteger(bst);
            break;
        }
        default: 
            cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
    }

}


// BEGIN OF THE TEST
void startTest() {
    ushort scelta = 0;
    ushort dimensione = 0;

    cout << endl << "[1] PER POPOLARE LA STRUTTURA CON INTERI." << endl;
    cout << "[2] PER POPOLARE LA STRUTTURA CON FLOAT." << endl;
    cout << "[3] PER POPOLARE LA STRUTTURA CON STRINGHE." << endl;
    cout << "SCELTA: "; 
    cin >> scelta;

    switch(scelta) {
        case 1: {   
            dimensione = getStructureSize();
            List<int>* lista = new List<int>();

            cout << endl;
            for (int i = 0; i < dimensione; i++){
                int value = generateRandomInteger();
                cout << "HO GENERATO IL VALORE: " << value << endl;
                lista->InsertAtBack(value);
            }

            bstint = BST<int>(*lista);

            delete lista;

            menuBSTInteger(bstint);

            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        defaut: 
            cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
    }

}