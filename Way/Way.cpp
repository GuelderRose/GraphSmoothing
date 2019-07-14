#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <sstream>
#include "math.h"
#include "WayHeader.h"
#include <iomanip>

void OpenFile(vector<double>& x, vector<double>& y, string way)
{
	//÷òåíèå äàííûõ èç ôàéëà
	ifstream input;
	string X;
	string Y;
	input.open(way);
	if (input.is_open()) { std::cout << "file is opened" << endl; }
	else { std::cout << "cannot open this file" << endl; }
	for (int i = 0; i < 1; i++)
	{
		getline(input, X, '\n');
		getline(input, Y, '\n');
		std::cout << "X: " << X << endl;
		std::cout << "Y: " << Y << endl;
	}
	input.close();
	//çàïèñü êîîðäèíàò òî÷åê â âåêòîðû
	stringstream stringStream1(X);
	stringstream stringStream2(Y);
	string number;
	while (getline(stringStream1, number, ';'))
	{
		x.push_back(stod(number));
	}
	while (getline(stringStream2, number, ';'))
	{
		y.push_back(stod(number));
	}
	std::cout << endl;
}
string toString(double d)
{
	std::ostringstream out;
	out << d;
	return out.str();
}
double Ploshad(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double S = 0;
	double a = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	double b = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	double c = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	double p = 0;
	p = (a + b + c) / 2;
	S = sqrt(p*(p - a)*(p - b)*(p - c));
	return S;
}
void Delete(vector <double>& s, vector <double>& x, vector<double>& y, vector<double>& dels, double ssum)
{
	double mins = s[0];
	int j = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (mins > s[i])
		{
			mins = s[i];
			j = i;
		}
	}
	if (dels.size() == 0)
	{
		dels.push_back(s[j] * 100 / ssum);
	}
	else
	{
		dels.push_back((s[j] * 100 / ssum) + dels[dels.size() - 1]);
	}
	x.erase(x.begin() + j + 1);
	y.erase(y.begin() + j + 1);
	s.erase(s.begin() + j);
	if (s.size() == 0)
	{
		cout << "Two points left" << endl;
	}
	else
	{
		if (s.size() == j)
		{
			s[j - 1] = Ploshad(x[j - 1], y[j - 1], x[j], y[j], x[j + 1], y[j + 1]);
		}
		else
		{
			if (j == 0)
			{
				s[j] = Ploshad(x[j], y[j], x[j + 1], y[j + 1], x[j + 2], y[j + 2]);
			}
			else
			{
				s[j - 1] = Ploshad(x[j - 1], y[j - 1], x[j], y[j], x[j + 1], y[j + 1]);
				s[j] = Ploshad(x[j], y[j], x[j + 1], y[j + 1], x[j + 2], y[j + 2]);
			}
		}
	}
}
vector<double> VecPloshad(vector<double>& x, vector<double>& y, double* ssum)
{
	vector<double> s;
	*ssum = 0;
	for (int i = 0; i < x.size() - 2; i++)
	{
		s.push_back(Ploshad(x[i], y[i], x[i + 1], y[i + 1], x[i + 2], y[i + 2]));
		*ssum += s[i];
		cout << setw(7) << s[i];
	}
	return s;
}
void Dobavlenie(vector<double>& x, vector<double>& y, vector<double>& x1, vector<double>& y1, vector<int>& position, string way)
{
	int u = x.size() - 1;
	bool wrongPosition = false;
	for (int i = 0; i < position.size(); i++)
	{
		if ((position[i] <= 0) || (position[i] >= u))
		{
			wrongPosition = true;
		}
	}
	if (wrongPosition)
	{
		cout << "Choose another positions" << endl;
	}
	else
	{
		int j = 0;
		int k = 0;
		for (int i = 1; i < x.size() - 1; i++)
		{
			if (i == position[j])
			{
				x.insert(x.begin() + i, x1[k]);
				y.insert(y.begin() + i, y1[k]);
				int f = position.size() - 1;
				if (j == f)
				{
					break;
				}
				k++;
				j++;
			}
		}
		ofstream output;
		output.open(way);
		if (output.is_open())
		{
			for (int i = 0; i < x.size(); i++)
			{
				output << toString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++)
			{
				output << toString(y[i]) << ";";
			}
			output << "\n";
		}
		output.close();
	}
}
void Sdvig(vector<double>& x, vector<double>& y, int position, string way, double sdvigx, double sdvigy)
{
	if (position >= x.size())
	{
		cout << "Choose another position" << endl;
	}
	else
	{
		for (int i = 0; i < x.size(); i++)
		{
			if (i == position)
			{
				x[i] += sdvigx;
				y[i] += sdvigy;
			}
		}
		ofstream output;
		output.open(way);
		if (output.is_open())
		{
			for (int i = 0; i < x.size(); i++)
			{
				output << toString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++)
			{
				output << toString(y[i]) << ";";
			}
			output << "\n";
		}
		output.close();
	}
}
void Obrabotka(string way, string modifiedWay, int delnumber)
{
	using namespace std;
	vector<double> x;
	vector<double> y;
	OpenFile(x, y, way);
	if (delnumber > x.size() - 2)
	{
		cout << "Choose fewer points" << endl;
	}
	else
	{
		for (int i = 0; i < x.size(); i++)
		{
			cout << x[i] << "    ";
		}
		int kolToch = x.size();
		cout << endl;
		for (int i = 0; i < y.size(); i++)
		{
			cout << y[i] << "    ";
		}
		cout << endl << endl;
		//âåêòîð ïëîùàäåé, êîòîðûå ïîòåíöèàëüíî ìîæíî óäàëèòü
		double ssum;
		vector<double> s = VecPloshad(x, y, &ssum);
		cout << endl << endl;
		//âåêòîð óäàë¸ííûõ ïëîùàäåé
		vector<double> dels;
		//óäàëåíèå ïëîùàäåé
		for (int i = 0; i < delnumber; i++)
		{
			Delete(s, x, y, dels, ssum);
		}
		//âûâîä äàííûõ äëÿ ïðîâåðêè
		cout << endl;
		for (int i = 0; i < x.size(); i++)
		{
			cout << x[i] << "    ";
		}
		cout << endl;
		for (int i = 0; i < y.size(); i++)
		{
			cout << y[i] << "    ";
		}
		cout << endl;
		for (int i = 0; i < s.size(); i++)
		{
			cout << s[i] << "    ";
		}
		cout << endl;
		for (int i = 0; i < dels.size(); i++)
		{
			cout << dels[i] << "    ";
		}
		//çàïèñü îáðàáîòàííûõ äàííûõ â ôàéë
		ofstream output;
		output.open(modifiedWay);
		if (output.is_open())
		{
			for (int i = 0; i < x.size(); i++)
			{
				output << toString(x[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < y.size(); i++)
			{
				output << toString(y[i]) << ";";
			}
			output << "\n";
			for (int i = 0; i < dels.size(); i++)
			{
				output << kolToch - i << ";";
			}
			output << "\n";
			for (int i = 0; i < dels.size(); i++)
			{
				output << toString(dels[i]) << ";";
			}
		}
		output.close();
	}
}
void ObrabotkaDobavlenie(string way, vector<double>& x1, vector<double>& y1, vector<int>& position)
{
	using namespace std;
	vector<double> x;
	vector<double> y;
	OpenFile(x, y, way);
	for (int i = 0; i < x.size(); i++)
	{
		cout << setw(7) << x[i];
	}
	cout << endl;
	for (int i = 0; i < y.size(); i++)
	{
		cout << setw(7)  << y[i];
	}
	cout << endl << endl;
	Dobavlenie(x, y, x1, y1, position, way);
	for (int i = 0; i < x.size(); i++)
	{
		cout << setw(7)  << x[i];
	}
	cout << endl;
	for (int i = 0; i < y.size(); i++)
	{
		cout << setw(7) << y[i];
	}
	cout << endl;
}
void ObrabotkaSdvig(string way, double sdvigx, double sdvigy, int position)
{
	using namespace std;
	vector<double> x;
	vector<double> y;
	OpenFile(x, y, way);
	for (int i = 0; i < x.size(); i++)
	{
		cout << setw(7) << x[i];
	}
	cout << endl;
	for (int i = 0; i < y.size(); i++)
	{
		cout << setw(7) << y[i];
	}
	cout << endl << endl;
	Sdvig(x, y, position, way, sdvigx, sdvigy);
	for (int i = 0; i < x.size(); i++)
	{
		cout << setw(7) << x[i];
	}
	cout << endl;
	for (int i = 0; i < y.size(); i++)
	{
		cout << setw(7) << y[i];
	}
	cout << endl;
}

