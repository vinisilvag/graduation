#include "Disciplina.hpp"

Disciplina::Disciplina(std::string codigo, std::string nome) {
	this->codigo = codigo;
	this->nome = nome;
}

void Disciplina::inserir_alocacao(std::string dia, std::string horario, std::string sala) {
	Alocacao nova_alocacao = Alocacao(dia, horario, sala);

	this->alocacao.insert(nova_alocacao);
}

void Disciplina::remover_alocacao(std::string horario) {
	std::set<Alocacao>::iterator it;
	bool removed = false;

	for(it = this->alocacao.begin(); it != this->alocacao.end() and removed != true; it++) {
		if(it->horario == horario) {
			this->alocacao.erase(it);
			removed = true;
		}
	}
}

void Disciplina::imprimir_alocacao() {
	for(Alocacao item : this->alocacao) {
		std::cout << this->codigo << " " << this->nome << " ";
		item.imprimir_dados();
	}
}