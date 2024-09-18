#ifndef POTENTIAL_FIELD_H
#define POTENTIAL_FIELD_H

class Vector2D
{
public:
    double x, y;
    Vector2D(double x, double y);
};

class PotentialField
{
private:
    double ***grid;
    int width, height;
    double K;

public:
    // constructor
    PotentialField(int w, int h);

    // destructor;
    ~PotentialField();

    void addPoint(char type, int x, int y);

    Vector2D getPotential(int x, int y);

    void clear();

    void update(double K);

    bool isValidPosition(int x, int y);
};

#endif