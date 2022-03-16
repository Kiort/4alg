#include <iostream>
using namespace std;


void filing(int mass[5][5]) {
	for (int i = 0; i < 5;i++) {
		for (int j = 0; j < i; j++) {
			if (i != j) {
				mass[i][j] = rand() % 10;
				mass[j][i] = mass[i][j];
			}

		}
		mass[i][i] = 0;
	}
}


void liner(int mass[5][5], int *lin) {
	lin = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i; j++)
			if (mass[i][j] != 0)
				lin++;
	}
}

void KP(int mass[5][5]){
	
//	int helper = new int[lin];
	int min;

	for (int i = 0; i < 5; i++) {
		min = 6000000;
		for (int j = 0; j < i; j++) {
			if (mass[i][j] < min && mass[i][j] != 0) {
				min = mass[i][j];
			}
			else {
				mass[i][j] = 0;
				mass[j][i] = 0;
			}
		}
	}
}


int main(){
	setlocale(LC_ALL, "rus");

	int mass[5][5];
	int lin;

	filing(mass);

	KP(mass);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << mass[i][j] << " ";
		cout << endl;
	}








}