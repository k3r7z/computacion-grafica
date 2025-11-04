#ifndef SUBDIVMESH_HPP
#define SUBDIVMESH_HPP

#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <memory>
#include <glm/glm.hpp>
#include "Nodo.hpp"
#include "Elemento.hpp"


// Malla guarda principalmente una lista de nodos y elementos
struct SubDivMesh {
	std::vector<Nodo> n;
	std::vector<Elemento> e;
	
	SubDivMesh() = default;
	SubDivMesh(const std::string &fname);
	void makeVecinos();
	void agregarElemento(int n0, int n1, int n2, int n3=-1);
	void reemplazarElemento(int ie, int n0, int n1, int n2, int n3=-1);
	
	void verificarIntegridad() const;
};

#endif

