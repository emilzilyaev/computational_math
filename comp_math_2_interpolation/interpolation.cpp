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
    double max_x = *std::max_element(x.begin(), x.end());

    double step_size = (max_x-0.000000000001)/ 101.0;
    float w, lagrangePolynomial;
    QVector<double> x_output(101), y_output(101);

    for (int x_point=1; x_point<102; x_point++) {
        x_output[x_point-1] = 0.000000000001 + x_point*step_size;
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
    }

    qDebug() << x_output[10] << y_output[10];
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

    double max_x = *std::max_element(x.begin(), x.end());
    double step_size = (max_x-0.000000000001)/ 51.0;

    QVector<double> x_output(51), y_output(51);
    double differences[x.size()][x.size()];

    for (int i = 0; i < x.size(); i++) {
        differences[i][0] = y[i];
        qDebug() << differences[i][0];
    }

    for (int i = 1; i < x.size(); i++) {
        for (int k = 0; k < x.size() - i; k++) {
            differences[k][i] = differences[k + 1][i - 1] - differences[k][i - 1];
        }
    }

    for (int x_point=1; x_point<52; x_point++) {

        x_output[x_point-1] = 0.000000000001 + x_point*step_size;
        x_output[x_point-1] = x_point*step_size;


        float sum = differences[0][0];
        float u = (x_output[x_point-1] - x[0]) / (x[1] - x[0]);
        for (int i = 1; i < x.size(); i++) {
            sum = sum + (u_cal(u, i) * differences[0][i]) /
                                             fact(i);
        }

        y_output[x_point-1] = sum;
    }

    qDebug() << x_output[10] << y_output[10];
    return {x_output, y_output};

}
