// Write a C++ program to calculate the slope of a line
// that concects two given points p(x1,y1) and q(x2,y2)

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

// Stores coordinate information about p and q
struct coordinate { double x, y; };
// The DDA algorithm
int DDA(struct coordinate* coord1, struct coordinate* coord2);
// Bresenham's algorithm
int Bresenham(struct coordinate* c1, struct coordinate* c2);
// Outputs results
int outputResults(vector<int> xValues, vector<int> yValues);

int main() {

    // Creates 2 coordintes, p and q, with x and y values each
    coordinate p, q;

    // Gets the values of p and q
    cout << "Input coordinates of p: x, y, no commas in between:" << endl;
    cin >> p.x >> p.y;
    cout << "Input coordinates of q: x, y, no commas in between:" << endl;
    cin >> q.x >> q.y;

    cout << "The slope, m, between p and q is: " << ((p.y) - (q.y)) / ((p.x) - (q.x)) << endl;
    DDA(&p, &q);
    cout << endl;
    Bresenham(&p, &q);

    return 0;
}

int DDA(struct coordinate *c1, struct coordinate *c2) {
    // Sets the slope, m
    double m = ((c1->y) - (c2->y)) / ((c1->x) - (c2->x));

    // Determines if we're going L->R or R->L by using the location
    // of the x coordinates of p and q. If p.x-q.x is negative, we're
    // going L->R, if positive, we're going R->L.
    bool direction = false;
    if ((c1->x - c2->x) > 0) {
        // false = L->R and true = R->L
        direction = true;
    }

    // Follows the big if-else statement seen in the slides,
    // determining deltaX and deltaY.
    double deltaX, deltaY;
    if (direction == 0) {
        if (abs(m) <= 1) {
            deltaX = 1;
            deltaY = m;
        }
        else if (m >= 0) {
            deltaX = 1/m;
            deltaY = 1;
        }
        else {
            deltaX = -1/m;
            deltaY = -1;
        }
    }
    else {
        if (abs(m) <= 1) {
            deltaX = -1;
            deltaY = -m;
        }
        else if (m >= 0) {
            deltaX = -1/m;
            deltaY = -1;
        }
        else {
            deltaX = 1/m;
            deltaY = 1;
        }
    }

    // Creates the values for all the x's and y's along the line
    vector<int> xArray, yArray;
    int i = 0;
    if (abs(deltaX) == 1) {
        while (i <= abs(c1->x - c2->x)) {
            xArray.push_back(round(deltaX*i + c1->x));
            yArray.push_back(round(deltaY*i + c1->y));
            i++;
        }
    }
    else {
        while (i <= abs(c1->y - c2->y)) {
            xArray.push_back(round(deltaX*i + c1->x));
            yArray.push_back(round(deltaY*i + c1->y));
            i++;
        }
    }

    // Outputs results of the DDA algorithm
    cout << "DDA Algorithm Results:" << endl;
    outputResults(xArray, yArray);

    return 0;
}

int Bresenham(struct coordinate* c1, struct coordinate* c2) {
    // Sets the starting positions of x and y for the line to be drawn
    double xPos = c1->x, yPos = c1->y;
    // Sets deltaX and deltaY
    double deltaX = (c2->x) - (c1->x), deltaY = (c2->y - c1->y);

    // Creates places to store the values of x and y
    vector<int> xArray, yArray;
    // Plots the initial values of x and y
    xArray.push_back(xPos);
    yArray.push_back(yPos);

    // Sets p
    double p = (2 * deltaY) - deltaX;

    // Loops through the algorithm, deciding on the remaining values of x,y and drawing the line
    while (xPos < c2->x) {
        if (p < 0) {
            xPos = xPos + 1;
            xArray.push_back(xPos);
            yArray.push_back(yPos);
            p = p + (2 * deltaY);
        }
        else {
            xPos = xPos + 1;
            yPos = yPos + 1;
            xArray.push_back(xPos);
            yArray.push_back(yPos);
            p = p + (2 * deltaY) - (2 * deltaX);
        }
    }

    // Outputs results of the Bresenham algorithm
    cout << "Bresenham's Algorithm Results:" << endl;
    outputResults(xArray, yArray);

    return 0;
}

int outputResults(vector<int> xValues, vector<int> yValues) {
    cout << "(x , y)" << endl;
    for (int g = 0; g < xValues.size(); g++) {
        cout << "(" << xValues[g] << " , " << yValues[g] << ")" << endl;
    }

    return 0;
}