#ifndef ALOCACAO_H
#define ALOCACAO_H

#include <iostream>
#include <string>

struct Alocacao {
	std::string dia, horario, sala;

	Alocacao(std::string dia, std::string horario, std::string sala);
	void imprimir_dados();
};

#endif