#ifndef DOTPAIRSUPLOAD_H
#define DOTPAIRSUPLOAD_H

#include <QObject>


class DotPairsUpload : public QObject
{
public:
    DotPairsUpload();
    void uploadDotPairs(double a, double b, int n);
};

#endif // DOTPAIRSUPLOAD_H
