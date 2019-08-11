#pragma once
#include<iostream>
#include<vector>
void OpenFile(std::vector<double>& x, std::vector<double>& y, const std::string way);
std::string ToString(const double d);
double Area(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3);
std::vector <double> IntersectionPoint(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const double x4, const double y4);
double DeviationArea(const std::vector <double>& x, const std::vector<double>& y);
void Delete(std::vector <double>& s, std::vector <double>& x, std::vector<double>& y, std::vector<double>& devs, std::vector<double>& dels, const double DevArea);
void PointAdding(std::vector<double>& x, std::vector<double>& y, const std::vector<double>& x1, const std::vector<double>& y1, const std::vector<int>& position, const std::string way);
void PointShift(std::vector<double>& x, std::vector<double>& y, const int position, const std::string way, const double shiftx, const double shifty);
void DataProcessing(const std::string way, const std::string modifiedWay, const int delnumber);
void DataProcessingWithAdding(const std::string way, const std::vector<double>& x1, const std::vector<double>& y1, const std::vector<int>& position);
void ShearProcessing(const std::string way, const double shiftx, const double shifty, const int position);
std::vector <double> IntersectionPoint(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
