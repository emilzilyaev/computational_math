#include <QFile>
#include <QTextStream>

#include "dotpairsupload.h"
#include "QtCore/qdebug.h"

#include "math.h"

using namespace std;

DotPairsUpload::DotPairsUpload()
{

}

void DotPairsUpload::uploadDotPairs(double a, double b, int n)
{
//    qDebug() << a << b << n;
    double step_size = (b-a)/n;
    QVector<double> x(n), y(n);
    for (int i=1; i<n+1; ++i)
    {
      x[i-1] = a+i*step_size;
      y[i-1] = cos(2*x[i-1]) + x[i-1]*log(x[i-1]);
    }

    QString filename = "/Users/emilzilyaev/Desktop/n_points.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for (int i=0; i<n; ++i)
        {
          stream << x[i] << " " << y[i] << Qt::endl;
        }
    }
}
