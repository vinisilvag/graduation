#include <iostream>
#include <string>

using namespace std;

int main() {
	string word;
	int a = 0, e = 0, i = 0, o = 0, u = 0;

	cin >> word;

	for(int count = 0; count < int(word.length()); count++) {
		if(word[count] == 'a')
			a++;

		if(word[count] == 'e')
			e++;

		if(word[count] == 'i')
			i++;

		if(word[count] == 'o')
			o++;

		if(word[count] == 'u')
			u++;
	}

	if(a != 0) cout << "a " << a << endl;
	if(e != 0) cout << "e " << e << endl;
	if(i != 0) cout << "i " << i << endl;
	if(o != 0) cout << "o " << o << endl;
	if(u != 0) cout << "u " << u << endl;

	return 0;
}