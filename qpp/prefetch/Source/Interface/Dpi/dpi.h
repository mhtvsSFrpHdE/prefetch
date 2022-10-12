#include <QMainWindow>

#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

class Dpi
{
public:
    static void init();

    // Any of the pixel size convert function is DPI scaled

    // Convert font point size to pixel size
    // https://accessibility.psu.edu/legibility/fontsize
    static int ptToPx(int pt);

    // Multiply number with dpiMultiplier
    static int multiply(int number);

    // Try scale object inherted from QWidget and QRect
    // For MainWindow, don't use this to avoid unexpected window move
    //     Qt return x and y as 0 if MainWindow as parameter
    static void scale_qWidgetRect(QWidget *widget);

    // Scale MainWindow without touching position
    static void scale_qMainWindow(QMainWindow *mainWindow);

    // Cancel fixed status of a widget
    // https://forum.qt.io/topic/6604/solved-unfix-a-window-previously-fixed/4
    static void undoFixed(QWidget *widget);

    // Default font pixel size, convert from point size in config
    static int defaultFontSize_pixel;

private:
    static cpp_bin_float_single zoomLevel;
    const static cpp_bin_float_single percentage;

    static cpp_bin_float_single dpiMultiplier;
    static cpp_bin_float_single pointToPixelMultiplier;

    // It seems Qt use 1/72 as internal dpi calculation
    const static cpp_bin_float_single assumeQtPointEachInch;
    // But Windows use 96/1 as internal dpi calculation
    const static cpp_bin_float_single assumeOsPointEachInch;

    static int defaultFontSize_point;
};
