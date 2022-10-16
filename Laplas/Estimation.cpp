#include "Estimation.h"
#include "GeneralLaplaceDistribution.h"

#include <algorithm>
#include <cmath>
#include <iostream>


double Estimation::mean(const std::vector<double>& rand)
{
    double sum = 0;
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += rand[i];
    }
    return sum / rand.size();
}

double Estimation::median(std::vector<double> rand)
{
    size_t n = rand.size() / 2;
    std::nth_element(rand.begin(), rand.begin() + n, rand.end());
    return rand[n];
}

double Estimation::variance(const std::vector<double>& rand)
{
    double sum = 0;
    double meanRand = mean(rand);
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += pow(rand[i] - meanRand, 2);
    }
    return sum / rand.size();
}

double Estimation::skewness(const std::vector<double>& rand)
{
    double sum = 0;
    double meanRand = mean(rand);
    double varianceRand = variance(rand);
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += pow(rand[i] - meanRand, 3);
    }

    return sum / (rand.size() * sqrt(pow(varianceRand, 3)));
}

double Estimation::kurtosis(const std::vector<double>& rand)
{
    double sum = 0;
    double meanRand = mean(rand);
    double varianceRand = variance(rand);
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += pow(rand[i] - meanRand, 4);
    }

    return sum / (rand.size() * pow(varianceRand, 2));
}

double Estimation::truncatedMean(double perc, std::vector<double> rand)
{
    std::sort(rand.begin(), rand.end());
    double sum = 0;
    size_t offset = rand.size() * perc / 2;
    for (size_t i = offset; i < rand.size() - offset; i++)
    {
        sum += rand[i];
    }
    return sum / (rand.size() - offset * 2);
}

double Estimation::LSE(double estimation, const std::vector<double>& rand, double lambda, const GeneralLaplaceDistribution& laplace)
{
    double epsilon = 0.00001;
    double delta = 1;
    double a = estimation - 5 * delta,
        b = estimation + 5 * delta,
        x1 = (a + b) / 2 - delta,
        x2 = (a + b) / 2 + delta;
    while (b - a > epsilon)
    {
        if (LSEM(x1, rand, lambda, laplace) > LSEM(x2, rand, lambda, laplace))
        {
            a = x1;
            delta = (b - a) / 10;
            x1 = (a + b) / 2 - delta;
            x2 = (a + b) / 2 + delta;
        }
        else
        {
            b = x2;
            delta = (b - a) / 10;
            x1 = (a + b) / 2 - delta;
            x2 = (a + b) / 2 + delta;
        }
    }

    return (a + b) / 2;
}

double Estimation::LSEM(double theta, const std::vector<double>& rand, double lambda, const GeneralLaplaceDistribution& laplace)
{
    double sum = 0;
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += LSELoss(rand[i], theta, lambda, laplace);
    }
    return sum;
}

double Estimation::LSELoss(double y, double theta, double lambda, const GeneralLaplaceDistribution &laplace)
{
    return -log(laplace.density((y - theta) / lambda));
}

double Estimation::minGamma(double deltaIn, double estimation, const std::vector<double>& rand, double lambda, const GeneralLaplaceDistribution& laplace)
{
    double epsilon = 0.00001;
    double delta = 1;
    double a = estimation - 5 * delta,
        b = estimation + 5 * delta,
        x1 = (a + b) / 2 - delta,
        x2 = (a + b) / 2 + delta;
    while (b - a > epsilon)
    {
        if (minGammaM(x1, deltaIn, rand, lambda, laplace) > minGammaM(x2, deltaIn, rand, lambda, laplace))
        {
            a = x1;
            delta = (b - a) / 10;
            x1 = (a + b) / 2 - delta;
            x2 = (a + b) / 2 + delta;
        }
        else
        {
            b = x2;
            delta = (b - a) / 10;
            x1 = (a + b) / 2 - delta;
            x2 = (a + b) / 2 + delta;
        }
    }

    return (a + b) / 2;
}

double Estimation::minGammaM(double theta, double delta, const std::vector<double>& rand, double lambda, const GeneralLaplaceDistribution& laplace)
{
    double sum = 0;
    for (size_t i = 0; i < rand.size(); i++)
    {
        sum += minGammaLoss(delta, rand[i], theta, lambda, laplace);
    }
    return sum;
}

double Estimation::minGammaLoss(double delta, double y, double theta, double lambda, const GeneralLaplaceDistribution& laplace)
{
    return -(1 / pow(laplace.density(0), delta)) * pow(laplace.density((y - theta) / lambda), delta);
}