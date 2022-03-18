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
		help[i] = new int[100];  
	
	min = 11;
	int ll = 0;
	int mm[5] = { 0,0,0,0,0 };
	int fix = lin;

	for(int i=0;i<5;i++)					//массив длин и точек
		for (int j = 0; j < i; j++) {
			if (mass[i][j] != 0)
			{
				help[0][ll] = mass[i][j];
				help[1][ll] = i;
				help[2][ll] = j;
				ll++;
			}
		}

	for(int i=0;i<lin;i++)					//Сортировка массива по возрастанию
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

	while (fix !=0) {										//Очищение основной матрици
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



void BR(int mass[5][5]) {


	int help[5];	// массив обратных элементов
	int min = 11;
//	int ll;
	bool flag = false;
//	cout << "\n\n";
	for (int i = 0; i < 4;i++) {							// нахождение вершин между которых находятся устраивающие нас пути
		min = 11;
		for (int j = 0; j < 5; j++) {
			if (mass[i][j] != 0) {
				if (i != help[j]) {
					if (i != 0) {
						if (help[i - 1] + 1 != j) {
//							flag = true;
							if (min > mass[i][j]) {
								min = mass[i][j];
								help[i] = j;
							}
						}
					}
					else
					{
						if (min > mass[i][j]) {
							min = mass[i][j];
							help[i] = j;
						}
					}
				}
			}
		}
//		cout <<i<<"  " <<help[i] << " / ";
	}


//	cout << "\n\n";

	for(int i=0;i<5;i++)						//Удаление всего лишнего
		for (int j = 0; j < 5; j++) {
			if (i < j) {
				if (mass[i][j] != 0) {
					if (j != help[i] && i!=help[j]) {
						mass[i][j] = 0;
						mass[j][i] = 0;
					}
				}
			}
		}
}


void touK(int mass[5][5]) {		//Ебучие два китайца

	int **help;
	help = new int* [3];
	for (int i = 0; i < 3; i++) {
		help[i] = new int[4];
		for (int j = 0; j < 4;j++) {
			help[i][j] = 11;
		}
	}
	int ll=0;
	int l=0;
	bool flag = true;
	int gryyb = 0;

	while (ll <= 4 && gryyb<1000) {
		gryyb++; // Эта штука нужна чтоб алгоритм не застревал в бесконечный цикл ели не способен чтото найти (не трогай ему и так плохо)
		for(int i=0;i<5;i++)
			for (int j = 0; j < 5; j++) {
				mass[i][j]--;
				flag = true;
				if (mass[i][j] == 0) {
					for (int k = 0; k < 4; k++)
						if (help[1][k] == i)
							flag = false;
					if (flag) {
						help[0][ll] = i;
						help[1][ll] = j;
						help[2][ll] = mass[i][j] + 1+l;
						ll++;
					}

				}
				
			}
		l++;
	}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			mass[i][j] = 0;

	mass[help[0][0]][help[1][0]] = help[2][0];	mass[help[1][0]][help[0][0]] = help[2][0];
	mass[help[0][1]][help[1][1]] = help[2][1];	mass[help[1][1]][help[0][1]] = help[2][1];
	mass[help[0][2]][help[1][2]] = help[2][2];	mass[help[1][2]][help[0][2]] = help[2][2];
	mass[help[0][3]][help[1][3]] = help[2][3];	mass[help[1][3]][help[0][3]] = help[2][3];

}

int main(){
	setlocale(LC_ALL, "rus");

	int mass[5][5];
	int lin;

	int raund = 0;
	cout << "Введите количество повторений";
	cin >> raund;
	double time1=0, time2=0;
	
	for (int i = 0; i < raund; i++) {

		filing(mass);
		liner(mass, &lin);
		time1 = clock();
		KP(mass, lin);
		time2 += clock() - time1;
	}
	cout << "\nКраскал " << time2 / raund;


	time1 = 0, time2 = 0;
	for (int i = 0; i < raund; i++) {

	filing(mass);
	time1 = clock();
	BR(mass);
	time2 += clock() - time1;
	}
	cout << "\nБорувка  " << time2 <<"\n";


	time1 = 0, time2 = 0;
	for (int i = 0; i < raund; i++) {
//		cout << i << " ";
	filing(mass);
	time1 = clock();
	touK(mass);
	time2 += clock() - time1;
	}
	cout << "\nКитайцы  " << time2 / raund;



}