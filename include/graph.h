
///////////////////////////////////////////////////////////////////////////////////////////
// Classe: Graph
//
// Objetivo: Criar Grafos
//
// Classes com interface: Vertex e Heap
//
// Autores: Charles, Zara e Bressane
//
// Data: 26/06/23
///////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "heap.h"

class Graph {
private:
    int numVertices;
    Vertex** adjList;

public:

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Método: Construtores
    ///////////////////////////////////////////////////////////////////////////////////////////
    Graph() { }

    Graph(int vertices) : numVertices(vertices) {
        adjList = new Vertex*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjList[i] = nullptr;
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Método: addEdge
    //
    // Parâmetros: src, dest e weight
    //
    // Retorno: NA
    //
    // Objetivo: Adicionar a um grafo vértices origem, destino e o seu peso
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 26/06/23
    // ///////////////////////////////////////////////////////////////////////////////////////
    void addEdge(int src, int dest, int weight) {

        Vertex* newVertex = new Vertex(dest);

        newVertex->next = adjList[src];

        newVertex->iWeight = weight;

        adjList[src] = newVertex;

    }


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Método: dijkstra(int source)
    //
    // Parâmetros: Nó origem que é utilizado no cálculo das distâncias
    //
    // Retorno: NA
    //
    // Objetivo: Calcular a menor distância com algoritmo de Dijkstra utilizando vetor
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 26/06/23
    // ///////////////////////////////////////////////////////////////////////////////////////
    void dijkstra(int source) {
        bool* visited   = new bool[numVertices];
        int*  distances = new int[numVertices];
        int   Step;
        int   tempVertex = -1;
        int   i;
	int   min_dist, v, w, custo;
	int   iVertexBefore=0;
        Vertex* vertex;

        // Inicializando distâncias
        for(i=0; i < numVertices; i++ ) {
            distances[i] = __INT_MAX__;   
        }

        // Colocando custo de origem com distância igual a zero    
        distances[source] = 0;

        // Inicializar conjunto de vértices resolvidos
        for (i=0; i < numVertices; i++)
            visited[i] = 0;

        Step=0;

        // A condição de parada é enquanto R não corresponder a todos os vértices.
        while (Step < numVertices ){
            min_dist = __INT_MAX__;
            v = -1;

            // Procurar a menor distância para o vértice que não está no R
            for(i=0; i<numVertices; i++)
            {
                if(visited[i]==0 && distances[i] < min_dist) {
                    v = i;
                    min_dist = distances[i];
                }
            }

            // Identificado colocá-lo em R
            visited[v] = 1; 
            Step++;

            // Percorrer toda a lista com vizinhos
	    vertex = adjList[v];
	    while(vertex) {

                w = vertex->iVertex;
                custo = vertex->iWeight;

                if( visited[w] == false && distances[w]>distances[v] + custo) {
                    distances[w] = distances[v] + custo;
                }

		vertex=vertex->next;
            }

        }

	// Impressao das menores distâncias
	std::cout << "\n";
	std::cout << "Dijkstra Vector" << "\n";
        for (int i = 0; i < numVertices; i++) 
           std::cout << "Vertice " << i << " - Peso " << distances[i] << "\n";

        std::cout << std::endl;
    }


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Método: dijkstraheap(int source)
    //
    // Parâmetros: Nó origem que é utilizado no cálculo das distâncias
    //
    // Retorno: NA
    //
    // Objetivo: Calcular a menor distância com algoritmo de Dijkstra utilizando Heap binário
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 26/06/23
    // ///////////////////////////////////////////////////////////////////////////////////////
    void dijkstraheap(int source) {
        int *distances = new int[numVertices];
        bool* visited   = new bool[numVertices];
        int i, v, w, custo, tam_H;
        Heap *H; 
	elem elem_aux;
        Vertex *vertex;
 
        for(i = 0; i < numVertices; i++) 
    	    distances[i] = __INT_MAX__;

        // Inicializar conjunto de vértices resolvidos
        for (i=0; i < numVertices; i++)
            visited[i] = 0;

        distances[source] = 0;

        tam_H = numVertices;

	H = new Heap(numVertices,source);

	// Loop será executado até visitar todos os vértices
        while (tam_H >0) { 

            // buscando vértice v que minimiza dist[v]
    	    tam_H = H->removeHeap(tam_H, &elem_aux);

	    // elem_aux.conteudo retorna o elemento removido do Heap
	    // Este v passa a ser um vertice "visitado".
    	    v = elem_aux.conteudo;

	    visited[v]=true;

    	    // percorrendo Lista com vizinhos de v
            vertex = adjList[v];

            while(vertex) {
                w = vertex->iVertex;
                custo = vertex->iWeight;

                // e atualizando as distâncias quando for o caso
                if (  distances[w] > (distances[v] + custo) )  {

                    distances[w] = (distances[v] + custo);

                    elem_aux.chave = distances[w];

                    elem_aux.conteudo = w;

      		    if(!visited[w])
                        H->modifyHeap(elem_aux);

                }
                vertex = vertex->next;

            }

        }

	// Impressao das menores distâncias
        std::cout << std::endl;
	std::cout << "Dijkstra Heap" << "\n";
        for (int i = 0; i < numVertices; i++) 
           std::cout << "Vertice " << i << " - Peso " << distances[i] << "\n";

        std::cout << std::endl;
    }


    ///////////////////////////////////////////////////////////////////////////////////////////
    // Método: printGraph
    //
    // Parâmetros: NA
    // 
    // Retorno: NA
    //
    // Objetivo: Imprimir grafo gerado em lista de adjacencias
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 26/06/23
    // ///////////////////////////////////////////////////////////////////////////////////////
    void printGraph() {
        for (int i = 0; i < numVertices; ++i) {
            Vertex* vertex = adjList[i];
            std::cout << "Adjacências do vértice " << i << ": ";

            while (vertex) {
                std::cout << "No " << vertex->iVertex << " - Peso " << vertex->iWeight << " ";
                vertex = vertex->next;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    ~Graph() {

        for (int i = 0; i < numVertices; ++i) {
              delete adjList[i];
        }

    }

};
