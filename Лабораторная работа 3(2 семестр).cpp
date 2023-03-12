//                          Задание: 
// Реализовать программу, формирующую множество равное пересечению произвольного
// количества исходных множеств(с учетом кратных вхождений).

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

ofstream spisok("Spisok.txt", ios::app);
ifstream info("Spisok.txt");

void Show(vector<vector<string>>& glav) {
	setlocale(LC_ALL, "ru");
	for (int i = 0; i < glav.size(); i++) {
		std::cout << "\n Множество " << i + 1 << ": ";
		for (int j = 0; j < glav[i].size(); j++) {
			cout << glav[i][j] << ", ";
		}
	}
}

bool Part(vector<char> control1, vector<char>control2) {
	int check = 0;
	for (int i = 0; i < control1.size(); i++) {
		for (int j = 0; j < control2.size(); j++) {
			if (check != control1.size() - 1) {
				if (control1[i] == control2[j]) {
					check++;
				}
			}
			else {
				return true;
			}
		}
	}
	return false;
}

void Proverka(int situation, vector<vector<string>>& glav) {
	switch (situation) {
	case 1:
		for (int i = 0; i < glav.size(); i++) {
			for (int j = 0; j < glav[i].size(); j++) {
				for (int k = j + 1; k < glav[i].size(); k++) {
					if (glav[i][k] == glav[i][j]) { glav[i].erase(glav[i].begin() + k); }
				}
			}
		}	break;
	case 2:
		vector<vector<char>> check;
		vector<char> control1;
		vector<char> control2;
		for (int i = 0; i < glav.size(); i++) {
			for (int j = 0; j < glav[i].size(); j++) {

				if (glav[i][j][0] == '{') {
					for (int k = 1; k < glav[i][j].size() - 1; k++) {
						control1.push_back(glav[i][j][k]);
					}

					for (int k = j + 1; k < glav[i].size(); k++) {
						if (glav[i][k][0] == '{') {
							for (int u = 1; u < glav[i][j].size() - 1; u++) {
								control2.push_back(glav[i][j][u]);
							}
						}
					}

					if (Part(control1, control2)) {
						glav[i].erase(glav[i].begin() + j);
					}
				}
			}

			for (int i = 0; i < control1.size(); i++) {
				control1.erase(control1.begin() + i);
			}
			for (int i = 0; i < control2.size(); i++) {
				control2.erase(control2.begin() + i);
			}

		}	break;
	}
}

void Read_file(vector<vector<string>>& glav) {
	ifstream info("spisok.txt");
	vector<string> add;
	string get;
	if (info.is_open())
	{
		while (info >> get) {
			if (get == "|") {
				glav.push_back(add);
			}
			else {
				get.erase(get.size() - 1);
				glav[glav.size() - 1].push_back(get);
			}
		}
	}
	info.close();
	Proverka(1, glav);
	Proverka(2, glav);
	Show(glav);
}

void Add(vector<vector<string>>& glav) {
	setlocale(LC_ALL, "ru");
	cout << "\n\tЧто добавляем?\n 1)Множество\n 2)Элемент\n ";
	int operation;
	cin >> operation;
	if (operation == 1) {
		vector<string> arr;
		cout << "Введите элемент: ";
		string element;
		cin >> element;
		arr.push_back(element);
		glav.push_back(arr);
	}
	else {
		cout << "\n Выберите множество из " << glav.size() << ": ";
		int k;
		cin >> k;
		cout << "\n Введите элемент: ";
		string element;
		cin >> element;
		glav[k - 1].push_back(element);
	}
	Show(glav);
}

void Peresechenie(vector<vector<string>>& glav) {
	vector<string> vec;
	vec = glav[0];
	for (int i = 1; i < glav.size(); i++) {
		for (int k = 0; k < vec.size();) {
			for (int j = 0; j < glav[i].size(); j++) {
				if (k == vec.size()) { break; }
				if (j != glav[i].size() - 1) {
					if (vec[k] == glav[i][j]) {
						k++;
						j = 0;
					}
				}
				else {
					if (vec[k] == glav[i][j]) {
						k++;
						j = 0;
					}
					else {
						vec.erase(vec.begin() + k);
					}
				}
			}
		}
	}

	cout << "Пересечение: ";

	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << ", ";
	}
}

void Delete_element(vector<vector<string>>& glav) {
	Show(glav);
	cout << "\n Введите номер множества, из которого будем удалять элемент: ";
	int mas;
	cin >> mas;
	cout << "\n Введите номер элемента: ";
	int nom;
	cin >> nom;
	glav[mas - 1].erase(glav[mas - 1].begin() + nom - 1);
}

int main()
{
	vector<vector<string>> glav;
	Read_file(glav);
	setlocale(LC_ALL, "ru");
	for (;;) {
		cout << "\n\tВыберите операцию:\n 1) Добавление\n 2) Просмотр\n 3) Нахождение пересечения\n 4) Удаление элемента\n 5) Выход\n";
		int k;
		cin >> k;
		if (k == 5) { break; }
		else {
			switch (k) {
			case 1: Add(glav); break;
			case 2: Show(glav); break;
			case 3: Peresechenie(glav); break;
			case 4: Delete_element(glav); break;
			default: cout << "\n Проверьте введенную вами операцию!"; break;
			}
		}
	}
}