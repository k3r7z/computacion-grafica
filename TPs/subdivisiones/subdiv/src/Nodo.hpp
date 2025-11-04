#ifndef NODO_HPP
#define NODO_HPP

#include <vector>
#include <glm/glm.hpp>

// Nodo o vértice: punto mas datos para usar en una malla
 struct Nodo {
	glm::vec3 p;
	bool es_frontera = false;
	std::vector<int> e; // en que elementos esta este Punto
	explicit Nodo(const glm::vec3 &pos) : p(pos) { }
	Nodo &operator=(glm::vec3 &p) { this->p = p; return *this; }
};

#endif
