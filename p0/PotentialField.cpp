#include "PotentialField.h"

#include <cmath>
#include <iostream>

const double PotentialField::GOAL_TYPE = 1.0;
const double PotentialField::OBSTACLE_TYPE = 2.0;

PotentialField::PotentialField()
    : width(0.0), height(0.0), K(0.0), grid(nullptr) {}

PotentialField::~PotentialField() { deleteGrid(); }

void PotentialField::deleteGrid()
{
    // iterate through each row
    for (int i = 0; i < height; i++)
    {
        // iterate through each pair in row
        for (int j = 0; j < width; j++)
        {
            // deallocate innermost array
            delete[] grid[i][j];
        }
        // deallocate row array
        delete[] grid[i];
    }
    // deallocate outermost array
    delete[] grid;
}

void PotentialField::create(int w, int h)
{
    // if a grid already exists, we have to delete it first
    if (grid != nullptr)
        deleteGrid();

    // set dimensions
    width = w;
    height = h;

    // set K
    K = 1.0;

    // allocate height
    grid = new double **[height];
    // iterate through height to allocate width
    for (int i = 0; i < height; i++)
    {
        grid[i] = new double *[width];
        // iterate through width to allocate arrays of size 2
        for (int j = 0; j < width; j++)
        {
            // initialize with values of 0
            grid[i][j] = new double[2]{0.0, 0.0};
        }
    }

    std::cout << "success" << std::endl;

    return;
}

void PotentialField::point(char type, int xG, int yG)
{
    // check if coordinates are valid
    if (!isValidPosition(xG, yG))
    {
        std::cout << "failure" << std::endl;
        return;
    }

    // if the point that we are trying to place is
    // already there, return
    if ((type == 'O' && grid[yG][xG][1] == OBSTACLE_TYPE) ||
        (type == 'G' && grid[yG][xG][1] == GOAL_TYPE))
    {
        std::cout << "success" << std::endl;
        return;
    }

    // iterate through each cell and update the potential
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // skip if the cell in which the new object is being placed
            if (xG == j && yG == i)
                continue;
            recomputePotential(j, i, xG, yG, type);
        }
    }

    // update object type at the given coordinates
    switch (type)
    {
    case 'O':
        grid[yG][xG][1] = OBSTACLE_TYPE;
        break;
    case 'G':
        grid[yG][xG][1] = GOAL_TYPE;
        break;
    }

    std::cout << "success" << std::endl;

    return;
}

void PotentialField::move(int x, int y)
{
    // check if coordinates are valid
    if (!isValidPosition(x, y))
    {
        std::cout << "failure" << std::endl;
        return;
    }
    // get potential at given coordinates
    double potential = grid[y][x][0];

    // print potential (twice)
    std::cout << potential << " " << potential << std::endl;

    return;
}

void PotentialField::clear()
{
    // grid must already be initialized to call this function
    if (grid == nullptr)
    {
        std::cout << "failure" << std::endl;
        return;
    }
    // iterate through grid and set all values to 0.0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j][0] = 0.0;
            grid[i][j][1] = 0.0;
        }
    }

    std::cout << "success" << std::endl;

    return;
}

void PotentialField::update(double newK)
{
    // newK must be a positive value
    if (newK <= 0)
    {
        std::cout << "failure" << std::endl;
        return;
    }

    // all potentials must be updated by dividing by
    // oldK and multiplying by newK
    double ratio = newK / K;

    // iterate through array and multiply all potentials by newK / oldK
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j][0] *= ratio;
        }
    }

    // update K
    K = newK;

    std::cout << "success" << std::endl;

    return;
}

bool PotentialField::isValidPosition(int x, int y)
{
    // return true if x and y are both with the dimensions of grid
    return x >= 0 && x < width && y >= 0 && y < height;
}

void PotentialField::recomputePotential(int x, int y, int xG, int yG,
                                        char type)
{
    // x and y are coordinates for the cell to be updated
    // xG and yG are coordinates for the newly placed goal or obstacle

    double sign = (type == 'O') ? 1.0 : -1.0;

    double P = sign * K / (sqrt(pow(x - xG, 2) + pow(y - yG, 2)));

    // if object in cell is opposite of object being added,
    // e.g. cell has obstacle and we are adding goal,
    // we need to double the potential being added
    // to cancel out the potential from the original object
    if ((grid[yG][xG][1] == GOAL_TYPE && type == 'O') ||
        (grid[yG][xG][1] == OBSTACLE_TYPE && type == 'G'))
    {
        P *= 2.0;
    }

    // add potential due to new object at given coordinates
    grid[y][x][0] += P;

    return;
}
