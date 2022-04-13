#include <iostream>
using namespace std;


void filing(int **mass, int koll) {
	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			mass[i][j] = 0;
	int *lidr;
		lidr= new int[koll];

		for (int i = 0; i < koll; i++)
			lidr[i] = 0;

	for (int i = 0; i < koll;i++) {
		for (int j = 0; j < i; j++) {
			if (i != j) {
				if (lidr[i] < 4 && lidr[j] < 4) {
					lidr[i]++;
					lidr[j]++;
					mass[i][j] = rand() % 10;
					mass[j][i] = mass[i][j];
				}
			}

		}
		mass[i][i] = 0;
	}
	delete [] lidr;
} 
//Сделано под денамический массив


void liner(int **mass, int *lin,int koll) {
	lin = 0;
	for (int i = 0; i < koll; i++) {
		for (int j = 0; j < i; j++)
			if (mass[i][j] != 0)
				lin++;
	}
}
//Переделаноо под денамический массив


void KP(int **mass,int lin,int koll){
	
	int min=3;

	int **help;
	help = new int *[3];
	for(int i=0;i<min;i++)
		help[i] = new int[110];  
	
	min = 11;
	int ll = 0;
	int *mm =new int(lin);
	for (int i = 0; i < lin; i++)
		mm[i] = 0;
	int fix = lin;

	for(int i=0;i<koll;i++)					//массив длин и точек
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
	
	delete [] help;
	
	
}
// Вроде сделано под денамические массивы



void BR(int **mass, int koll) {


	int *help;
	help = new int[koll];	// массив обратных элементов
	for (int i = 0; i < koll; i++)
		help[i] = -1;

	int min = 11;
//	int ll;
	bool flag = false;
//	cout << "\n\n";
	for (int i = 0; i < koll;i++) {							// нахождение вершин между которых находятся устраивающие нас пути
		min = 11;
		for (int j = 0; j < koll; j++) {
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

	for(int i=0;i<koll;i++)						//Удаление всего лишнего
		for (int j = 0; j < koll; j++) {
			if (i < j) {
				if (mass[i][j] != 0) {
					if (j != help[i] && i!=help[j]) {
						mass[i][j] = 0;
						mass[j][i] = 0;
					}
				}
			}
		}
	delete [] help;
}
//Вроде сделан под денамический массив


void touK(int **mass,int lin, int koll) {		//Ебучие два китайца

	int **help;
	help = new int* [3];
	for (int i = 0; i < 3; i++) {
		help[i] = new int[lin];
		for (int j = 0; j < lin;j++) {
			help[i][j] = 11;
		}
	}
	int ll=0;
	int l=0;
	bool flag = true;
	int gryyb = 0;

	while (ll <= lin && gryyb<1000) {
		gryyb++; // Эта штука нужна чтоб алгоритм не застревал в бесконечный цикл ели не способен чтото найти (не трогай ему и так плохо)
		for(int i=0;i<koll;i++)
			for (int j = 0; j < koll; j++) {
				mass[i][j]--;
				flag = true;
				if (mass[i][j] == 0) {
					for (int k = 0; k < lin; k++)
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

	for (int i = 0; i < koll; i++)
		for (int j = 0; j < koll; j++)
			mass[i][j] = 0;

	for (int i = 0; i < lin; i++) {
		mass[help[0][i]][help[1][i]] = help[2][i];	
		mass[help[1][i]][help[0][i]] = help[2][i];
	}

	delete [] help;

}
//Эти китайцы меня доебут окончательно когданибудь (вроде сделано)

int main(){ 
	setlocale(LC_ALL, "rus");

	int raund = 0;
	cout << "Введите количество повторений";
	cin >> raund;
	for (int k= 10; k <= 100; k += 10) {

		cout << "\n\n\nМатрица   "<<k<<" х " <<k<<"\n";
		int** mass;
		mass = new int*[k];
		for (int j = 0; j < k; j++) {
			mass[j] = new int[k];
			for (int l = 0; l < k; l++)
				mass[j][l] = 0;
		}
		int lin;

		
		double time1 = 0, time2 = 0;

		for (int i = 0; i < raund; i++) {

			filing(mass, k);
			liner(mass, &lin,k);
			time1 = clock();
			KP(mass, lin,k);
			time2 += clock() - time1;
		}
		cout << "\nКраскал " << time2 / raund;


		time1 = 0, time2 = 0;
		for (int i = 0; i < raund; i++) {

			filing(mass, k);
			liner(mass, &lin, k);
			time1 = clock();
			BR(mass,k);
			time2 += clock() - time1;
		}
		cout << "\nБорувка  " << time2 << "\n";


		time1 = 0, time2 = 0;
		for (int i = 0; i < raund; i++) {
			//		cout << i << " ";
			filing(mass, k);
			liner(mass, &lin, k);
			time1 = clock();
			touK(mass,lin,k);
			time2 += clock() - time1;
		}
		cout << "\nКитайцы  " << time2 / raund;

		for (int i = 0; i < k; i++)
			delete [] mass[i];
		delete [] mass;
	}

}