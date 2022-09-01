#include <boost/math/special_functions/round.hpp>
#include <cmath>
#include <QWidget>

#include "dpi.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const.h"

using boost::multiprecision::cpp_bin_float_single;

cpp_bin_float_single Dpi::zoomLevel;
const cpp_bin_float_single Dpi::percentage = 100;

cpp_bin_float_single Dpi::dpiMultiplier;
cpp_bin_float_single Dpi::pointToPixelMultiplier;

const cpp_bin_float_single Dpi::assumeQtPointEachInch = 72;
const cpp_bin_float_single Dpi::assumeOsPointEachInch = 96;

int Dpi::defaultFontSize_point;
int Dpi::defaultFontSize_pixel;

void Dpi::init()
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;

    // Zoom level
    auto getZoomLevel = Setting::getInt(Instance, ZoomLevel, Setting::setting);
    zoomLevel = getZoomLevel.result;

    // Ratio
    dpiMultiplier = zoomLevel / percentage;
    pointToPixelMultiplier = assumeQtPointEachInch / assumeOsPointEachInch;

    // Font size
    auto getFontSize = Setting::getInt(Instance, FontSize, Setting::setting);
    defaultFontSize_point = getFontSize.result;
    defaultFontSize_pixel = ptToPx(defaultFontSize_point);
}

int Dpi::ptToPx(int pt)
{
    // Parse input to float
    cpp_bin_float_single floatPt = pt;
    // Convert point to pixel
    cpp_bin_float_single floatResult = floatPt / pointToPixelMultiplier;
    // DPI scale
    floatResult = floatResult * dpiMultiplier;

    int result_floor = std::floor(floatResult.convert_to<float>());
    return result_floor;
}

int Dpi::multiply(int number)
{
    cpp_bin_float_single floatResult = number;

    floatResult = floatResult * dpiMultiplier;

    int result_floor = std::floor(floatResult.convert_to<float>());
    return result_floor;
};

void Dpi::scale_qWidgetRect(QWidget *widget)
{
    auto qRect = widget->geometry();

    auto newX = multiply(qRect.x());
    auto newY = multiply(qRect.y());
    auto newWidth = multiply(qRect.width());
    auto newHeight = multiply(qRect.height());

    widget->setGeometry(newX, newY, newWidth, newHeight);
}

void Dpi::scale_qMainWindow(QMainWindow *mainWindow)
{
    auto newWidth = multiply(mainWindow->width());
    auto newHeight = multiply(mainWindow->height());

    mainWindow->setFixedSize(newWidth, newHeight);
}
