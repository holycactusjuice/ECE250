#ifndef POTENTIAL_FIELD_H
#define POTENTIAL_FIELD_H

class PotentialField {
   private:
    // static constants to reprsent goals and obstacles
    static const double GOAL_TYPE, OBSTACLE_TYPE;

    // dimensions of grid
    int width, height;
    // 3D array to represent the map
    double ***grid;
    // constant used for potential calculations
    double K;

    // helper functions that don't need to be accessed
    // outside of the scope of the class

    // deallocates the grid
    void deleteGrid();
    // checks if a pair of coordinates is within the grid
    bool isValidPosition(int x, int y);
    // recomputes the potential for a grid cell given a newly placed object
    void recomputePotential(int x, int y, int xO, int yO, char type);

   public:
    // trivial constructor
    PotentialField();

    // destructor;
    ~PotentialField();

    // initialize values of PotentialField object
    void create(int w, int h);

    // add goal or obstacle to field at given coordinates
    void point(char type, int x, int y);

    // prints the potential at the given coordinates
    void move(int x, int y);

    // sets all values in grid to 0.0
    void clear();

    // updates value of K
    void update(double newK);
};

#endif