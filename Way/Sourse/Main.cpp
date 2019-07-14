#include<iostream>
#include"WayHeader.h"
#include<vector>
using namespace std;
int main()
{
	string way = "D:\\Óíèâåðñêàÿ ôèãîòà\\Ïðàêòèêà\\way.txt";
	string modifiedWay = "D:\\Óíèâåðñêàÿ ôèãîòà\\Ïðàêòèêà\\modifiedWay.txt";
	int delnumber = 3;
	//Obrabotka(way, modifiedWay, delnumber);
	vector<double> x1{ 1.5,6 };
	vector<double> y1{ 2,1 };
	vector<int> position{ 1,3 };
	//ObrabotkaDobavlenie(way, x1, y1, position);
	double sdvigx = 1;
	double sdvigy = -2.5;
	int position1 = 3;
	ObrabotkaSdvig(way, sdvigx, sdvigy, position1);
	system("pause");
	return 0;
}
