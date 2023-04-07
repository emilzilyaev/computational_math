#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dotpairsupload.h"
#include "interpolation.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(QVector<double>& x, QVector<double>& y, QVector<double>& x_points, QVector<double>& y_points)
{
    double min_x = *std::min_element(x.begin(), x.end());
    double max_x = *std::max_element(x.begin(), x.end());
    double min_y = *std::min_element(y.begin(), y.end());
    double max_y = *std::max_element(y.begin(), y.end());

    qDebug() << min_x << max_x << min_y << max_y;

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setRange(min_x, max_x);
    ui->customPlot->yAxis->setRange(min_y, max_y);


    QCPGraph* dwPoints = new QCPGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    dwPoints->setAdaptiveSampling(false);
    dwPoints->setLineStyle(QCPGraph::lsNone);
    dwPoints->setScatterStyle(QCPScatterStyle::ssCircle);
    dwPoints->setPen(QPen(QBrush(Qt::red), 2));

    for (int x_=0; x_<x_points.size(); x_++) {
         dwPoints->addData(x_points[x_], y_points[x_]);
    }

    ui->customPlot->replot();
}


void MainWindow::on_pushButton_pressed()
{
    bool inputCanBeProcessed = true;
    double a;
    double b;
    int n;

    if (ui->lineEdit->text().isEmpty()) inputCanBeProcessed=false;
    if (ui->lineEdit_2->text().isEmpty()) inputCanBeProcessed=false;
    if (ui->lineEdit_3->text().isEmpty()) inputCanBeProcessed=false;


    if (inputCanBeProcessed == true) {
        if (ui->lineEdit->text() == "0.0") {
            a = 0.0;
        } else if (ui->lineEdit->text().toDouble() == 0.0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Неправильный формат ввода. Поддерживаются только числа в диапазоне от -1,7*10^308 до 1,7*10^308");
            inputCanBeProcessed = false;
        } else {
            a = ui->lineEdit->text().toDouble();
        }

        if (ui->lineEdit_2->text() == "0.0") {
            b = 0.0;
        } else if (ui->lineEdit_2->text().toDouble() == 0.0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Неправильный формат ввода. Поддерживаются только числа в диапазоне от -1,7*10^308 до 1,7*10^308");
            inputCanBeProcessed = false;
        } else {
            b = ui->lineEdit_2->text().toDouble();
        }

        if (ui->lineEdit_3->text() == "0.0") {
            n = 0.0;
        } else if (ui->lineEdit_3->text().toInt()  == 0.0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Неправильный формат ввода для n. Поддерживаются только числа в диапазоне от -2147483648 до 2147483647");
            inputCanBeProcessed = false;
        } else {
            n = ui->lineEdit_3->text().toInt();
        }

        if (n <= 0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Кол-во точек n не может быть меньше или равно нулю");
            inputCanBeProcessed = false;
        }

        if (a >= b) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Правая граница b не может быть меньше или равна левой границе a");
            inputCanBeProcessed = false;
        }

        if (a<=0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Левая граница a должна быть строго больше нуля");
            inputCanBeProcessed = false;
        }

        if (inputCanBeProcessed==true) {
            ui->statusbar->setStyleSheet("background-color: rgb(0, 0, 0);");
            ui->statusbar->showMessage("Сохранение n пар точек в файл");

            DotPairsUpload uploadPairs;
            uploadPairs.uploadDotPairs(a, b, n);

        }
    }
    else {
        ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
        ui->statusbar->showMessage("Необходимо ввести значения a,b и n");
    }
}


void MainWindow::on_pushButton_2_pressed()
{
    bool lagrange = false;
    bool newton = false;
    bool inputCanBeProcessed = true;
    int m;
    int leng;

    if (ui->radioButton->isChecked()) {
        ui->statusbar->setStyleSheet("background-color: rgb(0, 0, 0);");
        ui->statusbar->showMessage("Интерполирование полиномом Лагранжа");
        lagrange = true;
    } else if (ui->radioButton_2->isChecked()) {
        ui->statusbar->setStyleSheet("background-color: rgb(0, 0, 0);");
        ui->statusbar->showMessage("Интерполирование полиномом Ньютона");
        newton = true;
    } else {
        ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
        ui->statusbar->showMessage("Требуется выбрать метод интерполирования");
        inputCanBeProcessed = false;
    }

    if (ui->lineEdit_4->text().isEmpty()) inputCanBeProcessed=false;

    if (inputCanBeProcessed == true) {
        if (ui->lineEdit_4->text() == "0.0") {
            m = 0.0;
        } else if (ui->lineEdit_4->text().toInt() == 0.0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Неправильный формат ввода для m. Поддерживаются только числа в диапазоне от -2147483648 до 2147483647");
            inputCanBeProcessed = false;
        } else {
            m = ui->lineEdit_4->text().toInt();
        }

        if (m <= 0) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Порядок полинома не может быть меньше или равен нулю");
            inputCanBeProcessed = false;
        }

        QVector<double> x_PointsSelected(0), y_PointsSelected(0);
        QFile file("/Users/emilzilyaev/Desktop/n_points.txt");
        int leng;

        if(!file.open(QIODevice::ReadOnly)) {
            ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->statusbar->showMessage("Возникла ошибка при чтении из файла");
            inputCanBeProcessed = false;
        }
        else{
            QTextStream in(&file);
            while(!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(" ");
                x_PointsSelected.append(fields[0].toDouble());
                y_PointsSelected.append(fields[1].toDouble());
            }
            file.close();
        }

        leng = x_PointsSelected.size();

        if (inputCanBeProcessed == true) {
            /*if (m==1) {
                ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
                ui->statusbar->showMessage("Порядок m должен быть больше единицы");
                inputCanBeProcessed = false;
            } else*/
            if (m < leng) {
                for(int i=leng-1; i>m; i--){
                        x_PointsSelected.remove(i);
                        y_PointsSelected.remove(i);
                }
            }
            else {
                ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
                ui->statusbar->showMessage("Порядок m не может быть больше или равен кол-ву пар точек в файле");
                inputCanBeProcessed = false;
            }
        }
        if (inputCanBeProcessed == true) {
//            QVector<double> x_out(1001), y_out(1001);
            Interpolation interp;
            if (lagrange==true) {
                auto [x_out, y_out] = interp.lagrangeInterpolation(x_PointsSelected, y_PointsSelected);
//                for (int x_=0; x_<x_out.size(); x_++) {
//                    qDebug() << x_out[x_] << y_out[x_];
//                }

                MainWindow::makePlot(x_out, y_out, x_PointsSelected, y_PointsSelected);
            }
            else {
                auto [x_out, y_out] = interp.newtonInterpolation(x_PointsSelected, y_PointsSelected);
//                for (int x_=0; x_<x_out.size(); x_++) {
//                    qDebug() << x_out[x_] << y_out[x_];
//                }

                MainWindow::makePlot(x_out, y_out, x_PointsSelected, y_PointsSelected);
            }
        }
    }
    else {
        ui->statusbar->setStyleSheet("background-color: rgb(255, 0, 0);");
        ui->statusbar->showMessage("Необходимо ввести значение m");
    }
}

