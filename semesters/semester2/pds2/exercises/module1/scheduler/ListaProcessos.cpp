#include "ListaProcessos.hpp"

void ListaProcessos::adicionar_processo(Processo* proc) {
	Processo *aux = this->head;

	if(aux == nullptr || proc->_prioridade > aux->_prioridade) {
		proc->next = aux;
		this->head = proc;
	} else {
		while(aux->next != nullptr && aux->next->_prioridade >= proc->_prioridade) {
			aux = aux->next;
		}

		proc->next = aux->next;
		aux->next = proc;
	}
}

Processo* ListaProcessos::remover_processo_maior_prioridade() {
	if(this->head != nullptr) {
		Processo *removed = this->head;

		this->head = this->head->next;

		return removed;
	}

	return nullptr;
}

Processo* ListaProcessos::remover_processo_menor_prioridade() {
	if(this->head != nullptr) {
		Processo *aux = this->head;

		while(aux->next != nullptr) {
			aux = aux->next;
		}

		Processo *removed = aux;

		if(aux == this->head) {
			return remover_processo_maior_prioridade();
		}

		Processo *tmp = this->head;

		while(tmp->next != aux) {
			tmp = tmp->next;
		}


		tmp->next = nullptr;

		return removed;
	}

	return nullptr;
}

Processo* ListaProcessos::remover_processo_por_id(int id) {
	Processo *aux = this->head;

	if(aux != nullptr) {
		if(aux->_id == id) {
			return remover_processo_maior_prioridade();
		}
	} else {
		return nullptr;
	}

	while(aux) {
		if(aux->_id == id) {
			Processo *removed = aux;

			Processo *tmp = this->head;

			while(tmp->next != aux) {
				tmp = tmp->next;
			}

			tmp->next = aux->next;

			return removed;
		} else {
			aux = aux->next;
		}
	}

	return nullptr;
}

void ListaProcessos::imprimir_lista() {
	Processo *aux = this->head;

	while(aux) {
		aux->imprimir_dados();

		aux = aux->next;
	}
}