#include <iostream>
#include <string>
#include "include/NFA.h"

void menu() {
	unsigned int opcion;
	bool NFAIntroducido = false;
	CyA::NFA nfa;

	do {
		std::cout << "Autómata Finito Determinista -- CyA\n" <<
						     "1. Leer NFA.\n" <<
								 "2. Mostrar NFA.\n" <<
								 "3. Identificar estados de muerte.\n" <<
								 "4. Identificar estados importantes.\n" <<
								 "5. Es DFA.\n" <<
								 "6. Analizar cadena.\n" <<
								 "0. Salir del programa.\n" <<
								 "\n" <<
								 "Introduce una opción: ";

		std::cin >> opcion;

		std::cout << '\n';

		switch (opcion) {
			case 0: {
				std::cout << "Fin del programa.\n";
				break;
			}

			case 1: {
				std::string rutaFichero;

				std::cout << "Introduce ruta al fichero: "; std::cin >> rutaFichero;
				nfa.leerFichero(rutaFichero);
				NFAIntroducido = true;
				break;
			}

			case 2: {
				if (NFAIntroducido) {
					std::cout << nfa << '\n';
				} else {
					std::cout << "Debes introducir un NFA primero.\n";
				}
				break;
			}

			case 3: {
				if (NFAIntroducido) {
					nfa.mostrarEstadosDeMuerte();
				} else {
					std::cout << "Debes introducir un NFA primero.\n";
				}
				break;
			}

			case 4: {
				if (NFAIntroducido) {
					nfa.mostrarEstadosImportantes();
				} else {
					std::cout << "Debes introducir un NFA primero.\n";
				}
				break;
			}

			case 5: {
				if (NFAIntroducido) {
					if (nfa.esDFA()) {
						std::cout << "El NFA introducido ES DFA.\n";
					} else {
						std::cout << "El NFA introducido NO ES DFA.\n";
					}
				} else {
					std::cout << "Debes introducir un NFA primero.\n";
				}
				break;
			}

			case 6: {
				if (NFAIntroducido) {
					std::string cadena;
					std::cout << "Introduce una cadena a analizar: "; std::cin >> cadena;
					nfa.analizarCadena(cadena);
				} else {
					std::cout << "Debes introducir un NFA primero.\n";
				}
				break;
			}

			default: {
				std::cout << "Opción incorrecta o aún no implementada.\n";
				break;
			}
		}
		std::cout << '\n';
	} while (opcion != 0);
}

int main(int argc, char* argv[]) {
	menu();
}
