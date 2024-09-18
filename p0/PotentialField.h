#ifndef POTENTIAL_FIELD_H
#define POTENTIAL_FIELD_H

class PotentialField {
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

    double getPotential(int x, int y);

    void clear();

    void recomputePotential(int x, int y, int xO, int yO, char type);

    void updateK(double newK);

    bool isValidPosition(int x, int y);
};

#endif