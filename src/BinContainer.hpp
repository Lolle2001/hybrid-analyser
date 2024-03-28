#ifndef BINCONTAINER_HPP
#define BINCONTAINER_HPP

#include <map>
#include <vector>

namespace Statistics {

struct BinContainer {
    std::vector<double> Edge;
    std::map<int, int> IndexMap;
};

}  // namespace Statistics

#endif