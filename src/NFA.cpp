#include "../include/NFA.h"


namespace CyA {

bool NFA::contieneSimbolosAlfabeto(Estado& estado) const {

  for (auto& transicion : estado.getTransiciones()) {
    if (alfabeto_.count(transicion.first)) {
      return true;
    }
  }
  return false;

}

NFA::NFA(std::string& rutaFichero) {

  leerFichero(rutaFichero);

}

void NFA::leerFichero(std::string& rutaFichero) {
  std::ifstream fichero;

  try {
    fichero.open(rutaFichero);

    if (fichero.is_open()) {

      estados_.clear();
      alfabeto_.clear();

      unsigned int numEstados;

      fichero >> numEstados;
      fichero >> arranque_;

      if (fichero.peek() != '\n' && fichero.peek() != 13) {
        throw 2;
      }

      for (unsigned int i = 0; i < numEstados; ++i) {
        unsigned int id, aceptacion, numTransiciones;
        fichero >> id;
        fichero >> aceptacion;
        fichero >> numTransiciones;

        Estado estado(id, aceptacion, numTransiciones);

        for (unsigned int j = 0; j < numTransiciones; ++j) {
          std::string simbolo;
          unsigned int destino;

          fichero >> simbolo;
          fichero >> destino;

          if (simbolo[0] != '~') {
            alfabeto_.insert(simbolo);
          }
          estado.addTransicion(simbolo, destino);

        }
        estados_.insert(estado);
      }
    } else {
      throw 1;
    }

  } catch (int e) {
    std::cout << "Fallo en la síntesis del fichero: " << e << "\n";
    estados_.clear();
  }
  fichero.close();
}

void NFA::mostrarEstadosDeMuerte() {

  bool hayEstadosDeMuerte = false;

  for (auto& estado : estados_) {
    if (estado.esEstadoDeAceptacion()) {
      if (!hayEstadosDeMuerte) {
        std::cout << "[+] Hay estado/s de muerte: \n";
        hayEstadosDeMuerte = true;
      }

      std::cout << "[*] Estado de muerte en: q" << estado.getId() << '\n';

    }
  }

  if (!hayEstadosDeMuerte) {
    std::cout << "[-] No hay estados de muerte.\n";
  }

}

void NFA::mostrarEstadosImportantes() {

  std::vector<Estado> estadosImportantes, estadosNoImportantes;

  for (auto estado : estados_) {
    if (estado.esEstadoDeAceptacion() || contieneSimbolosAlfabeto(estado)) {
      estadosImportantes.push_back(estado);
    } else {
      estadosNoImportantes.push_back(estado);
    }
  }

  std::cout << "Estados importantes: \n";
  for (auto& elemento : estadosImportantes) {
    std::cout << 'q' << elemento.getId() << '\n';
  }

  std::cout << "Estados no importantes: \n";
  for (auto& elemento : estadosNoImportantes) {
    std::cout << 'q' << elemento.getId() << '\n';
  }

}

bool NFA::esDFA() const {

  for (auto estado : estados_) {
    if (alfabeto_.size() == estado.getTransiciones().size()) {

      std::set<std::string> simbolosProcesados;

      for (auto transicion : estado.getTransiciones()) {

        std::string simbolo = transicion.first;

        if (alfabeto_.count(simbolo) && !simbolosProcesados.count(simbolo)) {
          simbolosProcesados.insert(simbolo);
        } else {
          return false;
        }
      }
    } else {
      return false;
    }
  }

  return true;

}

void NFA::analizarCadena(std::string& cadena) {

  bool esCadenaAceptada = false;
  std::cout << "Cadena de entrada: " << cadena << '\n';

  analizarCamino(0, arranque_, cadena, esCadenaAceptada);

  std::cout << "\nDecisión final:\n";
  std::cout << ((esCadenaAceptada) ? "CADENA ACEPTADA\n" :
 "CADENA NO ACEPTADA\n");

}

void NFA::analizarCamino(unsigned int profundidad, unsigned int idEstado, std::string cadena, bool& aceptacion) {

  Estado estadoActual = (*std::next(estados_.begin(), idEstado));
  static unsigned int camino;

  if (profundidad == 0) {
    camino = 1;
  }

  if (cadena.size() > 0 && !estadoActual.getTransiciones().empty()) {
    for (auto transicion : estadoActual.getTransiciones()) {
      if (transicion.first[0] == cadena.at(0) || transicion.first[0] == '~') {
        std::string subcadena = cadena;

        if (transicion.first[0] != '~') {
          subcadena = cadena.substr(1, cadena.size() - 1);
        }

        analizarCamino(profundidad, transicion.second, subcadena, aceptacion);
        ++profundidad;
      }
    }
  } else {

    std::cout << "Camino " << camino << '\n';
    ++camino;

    std::cout << "Estado actual    Entrada    Siguiente estado\n";

    std::cout << 'q' << estadoActual.getId() <<
      "                " << 'x' <<
      "                ";

    std::cout << ((estadoActual.esEstadoDeAceptacion()) ? "CADENA ACEPTADA\n" :
   "CADENA NO ACEPTADA\n");

   if (estadoActual.esEstadoDeAceptacion()) {
     aceptacion = true;
   }

  }

}

void NFA::imprimir(std::ostream& salida) const {
  std::cout << estados_.size() << '\n' <<
               arranque_ << '\n';

  for (auto& estado : estados_) {
    std::cout << estado << '\n';
  }
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::NFA& NFA) {
  NFA.imprimir(salida);
  return salida;
}
