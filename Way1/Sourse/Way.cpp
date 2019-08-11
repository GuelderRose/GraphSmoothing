#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <sstream>
#include "math.h"
#include "WayHeader.h"
#include <iomanip>

void OpenFile(std::vector<double>& x, std::vector<double>& y, const std::string way) {
	//чтение данных из файла
	std::ifstream input;
	std::string X;
	std::string Y;
	input.open(way);
	if (input.is_open()) {
		std::cout << "File is opened" << std::endl << std::endl;
		std::cout << "Data from file:" << std::endl;
		for (int i = 0; i < 1; i++) {
			getline(input, X, '\n');
			getline(input, Y, '\n');
			std::cout << "X: " << X << std::endl;
			std::cout << "Y: " << Y << std::endl;
		}
		input.close();
		//запись координат точек в векторы
		std::stringstream stringStream1(X);
		std::stringstream stringStream2(Y);
		std::string number;
		while (getline(stringStream1, number, ';')) {
			x.push_back(stod(number));
		}
		while (getline(stringStream2, number, ';')) {
			y.push_back(stod(number));
		}
		std::cout << std::endl;
	} else {
		std::cout << "cannot open this file" << std::endl;
	}
}
std::string ToString(const double d) {
	std::ostringstream strd;
	strd << d;
	return strd.str();
}
std::vector <double> IntersectionPoint(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const double x4, const double y4) {
	std::vector <double> PointCoordinates;
	double k1 = (y2 - y1) / (x2 - x1);
	double k2 = (y4 - y3) / (x4 - x3);
	double c1 = (x2 * y1 - x1 * y2) / (x2 - x1);
	double c2 = (x4 * y3 - x3 * y4) / (x4 - x3);
	double p = (c2 - c1) / (k1 - k2);
	double f = k1 * p + c1;
	if (x1 > x2) {
		if ((p > x1) || (p < x2)) {
			p = x1; f = y1;
		}
	}
	else {
		if ((p < x1) || (p > x2)) {
			p = x1; f = y1;
		}
	}
	PointCoordinates.push_back(p);
	PointCoordinates.push_back(f);
	return PointCoordinates;
}
double DeviationArea(const std::vector <double>& x, const std::vector<double>& y) {
	std::vector <double> a;
	int i = 0;
	std::vector <double> PointCoordinates;
	double s1 = 0, s2 = 0, s3 = 0;
	double p1 = 0, p2 = 0;
	int k = 2;
	if (x.size() > 2) {
		if (x.size() == 3) {
			k = 1;
		}
		while (i != x.size() - k) {
			PointCoordinates.clear();
			PointCoordinates = IntersectionPoint(x[i], y[i], x[i + 1], y[i + 1], x[0], y[0], x[x.size() - 1], y[y.size() - 1]);
			if (((x[i] != PointCoordinates[0]) && (y[i] != PointCoordinates[1])) && ((x[i + 1] != PointCoordinates[0]) && (y[i + 1] != PointCoordinates[1]))) {
				p1 = x[i], p2 = PointCoordinates[0];
				s1 = (((PointCoordinates[1] - y[i]) / (PointCoordinates[0] - x[i])) / 2)*(p2 * p2 - p1 * p1) + (PointCoordinates[0] * y[i] - x[i] * PointCoordinates[1]) / (PointCoordinates[0] - x[i])*(p2 - p1);
				s2 = (((y[y.size() - 1] - y[0]) / (x[x.size() - 1] - x[0])) / 2)*(p2 * p2 - p1 * p1) + (x[x.size() - 1] * y[0] - x[0] * y[x.size() - 1]) / (x[x.size() - 1] - x[0])*(p2 - p1);
				if (x[i] > PointCoordinates[0]) {
					if (y[i] < PointCoordinates[1]) {
						s3 = s2 - s1;
					} else {
						s3 = s1 - s2;
					}
				} else {
					s3 = abs(s1 - s2);
				}
				a.push_back(s3);
				p1 = PointCoordinates[0]; p2 = x[i + 1];
				s1 = (((PointCoordinates[1] - y[i]) / (PointCoordinates[0] - x[i])) / 2)*(p2 * p2 - p1 * p1) + (PointCoordinates[0] * y[i] - x[i] * PointCoordinates[1]) / (PointCoordinates[0] - x[i])*(p2 - p1);
				s2 = (((y[y.size() - 1] - y[0]) / (x[x.size() - 1] - x[0])) / 2)*(p2 * p2 - p1 * p1) + (x[x.size() - 1] * y[0] - x[0] * y[x.size() - 1]) / (x[x.size() - 1] - x[0])*(p2 - p1);
				s3 = abs(s1 - s2);
				a.push_back(s3);
			} else {
				p1 = x[i]; p2 = x[i + 1];
				s1 = (((y[i + 1] - y[i]) / (x[i + 1] - x[i])) / 2)*(p2 * p2 - p1 * p1) + (x[i + 1] * y[i] - x[i] * y[i + 1]) / (x[i + 1] - x[i])*(p2 - p1);
				if (x[i + 1] < x[0]) {
					p1 = x[i]; p2 = x[0];
				}
				if (x[i] < x[0]) {
					p1 = x[0]; p2 = x[i + 1];
				}
				s2 = (((y[y.size() - 1] - y[0]) / (x[x.size() - 1] - x[0])) / 2)*(p2 * p2 - p1 * p1) + (x[x.size() - 1] * y[0] - x[0] * y[x.size() - 1]) / (x[x.size() - 1] - x[0])*(p2 - p1);
				if (PointCoordinates[0] > x[i + 1]) {
					s3 = s1 - s2;
				} else {
					s3 = abs(s1 - s2);
				}
				a.push_back(s3);
			}
			i++;
		}
	} else {
		
		return 0;
	}
	double A = -1;
	for (int i = 0; i < a.size(); i++) {
		A+=a[i];
	}
	return A;
}
double Area(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3) {
	double S = 0;
	double a = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	double b = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	double c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	double p = 0;
	p = (a + b + c) / 2;
	S = sqrt(p*(p - a)*(p - b)*(p - c));
	return S;
}
void Delete(std::vector <double>& s, std::vector <double>& x, std::vector<double>& y, std::vector<double>& devs, std::vector<double>& dels, const double DevArea) {
	double mins = s[0];
	int j = 0;
	for (int i = 0; i < s.size(); i++) {
		if (mins > s[i]) {
			mins = s[i];
			j = i;
		}
	}
	if (dels.size() == 0) {
		dels.push_back(s[j]);
	} else {
		dels.push_back((s[j]) + dels[dels.size() - 1]);
	}
	x.erase(x.begin() + j + 1);
	y.erase(y.begin() + j + 1);
	s.erase(s.begin() + j);
	if (s.size() == 0) {
		std::cout << "Two points left" << std::endl;
	} else {
		if (s.size() == j) {
			s[j - 1] = Area(x[j - 1], y[j - 1], x[j], y[j], x[j + 1], y[j + 1]);
		} else {
			if (j == 0) {
				s[j] = Area(x[j], y[j], x[j + 1], y[j + 1], x[j + 2], y[j + 2]);
			} else {
				s[j - 1] = Area(x[j - 1], y[j - 1], x[j], y[j], x[j + 1], y[j + 1]);
				s[j] = Area(x[j], y[j], x[j + 1], y[j + 1], x[j + 2], y[j + 2]);
			}
		}
	}
	double DevArea1 = DeviationArea(x, y);
	devs.push_back(DevArea1 / (DevArea / 100));
}
std::vector<double> AreaVector(const std::vector<double>& x, const std::vector<double>& y) {
	std::vector<double> s;
	std::cout << "Areas:" << std::endl;
	for (int i = 0; i < x.size() - 2; i++) {
		s.push_back(Area(x[i], y[i], x[i + 1], y[i + 1], x[i + 2], y[i + 2]));
		std::cout << std::setw(7) << s[i];
	}
	return s;
}
void PointAdding(std::vector<double>& x, std::vector<double>& y, const std::vector<double>& x1, const std::vector<double>& y1, const std::vector<int>& position, const std::string way) {
	int u = x.size() - 1;
	bool WrongPosition = false;
	for (int i = 0; i < position.size(); i++) {
		if ((position[i] <= 0) || (position[i] >= u)) {
			WrongPosition = true;
		}
	}
	if (WrongPosition) {
		std::cout << "Choose another positions" << std::endl;
	} else {
		int j = 0;
		int k = 0;
		for (int i = 1; i < x.size() - 1; i++) {
			if (i == position[j]) {
				x.insert(x.begin() + i, x1[k]);
				y.insert(y.begin() + i, y1[k]);
				int f = position.size() - 1;
				if (j == f) {
					break;
				}
				k++;
				j++;
			}
		}
		std::ofstream output;
		output.open(way);
		if (output.is_open()) {
			for (int i = 0; i < x.size(); i++) {
				output << ToString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++) {
				output << ToString(y[i]) << ";";
			}
			output << "\n";
		}
		output.close();
	}
}
void PointShift(std::vector<double>& x, std::vector<double>& y, const int position, const std::string way, const double shiftx, const double shifty) {
	if (position >= x.size()) {
		std::cout << "Choose another position" << std::endl;
	} else {
		for (int i = 0; i < x.size(); i++) {
			if (i == position) {
				x[i] += shiftx;
				y[i] += shifty;
			}
		}
		std::ofstream output;
		output.open(way);
		if (output.is_open()) {
			for (int i = 0; i < x.size(); i++) {
				output << ToString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++) {
				output << ToString(y[i]) << ";";
			}
			output << "\n";
		}
		output.close();
	}
}
void DataProcessing(const std::string way, const std::string modifiedWay, const int delnumber) {
	std::vector<double> x;
	std::vector<double> y;
	OpenFile(x, y, way);
	if (delnumber > x.size() - 2) {
		std::cout << "Choose fewer points" << std::endl;
	} else {
		std::cout << "Point coordinates" << std::endl;
		std::cout << "X:" << std::endl;
		for (int i = 0; i < x.size(); i++) {
			std::cout << x[i] << "    ";
		}
		int NumberOfPoints = x.size();
		std::cout << std::endl;
		std::cout << "Y:" << std::endl;
		for (int i = 0; i < y.size(); i++) {
			std::cout << y[i] << "    ";
		}
		std::cout << std::endl << std::endl;
		//Находим минимальный и максимальный х
		double xmin = x[0]; double xmax = x[0];
		for (int i = 0; i < x.size(); i++)
		{
			if (x[i]<xmin) { xmin = x[i]; }
			if (x[i]>xmax) { xmax = x[i]; }
		}
		//Находим минимальный и максимальный у
		double ymin = y[0]; double ymax = y[0];
		for (int i = 0; i < y.size(); i++)
		{
			if (y[i]<ymin) { ymin = y[i]; }
			if (y[i]>ymax) { ymax = y[i]; }
		}
		//Изменение координат таким образом, чтобы все точки оказались в первой координатной четверти
		if (xmin != 0)
		{
			for (int i = 0; i < x.size(); i++)
			{
				x[i] -= xmin;
			}
			xmax -= xmin; xmin = 0;
		}
		if (ymin != 0)
		{
			for (int i = 0; i < y.size(); i++)
			{
				y[i] -= ymin;
			}
			ymax -= ymin; ymin = 0;
		}
		//общая площадь отклонений от прямой, соединяющей первую и последнюю точку
		double DevArea = DeviationArea(x, y);
		//вектор площадей, которые потенциально можно удалить
		std::vector<double> s = AreaVector(x, y);
		std::cout << std::endl << std::endl;
		//вектор областей отклонения от прямой 
		std::vector<double> devs;
		//вектор удалённых площадей
		std::vector<double> dels;
		//удаление площадей
		for (int i = 0; i < delnumber; i++) {
			Delete(s, x, y, devs, dels, DevArea);
		}
		//вывод данных для проверки
		std::cout << std::endl;
		std::cout << "Coordinates of points after processing" << std::endl;
		std::cout << "X:" << std::endl;
		for (int i = 0; i < x.size(); i++) {
			std::cout << x[i] << "    ";
		}
		std::cout << std::endl;
		std::cout << "Y:" << std::endl;
		for (int i = 0; i < y.size(); i++) {
			std::cout << y[i] << "    ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Areas after processing:" << std::endl;
		for (int i = 0; i < s.size(); i++) {
			std::cout << s[i] << "    ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Deviation area (in percents):" << std::endl;
		for (int i = 0; i < devs.size(); i++) {
			std::cout << devs[i] << "    ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Removed area:" << std::endl;
		for (int i = 0; i < dels.size(); i++) {
			std::cout << dels[i] << "    ";
		}
		//запись обработанных данных в файл
		std::ofstream output;
		output.open(modifiedWay);
		if (output.is_open()) {
			for (int i = 0; i < x.size(); i++) {
				output << ToString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++) {
				output << ToString(y[i]) << ";";
			}
		}
		output.close();
	}
}
void DataProcessingWithAdding(const std::string way, const std::vector<double>& x1, const std::vector<double>& y1, const std::vector<int>& position) {
	std::vector<double> x;
	std::vector<double> y;
	OpenFile(x, y, way);
	std::cout << "Point coordinates" << std::endl;
	std::cout << "X:" << std::endl;
	for (int i = 0; i < x.size(); i++) {
		std::cout << std::setw(7) << x[i];
	}
	std::cout << std::endl;
	std::cout << "Y:" << std::endl;
	for (int i = 0; i < y.size(); i++) {
		std::cout << std::setw(7)  << y[i];
	}
	std::cout << std::endl << std::endl;
	PointAdding(x, y, x1, y1, position, way);
	std::cout << "Coordinates of points after processing" << std::endl;
	std::cout << "X:" << std::endl;
	for (int i = 0; i < x.size(); i++) {
		std::cout << std::setw(7)  << x[i];
	}
	std::cout << std::endl;
	std::cout << "Y:" << std::endl;
	for (int i = 0; i < y.size(); i++) {
		std::cout << std::setw(7) << y[i];
	}
	std::cout << std::endl;
}
void ShearProcessing( const std::string way, const double shiftx, const double shifty, const int position) {
	std::vector<double> x;
	std::vector<double> y;
	OpenFile(x, y, way);
	std::cout << "Point coordinates" << std::endl;
	std::cout << "X:" << std::endl;
	for (int i = 0; i < x.size(); i++) {
		std::cout << std::setw(7) << x[i];
	}
	std::cout << std::endl;
	std::cout << "Y:" << std::endl;
	for (int i = 0; i < y.size(); i++) {
		std::cout << std::setw(7) << y[i];
	}
	std::cout << std::endl << std::endl;
	PointShift(x, y, position, way, shiftx, shifty);
	std::cout << "Coordinates of points after processing" << std::endl;
	std::cout << "X:" << std::endl;
	for (int i = 0; i < x.size(); i++) {
		std::cout << std::setw(7) << x[i];
	}
	std::cout << std::endl;
	std::cout << "Y:" << std::endl;
	for (int i = 0; i < y.size(); i++) {
		std::cout << std::setw(7) << y[i];
	}
	std::cout << std::endl;
}

