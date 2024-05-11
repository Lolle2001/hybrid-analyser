#ifndef BINCONTAINER_HPP
#define BINCONTAINER_HPP

#include <map>
#include <vector>

#include "Utilities.hpp"

namespace Statistics {

struct BinContainer {
    std::vector<double> Edges;
    std::map<int, int> IndexMap;
    double min;
    double max;
    double width;
    double n;

    BinContainer(std::vector<double>& Edges_)
        : Edges(Edges_) {
        CalculateProperties();
    };

    void CalculateProperties() {
        n = Edges.size();
        max = Edges.back();
        min = Edges.front();

        std::vector<double> widths(n);

        for (int i = 0; i < n; ++i) {
            widths[i] = Edges[i + 1] - Edges[i];
        }

        double smallest_width = widths[0];

        double temp_width;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                temp_width = Utilities::igcd(widths[i], widths[j], 0.001);
                if (temp_width < smallest_width) {
                    smallest_width = temp_width;
                }
            }
        }

        width = smallest_width;

        int temp_nx = static_cast<int>((max - min) / width);

        double x;

        for (int i = 0; i < n; ++i) {
            x = (min + i * width + width * 0.5);

            for (int j = 0; j < n; ++j) {
                if (x > Edges[j] && x < Edges[j + 1]) {
                    IndexMap[i] = j;
                }
            }
        }

        widths.clear();
    }
};

}  // namespace Statistics

#endif