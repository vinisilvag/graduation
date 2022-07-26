#include <iostream>

using namespace std;

int main() {
	// 1) Declare uma variável do tipo inteiro e atribua o valor '10'
	int a = 10;

    // 2) Declare um ponteiro para inteiros e inicialize com valor nulo
    int *ptr = nullptr;
    
    // 3) Declare um vetor de inteiros e inicialize com valores de 9 a 0 (nessa ordem)
   	int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // 4) Imprima o ENDEREÇO da variável declarada em (1)
    cout << &a << endl;

    // 5) Imprima o VALOR da variável declarada em (1)
    cout << a << endl;

    // 6) Imprima o ENDEREÇO da variável declarada em (2)
    cout << &ptr << endl;
    
    // 7) Imprima o VALOR da variável declarada em (2)
    cout << ptr << endl;

    // 8) Imprima o ENDEREÇO da variável declarada em (3)
    cout << arr << endl;

    // 9) Imprima o ENDEREÇO da primeira posição da variável declarada em (3)
    cout << &arr[0] << endl;

    // 10) Imprima o VALOR da primeira posição da variável declarada em (3)
    cout << arr[0] << endl;

    // 11) Atribua o ENDEREÇO da variável declarada em (1) à variável declarada em (2)
    ptr = &a;

    // 12) Imprima o VALOR da variável declarada em (2)
    cout << ptr << endl;

    // 13) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *ptr << endl;

    // 14) Imprima o resultado da comparação do ENDEREÇO de (1) e do VALOR de (2)
    cout << (&a == ptr) << endl;

    // 15) Coloque o VALOR '5' no ENDEREÇO apontado por (2)
    *ptr = 5;

    // 16) Imprima o VALOR da variável declarada em (1)
    cout << a << endl;

    // 17) Atribua o ENDEREÇO da variável (3) à variável declarada em (2)
    ptr = arr;

    // 18) Imprima o VALOR da variável declarada em (2)
    cout << ptr << endl;

    // 19) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *ptr << endl;

    // 20) Atribua o ENDEREÇO da primeira posição de (3) à variável declarada em (2)
    ptr = &arr[0];

    // 21) Imprima o VALOR da variável declarada em (2)
    cout << ptr << endl;

    // 22) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *ptr << endl;

    // 23) Multiplique todos os valores do vetor declarado em (3) por '10', porém manipulando apenas a variável (2)
    for(int i = 0; i < 10; i++) {
        *(ptr + i) *= 10;
    }

    // 24) Imprima os elementos de (3) a partir variável do vetor utilizando a notação [] (colchetes)
    for(int i = 0; i < 10; i++) {
        if(i == 9)
            cout << arr[i] << endl;
        else
            cout << arr[i] << " ";
    }

    // 25) Imprima os elementos de (3) a partir variável do vetor utilizando a notação ponteiro/deslocamento
    for(int i = 0; i < 10; i++) {
        if(i == 9)
            cout << *(arr + i) << endl;
        else
            cout << *(arr + i) << " ";
    }

    // 26) Imprima os elementos de (3) utilizando a variável (2) e a notação ponteiro/deslocamento
    for(int i = 0; i < 10; i++) {
        if(i == 9)
            cout << *(ptr + i) << endl;
        else
            cout << *(ptr + i) << " ";
    }

    // 27) Atribua o ENDEREÇO da quinta posição de (3) à variável declarada em (2)
    ptr = &arr[4];
    
    // 28) Imprima o VALOR da variável declarada em (2)
    cout << ptr << endl;

    // 29) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *ptr << endl;

    // 30) Imprima o VALOR guardado no ENDEREÇO do ponteiro (2) decrementado de 4
    cout << *(ptr - 4) << endl;

    // 31) Declare um ponteiro para ponteiro e o inicialize com o ENDEREÇO da variável (2)
    int **new_ptr = &ptr;

    // 32) Imprima o VALOR da variável declarada em (31)
    cout << new_ptr << endl;

    // 33) Imprima o ENDEREÇO da variável declarada em (31)
    cout << &new_ptr << endl;

    // 34) Imprima o VALOR guardado no ENDEREÇO apontado por (31)
    cout << *new_ptr << endl;

    // 35) Imprima o VALOR guardado no ENDEREÇO do ponteiro apontado por (31)
    cout << **new_ptr << endl;

	return 0;
}