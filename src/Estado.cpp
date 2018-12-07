#include "../include/Estado.h"

namespace CyA {

void Estado::addTransicion(std::string& simbolo, unsigned int destino) {
  transiciones_.insert(Transicion(simbolo, destino));
}

std::set<Transicion>& Estado::getTransiciones() {
  return transiciones_;
}

bool Estado::esEstadoDeAceptacion() const {
  return aceptacion_;
}

unsigned int Estado::getId() const {
  return id_;
}

std::vector<unsigned int> Estado::nextTransiciones(std::string c) const {

  std::vector<unsigned int> helper;

  for (auto& transicion : transiciones_) {
    if (transicion.first == c) {
      helper.push_back(transicion.second);
    }
  }
  return helper;
}

bool Estado::operator<(const Estado& estado) const {
  return id_ < estado.id_;
}

void Estado::imprimir(std::ostream& salida) const {
  std::cout << id_ << ' ' << aceptacion_ << ' ' << transiciones_.size() << ' ';
  for (auto& transicion : transiciones_) {
    std::cout << transicion.first << ' ' << transicion.second << ' ';
  }
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::Estado& estado) {
  estado.imprimir(salida);
  return salida;
}
