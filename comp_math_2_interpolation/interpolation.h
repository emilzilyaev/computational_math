#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QObject>


class Interpolation : public QObject
{
public:
    Interpolation();
    float u_cal(float u, int n);
    int fact(int n);
    auto lagrangeInterpolation(QVector<double>& x, QVector<double>& y) -> std::tuple<QVector<double>, QVector<double>>;
    auto newtonInterpolation(QVector<double>& x, QVector<double>& y) -> std::tuple<QVector<double>, QVector<double>>;

};
#endif // INTERPOLATION_H
