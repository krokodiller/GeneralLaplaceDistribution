#pragma once
class GeneralLaplaceDistribution
{
public:
    GeneralLaplaceDistribution();
    GeneralLaplaceDistribution(int);
    double density(double) const;

    double randomValue(double, double) const;
    double distortedRandomValue(double, double, double, double, double) const;

private:
    int factorial(int) const;

    int n;
};

