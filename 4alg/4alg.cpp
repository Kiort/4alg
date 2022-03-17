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

void KP(int mass[5][5],int lin){
	
//	int helper = new int[lin];
	int min=3;

	int **help;
	help = new int *[3];
	for(int i=0;i<min;i++)
		help[i] = new int[100];  //Сдесь случается хуета, тип что-то не инициализировано
	
	min = 11;
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

	
	int mirt = 0;

	while (fix !=0) {
		if (mirt == ll)
			break;

		if (mm[help[1][mirt]] < 2 && mm[help[2][mirt]] < 2) {
			mm[help[1][mirt]]++;
			mm[help[2][mirt]]++;
		}
		else {
			mass[help[1][mirt]][help[2][mirt]] = 0;
			mass[help[2][mirt]][help[1][mirt]] = 0;
		}
		mirt++;
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




	cout << endl;





	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << mass[i][j] << " ";
		cout << endl;
	}








}