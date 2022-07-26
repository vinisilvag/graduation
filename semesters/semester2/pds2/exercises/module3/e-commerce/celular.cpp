#include "celular.hpp"

int Celular::identificador = 0;

Celular::Celular(std::string modelo,
                 std::string fabricante,
                 int armazenamento,
                 int memoria,
                 double peso,
                 std::string cor,
                 int qtd,
                 float valor) {
  identificador++;

  this->modelo = modelo;
  this->fabricante = fabricante;
  this->armazenamento = armazenamento;
  this->memoria = memoria;
  this->peso = peso;
  this->cor = cor;
  this->qtd = qtd;
  this->valor = valor;
  this->cod = identificador;
}

bool Celular::operator<(const Celular& other) {
  if(this->fabricante < other.fabricante)
    return true;
  else
    if(this->fabricante == other.fabricante)
      if(this->modelo < other.modelo)
        return true;
  
  return false;
}