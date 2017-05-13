#include "bin.h"
#include <QFileInfo>

int Bin::X;
int Bin::Y;
int Bin::Z;
short* Bin::array;


Bin::Bin()
{

}

void Bin::readBIN(QString path)
{
    QFileInfo File = path;
    if (File.exists() && File.isFile())
    {
        QFile pStream(path);                //QFile pStream;
        pStream.open(QIODevice::ReadOnly);  // pStream.open(path, QIODevice::ReadOnly);
        pStream.read((char*)&X, sizeof(__int32));
        pStream.read((char*)&Y, sizeof(__int32));
        pStream.read((char*)&Z, sizeof(__int32));

        int arraySize = X * Y * Z;
        array = new short[arraySize];
        for (int i = 0; i < arraySize; ++i)
        {
           pStream.read((char*)&(array[i]), sizeof(__int16));
        }
        pStream.close();
    }
}
