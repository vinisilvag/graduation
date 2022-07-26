// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_escalonador.hpp"

int main() {
	ListaProcessos lista;

	int id, prioridade;
	std::string nome;

	char data;
    while (cin >> data) {
        switch (data) {
        	case 'a':                 
                cin >> id >> nome >> prioridade;

                lista.adicionar_processo(new Processo(id, nome, prioridade));

                break;

            case 'm':                 
                lista.remover_processo_maior_prioridade();

                break;

            case 'n': 
                lista.remover_processo_menor_prioridade();
                
                break;

            case 'r':                  
                cin >> id; // ID do processo na lista

                lista.remover_processo_por_id(id);
                
                break;   

            case 'p':                  
                lista.imprimir_lista();
                
                break;     

            case 'b':                  
                avaliacao_basica();
                
                break;                                              
        }
    }

    return 0;
}