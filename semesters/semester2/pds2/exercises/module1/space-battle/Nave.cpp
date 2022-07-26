#include "Nave.hpp"

Nave::Nave(Ponto2D posicao, double forca = 1) {
	this->posicao = posicao;
	this->forca = forca;
	this->energia = 100;
}

void Nave::mover(double dx, double dy) {
	this->posicao.x += dx;
	this->posicao.y += dy;
}

double Nave::calcular_distancia(Nave* nave) {
	return this->posicao.calcular_distancia(&nave->posicao);
}

Nave* Nave::determinar_nave_mais_proxima(Nave** naves, int n) {
	double min_dist = numeric_limits<double>::infinity();
	int index = 0;

	for(int i = 0; i < n; i++) {
		if(naves[i] != this) {
			double dist = this->posicao.calcular_distancia(&naves[i]->posicao);
			if(dist < min_dist) {
				min_dist = dist;
				index = i;
			}
		}
	}

	return naves[index];
}

void Nave::atacar(Nave** naves, int n) {
	Nave *ship = this->determinar_nave_mais_proxima(naves, n);

	double distance = this->calcular_distancia(ship);
	double damage = (100/distance) * this->forca;

	if(damage > 30)
		damage = 30;

	ship->energia -= damage;

	if(ship->energia < 50) {
		cout << "Energia baixa!" << endl;
	} 
}

void Nave::imprimir_status() {
	cout << this->posicao.x << " " << this->posicao.y << " " << this->energia << endl;
}