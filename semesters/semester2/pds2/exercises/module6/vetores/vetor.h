#pragma once

#include <cassert>
#include <vector>
#include <set>

// Define um vetor de qualquer Tipo cujos índices variam em
// qualquer intervalo, inclusive negativos.
template <class Tipo> 
class Vetor {
  public:
    // Cria um vetor cujos índices variam de 'inicio' até 'fim'.
    // PRECONDIÇÃO: fim >= inicio.
    Vetor(int inicio, int fim);

    // Altera o valor do índice i.
    // PRECONDIÇÃO: i está dentro do intervalo de índices do vetor.
    void atribuir(int i, Tipo valor);

    // Retorna o valor do índice i.
    // PRECONDIÇÕES: 
    // (1) i está dentro do intervalo de índices do vetor.
    // (2) i foi inicializando anteriormente.
    Tipo valor(int i) const; 
  
  private:
    int inicio_;  // Primeiro índice válido do vetor.
    int fim_;  // Último índice válido do vetor.
    std::vector<Tipo> elementos_;  // Elementos do vetor.
    std::set<int> indices_; // Indices inicializados
};

// DEFINIÇÃO DAS CLASSES DE EXCEÇÃO.

// Lançada quando o intervalo [inicio, fim] não contém nenhum índice.
struct ExcecaoIntervaloVazio {
  int inicio;  // Índice de início do arranjo que lançou a excecao.
  int fim;  // Índice de fim do arranjo que lançou a excecao.
};

//Lançada quando 'indice' não pertence a [inicio, fim].
struct ExcecaoIndiceInvalido {
  int inicio;  // Índice de início do arranjo que lançou a excecao.
  int fim;  // Índice de fim do arranjo que lançou a excecao.
  int indice;  // Índice inválido. 
};

// Lançada quando o valor de 'indice' é solicitado e o mesmo não foi previamente
// inicializado.
struct ExcecaoIndiceNaoInicializado {
  int indice;  // Índice do arranjo que não foi inicializado. 
};


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE.

template <class Tipo> 
Vetor<Tipo>::Vetor(int inicio, int fim) {
  if(inicio >= fim)
    throw ExcecaoIntervaloVazio {inicio, fim};

  inicio_ = inicio; 
  fim_ = fim;
  elementos_.resize(fim - inicio + 1);
}

template <class Tipo> 
void Vetor<Tipo>::atribuir(int i, Tipo valor) {
  if(i < inicio_ || i > fim_)
    throw ExcecaoIndiceInvalido {inicio_, fim_, i};

  indices_.insert(i);

  int j = i - inicio_;
  elementos_[j] = valor;
}

template <class Tipo> 
Tipo Vetor<Tipo>::valor(int i) const {
  if(i < inicio_ || i > fim_)
    throw ExcecaoIndiceInvalido {inicio_, fim_, i};

  if(indices_.find(i) == indices_.end())
    throw ExcecaoIndiceNaoInicializado {i};

  int j = i - inicio_;
  return elementos_[j];
}