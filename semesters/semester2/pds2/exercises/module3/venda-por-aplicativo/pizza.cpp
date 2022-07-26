#include "pizza.hpp"

std::string Pizza::descricao() const {
  std:: string desc = std::to_string(this->m_qtd)
                      + "X Pizza "
                      + this->sabor
                      + ", " + std::to_string(this->pedacos)
                      + " pedacos ";

  if(this->borda_recheada)
    desc += "e borda recheada.\n";
  else
    desc += "e sem borda recheada.\n";
   
  return desc;
}

Pizza::Pizza(const std::string& sabor,
             int pedacos,
             bool borda_recheada,
             int qtd,
             float valor_unitario) {
  this->sabor = sabor;
  this->pedacos = pedacos;
  this->borda_recheada = borda_recheada;
  this->m_qtd = qtd;
  this->m_valor_unitario = valor_unitario;
}