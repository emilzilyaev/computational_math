#include <QFile>
#include <QTextStream>
#include "QtCore/qdebug.h"
#include <QtDebug>
#include <QWidget>

#include "interpolation.h"
#include "math.h"
//#include<bits/stdc++.h>

using namespace std;

Interpolation::Interpolation()
{

}
auto Interpolation::lagrangeInterpolation(QVector<double>& x, QVector<double>& y) -> std::tuple<QVector<double>, QVector<double>> {
    QVector<double> x_output(1001), y_output(1001);
    double max_x = *std::max_element(x.begin(), x.end());
    double step_size = max_x/ 1001.0;
    float w, lagrangePolynomial;

    for (int x_point=1; x_point<1002; x_point++) {
        x_output[x_point-1] = x_point*step_size;
        lagrangePolynomial = 0.0;
        for(int i=0; i<x.size(); i++){
            w = 1.0;
            for (int j=0; j<x.size(); j++) {
                if (j!=i) {
                    w = w*((x_output[x_point-1] - x[j])/(x[i]-x[j]));                }
            }
            lagrangePolynomial = lagrangePolynomial + w*y[i];
        }
        if (lagrangePolynomial != 0.0) {
            y_output[x_point-1] = lagrangePolynomial;
        }
//        qDebug() << x_output[x_point-1]  << y_output[x_point-1];
    }

//    qDebug() << x_output[0] << y_output[0];
    return {x_output, y_output};
}

float Interpolation::u_cal(float u, int n)
{
    float temp = u;
    for (int i = 1; i < n; i++)
        temp = temp * (u - i);
    return temp;
}

int Interpolation::fact(int n)
{
    int f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

auto Interpolation::newtonInterpolation(QVector<double>& x, QVector<double>& y) -> std::tuple<QVector<double>, QVector<double>> {

    QVector<double> x_output(1001), y_output(1001);
    double max_x = *std::max_element(x.begin(), x.end());
    double step_size = max_x/ 1001.0;

    double differences[x.size()][x.size()];

    for (int i = 1; i < x.size(); i++) {
        differences[i][0] = y[i];
    }

    for (int i = 1; i < x.size(); i++) {
        for (int j = 0; j < x.size() - i; j++)
            differences[j][i] = differences[j + 1][i - 1] - differences[j][i - 1];
    }

    for (int x_point=1; x_point<1002; x_point++) {

        x_output[x_point-1] = x_point*step_size;

        float sum = differences[0][0];
        float u = (x_output[x_point-1] - x[0]) / (x[1] - x[0]);
        for (int i = 1; i < x.size(); i++) {
            sum = sum + (u_cal(u, i) * differences[0][i]) /
                                     fact(i);
        }

        y_output[x_point-1] = sum;
    }

//    qDebug() << x_output[100] << y_output[100];
    return {x_output, y_output};
}
