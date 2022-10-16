#pragma once
#include <vector>
#include "GeneralLaplaceDistribution.h"
class Estimation
{
public:
    static double mean(const std::vector<double>&);
    static double median(std::vector<double>);
    static double variance(const std::vector<double>&);
    static double skewness(const std::vector<double>&);
    static double kurtosis(const std::vector<double>&);
    static double truncatedMean(double, std::vector<double>);
    static double LSE(double, const std::vector<double>&, double, const GeneralLaplaceDistribution&);
    static double minGamma(double, double, const std::vector<double>&, double, const GeneralLaplaceDistribution&);

private:
    static double LSEM(double, const std::vector<double>&, double, const GeneralLaplaceDistribution&);
    static double LSELoss(double, double, double, const GeneralLaplaceDistribution&);
    static double minGammaM(double, double, const std::vector<double>&, double, const GeneralLaplaceDistribution&);
    static double minGammaLoss(double, double, double, double, const GeneralLaplaceDistribution&);
};

