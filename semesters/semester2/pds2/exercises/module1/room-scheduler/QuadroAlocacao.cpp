#include "QuadroAlocacao.hpp"

void QuadroAlocacao::inserir_alocacao(std::string codigo, std::string nome, std::string dia, std::string horario, std::string sala) {
	std::map<std::string, Disciplina>::iterator it;

	it = this->disciplinas.find(codigo);

	if(it != this->disciplinas.end()) {
		it->second.inserir_alocacao(dia, horario, sala);
	} else {
		Disciplina nova_disciplina = Disciplina(codigo, nome);
		nova_disciplina.inserir_alocacao(dia, horario, sala);

		this->disciplinas.insert(std::pair<std::string, Disciplina>(codigo, nova_disciplina));
	}	
}

void QuadroAlocacao::remover_alocacao_disciplina(std::string codigo, std::string horario) {
	std::map<std::string, Disciplina>::iterator it;

	for(it = this->disciplinas.begin(); it != this->disciplinas.end(); it++) {
		if(it->second.codigo == codigo) {
			it->second.remover_alocacao(horario);
		}
	}		
}

std::vector<Disciplina> QuadroAlocacao::recuperar_disciplinas_mais_ofertadas() {
	std::vector<Disciplina> mais_ofertadas;
	std::map<std::string, Disciplina>::iterator it;

	unsigned maior = 0;

	for(it = this->disciplinas.begin(); it != this->disciplinas.end(); it++) {
		if(it->second.alocacao.size() > maior) {
			maior = it->second.alocacao.size();
		}
	}

	for(it = this->disciplinas.begin(); it != this->disciplinas.end(); it++) {
		if(it->second.alocacao.size() == maior) {
			mais_ofertadas.push_back(it->second);
		}
	}

	return mais_ofertadas;
}

void QuadroAlocacao::imprimir_alocacao_completa() {
	std::map<std::string, Disciplina>::iterator it;

	for(it = this->disciplinas.begin(); it != this->disciplinas.end(); it++) {
		it->second.imprimir_alocacao();
	}
}