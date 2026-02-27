#ifndef FIELD_H
#define FIELD_H

#include "point.h"
#include <vector>

class Field {
private:
    int size = 20;
    std::vector<unsigned char> field;


public:
    static int byteCount(int ind);
    static int numInByte(int column);
    static bool isBitSet(unsigned char byte, int pos);
    static void enableBit(unsigned char &byte, int pos);
    static void disableBit(unsigned char &chank, int pos);
    static int normalize(int coord, int size);
    Field();
    Field(std::vector<Point> coordinates);
    int getSize() const;
    bool getState(int row, int column) const;
    void setState(int row, int column, bool value);
};

#endif // FIELD_H
