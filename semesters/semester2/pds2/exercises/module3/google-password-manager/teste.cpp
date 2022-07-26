#include <iostream>

class Animal {
	public:
		virtual void fala() {
			std::cout << "fala padrao" << std::endl;
		};
};

class Pato : public Animal {
	public:
		void forcaFala() {
			fala();
		}

	private:
		void fala() override {
			std::cout << "teste" << std::endl;
		}
};

int main() {
	Pato p;

	p.forcaFala();

	return 0;
}