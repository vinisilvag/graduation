#include "pedido.hpp"


Pedido::~Pedido() {
  for(auto it : this->m_produtos) {
    delete it;
  }
}

void Pedido::setEndereco(const std::string& endereco) {
  this->m_endereco = endereco;
}

float Pedido::calculaTotal() const {
  float total = 0;

  for(auto it : this->m_produtos) {
    total += it->getQtd() * it->getValor();
  }

  return total;
}

void Pedido::adicionaProduto(Produto* p) {
  this->m_produtos.push_back(p);
}

std::string Pedido::resumo() const {
  std::string resume;

  for(auto it : this->m_produtos) {
    resume += it->descricao();
  }

  resume += "Endereco: " + this->m_endereco + "\n";

  return resume;
}