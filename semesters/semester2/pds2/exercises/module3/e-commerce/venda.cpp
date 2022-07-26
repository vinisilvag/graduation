#include "venda.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

void Venda::adicionaCelular(const Celular& celular) {
  this->m_celulares.push_back(celular);

  ordena();
}

void Venda::ordena() {
  this->m_celulares.sort();
}

void Venda::recarregaEstoque(int cod, int qtd) {
  std::list<Celular>::iterator it;

  for (it = this->m_celulares.begin(); it != this->m_celulares.end(); it++){
    if(it->cod == cod) {
      it->qtd += qtd;
    }
  }
}

void Venda::efetuaVenda(int cod, int qtd) {
  std::list<Celular>::iterator it;

  for (it = this->m_celulares.begin(); it != this->m_celulares.end(); it++){
    if(it->cod == cod) {
      if(qtd <= it->qtd)
        it->qtd -= qtd;
    }
  }
}

void Venda::aplicaDesconto(const std::string& fabricante, float desconto) {
  std::list<Celular>::iterator it;

  for (it = this->m_celulares.begin(); it != this->m_celulares.end(); it++){
    if(it->fabricante == fabricante) {
      float discount = it->valor * desconto/100;

      it->valor = it->valor - discount;
    }
  }
}

void Venda::removeModelo(int cod) {
  std::list<Celular>::iterator it;
  bool removed = false;

  for (it = this->m_celulares.begin(); it != this->m_celulares.end() and removed != true; it++){
    if(it->cod == cod) {
      this->m_celulares.erase(it);
      removed = true;
    }
  }
}

void Venda::imprimeEstoque() const {
  for(auto const& it : this->m_celulares) {
    if(it.qtd >= 1) {
      std::string cor = it.cor;

      cor[0] = std::toupper(cor[0]);

      std::cout << it.fabricante << " ";
      std::cout << it.modelo << ", ";
      std::cout << it.armazenamento << "GB, ";
      std::cout << it.memoria << "GB RAM, ";
      std::cout << std::fixed << std::setprecision(0) << it.peso * 1000 << " gramas, ";
      std::cout << cor << ", ";

      if (it.qtd == 1)
        std::cout << it.qtd << " restante, ";
      else
        std::cout << it.qtd << " restantes, ";

      std::cout << "R$ " << std::fixed << std::setprecision(2) << it.valor;
      std::cout << std::endl;
    }
  }
}