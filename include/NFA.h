#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include "Estado.h"

namespace CyA {
class NFA {
private:
  std::set<Estado> estados_;
  std::set<std::string> alfabeto_;
  unsigned int arranque_;

  bool contieneSimbolosAlfabeto(Estado& estado) const;
  void analizarCamino(unsigned int profundidad, unsigned int idEstado, std::string cadena, bool& aceptacion);

public:
  NFA() = default;
  NFA(std::string& rutaFichero);
  ~NFA() = default;

  void leerFichero(std::string& rutaFichero);
  void mostrarEstadosDeMuerte();
  void mostrarEstadosImportantes();
  bool esDFA() const;
  void analizarCadena(std::string& cadena);

  void imprimir(std::ostream& salida) const;

};
}

std::ostream& operator<<(std::ostream& salida, const CyA::NFA& nfa);

#endif // NFA_H
