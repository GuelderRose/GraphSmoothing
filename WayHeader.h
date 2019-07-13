#pragma once
#include<iostream>
#include<vector>
using namespace std;
string toString(double d);
double Ploshad(double x1, double y1, double x2, double y2, double x3, double y3);
vector<double> VecPloshad(vector<double>& x, vector<double>& y, double* ssum);
void Delete(vector <double>& s, vector <double>& x, vector<double>& y, vector<double>& dels, double ssum);
void Dobavlenie(vector<double>& x, vector<double>& y, vector<double>& x1, vector<double>& y1, vector<int>& position, string way);
void Sdvig(vector<double>& x, vector<double>& y, int position, string way, double sdvigx, double sdvigy);
void Obrabotka(string way, string modifiedWay, int delnumber);
void ObrabotkaDobavlenie(string way, vector<double>& x1, vector<double>& y1, vector<int>& position);
void ObrabotkaSdvig(string way, double sdvigx, double sdvigy, int position);
