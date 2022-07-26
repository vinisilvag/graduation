#include <string>

#include "Estoque.hpp"

void Estoque::add_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  std::map<std::string, int>::iterator it;
  bool inserted = false;

  for (it = stock.begin(); it != stock.end(); it++) {
    if(it->first == mercadoria) {
      it->second += qtd;
      inserted = true;
    }
  }

  if(!inserted)
    stock.insert(std::pair<std::string, int>(mercadoria, qtd));
}

void Estoque::sub_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  std::map<std::string, int>::iterator it;
  bool founded = false;

  for (it = stock.begin(); it != stock.end(); it++) {
    if(it->first == mercadoria) {
      if(it->second < int(qtd))
        std::cout << it->first << " insuficiente" << std::endl;
      else
        it->second -= qtd;

      founded = true;
    }
  }

  if(!founded)
    std::cout << it->first << " inexistente" << std::endl;
}

unsigned int Estoque::get_qtd(const std::string& mercadoria) const {
  int qtd = 0;

  for(auto const& it : stock) {
    if(it.first == mercadoria)
      qtd = it.second;
  }

  return qtd;
}

void Estoque::imprime_estoque() const {
  for(auto const& it : stock) {
    std::cout << it.first << ", " << it.second << std::endl;
  }
}

Estoque& Estoque::operator += (const Estoque& rhs) {
  std::map<std::string, int>::iterator found;

  for (auto const& it : rhs.stock) {
    found = stock.find(it.first);

    if(found != stock.end())
      found->second += it.second;
    else
      stock.insert(std::pair<std::string, int>(it.first, it.second));
  }

  return *this;
}

Estoque& Estoque::operator -= (const Estoque& rhs) {
  std::map<std::string, int>::iterator found;

  for (auto const& it : rhs.stock) {
    found = stock.find(it.first);

    if(found != stock.end())
      found->second -= it.second;
  }

  return *this;
}

bool operator < (Estoque& lhs, Estoque& rhs) {
  std::map<std::string, int>::iterator found;
  int counter = 0;
  bool right_contains = true;

  for(auto const& left : lhs.stock) {
    for(auto const& right : rhs.stock) {

      if(left.first == right.first) {
        if(left.second >= right.second){
          right_contains = false;
        }

        counter++;
        break;
      }

    }
  }

  if(counter == lhs.stock.size() and right_contains == true)
    return true;
  else
    return false;
}

bool operator > (Estoque& lhs, Estoque& rhs) {
  std::map<std::string, int>::iterator found;
  int counter = 0;
  bool left_contains = true;

  for(auto const& right : rhs.stock) {
    for(auto const& left : lhs.stock) {

      if(right.first == left.first) {
        if(right.second >= left.second){
          left_contains = false;
        }

        counter++;
        break;
      }

    }
  }

  if(counter == rhs.stock.size() and left_contains == true)
    return true;
  else
    return false;
}