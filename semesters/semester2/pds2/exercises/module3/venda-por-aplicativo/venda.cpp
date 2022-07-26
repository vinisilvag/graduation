#include "venda.hpp"

#include <iomanip>

Venda::~Venda() {
  for(auto it : this->m_pedidos) {
    delete it;
  }
}

void Venda::adicionaPedido(Pedido* p) {
  this->m_pedidos.push_back(p);
}

void Venda::imprimeRelatorio() const {
  int index = 0;
  float total = 0;

  for(auto it : this->m_pedidos) {
    index++;

    std::cout << "Pedido " << index << std::endl;
    std::cout << it->resumo();
    total += it->calculaTotal(); 
  }

  std::cout << "Relatorio de Vendas" << std::endl;
  std::cout << "Total de vendas: R$ " << std::fixed << std::setprecision(2) << total << std::endl;
  std::cout << "Total de pedidos: " << this->m_pedidos.size() << std::endl;
}