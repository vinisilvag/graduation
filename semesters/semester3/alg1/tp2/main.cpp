// 2021421869 - Vinicius Silva Gomes

#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'

#define f first
#define s second
#define pb push_back

// Valor máximo da capacidade que foi informado no enunciado
#define INF 1000000

// Algoritmo de Dijkstra modificado para se comportar ao problema do caminho com maior banda
int maximum_bandwith_dijkstra(int n, vector<vector<pair<int, int>>> &graph, pair<int, int> path);

int main() { _
    int n, m, q;

    // Recebe as entradas do arquivo de entrada
   
    cin >> n >> m >> q;

    // Declara o grafo e as queries que serão executadas pelo algoritmo
    vector<vector<pair<int, int>>> graph(n);
    vector<pair<int, int>> queries;

    for(int i = 0; i < m; i++) {
        int u, v, weight;

        cin >> u >> v >> weight;

        // Grafo declarado através de uma lista de adjacências
        // --u e --v para que o grafo seja 0-based
        graph[--u].pb(pair<int, int>(weight, --v));
    }

    for(int i = 0; i < q; i++) {
        int source, sink;

        cin >> source >> sink;

        // --source e --sink para que as queries sejam 0-based também
        queries.pb(pair<int, int>(--source, --sink));
    }

    // Percorre o vetor com as queries calculando o maior caminho e retorna o gargalo desse maior caminho
    for(unsigned i = 0; i < queries.size(); i++) {
        /*
            Chama a função que computa o gargalo passando o número de vértices, o grafo e o
            par {fonte, destino} para o qual o gargalo vai ser computado
        */
        int max_bandwith = maximum_bandwith_dijkstra(n, graph, queries[i]);

        cout << max_bandwith << endl;
    }

    return 0;
}

int maximum_bandwith_dijkstra(int n, vector<vector<pair<int, int>>> &graph, pair<int, int> path) {
    // Separa a fonte e o destino do par path passado como parâmetro
    int source = path.f, sink = path.s;

    // Declara a fila de prioridade (heap binário usado para selecionar os maiores vértices/arestas a serem processados)
    // Fila de prioridade implementada por um par { peso_da_aresta, indice_do_vertice }
    priority_queue<pair<int, int>> priority_queue;

    /*
        Declara o vetor que vai guardar as bandas máximas e inicializa ele com 0 para todos os vértices do grafo.
        Em seguida a banda para o vértice fonte é alterada para infinito. Como queremos computar caminhos que aumentem
        a banda máxima entre dois nós, vamos, na prática, realizar o "inverso" do que o algoritmo de Dijkstra propõem
    */
    vector<int> bandwith(n, 0);
    bandwith[source] = INF;

    // Insere a fonte na fila de prioridade
    priority_queue.push({ INF, source });

    // Enquanto existir algum caminho que possa aumentar a banda entre dois nós
    while(!priority_queue.empty()) {
        // Retira o nó da fila de prioridade
        int node = priority_queue.top().s;
        priority_queue.pop();

        // Analisa todos os seus vizinhos
        for(pair<int, int> neighbor : graph[node]) {
            // Pega a menor banda entre o nó atual sendo processado e o tamanho da aresta que conecta os dois nós
            int new_bandwith = min(bandwith[node], neighbor.f);

            /*
                Se a banda atual para o vizinho for menor que a nova banda calculada, significa que existe um outro caminho
                para esse vizinho que suporta um fluxo maior de recursos
            */
            if(bandwith[neighbor.s] < new_bandwith) {
                // Atualiza a nova banda para o vizinho e insere esse vizinho com sua nova banda na fila de prioridade
                bandwith[neighbor.s] = new_bandwith;
                priority_queue.push({ new_bandwith, neighbor.s });
            }
        }
    }

    // Retorna o valor do gargalo para o caminho até o destino
    return bandwith[sink];
}
