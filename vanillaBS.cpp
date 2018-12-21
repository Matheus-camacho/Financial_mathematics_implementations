#include "Random1.h"
#include <iostream>
#include <cmath>
using namespace std;

double monteCarlo1(double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths)
{
    double variance=Vol*Vol*Expiry;
    double rootVariance=sqrt(variance);
    double itoCorrection=-0.5*variance;

    double movedSpot = Spot*exp(r*Expiry+itoCorrection);
    double thisSpot;
    double runningSum=0;

    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot*exp(rootVariance*thisGaussian);
        double thisPayoff = thisSpot-Strike;
        thisPayoff = thisPayoff >0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }
    
    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r*Expiry);
    return mean;
}

int main(int argc, char const *argv[])
{
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    cout << "\nEnter expity\n";
    cin >> Expiry;
    cout << "\nEnter strike\n";
    cin >> Strike;
    cout << "\nEnter spot\n";
    cin >> Spot;
    cout << "\nEnter volatily\n";
    cin >> Vol;
    cout << "\nEnter r\n";
    cin >> r;
    cout << "\nNumber of Paths\n";
    cin >> NumberOfPaths;

    double result = monteCarlo1(Expiry, Strike, Spot, Vol, r, NumberOfPaths);

    cout << "The price is" << result << "\n";

    double tmp;
    cin >> tmp;

    return 0;
}
