#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "Alocacao.hpp"

#include <set>

struct compara_alocacao {
	bool operator() (const Alocacao& al1, const Alocacao& al2) {
		return al1.horario < al2.horario;
	}
};	

struct Disciplina {
	std::string codigo, nome;
	std::set<Alocacao, compara_alocacao> alocacao;

	Disciplina(std::string codigo, std::string nome);
	void inserir_alocacao(std::string dia, std::string horario, std::string sala);
	void remover_alocacao(std::string horario);
	void imprimir_alocacao();
};

#endif