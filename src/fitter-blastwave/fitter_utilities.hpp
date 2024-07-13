// Copyright (C) 2024 Lieuwe Huisman
#ifndef FITTER_UTILITIES_HPP
#define FITTER_UTILITIES_HPP

using index_t = unsigned int;

namespace Utilities {
struct RGB {
   public:
    float r;
    float g;
    float b;
    RGB(){};
    RGB(float r_, float g_, float b_) : r(r_), g(g_), b(b_){};
};

template <class T>
void json_to_parameter(const nlohmann::json &j, const std::string key, T &target) {
    if (j.contains(key)) {
        j.at(key).get_to(target);
    } else {
        std::cout << "[WARNING]" << "JSON file does contain parameter with key: " << key << std::endl;
    }
};
}  // namespace Utilities
#endif