﻿#include <iostream>
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

void KP(int mass[5][5],int lin){
	
//	int helper = new int[lin];
	int min=11;
	int** help;
	help = new int *[3];
	help[0] = new int[lin];
	help[1] = new int[lin];
	help[2] = new int[lin];
	int ll = 0;
	int mm[5] = { 0,0,0,0,0 };
	int fix = lin;

	for(int i=0;i<5;i++)
		for (int j = 0; j < i; j++) {
			if (mass[i][j] != 0)
			{
				help[0][ll] = mass[i][j];
				help[1][ll] = i;
				help[2][ll] = j;
				ll++;
			}
		}

	for(int i=0;i<lin;i++)
		for(int j=0;j<lin;j++)
			if (help[0][i] < help[0][j]) {
				ll = help[0][i];
				help[0][i] = help[0][j];
				help[0][j] = ll;

				ll = help[1][i];
				help[1][i] = help[1][j];
				help[1][j] = ll;


				ll = help[2][i];
				help[2][i] = help[2][j];
				help[2][j] = ll;
			}

	ll = 0;

	while (fix !=0) {
		if (mm[help[1][ll]] < 2 && mm[help[2][ll]] < 2) {
			mm[help[1][ll]]++;
			mm[help[2][ll]]++;
		}
		else {
			mass[help[1][ll]][help[2][ll]] = 0;
			mass[help[2][ll]][help[1][ll]] = 0;
		}
		ll++;
		fix--;
	}
	
}





int main(){
	setlocale(LC_ALL, "rus");

	int mass[5][5];
	int lin;

	filing(mass);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << mass[i][j] << " ";
		cout << endl;
	}



	liner(mass,&lin);
	KP(mass,lin);










	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << mass[i][j] << " ";
		cout << endl;
	}








}