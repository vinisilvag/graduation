#include "fila.h"

struct No {
  int chave;
  No* proximo;

  No(int chave) {
    this->chave = chave;
    proximo = nullptr;
  }
};

Fila::Fila() {
  primeiro_ = nullptr;
  ultimo_ = nullptr;
}

void Fila::Inserir(int k) {
  No* node = new No(k);

  if(tamanho() == 0) {
    primeiro_ = node;
    ultimo_ = node;
  } else {
    ultimo_->proximo = node;
    ultimo_ = node;
  }
}

void Fila::RemoverPrimeiro() {
  if(tamanho() == 0)
    throw ExcecaoFilaVazia {};

  No* aux = primeiro_;

  if(aux != nullptr) {
    primeiro_ = aux->proximo;

    delete aux;
  }
}

int Fila::primeiro() const {
  if(tamanho() == 0)
    throw ExcecaoFilaVazia {};

  return primeiro_->chave;
}

int Fila::ultimo() const {
  if(tamanho() == 0)
    throw ExcecaoFilaVazia {};

  return ultimo_->chave;
}

int Fila::tamanho() const {
  No* aux = primeiro_;
  int count = 0;

  while(aux != nullptr) {
    aux = aux->proximo;
    count++;
  }

  return count;
}