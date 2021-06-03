#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT // qt objects and event handler

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    double firstValue;
    double secondValue;
    double solution;
    double combinedValue;
    QString fullNumber;

    bool divTrigger;
    bool multTrigger;
    bool addTrigger;
    bool subTrigger;

    Ui::Calculator *ui;

// mapping buttton purpose
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();
    void NumSignButtonPressed();
    void ClearEntryButtonPressed();
    void BackSpaceButtonPressed();
    void ReciporcalButtonPressed();
    void SquaredButtonPressed();
    void SquareRootButtonPressed();
    void DecimalButtonPressed();
    void PrecentageButtonPressed();
    void ResetTrigger();
    double CheckDecimalPlace();

};
#endif // CALCULATOR_H

