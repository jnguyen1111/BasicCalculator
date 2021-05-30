#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    double firstValue;
    double secondValue;
    double solution;
    double combinedValue;

    bool divTrigger;
    bool multTrigger;
    bool addTrigger;
    bool subTrigger;

    Ui::Calculator *ui;

//mapping buttons with purpose
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();
    void ClearEntryButtonPressed();
    void BackSpaceButtonPressed();
    void ResetTrigger();

};
#endif // CALCULATOR_H

