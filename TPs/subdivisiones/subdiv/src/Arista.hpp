// La struct Arista guarda los dos indices de nodos de una arista
// Siempre pone primero el menor indice, para facilitar la búsqueda en lista ordenada;
//    es para usar con el Mapa de más abajo, para asociar un nodo nuevo a una arista vieja
struct Arista {
	int n[2];
	Arista(int n1, int n2) {
		n[0] = n1;
		n[1] = n2;
		if (n[0] > n[1])
		    std::swap(n[0], n[1]);
	}
	Arista(Elemento &e, int i) { // i-esima arista de un elemento
		n[0] = e[i];
		n[1] = e[i+1];
		if (n[0] > n[1])
		    std::swap(n[0], n[1]); // pierde el orden del elemento
	}
	const bool operator<(const Arista &a) const {
		return (n[0] < a.n[0] || (n[0] == a.n[0] && n[1] < a.n[1]));
	}
};
