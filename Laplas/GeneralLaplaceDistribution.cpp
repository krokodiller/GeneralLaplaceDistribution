#include "GeneralLaplaceDistribution.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

GeneralLaplaceDistribution::GeneralLaplaceDistribution() : n(1)
{
    srand(time(0));
}
GeneralLaplaceDistribution::GeneralLaplaceDistribution(int n) : n(n)
{
    srand(time(0));
}

double GeneralLaplaceDistribution::density(double x) const
{
    double returnValue, sum = 0;
    if (n > 1)
    {
        for (size_t j = 0; j <= n - 1; j++)
        {
            sum += (factorial(n - 1 + j) / (factorial(n - 1 - j) * factorial(j))) * ((pow(fabs(x), n - 1 - j)) / pow(2, j));
        }
    }
    else
    {
        sum = 1;
    }


    returnValue = exp(-fabs(x)) / (factorial(n - 1) * pow(2, n)) * sum;
    return returnValue;
}

double GeneralLaplaceDistribution::randomValue(double theta, double lambda) const
{
    double returnValue;
    do
    {
        double firstProduct = 1,
            secondProduct = 1;

        for (size_t i = 0; i < n; i++)
        {
            double r = (double)rand() / RAND_MAX;
            if (r <= 0.5)
            {
                firstProduct *= 2 * r;
            }
            else
            {
                secondProduct *= 2 * (1 - r);
            }
        }

        returnValue =  log(firstProduct / secondProduct) * lambda + theta;
    } while (!std::isfinite(returnValue));
    
    return returnValue;

}

double GeneralLaplaceDistribution::distortedRandomValue(double perc, double theta, double lambda, double distTheta, double distLambda) const
{
    double returnValue;
    do
    {
        double firstProduct = 1,
            secondProduct = 1;

        for (size_t i = 0; i < n; i++)
        {
            double r = (double)rand() / RAND_MAX;

            if (r <= 0.5)
            {
                firstProduct *= 2 * r;
            }
            else
            {
                secondProduct *= 2 * (1 - r);
            }
        }

        if ((double)rand() / RAND_MAX < perc)
        {
            returnValue = log(firstProduct / secondProduct) * distLambda + distTheta;
        }
        else
        {
            returnValue = log(firstProduct / secondProduct) * lambda + theta;
        }

    } while (!std::isfinite(returnValue));

    return returnValue;
}

int GeneralLaplaceDistribution::factorial(int n) const
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}