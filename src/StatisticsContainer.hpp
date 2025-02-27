// Copyright (C) 2024 Lieuwe Huisman
#ifndef STATISTICSCONTAINER_HPP
#define STATISTICSCONTAINER_HPP

#include <cmath>
#include <iomanip>
#include <iostream>

//  namespace AMPT {
namespace Statistics {

struct StatisticsContainer {
    long double Total = 0;
    long double TotalSQR = 0;
    unsigned long int EntryCount = 0;
    long double Average = 0;
    long double AverageSQR = 0;
    long double Variance = 0;
    long double StandardDeviation = 0;
    long double StandardError = 0;
    unsigned long int SampleCount = 0;
    long double TotalCurrent = 0;
    long double TotalSQRCurrent = 0;
    long double AverageCurrent = 0;
    long double AverageSQRCurrnet = 0;
    unsigned long int EntryCountCurrent = 0;

    // StatisticsContainer();

    void Add(long double value);

    void AddCurrent(long double value);

    void AddEvent();

    void AddCurrentSpecial(long double value);

    void AddEventSpecial();

    void RedefineTotalSQR();
    void SetVariance(long double Variance_);
    void SetStandardError(long double StandardError_);
    void CalculatePoissonError();
    void CalculateAverage();
    void CalculateAverageSQR();
    void CalculateVariance();
    void CalculateStandardDeviation();
    void CalculateStandardError();
    void CalculateStatistics();

    long double GetAverage();
    long double GetAverageSQR();
    long double GetVariance();
    long double GetStandardDeviation();
    long double GetStandardError();
    long int GetSampleCount();
    long int GetEntryCount();

    void operator+=(StatisticsContainer const& rhs);

    StatisticsContainer operator+(StatisticsContainer const& rhs);

    void operator-=(StatisticsContainer const& rhs);

    StatisticsContainer operator-(StatisticsContainer const& rhs);
};

}  // namespace Statistics
   //  }

#endif