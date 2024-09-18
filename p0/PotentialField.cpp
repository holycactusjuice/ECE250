#include "PotentialField.h"

#include <cmath>
#include <iostream>

PotentialField::PotentialField() : width(0.0), height(0.0), K(0.0), grid(nullptr) {}

PotentialField::~PotentialField()
{
    deleteGrid();
}

void PotentialField::deleteGrid()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            delete[] grid[i][j];
        }
        delete[] grid[i];
    }
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
            grid[i][j] = new double[2]{0x0, 0x0};
        }
    }

    std::cout << "success" << std::endl;

    return;
}

void PotentialField::addPoint(char type, int xG, int yG)
{
    // check if coordinates are valid
    if (!isValidPosition(xG, yG))
    {
        std::cout << "failure" << std::endl;
        return;
    }

    // if the point that we are trying to place is
    // already there, return
    if ((type == 'O' && grid[yG][xG][1] == 0x10) ||
        (type == 'G' && grid[yG][xG][1] == 0x01))
        return;

    // iterate through each cell and update the potential
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // skip if the cell is the goal cell
            if (xG == j && yG == i)
                continue;
            recomputePotential(j, i, xG, yG, type);
        }
    }

    // update object type at the given coordinates
    switch (type)
    {
    case 'O':
        grid[yG][xG][1] = 0x10;
        break;
    case 'G':
        grid[yG][xG][1] = 0x01;
        break;
    }

    std::cout << "success" << std::endl;

    return;
}

double PotentialField::getPotential(int x, int y)
{
    if (!isValidPosition(x, y))
    {
        std::cout << "failure" << std::endl;
        return -1;
    }
    double potential = grid[y][x][0];

    std::cout << potential << " " << potential << std::endl;

    return grid[y][x][0];
}

void PotentialField::clear()
{
    if (grid == nullptr)
    {
        std::cout << "failure" << std::endl;
        return;
    }
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

void PotentialField::updateK(double newK)
{
    if (newK <= 0)
    {
        std::cout << "failure" << std::endl;
        return;
    }
    double ratio = newK / K;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j][0] *= ratio;
        }
    }

    K = newK;

    std::cout << "success" << std::endl;

    return;
}

bool PotentialField::isValidPosition(int x, int y)
{
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
    if (grid[yG][xG][1] == 0x01 && type == 'G' || grid[yG][xG][1] == 0x10 && type == 'O')
    {
        P *= 2.0;
    }

    grid[y][x][0] += P;

    return;
}
