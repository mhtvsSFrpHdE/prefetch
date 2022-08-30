#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

// Static class
class Dpi
{
public:
    static void init();

    // Any of the pixel size convert function is DPI scaled

    // Convert font point size to pixel size
    // https://accessibility.psu.edu/legibility/fontsize
    static int ptToPx(int pt);

    // Default font pixel size, convert from point size in config
    static int defaultFontSize_pixel;

private:
    // Disallow creating an instance of this object
    Dpi();

    static cpp_bin_float_single zoomLevel;
    const static cpp_bin_float_single percentage;

    static cpp_bin_float_single dpiMultiplyer;
    static cpp_bin_float_single pointToPixelMultiplyer;

    const static cpp_bin_float_single assumeQtPointEachInch;
    const static cpp_bin_float_single assumeOsPointEachInch;

    static int defaultFontSize_point;
};
