#include <boost/math/special_functions/round.hpp>
#include <cmath>

#include "dpi.h"
#include "..\..\Setting\setting.h"

using boost::multiprecision::cpp_bin_float_single;

cpp_bin_float_single Dpi::zoomLevel;
const cpp_bin_float_single Dpi::percentage = 100;

cpp_bin_float_single Dpi::dpiMultiplyer;
cpp_bin_float_single Dpi::pointToPixelMultiplyer;

const cpp_bin_float_single Dpi::assumeQtPointEachInch = 72;
const cpp_bin_float_single Dpi::assumeOsPointEachInch = 96;

int Dpi::defaultFontSize_point;
int Dpi::defaultFontSize_pixel;

void Dpi::init()
{
    // Zoom level
    auto getZoomLevel = Setting::getInt("Instance", "ZoomLevel", Setting::setting);
    if (getZoomLevel.success)
    {
        zoomLevel = getZoomLevel.result;
    }
    else
    {
        zoomLevel = 100;
    }

    // Ratio
    dpiMultiplyer = zoomLevel / percentage;
    pointToPixelMultiplyer = assumeQtPointEachInch / assumeOsPointEachInch;

    // Font size
    auto getFontSize = Setting::getInt("Instance", "FontSize", Setting::setting);
    if (getFontSize.success)
    {
        defaultFontSize_point = getFontSize.result;
    }
    else
    {
        defaultFontSize_point = 10;
    }
    defaultFontSize_pixel = ptToPx(defaultFontSize_point);
}

int Dpi::ptToPx(int pt)
{
    // Parse input to float
    cpp_bin_float_single floatPt = pt;
    // Convert point to pixel
    cpp_bin_float_single floatResult = floatPt / pointToPixelMultiplyer;
    // DPI scale
    floatResult = floatResult * dpiMultiplyer;

    int result_floor = std::floor(floatResult.convert_to<float>());
    return result_floor;
}
