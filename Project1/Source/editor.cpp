#include "editor.h"
#include "ui_editor.h"
#include <QGraphicsTextItem>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile(QVector<Point>& point, const QString way)
{
    QFile file(way);
       if(file.open(QIODevice::ReadOnly |QIODevice::Text)) {
           while(!file.atEnd()) {
               QString str = file.readLine();
               QStringList k = str.split(" ");
                qDebug() << k.at(0) << k.at(1);
                Point p(k.at(0).toDouble(),k.at(1).toDouble());
                point.push_back(p);
           }
       } else {
              qDebug()<< "Can't open this file";
          }
}

void MainWindow::OpenFile(QVector<Point>& point, const QString way, QVector<Point>& point1)
{
    QFile file(way);
       if(file.open(QIODevice::ReadOnly |QIODevice::Text)) {
           while(!file.atEnd()) {
               QString str = file.readLine();
               QStringList k = str.split(" ");
                qDebug() << k.at(0) << k.at(1);
                Point p(k.at(0).toDouble(),k.at(1).toDouble());
                point.push_back(p);
                Point p1(k.at(0).toDouble(),k.at(1).toDouble());
                point1.push_back(p1);
           }
       } else {
              qDebug()<< "Can't open this file";
          }
}

QVector <double> MainWindow::IntersectionPoint(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const double x4, const double y4) {
    QVector <double> PointCoordinates;
    double k1,k2,c1,c2;
        double p,f;
       // if((x1<x3)&&(x2>x3))
        if (x1 == x2){
            k1=0;
            c1=0;
        } else {
            k1 = (y2 - y1) / (x2 - x1);
            c1 = (x2 * y1 - x1 * y2) / (x2 - x1);
        }
        if(x3==x4){
            k2=0;
            c2=0;
        } else {
          k2 = (y4 - y3) / (x4 - x3);
          c2 = (x4 * y3 - x3 * y4) / (x4 - x3);
        }

    if(k1 == k2){
        p = x1;f = y1;
    } else {
        if (y1 == y2){
            p = 0;
            f = y1;
        }
        if(y3 == y4){
             p = 0;
             f = y3;
            }
            else{
                if(x3==x4){
                    p=x3;
                    f=k1*p+c1;
                } else {
                    p = (c2 - c1) / (k1 - k2);
                    f = k1 * p + c1;
                }
            }
    }
    if (x1 > x2) {
        if ((p > x1) || (p < x2)) {
            p = x1; f = y1;
        }
    }
    else {
        if((x1==x2)||((p < x1) || (p > x2))){
            p=x1;f=y1;
        }
    }
    PointCoordinates.push_back(p);
    PointCoordinates.push_back(f);
    return PointCoordinates;
}

double MainWindow::DeviationArea(QVector <Point>& point) {
    QVector <double> a;
        int i = 0;
        QVector <double> PointCoordinates;
        double s1 = 0, s2 = 0, s3 = 0;
        double p1 = 0, p2 = 0;
        int k = 2;
        if (point.size() > 2) {
            if (point.size() == 3) {
                k = 1;
            }
            while (i <= point.size() - k) {
                PointCoordinates.clear();
                if((point.size()==3)&&(i==2)){
                   PointCoordinates = IntersectionPoint(point[0].x, point[0].y, point[1].x, point[1].y, point[0].x, point[0].y, point[1].x, point[1].y);
                }else{
                PointCoordinates = IntersectionPoint(point[i].x, point[i].y, point[i + 1].x, point[i + 1].y, point[0].x, point[0].y, point[point.size() - 1].x, point[point.size() - 1].y);
                if (((point[i].x != PointCoordinates[0]) && (point[i].y != PointCoordinates[1])) && ((point[i + 1].x != PointCoordinates[0]) && (point[i + 1].y != PointCoordinates[1]))) {
                    p1 = point[i].x, p2 = PointCoordinates[0];
                    s1 = (((PointCoordinates[1] - point[i].y) / (PointCoordinates[0] - point[i].x)) / 2)*(p2 * p2 - p1 * p1) + (PointCoordinates[0] * point[i].y - point[i].x * PointCoordinates[1]) / (PointCoordinates[0] - point[i].x)*(p2 - p1);
                    if (point[point.size()-1].x==point[0].x){
                        s2=0;
                        if(point[i].x>point[point.size()-1].x){
                            s1*=-1;
                        }
                    } else {
                    s2 = (((point[point.size() - 1].y - point[0].y) / (point[point.size() - 1].x - point[0].x)) / 2)*(p2 * p2 - p1 * p1) + (point[point.size() - 1].x * point[0].y - point[0].x * point[point.size() - 1].y) / (point[point.size() - 1].x - point[0].x)*(p2 - p1);
                    }
                    if (point[i].x > PointCoordinates[0]) {
                        if (point[i].y < PointCoordinates[1]) {
                            s3 = s2 - s1;
                        }
                        else {
                            s3 = s1 - s2;
                        }
                    }
                    else {
                        s3 = abs(s1 - s2);
                    }
                    a.push_back(s3);
                    p1 = PointCoordinates[0]; p2 = point[i + 1].x;
                    s1 = (((PointCoordinates[1] - point[i].y) / (PointCoordinates[0] - point[i].x)) / 2)*(p2 * p2 - p1 * p1) + (PointCoordinates[0] * point[i].y - point[i].x * PointCoordinates[1]) / (PointCoordinates[0] - point[i].x)*(p2 - p1);
                    if(point[point.size()-1].x==point[0].x){
                        s2=0;
                        if(point[i+1].x>point[0].x){
                            s1*=-1;
                        }
                    } else {
                    s2 = (((point[point.size() - 1].y - point[0].y) / (point[point.size() - 1].x - point[0].x)) / 2)*(p2 * p2 - p1 * p1) + (point[point.size() - 1].x * point[0].y - point[0].x * point[point.size() - 1].y) / (point[point.size() - 1].x - point[0].x)*(p2 - p1);
                    }
                    if(s1<0){
                        s3=s1;
                    } else {
                    s3 = abs(s1 - s2);
                    }
                    a.push_back(s3);
                }
                else {
                    p1 = point[i].x; p2 = point[i + 1].x;
                    if (p1 == p2){
                        s1 = 0;
                    } else {
                    s1 = (((point[i + 1].y - point[i].y) / (point[i + 1].x - point[i].x)) / 2)*(p2 * p2 - p1 * p1) + (point[i + 1].x * point[i].y - point[i].x * point[i + 1].y) / (point[i + 1].x - point[i].x)*(p2 - p1);
                    }
                    if (point[i+1].x>point[point.size()-1].x){
                       p2 = point[point.size()-1].x;
                    }
                    if(point[i].x<point[0].x){
                        p1=point[0].x;
                    }
                    if((point[i].x>point[point.size()-1].x)||(point[i+1].x<point[0].x)){
                        s2 = 0;
                        if(point[point.size() - 1].x == point[0].x){
                            s2=0;
                            if(point[i].x>point[0].x){
                                s1*=-1;
                            }
                        }
                    } else {
                        if(point[point.size() - 1].x == point[0].x){
                            s2=0;
                            if(point[i].x>point[0].x){
                                s1*=-1;
                            }
                        } else {
                        s2 = (((point[point.size() - 1].y - point[0].y) / (point[point.size() - 1].x - point[0].x)) / 2)*(p2 * p2 - p1 * p1) + (point[point.size() - 1].x * point[0].y - point[0].x * point[point.size() - 1].y) / (point[point.size() - 1].x - point[0].x)*(p2 - p1);
                        }
                    }
                    if(s2 == 0){
                        s3 = s1;
                    } else{
                        if (PointCoordinates[0] > point[i + 1].x) {
                        s3 = s1 - s2;
                        }
                    else {
                            //
                            if(s2 < 0){
                                s3 = s1 + s2;
                            } else {
                                s3 = abs(s1 - s2);
                            }
                    }
                    }
                    a.push_back(s3);
                }
                }
                i++;
            }
        }
        else {
            return 0;
        }
        double A = 0;
        for (int i = 0; i < a.size(); i++) {
            A += a[i];
        }
        return A;
}

double MainWindow::Area(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double S = 0;
    double s1,s2,s3;
    double p1,p2;
    p1=x1;p2=x2;
    s1=(((y2-y1)/(x2-x1))/2)*(p2*p2-p1*p1)+(x2*y1-x1*y2)/(x2-x1)*(p2-p1);
    p1=x2;p2=x3;
    s2=(((y3-y2)/(x3-x2))/2)*(p2*p2-p1*p1)+(x3*y2-x2*y3)/(x3-x2)*(p2-p1);
    p1=x3;p2=x1;
    s3=(((y1-y3)/(x1-x3))/2)*(p2*p2-p1*p1)+(x1*y3-x3*y1)/(x1-x3)*(p2-p1);
    S=s1+s2+s3;
    if (S<0) {
        s1*=-1;s2*=-1;s3*=-1;
    }
    S=s1+s2+s3;
    return S;
}

void MainWindow::AreaVector(QVector <double> &s, QVector <Point>& point)
{
    for (int i = 0; i < point.size() - 2; i++){
        s.push_back(Area(point[i].x, point[i].y, point[i + 1].x, point[i + 1].y, point[i + 2].x, point[i + 2].y));
    }
}

void MainWindow::Delete(const double DevArea, QVector <Point> &point,QVector <double> &s, QVector <double> &dels)
{
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
    }
    else {
        dels.push_back(s[j] + dels[dels.size() - 1]);
    }
    point.erase(point.begin()+j+1);
    s.erase(s.begin() + j);
    if (s.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Two points left");
        msgBox.exec();
    } else {
        if (s.size() == j) {
            s[j - 1] = Area(point[j - 1].x, point[j - 1].y, point[j].x, point[j].y, point[j + 1].x, point[j + 1].y);
        } else {
            if (j == 0) {
                s[j] = Area(point[j].x, point[j].y, point[j + 1].x, point[j + 1].y, point[j + 2].x, point[j + 2].y);
            } else {
                s[j - 1] = Area(point[j - 1].x, point[j - 1].y, point[j].x, point[j].y, point[j + 1].x, point[j + 1].y);
                s[j] = Area(point[j].x, point[j].y, point[j + 1].x, point[j + 1].y, point[j + 2].x, point[j + 2].y);
            }
        }
    }
}

void MainWindow::Delete1(const double DevArea, QVector <Point> &point,QVector <double> &s, QVector <double> &dels)
{
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
    }
    else {
        dels.push_back(s[j] + dels[dels.size() - 1]);
    }
    point.erase(point.begin()+j+1);
    s.erase(s.begin() + j);
    if (s.size() != 0) {
        if (s.size() == j) {
            s[j - 1] = Area(point[j - 1].x, point[j - 1].y, point[j].x, point[j].y, point[j + 1].x, point[j + 1].y);
        } else {
            if (j == 0) {
                s[j] = Area(point[j].x, point[j].y, point[j + 1].x, point[j + 1].y, point[j + 2].x, point[j + 2].y);
            } else {
                s[j - 1] = Area(point[j - 1].x, point[j - 1].y, point[j].x, point[j].y, point[j + 1].x, point[j + 1].y);
                s[j] = Area(point[j].x, point[j].y, point[j + 1].x, point[j + 1].y, point[j + 2].x, point[j + 2].y);
            }
        }
     }
}

void MainWindow::on_pushButton_clicked()
{
    point.clear();
    s.clear();
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QGraphicsScene *scenewithpoints = new QGraphicsScene(ui->graphicsView_2);
    //Рисование осей
    QPen pen(Qt::blue);
    scene->addLine(0,0,470,0,pen);
    scene->addLine(0,0,0,-310,pen);
    ui->graphicsView->setScene(scene);
    //Открытие файла с исходными данными
    OpenFile(point,way,point1);
    //Зеркальное отражение координат, если начальная координата больше конечной
    if(point[0].x>point[point.size()-1].x){
        for (int i = 0;i < point.size(); i++) {
            point[i].x*=-1;
        }
    }
    //Находим минимальный и максимальный х
    double xmin=point[0].x; double xmax=point[0].x;
    for (int i = 0;i < point.size(); i++) {
       if(point[i].x<xmin){xmin=point[i].x;}
       if(point[i].x>xmax){xmax=point[i].x;}
    }
    //Находим минимальный и максимальный у
    double ymin=point[0].y; double ymax=point[0].y;
    for (int i = 0;i < point.size(); i++) {
       if(point[i].y<ymin){ymin=point[i].y;}
       if(point[i].y>ymax){ymax=point[i].y;}
    }
    //Изменение координат таким образом, чтобы все точки оказались в первой координатной четверти
    if(xmin!=0) {
        for (int i = 0;i < point.size(); i++)
        {point[i].x-=xmin;}
        xmax-=xmin; xmin=0;
    }
    if(ymin!=0) {
        for (int i = 0;i < point.size(); i++)
        {point[i].y-=ymin;}
        ymax-=ymin; ymin=0;
    }
    //Добавление делений на оси
    double dx=450/xmax;
    int divx=xmax/30;
    double dy=300/ymax;
    int divy=ymax/30;

    for (int i = 0;i < (xmax)/(divx+1)+1; i++) {
       scene->addLine(i*(dx*(divx+1)),-3,i*(dx*(divx+1)),3,pen);
    }
    for (int i = 0;i < (ymax)/(divy+1)+1; i++) {
       scene->addLine(-3,-i*(dy*(divy+1)),3,-i*(dy*(divy+1)),pen);
    }
    QString str;
    for (int i = 0;i < ((xmax/30)*30+1)/(divx+1); i++) {
       str=QString::number(i*(divx+1));
       QGraphicsTextItem *text = scene->addText(str);
       text->setPos(i*(divx+1)*dx-6, 5);
    }
    for (int i = 1;i < ((ymax/30)*30+1)/(divy+1); i++) {
       str=QString::number(i*(divy+1));
       QGraphicsTextItem *text = scene->addText(str);
       text->setPos(-20,-(i*(divy+1)*dy)-10);
    }
    //Добавление точек
    QPen pen2(Qt::green);
    QPen pen3(Qt::cyan);
    pen3.setWidth(3);
    scene->addEllipse(point[0].x*dx,-point[0].y*dy,3,3, pen3);
    for (int i = 0;i < point.size()-1; i++) {
        scene->addLine(point[i].x*dx,-point[i].y*dy,point[i+1].x*dx,-point[i+1].y*dy,pen2);
        scene->addEllipse(point[i+1].x*dx-2.5,-point[i+1].y*dy-2.5,3,3, pen3);
    }
    //Отображение координат точек
    ui->graphicsView_2->setScene(scenewithpoints);
    scenewithpoints->addLine(0,0,518,0,pen);
    scenewithpoints->addLine(38,-34,38,34,pen);
    QGraphicsTextItem *textX = scenewithpoints->addText("X");
    textX->setPos(10,-28);
    QGraphicsTextItem *textY = scenewithpoints->addText("Y");
    textY->setPos(10,8);
    double d=480/point.size();
    if (d<48){
        d=48;
    }
    if(point.size()>10){
        scenewithpoints->addLine(518,0,38+(point.size()*d),0,pen);
    }
    for (int i = 0;i < point.size()+1; i++) {
       scenewithpoints->addLine(38+i*d,-34,38+i*d,34,pen);
    }
    QString strx,stry;
    QGraphicsTextItem *text;
    for (int i = 0;i < point.size(); i++) {
       strx=QString::number(point[i].x);
       stry=QString::number(point[i].y);
       text = scenewithpoints->addText(strx);
       text->setPos(38+(d/8)+i*d,-28);
       text = scenewithpoints->addText(stry);
       text->setPos(38+(d/8)+i*d,8);
    }
    //Площадь отклонения и её вывод
    DevArea = DeviationArea(point);
    ui->lineEdit_6->setText(QString::number(DevArea));
    on_pushButton_7_clicked();
    on_pushButton_7_clicked();
}

void MainWindow::on_pushButton_2_clicked()
{
    way=QFileDialog::getOpenFileName(this, tr("Open File"), "." , tr("*"));
    savedWay=way;
    point.clear();
    s.clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    int delnumber=ui->lineEdit->text().toInt();
    if(delnum!=-1){
        delnumber=delnum;
    }
    if (delnumber > point.size() - 2) {
            QMessageBox msgBox;
            msgBox.setText("Choose fewer points");
            msgBox.exec();
        } else {
            //вектор площадей, которые потенциально можно удалить
            AreaVector(s,point);
            //удаление площадей
            for (int i = 0; i < delnumber; i++) {
                Delete(DevArea,point,s,dels);
            }
        QFile fileOut(modifiedWay);
               if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
                   QTextStream writeStream(&fileOut);
                   for (int i = 0; i < point.size(); i++) {
                       writeStream << QString::number(point[i].x)<<" "<<QString::number(point[i].y)<<"\n";
                   }
                   fileOut.close();
               }
               way=modifiedWay;
               point.clear();
               s.clear();
               on_pushButton_clicked();
    }
}

void MainWindow::on_pushButton_3_clicked(const int delnumber)
{
            AreaVector(s1,point1);
            for (int i = 0; i < delnumber; i++) {
                Delete1(DevArea,point1,s1,dels1);
            }
            s1.clear();
}

void MainWindow::on_pushButton_4_clicked()
{
        double coordx=ui->lineEdit_2->text().toDouble();
        double coordy=ui->lineEdit_3->text().toDouble();
        int position=ui->lineEdit_4->text().toInt();
        Point p(coordx,coordy);
        point.insert(point.begin()+position,p);
        Point pa(coordx,coordy);
        padd.push_back(pa);
        QFile fileOut(savedWay);
               if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
                   QTextStream writeStream(&fileOut);
                   for (int i = 0; i < point.size(); i++) {
                       writeStream << QString::number(point[i].x)<<" "<<QString::number(point[i].y)<<"\n";
                   }
                   fileOut.close();
               }
               point.clear();
               s.clear();
               way=savedWay;
               on_pushButton_clicked();
               on_pushButton_7_clicked();
               on_pushButton_7_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    OpenFile(psaved,savedWay);
     delnum=psaved.size()-point.size()-1;
     if (point.size()==psaved.size())
     {
         psaved.clear();
         point.clear();
         s.clear();
         way=savedWay;
         delnum=-1;
         on_pushButton_clicked();
         QMessageBox msgBox;
         msgBox.setText("Nothing to cancel");
         msgBox.exec();
     } else {
     psaved.clear();
     point.clear();
     s.clear();
     way=savedWay;
     on_pushButton_clicked();
     on_pushButton_3_clicked();
     delnum=-1;
     }
}

void MainWindow::on_pushButton_6_clicked()
{
    int position=ui->lineEdit_5->text().toInt();
    if(QString::number(position)==" ")
    {
        QMessageBox msgBox;
        msgBox.setText("Enter position");
        msgBox.exec();
    } else {
    point.erase(point.begin()+position);
    QFile fileOut(savedWay);
           if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
               QTextStream writeStream(&fileOut);
               for (int i = 0; i < point.size(); i++) {
                   writeStream << QString::number(point[i].x)<<" "<<QString::number(point[i].y)<<"\n";
               }
               fileOut.close();
           }
           point.clear();
           s.clear();
           on_pushButton_clicked();
           on_pushButton_7_clicked();
           on_pushButton_7_clicked();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QGraphicsScene *scenewithgraph = new QGraphicsScene(ui->graphicsView_2);
    QPen pen(Qt::blue);
    QPen pen2(Qt::green);
    QPen pen3(Qt::cyan);
    pen3.setWidth(3);
    scenewithgraph->addLine(0,0,320,0,pen);
    scenewithgraph->addLine(0,0,0,-200,pen);
    ui->graphicsView_3->setScene(scenewithgraph);
    double dn=320/point1.size();
    double divn=point1.size()/20;
    for (int i = 1;i < (point1.size()+1)/(divn+1); i++) {
       scenewithgraph->addLine(i*(dn*(divn+1)),-3,i*(dn*(divn+1)),3,pen);
    }
    QString str;
    for (int i = 0;i < (point1.size()+1)/(divn+1); i++) {
       str=QString::number(i*(divn+1));
       QGraphicsTextItem *text = scenewithgraph->addText(str);
       text->setPos(i*(divn+1)*dn-6, 5);
    }
     a.push_back(DeviationArea(point1));
     int n=point1.size();
    for (int i = 0;i < n-2; i++) {
        on_pushButton_3_clicked(1);
        a.push_back(DeviationArea(point1));
    }
    double maxdeva=0;
    for (int i = 0;i < a.size(); i++) {
        if(a[i]>maxdeva){
            maxdeva=a[i];
        }
    }
    double da=200/maxdeva;
    QGraphicsTextItem *text1;
    scenewithgraph->addEllipse(2*dn,0,3,3, pen3);
    //scenewithgraph->addLine(2*dn,0,3*dn,-a[a.size()-1]*da,pen2);
    //scenewithgraph->addEllipse(3*dn-2.5,-a[a.size()-1]*da-2.5,3,3, pen3);
    text1 = scenewithgraph->addText(QString::number(maxdeva));
    text1->setPos(-50,-maxdeva*da-10);
    text1 = scenewithgraph->addText("N");
    text1->setPos(310,20);
    for (int i = 0;i < a.size()-1; i++) {
        scenewithgraph->addLine((i+2)*dn,-a[a.size()-1-i]*da,(i+3)*dn,-a[a.size()-2-i]*da,pen2);
        scenewithgraph->addEllipse((i+3)*dn-2.5,-a[a.size()-2-i]*da-2.5,3,3, pen3);
    }
    point1.clear();
    a.clear();
    s1.clear();
    dels1.clear();
    OpenFile(point1,savedWay);
}
