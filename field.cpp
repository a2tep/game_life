#include "field.h"
#include <stdexcept>

//сколько байт для n клеток

int Field::byteCount(int ind) {
    if (ind==0) {
        return 1;
    }
    if (ind %8!=0) {
        return (ind/8)+1;
    }else {
        return ind/8;
    }
}
//внутри байта
int Field::numInByte(int column) {
    if (column < 8) {
        return column;
    }
    if (column % 8 == 0) {
        return 0;
    } else {
        return column % 8;
    }
}
//проверяем 0/1
bool Field::isBitSet(unsigned char byte, int pos) {
    return static_cast<bool>((1 << (7 - pos)) & byte);
}
//ставим туда 1
void Field::enableBit(unsigned char &byte, int pos) {
    byte |= (1 << (7 - pos));
}
// ставим 0
void Field::disableBit(unsigned char &chank, int pos) {
    chank &= ~(1 << (7 - pos));
}
//выход за границу поля
int Field::normalize(int coord, int size) {
    int k = coord / size;
    k -= coord < (-1) * size ? 1 : 0;
    if (coord >= 0 || coord < (-1) * size) {
        coord -= k * size;
    } else {
        coord += size;
    }
    return coord;
}

Field::Field() {
    field.resize(size * byteCount(size), 0);//все биты 0
}

Field::Field(std::vector<Point> coords) {
    field.resize(size * byteCount(size), 0);
    for (auto& i: coords) {
        i.x = normalize(i.x, size);
        i.y = normalize(i.y, size);
        int num_chank = i.x * byteCount(size) + byteCount(i.y);
        int pos = numInByte(i.y);
        if (i.y % 8 == 0 && i.y != 0) {
            num_chank += 0;
        } else {
            num_chank += -1;
        }
        if (isBitSet(field[num_chank], pos)) {
            throw std::invalid_argument("error");
        } else {
            enableBit(field[num_chank], pos);
        }
    }
}

int Field::getSize() const {
    return size;
}
//живая мертвая
bool Field::getState(int row, int column) const{
    row = normalize(row, size);
    column = normalize(column, size);
    int num_chank = row * byteCount(size) + byteCount(column);
    int pos = numInByte(column);
    num_chank += column % 8 == 0 && column != 0? 0: -1;
    return isBitSet(field[num_chank], pos);
}
//устанавливаем состояние
void Field::setState(int row, int column, bool value) {
    row = normalize(row, size);
    column = normalize(column, size);
    int num_chank = row * byteCount(size) + byteCount(column);
    int pos = numInByte(column);
    num_chank += column % 8 == 0 && column != 0? 0: -1;
    if (value) {
        enableBit(field[num_chank], pos);
    } else {
        disableBit(field[num_chank], pos);
    }
}
