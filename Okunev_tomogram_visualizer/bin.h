#ifndef BIN_H
#define BIN_H
#include <QString>

class Bin
{
public:
    static int X, Y, Z;
    static short* array;
    Bin();
    static void readBIN(QString path);
};

#endif // BIN_H
