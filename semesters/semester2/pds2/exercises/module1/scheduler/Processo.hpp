#ifndef PROCESSO_H
#define PROCESSO_H

#include <iostream>
#include <string>

struct Processo {
	int _id, _prioridade;
	std::string _nome;
	Processo *next;

	Processo(int id, std::string nome, int prioridade);
	void imprimir_dados();
};

#endif