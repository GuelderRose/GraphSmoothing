#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct Point{
        double x{0};
        double y{0};
     Point(){}
        Point(double x1, double y1)
         :x(x1)
         ,y(y1)
     {
     }
    };
    QVector<Point> point;
    QVector<double> s;
    QVector<Point> point1;
    QVector<double> s1;
    QVector<double> dels;
    QVector<double> dels1;
    QString way;
    //QString modifiedWay="D:\\Универская фигота\\Практика\\modifiedWayQt.txt";
    QString modifiedWay;
    QString savedWay;
    QVector<Point> psaved;
    QVector<Point> padd;
    QVector<double> a;
    QVector<double> l;
    double DevArea;
    double length;
    int delnum=-1;
    bool wrongsimbol=false;
    void OpenFile(QVector<Point>& point, const QString way);
    void OpenFile(QVector<Point>& point, const QString way, QVector<Point>& point1);
    void AreaVector(QVector <double> &s, QVector <Point> &point);
    double Area(double x1, double y1, double x2, double y2, double x3, double y3);
    void Delete(const double DevArea,QVector <Point> &point,QVector <double> &s, QVector <double> &dels);
    void Delete1(const double DevArea, QVector <Point> &point,QVector <double> &s, QVector <double> &dels);
    QVector <double> IntersectionPoint(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const double x4, const double y4);
    double DeviationArea(QVector <Point>& point);
    void OpenOutFile(QVector<Point>& point);
    double Length(QVector <Point>& point);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_3_clicked(const int delnumber);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void AreaGraph();

    void LengthGraph();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
