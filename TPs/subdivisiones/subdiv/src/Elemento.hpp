#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP


// El Elemento guarda los indice de los 3/4 nodos de un triangulo/cuadrilatero 
//  y los indices de los 3/4 elementos vecinos
// El orden es importante pues indica la orientacion
// Notar que no conoce las posiciones, solo indices en listas de una malla que tampoco conoce
struct Elemento {
	int nv=0; // cantidad de vertices 3 o 4, me dice que tipo de elemento es
	int n[4]; // los tres/cuatro nodos
	int v[4]; // los tres/cuatro elementos vecinos por arista (-1 indica arista de frontera)
	explicit Elemento(int n0=0, int n1=0, int n2=0, int n3=-1) {
		n[0]=n0;
		n[1]=n1;
		n[2]=n2;
		n[3]=n3;
		nv = n3 < 0 ? 3 : 4;
	}
	void SetNodos(int n0=0, int n1=0, int n2=0, int n3=-1) {
		n[0] = n0;
		n[1] = n1;
		n[2] = n2;
		n[3] = n3;
		nv = n3 < 0 ? 3 : 4;
	}
    
	int &operator[](int i) { 
		return n[ (i+nv) % nv ]; // %nv para poder ciclar (usar indices fuera de rango)
	}
    
	const int operator[](int i) const { 
		return n[(i+nv)%nv]; // %nv para poder ciclar (usar indices fuera de rango)
	}
    
	bool Tiene(int i) const { // pregunta si el Elemento tiene al nodo i
		return n[0] == i || n[1] == i || n[2] == i || (nv == 4 && n[3] == i);
	}
	int Indice(int i) const { // devuelve en que posicion el elemento tiene al nodo i (o -1, si no)
		int j = nv-1;
		while (j >= 0 && n[j] != i) j--;
		return j;
	}
	
	// los siguiente métodos son para poder recorrer los nodos del elemento con el range-based for(int in : e)...
	int *begin() { return n; }
	int *end() { return n+nv; }
	const int *begin() const { return n; }
	const int *end() const { return n+nv; }
};


#endif
