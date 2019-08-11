#include<iostream>
#include"WayHeader.h"
#include<vector>
int main() {
	std::string way = 0;
	std::string modifiedWay = "D:\\Универская фигота\\Практика\\modifiedWay.txt";
	int delnumber = 2;
	//Тест обработки исходного файла с выводом в другой файл
	DataProcessing(way, modifiedWay, delnumber);
	
	std::vector<double> x1{ -3.5,1 };
	std::vector<double> y1{ 4.5,2.5 };
	std::vector<int> position{ 3,5 };
	//Тест на добавление точек в исходный файл
	//DataProcessingWithAdding(way, x1, y1, position);
	double shiftx = 1;
	double shifty = -2.5;
	int position1 = 3;
	//Тест на изменение координат определённой точки (сдвиг)
	//ShearProcessing(way, sdvigx, sdvigy, position1);
	system("pause");
	return 0;
}
