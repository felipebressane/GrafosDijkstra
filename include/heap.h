///////////////////////////////////////////////////////////////////////////////////////////
// Classe: Heap
//
// Objetivo: Criar Heap binários para cálculo de distância minima de Grafos
//
// Classes com interface: Graph
//
// Autores: Charles, Zara e Bressane
//
// Data: 03/07/23
///////////////////////////////////////////////////////////////////////////////////////////
struct elem {
   int chave;     // distância
   int conteudo;  // vértice  
};


class Heap
{
public:
	
        ///////////////////////////////////////////////////////////////////////////////////
        // Método: Construtor
        ///////////////////////////////////////////////////////////////////////////////////
	Heap( int numVertices, int source ) {

	    Elements = (elem *)malloc(numVertices*sizeof(elem)); 

	    pos_H    = (int *)malloc(numVertices*sizeof(elem));

	    for (int i = 0; i< numVertices; i++) {
      	       Elements[i].chave = __INT_MAX__;      // chave é a distância do vértice 
    	       Elements[i].conteudo = i;             // conteúdo é o rótulo do vértice
    	       pos_H[i] = i;                         // vertice i está na posição i do heap h 
            }

            swap(Elements[0], Elements[source]);     // coloca origem no início do heap
            swap(pos_H[0], pos_H[source]);           // atualiza a posição
						     
	}


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: upHeap
        //
        // Parâmetros: pos_elem_v - Elemento que deverá subir no Heap
	//
	// Retôrno: NA
        //
        // Objetivo: Subir um elemento no Heap
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        void upHeap( int pos_elem_v ) {
	    int f = pos_elem_v;
	    int conteudoPai=0;
	    int conteudoFilho=0;

	    while( f>0 && Elements[parent(f)].chave > Elements[f].chave ) {

		 conteudoPai=Elements[parent(f)].conteudo;
	         conteudoFilho=Elements[f].conteudo;	 

                 swap(Elements[f],Elements[parent(f)]);

                 swap(pos_H[conteudoFilho],pos_H[conteudoPai]);

//               swap(pos_H[Elements[f].conteudo],pos_H[Elements[parent(f)].conteudo]);

                 f = parent(f);
	    }

        }


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: pushHeap
        //
        // Parâmetros: m - Tamanho do Heap
	//             x - Elemento a ser incluido do Heap 
	//
	// Retôrno: m - Tamanho do Heap atualizado
        //
        // Objetivo: Incluir elemento no Heap
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        int pushHeap( int m, elem x ) {
	        Elements[m] = x;

                pos_H[x.conteudo] = m;

                upHeap(m);

                return(m+1);
        }


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: downHeap
        //
        // Parâmetros: m - Tamanho do Heap
	//             pos_elem_v - Posição do elemento que descerá no Heap
	//
	// Retôrno: NA
        //
        // Objetivo: Descer um elemento no Heap
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        void downHeap(int m, int pos_elem_v ) {
	        int p = pos_elem_v, f;
		int conteudoPai=0;
		int conteudoFilho=0;
 
  	        while ( (left(p) < m && Elements[left(p)].chave < Elements[p].chave ) || ( right(p) < m && Elements[right(p)].chave < Elements[p].chave) ) {

		    f = left(p);

		    if(right(p) < m && Elements[right(p)].chave < Elements[p].chave) 
                        f = right(p);

                    conteudoPai=Elements[p].conteudo;
		    conteudoFilho=Elements[f].conteudo;

                    swap(Elements[p], Elements[f]);

                    swap(pos_H[conteudoPai], pos_H[conteudoFilho]);

//                  swap(pos_H[Elements[p].conteudo], pos_H[Elements[f].conteudo]);

                    p = f;
		
	        }
        }


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: removeHeap
        //
        // Parâmetros: m - Tamanho do Heap
	//             px - É utilizado para retornar neste ponteiro o elemento que está
	//                  sendo removido. No caso o que está na posição mínima.
	//
	// Retôrno: m - Tamanho do Heap - 1
        //
        // Objetivo: Remover do Heap o primeiro elemento
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        int removeHeap(int m, elem *px) {
 	        *px = Elements[0];
		int conteudoMin=0;
		int conteudoFinal=0;

		conteudoMin=Elements[0].conteudo;
		conteudoFinal=Elements[m - 1].conteudo;

	        swap(Elements[0], Elements[m - 1]);

  	        swap(pos_H[conteudoMin], pos_H[conteudoFinal]);

//	        swap(pos_H[Elements[0].conteudo], pos_H[Elements[(m - 1)].conteudo]);

	        downHeap(m-1, 0);

                return(m-1);

        }


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: modifyHeap
        //
        // Parâmetros: x - Elemento a ser incluido no Heap
	//
	// Retôrno: NA
        //
        // Objetivo: Modificar o Heap em função da entrada de um novo elemento
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        void modifyHeap(elem x) {
 	        int pos_x_v = pos_H[x.conteudo];   // pega a posição de x em v

	        Elements[pos_x_v].chave = x.chave; // atualiza a chave de x em v

	        upHeap(pos_x_v);   
        }


  	~Heap() {
      	   delete Elements;
	   delete pos_H;
  	}



private:
	struct elem *Elements;
	int *pos_H;
  

        ///////////////////////////////////////////////////////////////////////////////////
        // Método: parent
        //
        // Parâmetros: i - Posição de um elemento
	//
	// Retôrno: Posição do pai
        //
        // Objetivo: Retornar a posição do pai
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        int parent(int i) {
            return (i - 1) / 2;
        }
 

        ///////////////////////////////////////////////////////////////////////////////////
        // Método: left
        //
        // Parâmetros: i - Posição de um elemento
	//
	// Retôrno: Posição da esquerda do pai
        //
        // Objetivo: Retornar a posição esquerda do pai
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        int left(int i) {
            return (2*i + 1);
        }
 
        
        ///////////////////////////////////////////////////////////////////////////////////
        // Método: right
        //
        // Parâmetros: i - Posição de um elemento
	//
	// Retôrno: Posição da direita do pai
        //
        // Objetivo: Retornar a posição direita do pai
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        int right(int i) {
            return (2*i + 2);
        }  


        ///////////////////////////////////////////////////////////////////////////////////
        // Método: swap
        //
        // Parâmetros: origin - Elemento origem
	//             target - Elemento destino
	//
	// Retôrno: NA
        //
        // Objetivo: Troca de posição de elementos
        //
        // Autores: Charles, Zara e Bressane
        //
        // Data: 03/07/23
        ///////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void swap(T& origin, T& target) {
           T temp = origin;
           origin = target;
           target = temp;
        }  
	

};
