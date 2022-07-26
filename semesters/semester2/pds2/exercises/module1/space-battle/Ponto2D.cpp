#include "Ponto2D.hpp"

Ponto2D::Ponto2D() {
	this->x = 0;
	this->y = 0;
}

Ponto2D::Ponto2D(double x, double y) {
	this->x = x;
	this->y = y;
}

double Ponto2D::calcular_distancia(Ponto2D* ponto) {
	double dx = this->x - ponto->x;
	double dy = this->y - ponto->y;

	return sqrt(pow(dx, 2) + pow(dy, 2));
}