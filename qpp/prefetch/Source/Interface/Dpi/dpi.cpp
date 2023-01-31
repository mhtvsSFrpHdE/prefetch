#include <boost/math/special_functions/round.hpp>
#include <cmath>
#include <QWidget>

#include "dpi.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"

using boost::multiprecision::cpp_bin_float_single;

cpp_bin_float_single Dpi::zoomLevel;
const cpp_bin_float_single Dpi::percentage = 100;

cpp_bin_float_single Dpi::dpiMultiplier;
cpp_bin_float_single Dpi::pointToPixelMultiplier;

const cpp_bin_float_single Dpi::assumeQtPointEachInch = 72;
const cpp_bin_float_single Dpi::assumeOsPointEachInch = 96;

int Dpi::defaultFontSize_point;
int Dpi::defaultFontSize_pixel;

#define gn Const_Setting::ConfigGroupName
#define ikn Const_Setting::ConfigKeyName::Instance

void Dpi::init()
{
    // Zoom level
    auto getZoomLevel = Setting::getInt(gn::Instance, ikn::ZoomLevel, Setting::setting);
    zoomLevel = getZoomLevel.result;

    // Ratio
    dpiMultiplier = zoomLevel / percentage;
    pointToPixelMultiplier = assumeQtPointEachInch / assumeOsPointEachInch;

    // Font size
    auto getFontSize = Setting::getInt(gn::Instance, ikn::FontSize, Setting::setting);
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
    auto geometry = widget->geometry();
    auto minimumSize = widget->minimumSize();

    auto newX = multiply(geometry.x());
    auto newY = multiply(geometry.y());
    auto newWidth = multiply(geometry.width());
    auto newHeight = multiply(geometry.height());

    auto newMinimumWidth = multiply(minimumSize.width());
    auto newMinimumHeight = multiply(minimumSize.height());

    widget->setGeometry(newX, newY, newWidth, newHeight);
    widget->setMinimumSize(newMinimumWidth, newMinimumHeight);
}

void Dpi::scale_qMainWindow(QMainWindow *mainWindow)
{
    auto newWidth = multiply(mainWindow->width());
    auto newHeight = multiply(mainWindow->height());

    mainWindow->setMinimumSize(newWidth, newHeight);
}

void Dpi::undoFixed(QWidget *widget)
{
    widget->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    widget->setMinimumSize(0, 0);
}
