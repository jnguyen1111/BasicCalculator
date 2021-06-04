#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication gui(argc, argv);
    Calculator calculatorInterface;
    calculatorInterface.show();
    return gui.exec();
}
