#include "hamburguer.hpp"

std::string Hamburguer::descricao() const {
  std:: string desc = std::to_string(this->m_qtd)
                      + "X Hamburguer "
                      + this->tipo;

  if(this->artesanal)
    desc += " artesanal.\n";
  else
    desc += " simples.\n";
   
  return desc;
}

Hamburguer::Hamburguer(const std::string& tipo,
                       bool artesanal,
                       int qtd,
                       float valor_unitario) {
  this->tipo = tipo;
  this->artesanal = artesanal;
  this->m_qtd = qtd;
  this->m_valor_unitario = valor_unitario;
}