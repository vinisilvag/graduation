#include <iostream>

using namespace std;

int selection_sort(int arr[], int size) {
	if(size > 1) {

	} else {
		return arr;
	}
}

int main() {
	int size = 4;
    int arr[size] = { 64, 25, 12, 22, 11 };

   	int ordered[size] = selection_sort();

    for(int i = 0; i < size; i++) {
    	cout << arr[i] << " " << endl;
    }
}
