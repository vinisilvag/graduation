// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_alocacao.hpp"

#include "QuadroAlocacao.hpp"

using namespace std;

int main() {
    QuadroAlocacao quadro_alocacao;

    string codigo, nome, dia, horario, sala;
    vector<Disciplina> mais_ofertadas;

	char data;
    while (cin >> data) {
        switch (data) {
        	case 'a':                 
                cin >> codigo >> nome >> dia >> horario >> sala;

                quadro_alocacao.inserir_alocacao(codigo, nome, dia, horario, sala);

                break;

            case 'm':                 
                mais_ofertadas = quadro_alocacao.recuperar_disciplinas_mais_ofertadas();

                for (Disciplina &disciplina : mais_ofertadas)
                    disciplina.imprimir_alocacao();
                    

                break;

            case 'r':                  
                cin >> codigo >> horario;

                quadro_alocacao.remover_alocacao_disciplina(codigo, horario);
                
                break;   

            case 'p':                  
                quadro_alocacao.imprimir_alocacao_completa();
                
                break;     

            case 'b':                  
                avaliacao_basica();
                
                break;                                              
        }
    }

    return 0;
}