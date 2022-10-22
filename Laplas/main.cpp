#include "GeneralLaplaceDistribution.h"
#include "Estimation.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#define LAPLACE_N 3
#define N_OF_RAND_VALUES 1000
#define PERC_OF_DIST_VALUES 0.4
#define THETA 0
#define LAMBDA 1
#define DIST_THETA 5
#define DIST_LAMBDA 1.1
#define TRUNC_MEAN_PERC 0.05
#define DELTA 0.5

int main()
{
    GeneralLaplaceDistribution laplace(LAPLACE_N);
    std::vector<double> random(N_OF_RAND_VALUES);
    std::vector<double> distortedRandom(N_OF_RAND_VALUES);

    std::ofstream out("density.txt", std::ofstream::out);
    for (double i = -10; i < 10; i += 0.01)
    {
        out << i << " " << laplace.density(i) << "\n";
    }
    out.close();

    out.open("distortionDensity.txt", std::ofstream::out);
    for (double i = -10; i < 10; i += 0.01)
    {
        out << i << " " << laplace.density(i, DIST_THETA, DIST_LAMBDA) << "\n";
    }
    out.close();

    out.open("random.txt", std::ofstream::out);
    for (size_t i = 0; i < N_OF_RAND_VALUES; i++)
    {
        random[i] = laplace.randomValue(THETA, LAMBDA);
        out << random[i] << "\n";
    }
    out.close();
    std::cout << "Theta: " << THETA << "\n";
    std::cout << "Lambda: " << LAMBDA << "\n";
    std::cout << "Number of random elements: " << N_OF_RAND_VALUES << "\n";
    std::cout << "Percentage of truncated elements: " << TRUNC_MEAN_PERC << "\n";
    std::cout << "Delta: " << DELTA << "\n\n";
    std::cout << "Mean accurate random: " << Estimation::mean(random) << "\n";
    std::cout << "Median accurate random: " << Estimation::median(random) << "\n";
    std::cout << "Variance accurate random: " << Estimation::variance(random) << "\n";
    std::cout << "Skewness accurate random: " << Estimation::skewness(random) << "\n";
    std::cout << "Kurtosis accurate random: " << Estimation::kurtosis(random) << "\n";
    std::cout << "Truncated mean accurate random: " << Estimation::truncatedMean(TRUNC_MEAN_PERC, random) << "\n";
    std::cout << "LSE accurate random: " << Estimation::LSE(Estimation::median(random), random, LAMBDA, laplace) << "\n";
    std::cout << "Minimum gamma accurate random: " << Estimation::minGamma(DELTA, Estimation::median(random), random, LAMBDA, laplace) << "\n";
    std::cout << "----------------------------------\n";

    //std::cout << "Theta: " << THETA << "\n";
    //std::cout << "Lambda: " << LAMBDA << "\n";
    //std::cout << "Number of random elements: " << N_OF_RAND_VALUES << "\n\n";
    //std::cout << Estimation::mean(random) << "\n";
    //std::cout << Estimation::median(random) << "\n";
    //std::cout << Estimation::LSE(Estimation::median(random), random, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::truncatedMean(0.05, random) << "\n";
    //std::cout << Estimation::truncatedMean(0.10, random) << "\n";
    //std::cout << Estimation::truncatedMean(0.15, random) << "\n";
    //std::cout << Estimation::minGamma(0.1, Estimation::median(random), random, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::minGamma(0.5, Estimation::median(random), random, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::minGamma(1., Estimation::median(random), random, LAMBDA, laplace) << "\n";



    out.open("distRandom.txt", std::ofstream::out);
    for (size_t i = 0; i < N_OF_RAND_VALUES; i++)
    {
        distortedRandom[i] = laplace.distortedRandomValue(PERC_OF_DIST_VALUES, THETA, LAMBDA, DIST_THETA, DIST_LAMBDA);
        out << distortedRandom[i] << "\n";
    }
    out.close();
    std::cout << "Mean distorted random: " << Estimation::mean(distortedRandom) << "\n";
    std::cout << "Median distorted random: " << Estimation::median(distortedRandom) << "\n";
    std::cout << "Variance distorted random: " << Estimation::variance(distortedRandom) << "\n";
    std::cout << "Skewness distorted random: " << Estimation::skewness(distortedRandom) << "\n";
    std::cout << "Kurtosis distorted random: " << Estimation::kurtosis(distortedRandom) << "\n";
    std::cout << "Truncated mean distorted random: " << Estimation::truncatedMean(TRUNC_MEAN_PERC, distortedRandom) << "\n";
    std::cout << "LSE distorted random: " << Estimation::LSE(Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
    std::cout << "Minimum gamma distorted random: " << Estimation::minGamma(DELTA, Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
    std::cout << "----------------------------------\n";

    //std::cout << "Theta: " << THETA << "\n";
    //std::cout << "Lambda: " << LAMBDA << "\n";
    //std::cout << "Number of random elements: " << N_OF_RAND_VALUES << "\n";
    //std::cout << "Distorted Theta: " << DIST_THETA << "\n";
    //std::cout << "Distorted Lambda: " << DIST_LAMBDA << "\n";
    //std::cout << "Percentage of distorted elements: " << PERC_OF_DIST_VALUES << "\n\n";
    //std::cout << Estimation::mean(distortedRandom) << "\n";
    //std::cout << Estimation::median(distortedRandom) << "\n";
    //std::cout << Estimation::LSE(Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::truncatedMean(0.05, distortedRandom) << "\n";
    //std::cout << Estimation::truncatedMean(0.10, distortedRandom) << "\n";
    //std::cout << Estimation::truncatedMean(0.15, distortedRandom) << "\n";
    //std::cout << Estimation::minGamma(0.1, Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::minGamma(0.5, Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
    //std::cout << Estimation::minGamma(1., Estimation::median(distortedRandom), distortedRandom, LAMBDA, laplace) << "\n";
}

