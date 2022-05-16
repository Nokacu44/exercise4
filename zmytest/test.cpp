#include "test.hpp"
#include <random>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace lasd;

BST<int> bstint;
BST<float> bstfloat;
BST<string> bststring;

// AUXILIARY FUNCTIONS
int generateRandomInteger() {
    default_random_engine generator( random_device{}() );
    uniform_int_distribution<int> distribution(-100, 100);
    return distribution(generator); 
}

float generateRandomFloat() {
    default_random_engine generator( random_device{}() );
    uniform_real_distribution<float> distribution(-25.0f, 25.0f);
    return distribution(generator); 
}

string generateRandomString() {
    const string collezione_caratteri = "abcdefghijklmnopqrstuvwxyz";

    default_random_engine generator( std::random_device{}() );
    uniform_int_distribution<int> distribution(0, collezione_caratteri.size() - 1);

    string random_string = "";

    int random_lenght = distribution(generator);

    for (size_t i = 0; i < random_lenght; ++i) {
        random_string += collezione_caratteri[ distribution(generator) ];
    }

    return random_string;
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

void visualizeBSTFloat(float& value, void* other_par) {
    cout << setprecision(9) << "[" << value << "] ";
}

void visualizeBSTString(string& value, void* other_par) {
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

void foldBSTFloat(const float& value, const void* limit, void* accumulator) {
        if(value > *((float*) limit)) {
        *((float*) accumulator) = *((float*) accumulator) + value; 
        std::cout << setprecision(9) << "ACCUMULATORE: " << *((float*) accumulator) << std::endl; 
    } else {
        *((float*) accumulator) = *((float*) accumulator) + 0.0f;
    }
}

void foldBSTString(const std::string& s, const void* limit, void* accumulator) {
    if(s.length() <= *((uint*) limit)) {
        *((std::string*) accumulator) += s;
        std::cout << "Accumulatore: " << *((std::string*) accumulator) << std::endl;
    } else {
        *((std::string*) accumulator) += "";
    }
}

// MENU
void menuBSTInteger(BST<int>& bst) {
    ushort choice = 0;
    cout << endl << "[1] (MAP) PER VISUALIZZAZIONE ALBERO IN AMPIEZZA, PRE-ORDER, POST-ORDER, IN-ORDER." << endl;
    cout << "[2] PER CONTROLLO DI ESISTENZA DI UN VALORE." << endl;
    cout << "[3] (FOLD) PER APPLICAZIONE FUNZIONE PRODOTTO PER GLI INTERI MINORI DI N." << endl;
    cout << "[4] PER INSERIRE UN ELEMENTO." << endl;
    cout << "[5] PER ELIMINARE UN ELEMENTO." << endl;
    cout << "[6] RIMOZIONE DEL MINIMO." << endl;
    cout << "[7] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MINIMO." << endl;
    cout << "[8] RIMOZIONE DEL MASSIMO." << endl;
    cout << "[9] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MASSIMO." << endl;
    cout << "[10] RIMOZIONE DEL SUCCESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[11] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI UN DATO ELEMENTO." << endl; 
    cout << "[12] RIMOZIONE DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[13] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[14] CLEAR DELLA STRUTTURA." << endl;
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
        case 4: {
            int elem = 0;
            while (cout << endl << "DIGITARE IL NUMERO DA INSERIRE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (!bst.Exists(elem)) {
                bst.Insert(elem);

                cout << endl << elem << " E' STATO INSERITO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
            } else {
                cout << endl << "NON POSSO INSERIRE: L'ELEMENTO ESISTE GIA'." << endl;
            }
            cout << endl;

            menuBSTInteger(bst);
            break;
        }
        case 5: {
            int elem = 0;
            while (cout << endl << "DIGITARE IL NUMERO DA RIMUOVERE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(elem)) {
                bst.Remove(elem);

                cout << endl << elem << " E' STATO RIMOSSO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: ELEMENTO INESISTENTE." << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 6: {
            int minimo = bst.Min();
            cout << endl << "IL MINIMO DELL'ALBERO E': "<< minimo << endl;
            
            bst.RemoveMin();

            cout << minimo << " E' STATO ELIMINATO." << endl;

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
        case 7: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MINIMO:" << endl; 
            cout << "--> IL MINIMO DELL'ALBERO E': " << bst.Min();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MINIMO: " << endl;
            cout << "--> " << bst.MinNRemove() << " E' STATO RIMOSSO." << endl; 
            
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
        case 8: {
            int massimo = bst.Max();
            cout << endl << "IL MASSIMO DELL'ALBERO E': " << massimo << endl;
            
            bst.RemoveMax();

            cout << massimo << " E' STATO ELIMINATO." << endl;

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
        case 9: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MASSIMO:" << endl; 
            cout << "--> IL MASSIMO DELL'ALBERO E': " << bst.Max();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MASSIMO: " << endl;
            cout << "--> " << bst.MaxNRemove() << " E' STATO RIMOSSO." << endl; 
            
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
        case 10: {
            int value = 0;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                int successor = bst.Successor(value);
                cout << endl << "IL SUCCESSORE DI " << value << " E': "<< successor << endl;
                bst.RemoveSuccessor(value);
                cout << successor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 11: {
            int value = 0;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI " << value << " :" << endl; 
                cout << "--> IL SUCCESSORE E': " << bst.Successor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL SUCCESSORE: " << endl;
                cout << "--> " << bst.SuccessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 12: {
            int value = 0;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                int predecessor = bst.Predecessor(value);
                cout << endl << "IL PREDECESSORE DI " << value << " E': " << predecessor << endl;
                bst.RemovePredecessor(value);
                cout << predecessor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 13: {
            int value = 0;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI " << value << " :" << endl; 
                cout << "--> IL PREDECESSORE E': " << bst.Predecessor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL PREDECESSORE: " << endl;
                cout << "--> " << bst.PredecessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTInt, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTInt, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTInteger(bst);
            break;
        }
        case 14: {
            bst.Clear();
            cout << endl << "LA STRUTTURA ORA E' VUOTA! " << endl;
            menuBSTInteger(bst);
            break;
        }
        default: 
            cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
    }
}

void menuBSTFloat(BST<float>& bst){
    ushort choice = 0;
    cout << endl << "[1] (MAP) PER VISUALIZZAZIONE ALBERO IN AMPIEZZA, PRE-ORDER, POST-ORDER, IN-ORDER." << endl;
    cout << "[2] PER CONTROLLO DI ESISTENZA DI UN VALORE." << endl;
    cout << "[3] (FOLD) PER APPLICAZIONE FUNZIONE SOMMA PER I FLOAT MAGGIORI DI N." << endl;
    
    
    cout << "[4] PER INSERIRE UN ELEMENTO." << endl;
    cout << "[5] PER ELIMINARE UN ELEMENTO." << endl;
    cout << "[6] RIMOZIONE DEL MINIMO." << endl;
    cout << "[7] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MINIMO." << endl;
    cout << "[8] RIMOZIONE DEL MASSIMO." << endl;
    cout << "[9] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MASSIMO." << endl;
    cout << "[10] RIMOZIONE DEL SUCCESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[11] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI UN DATO ELEMENTO." << endl; 
    cout << "[12] RIMOZIONE DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[13] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[14] CLEAR DELLA STRUTTURA." << endl;
    cout << "SCELTA: ";
    cin >> choice;

    switch(choice) {
        case 1: {
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTFloat, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTFloat, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTFloat, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTFloat, nullptr);

            cout << endl;
            menuBSTFloat(bst);
            break;
        }
        case 2: {
            float elem = 0.0f;
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

            menuBSTFloat(bst);
            break;
        }
        case 3: {
            float n = 0.0f; 
            while (cout << endl << "DIGITARE IL VALORE SECONDO CUI APPLICARE LA FUNZIONE: " && !(cin >> n)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }
            
            cout << endl;

            const float lim = n;
            int start = 0;

            cout << endl << "APPLICAZIONE FOLD IN AMPIEZZA: " << endl;
            bst.FoldBreadth(foldBSTFloat, &lim, &start);
    
            start = 0;

            cout << endl << "APPLICAZIONE FOLD IN PRE-ORDER: " << endl;
            bst.FoldPreOrder(foldBSTFloat, &lim, &start);
    
            start = 0;

            cout << endl << "APPLICAZIONE FOLD IN POST-ORDER: " << endl;
            bst.FoldPostOrder(foldBSTFloat, &lim, &start);

            start = 0;

            cout << endl << "APPLICAZIONE FOLD IN IN-ORDER: " << endl;
            bst.FoldInOrder(foldBSTFloat, &lim, &start);

            cout << endl;
            menuBSTFloat(bst);
            break;
        }
        case 4: {
            float elem = 0.0f;
            while (cout << endl << "DIGITARE IL NUMERO DA INSERIRE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (!bst.Exists(elem)) {
                bst.Insert(elem);

                cout << endl << setprecision(9) << elem << " E' STATO INSERITO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
            } else {
                cout << endl << "NON POSSO INSERIRE: L'ELEMENTO ESISTE GIA'." << endl;
            }
            cout << endl;

            menuBSTFloat(bst);
            break;
        }
        case 5: {
            float elem = 0.0f;
            while (cout << endl << "DIGITARE IL NUMERO DA RIMUOVERE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (bst.Exists(elem)) {
                bst.Remove(elem);

                cout << endl << setprecision(9) << elem << " E' STATO RIMOSSO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: ELEMENTO INESISTENTE." << endl;
            }

            menuBSTFloat(bst);
            break;
        }
        case 6: {
            float minimo = bst.Min();
            cout << endl << "IL MINIMO DELL'ALBERO E': " << setprecision(9) << minimo << endl;
            
            bst.RemoveMin();

            cout << setprecision(9) << minimo << " E' STATO ELIMINATO." << endl;

            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTFloat, nullptr);
            cout << endl;

            menuBSTFloat(bst);
            break;
        }
        case 7: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MINIMO:" << endl; 
            cout << "--> IL MINIMO DELL'ALBERO E': " << setprecision(9) << bst.Min();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MINIMO: " << endl;
            cout << "--> " << setprecision(9) << bst.MinNRemove() << " E' STATO RIMOSSO." << endl; 
            
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTFloat, nullptr);
            cout << endl;

            menuBSTFloat(bst);
            break;
        }
        case 8: {
            float massimo = bst.Max();
            cout << endl << "IL MASSIMO DELL'ALBERO E': " << setprecision(9) << massimo << endl;
            
            bst.RemoveMax();

            cout << setprecision(9) << massimo << " E' STATO ELIMINATO." << endl;

            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTFloat, nullptr);
            cout << endl;

            menuBSTFloat(bst);
            break;
        }
        case 9: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MASSIMO:" << endl; 
            cout << "--> IL MASSIMO DELL'ALBERO E': " << setprecision(9) << bst.Max();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MASSIMO: " << endl;
            cout << "--> " << setprecision(9) << bst.MaxNRemove() << " E' STATO RIMOSSO." << endl; 
            
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTFloat, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTFloat, nullptr);
            cout << endl;

            menuBSTFloat(bst);
            break;
        }
        case 10: {
            float value = 0.0f;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                float successor = bst.Successor(value);
                cout << endl << "IL SUCCESSORE DI " << setprecision(9) << value << " E': " << setprecision(9) << successor << endl;
                bst.RemoveSuccessor(value);
                cout << setprecision(9) << successor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTFloat(bst);
            break;
        }
        case 11: {
            float value = 0.0f;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI " << setprecision(9) << value << " :" << endl; 
                cout << "--> IL SUCCESSORE E': " << setprecision(9) << bst.Successor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL SUCCESSORE: " << endl;
                cout << "--> " << setprecision(9) << bst.SuccessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTFloat(bst);
            break;
        }
        case 12: {
            float value = 0.0f;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                float predecessor = bst.Predecessor(value);
                cout << endl << "IL PREDECESSORE DI " << setprecision(9) << value << " E': " << setprecision(9) << predecessor << endl;
                bst.RemovePredecessor(value);
                cout << setprecision(9) << predecessor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTFloat(bst);
            break;
        }
        case 13: {
            float value = 0.0f;   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON FLOAT, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI " << setprecision(9) << value << " :" << endl; 
                cout << "--> IL PREDECESSORE E': " << setprecision(9) << bst.Predecessor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL PREDECESSORE: " << endl;
                cout << "--> " << setprecision(9) << bst.PredecessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTFloat, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTFloat, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTFloat(bst);
            break;
        }
        case 14: {
            bst.Clear();
            cout << endl << "LA STRUTTURA ORA E' VUOTA! " << endl;
            menuBSTFloat(bst);
            break;
        }
        default: 
            cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
    }
}

void menuBSTString(BST<string>& bst) {
    ushort choice = 0;
    cout << endl << "[1] (MAP) PER VISUALIZZAZIONE ALBERO IN AMPIEZZA, PRE-ORDER, POST-ORDER, IN-ORDER." << endl;
    cout << "[2] PER CONTROLLO DI ESISTENZA DI UN VALORE." << endl;
    cout << "[3] (FOLD) PER APPLICAZIONE FUNZIONE CONCATENAZIONE PER LE STRINGHE DI DIMENSIONE MINORE O UGUALE A N." << endl;
    cout << "[4] PER INSERIRE UN ELEMENTO." << endl;
    cout << "[5] PER ELIMINARE UN ELEMENTO." << endl;
    cout << "[6] RIMOZIONE DEL MINIMO." << endl;
    cout << "[7] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MINIMO." << endl;
    cout << "[8] RIMOZIONE DEL MASSIMO." << endl;
    cout << "[9] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL MASSIMO." << endl;
    cout << "[10] RIMOZIONE DEL SUCCESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[11] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI UN DATO ELEMENTO." << endl; 
    cout << "[12] RIMOZIONE DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[13] RIMOZIONE CON LETTURA E LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI UN DATO ELEMENTO." << endl;
    cout << "[14] CLEAR DELLA STRUTTURA." << endl;
    cout << "SCELTA: ";
    cin >> choice;

    switch(choice) {
        case 1: {
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTString, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTString, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTString, nullptr);

            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTString, nullptr);

            cout << endl;
            menuBSTString(bst);
            break;
        }
        case 2: {
            string elem = "";
            while (cout << endl << "DIGITARE IL NUMERO DI CUI VERIFICARE LA PRESENZA: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(elem)) {
                cout << endl << "RISULTATO RICERCA: TRUE" << endl;
            } else {
                cout << endl << "RISULTATO RICERCA: FALSE" << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 3: {
            uint n = 0; 
            while (cout << endl << "DIGITARE IL VALORE SECONDO CUI APPLICARE LA FUNZIONE: " && !(cin >> n)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON INTERO, RIPETERE! ";
            }
            
            cout << endl;

            const uint lim = n;
            string start = "";

            cout << endl << "APPLICAZIONE FOLD IN AMPIEZZA: " << endl;
            bst.FoldBreadth(foldBSTString, &lim, &start);
    
            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN PRE-ORDER: " << endl;
            bst.FoldPreOrder(foldBSTString, &lim, &start);
    
            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN POST-ORDER: " << endl;
            bst.FoldPostOrder(foldBSTString, &lim, &start);

            start = 1;

            cout << endl << "APPLICAZIONE FOLD IN IN-ORDER: " << endl;
            bst.FoldInOrder(foldBSTString, &lim, &start);

            cout << endl;
            menuBSTString(bst);
            break;
        }
        case 4: {
            string elem = "";
            while (cout << endl << "DIGITARE LA STRINGA DA INSERIRE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (!bst.Exists(elem)) {
                bst.Insert(elem);

                cout << endl << elem << " E' STATO INSERITO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
            } else {
                cout << endl << "NON POSSO INSERIRE: L'ELEMENTO ESISTE GIA'." << endl;
            }
            cout << endl;

            menuBSTString(bst);
            break;
        }
        case 5: {
            string elem = "";
            while (cout << endl << "DIGITARE LA STRINGA DA RIMUOVERE: " && !(cin >> elem)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(elem)) {
                bst.Remove(elem);

                cout << endl << elem << " E' STATO RIMOSSO." << endl;

                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: ELEMENTO INESISTENTE." << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 6: {
            string minimo = bst.Min();
            cout << endl << "IL MINIMO DELL'ALBERO E': "<< minimo << endl;
            
            bst.RemoveMin();

            cout << minimo << " E' STATO ELIMINATO." << endl;

            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTString, nullptr);
            cout << endl;

            menuBSTString(bst);
            break;
        }
        case 7: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MINIMO:" << endl; 
            cout << "--> IL MINIMO DELL'ALBERO E': " << bst.Min();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MINIMO: " << endl;
            cout << "--> " << bst.MinNRemove() << " E' STATO RIMOSSO." << endl; 
            
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTString, nullptr);
            cout << endl;

            menuBSTString(bst);
            break;
        }
        case 8: {
            string massimo = bst.Max();
            cout << endl << "IL MASSIMO DELL'ALBERO E': " << massimo << endl;
            
            bst.RemoveMax();

            cout << massimo << " E' STATO ELIMINATO." << endl;

            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTString, nullptr);
            cout << endl;

            menuBSTString(bst);
            break;
        }
        case 9: {
            cout << endl << "LETTURA NON DISTRUTTIVA DEL MASSIMO:" << endl; 
            cout << "--> IL MASSIMO DELL'ALBERO E': " << bst.Max();
            cout << endl; 

            cout << endl << "RIMOZIONE CON LETTURA DEL MASSIMO: " << endl;
            cout << "--> " << bst.MaxNRemove() << " E' STATO RIMOSSO." << endl; 
            
            cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
            bst.MapBreadth(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
            bst.MapPreOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
            bst.MapPostOrder(visualizeBSTString, nullptr);
            cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
            bst.MapInOrder(visualizeBSTString, nullptr);
            cout << endl;

            menuBSTString(bst);
            break;
        }
        case 10: {
            string value = "";   
            while (cout << endl << "DIGITARE LA STRINGA DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                string successor = bst.Successor(value);
                cout << endl << "IL SUCCESSORE DI " << value << " E': "<< successor << endl;
                bst.RemoveSuccessor(value);
                cout << successor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 11: {
            string value = "";   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL SUCCESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL SUCCESSORE DI " << value << " :" << endl; 
                cout << "--> IL SUCCESSORE E': " << bst.Successor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL SUCCESSORE: " << endl;
                cout << "--> " << bst.SuccessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 12: {
            string value = "";   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                string predecessor = bst.Predecessor(value);
                cout << endl << "IL PREDECESSORE DI " << value << " E': " << predecessor << endl;
                bst.RemovePredecessor(value);
                cout << predecessor << " E' STATO ELIMINATO." << endl;
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 13: {
            string value = "";   
            while (cout << endl << "DIGITARE IL NUMERO DI CUI TROVARE IL PREDECESSORE: " && !(cin >> value)) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "ERRORE: INPUT NON STRINGA, RIPETERE! ";
            }

            if (bst.Exists(value)) {
                cout << endl << "LETTURA NON DISTRUTTIVA DEL PREDECESSORE DI " << value << " :" << endl; 
                cout << "--> IL PREDECESSORE E': " << bst.Predecessor(value);
                cout << endl; 

                cout << endl << "RIMOZIONE CON LETTURA DEL PREDECESSORE: " << endl;
                cout << "--> " << bst.PredecessorNRemove(value) << " E' STATO RIMOSSO." << endl; 
                
                cout << endl << "VISUALIZZAZIONE ALBERO IN AMPIEZZA: ";
                bst.MapBreadth(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN PRE-ORDER: ";
                bst.MapPreOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN POST-ORDER: ";
                bst.MapPostOrder(visualizeBSTString, nullptr);
                cout << endl << "VISUALIZZAZIONE ALBERO IN IN-ORDER: ";
                bst.MapInOrder(visualizeBSTString, nullptr);
                cout << endl;
            } else {
                cout << endl << "OPERAZIONE IMPOSSIBILE: IL NODO NON ESISTE." << endl;
            }

            menuBSTString(bst);
            break;
        }
        case 14: {
            bst.Clear();
            cout << endl << "LA STRUTTURA ORA E' VUOTA! " << endl;
            menuBSTString(bst);
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
            dimensione = getStructureSize();
            List<float>* lista = new List<float>();

            cout << endl;
            for (int i = 0; i < dimensione; i++){
                float value = generateRandomFloat();
                cout << setprecision(9) << "HO GENERATO IL VALORE: " << value << endl;
                lista->InsertAtBack(value);
            }

            bstfloat = BST<float>(*lista);
            delete lista;
            menuBSTFloat(bstfloat);
            break;
        }
        case 3: {
            dimensione = getStructureSize();
            List<string>* lista = new List<string>();

            cout << endl;
            for (int i = 0; i < dimensione; i++){
                string value = generateRandomString();
                cout << "HO GENERATO IL VALORE: " << value << endl;
                lista->InsertAtBack(value);
            }

            bststring = BST<string>(*lista);
            delete lista;
            menuBSTString(bststring);
            break;
        }
        defaut: 
            cout << "ERRORE: SCELTA NON DISPONIBILE!" << endl;
    }

}