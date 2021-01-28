#ifndef COORDPAIR_H
#define COORDPAIR_H

struct CoordPair {
    double x = 0;
    double y = 0;
    CoordPair(double x, double y) {
        this->x = x;
        this->y = y;
    }
    double get(char coord) const {
        if (coord == 'x') return x;
        else if (coord == 'y') return y;
        else return -1;
    }

    void set(char coord, int value) {
        if (coord == 'x') this->x = value;
        else if (coord == 'y') this->y = value;
    }
};

#endif // COORDPAIR_H
