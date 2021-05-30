#include "calculator.h"
#include "ui_calculator.h"
#include <math.h>

Calculator::Calculator(QWidget *parent): QMainWindow(parent), ui(new Ui::Calculator)
{
    firstValue = 0.0;
    secondValue =0.0;
    solution = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    ui->setupUi(this);
    ui->Display->setText(QString::number(firstValue)); //converts number to string for the calc display

    //array for number buttons
    QPushButton *numberButtons[10];
    for (int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);
        numberButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numberButtons[i] , SIGNAL(released()) , this , SLOT(NumPressed()));
    }
    connect(ui->Add , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Minus , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Multiply , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Divide , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Equal , SIGNAL(released()) , this , SLOT(EqualButtonPressed()));
    connect(ui->Clear , SIGNAL(released()) , this , SLOT(ClearButtonPressed()));
    connect(ui->ClearEntry , SIGNAL(released()) , this , SLOT(ClearEntryButtonPressed()));
    connect(ui->BackSpace , SIGNAL(released()) , this , SLOT(BackSpaceButtonPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *buttonPushed = (QPushButton *)sender(); // returns button pushed
    QString buttonValue = buttonPushed->text();           // gets the text from
    QString calcDisplay = ui->Display->text();

    if((calcDisplay.toDouble() == 0 ) || (calcDisplay.toDouble() == 0.0)){
        ui->Display->setText(buttonValue);
    }
    else{
        combinedValue = (calcDisplay + buttonValue).toDouble();
        ui->Display->setText(QString::number(combinedValue, 'g' , 16));
    }

}

void Calculator::ResetTrigger(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
}

void Calculator::MathButtonPressed(){
        ResetTrigger();

        //gets number then clears
        firstValue = (ui->Display->text()).toDouble();

        QString buttonOperator = ((QPushButton *)sender())->text();

        //match the operation button with the QString buttonOperator
        if(QString::compare(buttonOperator, "/" , Qt::CaseInsensitive) == 0){
              divTrigger = true;
        }
        else if(QString::compare(buttonOperator, "*" , Qt::CaseInsensitive) == 0){
            multTrigger = true;
        }
        else if(QString::compare(buttonOperator, "+" , Qt::CaseInsensitive) == 0){
            addTrigger = true;
        }
        else{
            subTrigger = true;
        }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    secondValue = (ui->Display->text()).toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = firstValue + secondValue;
        }
        else if(subTrigger){
            solution = firstValue - secondValue;
        }
        else if(multTrigger){
            solution = firstValue * secondValue;
        }
        else{
            solution = firstValue / secondValue;
        }
    }
    ui->Display->setText(QString::number(solution));

}

void Calculator::ClearButtonPressed(){
    firstValue = 0.0;
    secondValue = 0.0;
    ResetTrigger();
    ui->Display->setText(QString::number((firstValue)));
}

void Calculator::BackSpaceButtonPressed(){
    QString calcDisplay = ui->Display->text();
    calcDisplay.chop(1);
    if( (calcDisplay.size()) == 0 ){
        ui->Display->setText("0");

    }
    else{
        ui->Display->setText(calcDisplay);
    }
}

void Calculator::ClearEntryButtonPressed(){
    ui->Display->setText("");
}


