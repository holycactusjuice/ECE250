#include <iostream>
#include <cmath>
#include "PotentialField.h"

PotentialField::PotentialField(int w, int h) : width(w), height(h), K(1.0)
{
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
}

PotentialField::~PotentialField()
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

bool PotentialField::isValidPosition(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

void PotentialField::addPoint(char type, int x, int y)
{
    if (!isValidPosition(x, y))
    {
        std::cout << "failure" << std::endl;
        return;
    }
    grid[y][x][1] =
}

void update(double K)
{
    if (K <= 0)
    {
        std::cout << "failure" << std::endl;
        return
    }
    K = K
}