#ifndef POTENTIAL_FIELD_H
#define POTENTIAL_FIELD_H

class PotentialField {
   private:
    int width, height;
    double ***grid;
    double K;

   public:
    // constructor
    PotentialField();

    // destructor;
    ~PotentialField();

    void deleteGrid();

    void create(int w, int h);

    void addPoint(char type, int x, int y);

    void move(int x, int y);

    void clear();

    void recomputePotential(int x, int y, int xO, int yO, char type);

    void updateK(double newK);

    bool isValidPosition(int x, int y);
};

#endif