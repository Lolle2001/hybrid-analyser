// Copyright (C) 2024 Lieuwe Huisman
#include "StatisticsContainer.hpp"

// namespace AMPT {
namespace Statistics {
void StatisticsContainer::Add(long double value) {
    Total += value;
    TotalSQR += value * value;
    EntryCount += 1;
}

void StatisticsContainer::AddCurrent(long double value) {
    TotalCurrent += value;
    EntryCountCurrent += 1;
}

void StatisticsContainer::AddEvent() {
    // std::cout << "here" << std::endl;
    Total += TotalCurrent;
    TotalSQR += TotalCurrent * TotalCurrent;
    EntryCount += EntryCountCurrent;
    // std::cout << Total << std::endl;
    TotalCurrent = 0;
    EntryCountCurrent = 0;
}

void StatisticsContainer::AddEventSpecial() {
    // std::cout << "here" << std::endl;
    if (EntryCountCurrent > 0) {
        Total += TotalCurrent / (double)EntryCountCurrent;
        TotalSQR += TotalCurrent * TotalCurrent / ((double)EntryCountCurrent * (double)EntryCountCurrent);
        EntryCount += EntryCountCurrent;
    }

    EntryCountCurrent = 0;
    TotalCurrent = 0;
}

void StatisticsContainer::RedefineTotalSQR() {
    TotalSQR = Total * Total;
}
void StatisticsContainer::SetVariance(long double Variance_) {
    Variance = Variance_;
}
void StatisticsContainer::SetStandardError(long double StandardError_) {
    StandardError = StandardError_;
}

void StatisticsContainer::CalculatePoissonError() {
    StandardDeviation = std::sqrt(Average);
}

void StatisticsContainer::CalculateAverage() {
    Average = Total / (long double)EntryCount;
}

void StatisticsContainer::CalculateAverageSQR() {
    AverageSQR = TotalSQR / (long double)EntryCount;
}

void StatisticsContainer::CalculateVariance() {
    Variance = AverageSQR - Average * Average;
}

void StatisticsContainer::CalculateStandardDeviation() {
    StandardDeviation = std::sqrt(Variance);
}

void StatisticsContainer::CalculateStandardError() {
    // if(SampleCount > 0){
    StandardError = StandardDeviation / std::sqrt(EntryCount);
    // }
    // else{
    // std::cout << "SampleCount is zero, cannot calculate standard error." << std::endl;
    // }
}

void StatisticsContainer::CalculateStatistics() {
    CalculateAverage();
    CalculateAverageSQR();
    CalculateVariance();
    CalculateStandardDeviation();
    CalculateStandardError();
}

long double StatisticsContainer::GetAverage() {
    return Average;
}

long double StatisticsContainer::GetAverageSQR() {
    return AverageSQR;
}

long double StatisticsContainer::GetVariance() {
    return Variance;
}

long double StatisticsContainer::GetStandardDeviation() {
    return StandardDeviation;
}

long double StatisticsContainer::GetStandardError() {
    return StandardError;
}

long int StatisticsContainer::GetSampleCount() {
    return SampleCount;
}

long int StatisticsContainer::GetEntryCount() {
    return EntryCount;
}

void StatisticsContainer::operator+=(StatisticsContainer const& rhs) {
    Total += rhs.Total;
    TotalSQR += rhs.TotalSQR;
    EntryCount += rhs.EntryCount;
    SampleCount += rhs.SampleCount;
    Variance += rhs.Variance;
}

StatisticsContainer StatisticsContainer::operator+(StatisticsContainer const& rhs) {
    Total += rhs.Total;
    TotalSQR += rhs.TotalSQR;
    EntryCount += rhs.EntryCount;
    SampleCount += rhs.SampleCount;
    Variance += rhs.Variance;
    return *this;
}

void StatisticsContainer::operator-=(StatisticsContainer const& rhs) {
    Total -= rhs.Total;
    TotalSQR -= rhs.TotalSQR;
    EntryCount -= rhs.EntryCount;
    SampleCount -= rhs.SampleCount;
    Variance -= rhs.Variance;
}

StatisticsContainer StatisticsContainer::operator-(StatisticsContainer const& rhs) {
    Total -= rhs.Total;
    TotalSQR -= rhs.TotalSQR;
    EntryCount -= rhs.EntryCount;
    SampleCount -= rhs.SampleCount;
    Variance -= rhs.Variance;
    return *this;
}

std::ostream& operator<<(std::ostream& output, StatisticsContainer& obj) {
    output << std::setw(13) << std::scientific << std::right << obj.Total << " ";
    output << std::setw(13) << std::scientific << std::right << obj.TotalSQR << " ";
    output << std::setw(13) << std::scientific << std::right << (long double)obj.EntryCount << " ";
    output << std::setw(13) << std::scientific << std::right << obj.Average << " ";
    output << std::setw(13) << std::scientific << std::right << obj.AverageSQR << " ";
    output << std::setw(13) << std::scientific << std::right << obj.Variance << " ";
    output << std::setw(13) << std::scientific << std::right << obj.StandardDeviation << " ";
    output << std::setw(13) << std::scientific << std::right << obj.StandardError << " ";
    output << std::setw(13) << std::scientific << std::right << (long double)obj.SampleCount;
    return output;
}
}  // namespace Statistics
// }
