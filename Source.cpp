#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <string>

int const ROWS = 3;
int	const COLUMNS = 4;

int* createArray();
int** createDynamicArray(int N);
void calculatePositiveColumns(int* matrix, int rows, int columns);
void fillMatrix(int** matrix, int N);
int isValid();
int readFile();
void writeToFile(int** matrix, int N);

int main() {
	setlocale(LC_ALL, "Rus");
	//
	int* ptr = createArray();
	calculatePositiveColumns(ptr, ROWS, COLUMNS);
	//
	int N = readFile();
	int** ptr2 = createDynamicArray(N);
	fillMatrix(ptr2, N);
	return 0;
}

int* createArray() {
	srand(static_cast<unsigned int>(time(NULL)));
	static int newArray[ROWS][COLUMNS];
	std::cout << "Первое задание: " << std::endl;
	std::cout << "Выведен случайный массив: " << std::endl;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			newArray[i][j] = rand();
			if (newArray[i][j] % 2 == 0) {
				newArray[i][j] = -newArray[i][j];
			}
			std::cout << std::setw(10) << newArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	int* ptr = &newArray[0][0];
	return ptr;
}

int** createDynamicArray(int N) {
	static int** newArray = new int* [N];
	for (int i = 0; i < N; i++) {
		newArray[i] = new int[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			newArray[i][j] = 0;
		}
	}
	return newArray;
}

void calculatePositiveColumns(int* matrix, int rows, int columns) {
	int count = 0;
	int countBuffer = 0;
	for (int i = 0; i < COLUMNS; i++) {
		for (int j = i; j < ROWS * COLUMNS; j += COLUMNS) {
			if (*(matrix + j) > 0) {
				countBuffer++;
			}
		}
		if (countBuffer == ROWS) {
			count++;
		}
		countBuffer = 0;
	}
	std::cout << "Кол-во столбиков со всеми положительными элементами равно: " << count << std::endl;
}

void fillMatrix(int** matrix, int N) {
	int curValue = 1;
	if (N % 2 != 0) {
		*(*(matrix + N/2) + N/2) = (N * N);      
	}
	for (int i = 0; i < (N / 2); i++) {
		for (int j = i; j < (N - i); j++) {   
			*(*(matrix + i) + j) = curValue;
			curValue++;
		}
		for (int j = 1; j < (N - i - i); j++) {   
			*(*(matrix + j + i) + N - i -1) = curValue;
			curValue++;
		}
		for (int j = (N - 2) - i; j >= i; j--) {  
			*(*(matrix + N - i - 1) + j) = curValue; 
			curValue++;
		}
		for (int j = ((N - i) - 2); j > i; j--) {
			*(*(matrix + j) + i) = curValue;
			curValue++;
		}
	}
	writeToFile(matrix, N);
}

void writeToFile(int** matrix, int N) {
	std::cout << std::endl;
	std::ofstream fout;
	fout.open("test2.txt");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fout << std::setw(3) << *(*(matrix + i) + j) << " ";
		}
		fout << std::endl;
	}
	fout.close();
	std::cout << "Результаты второго задания в файле.";
}

int readFile() {
	std::fstream fin;
	fin.open("test.txt");

	int N;
	fin >> N;
	if (fin.bad()) {
		throw "Размер матрицы задан неправильным числом";
	}
	fin.close();
	return N;
}


int isValid() {
	int N;
	while (!(std::cin >> N)) {
		std::cout << "Неверное значение числа. Введите новое число.";
		std::cin.clear();
		std::cin.get();
	}
	return N;
}