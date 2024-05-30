#ifndef FITTER_UTILITIES_HPP
#define FITTER_UTILITIES_HPP

namespace Utilities {
struct RGB {
   public:
    float r;
    float g;
    float b;
    RGB(){};
    RGB(float r_, float g_, float b_) : r(r_), g(g_), b(b_){};
};
}  // namespace Utilities
#endif