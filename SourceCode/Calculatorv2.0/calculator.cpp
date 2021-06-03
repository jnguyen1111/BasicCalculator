#include "calculator.h"
#include "ui_calculator.h"
#include <math.h>


//NOTE FIX: precision and number formating with numbers
//add unit testing

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
    ui->Display->setMaxLength(16);

    //array for number buttons and mapping it
    QPushButton *numberButtons[10];
    for (int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);
        numberButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numberButtons[i] , SIGNAL(released()) , this , SLOT(NumPressed()));
    }

    //map button functions for gui
    connect(ui->Add , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Minus , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Multiply , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Divide , SIGNAL(released()) , this , SLOT(MathButtonPressed()));
    connect(ui->Equal , SIGNAL(released()) , this , SLOT(EqualButtonPressed()));
    connect(ui->Clear , SIGNAL(released()) , this , SLOT(ClearButtonPressed()));
    connect(ui->NumSign ,  SIGNAL(released()) , this , SLOT(NumSignButtonPressed()));
    connect(ui->ClearEntry , SIGNAL(released()) , this , SLOT(ClearEntryButtonPressed()));
    connect(ui->BackSpace , SIGNAL(released()) , this , SLOT(BackSpaceButtonPressed()));
    connect(ui->Percentage , SIGNAL(released()) , this , SLOT(PrecentageButtonPressed()));
    connect(ui->Reciporcal , SIGNAL(released()) , this , SLOT(ReciporcalButtonPressed()));
    connect(ui->PowerSquare , SIGNAL(released()) , this , SLOT(SquaredButtonPressed()));
    connect(ui->RootSquare , SIGNAL(released()) , this , SLOT(SquareRootButtonPressed()));
    connect(ui->Decimal , SIGNAL(released()) , this , SLOT(DecimalButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

//check if theres a digit after decimal place if not remove decimal place
double Calculator::CheckDecimalPlace(){
    QString checkDecimalValue = ui -> Display->text();
    int decimalIndex = checkDecimalValue.indexOf('.');
    if(checkDecimalValue.size() == (decimalIndex + 1)){
        checkDecimalValue.chop(1);
    }

    return checkDecimalValue.toDouble();
}

// reset to detect if user wants to do another math operation
void Calculator::ResetTrigger(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
}

void Calculator::EqualButtonPressed(){
    secondValue = CheckDecimalPlace();

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

    QString finalConvertedSolution = QString::number(solution , 'G' , 20);

    if (finalConvertedSolution.contains('.')){
        ui->Display->setText(QString::number(finalConvertedSolution.toDouble() , 'f' , 4));

    }
    else if(finalConvertedSolution.size() <= 16){
        ui->Display->setText(QString::number(finalConvertedSolution.toDouble() , 'g' , 16));
    }
    else{
        //error the max value does not turn into scientific notation
        ui->Display->setText(QString::number(finalConvertedSolution.toDouble()));

    }
}
void Calculator::MathButtonPressed(){
        ResetTrigger();
        firstValue = CheckDecimalPlace();
        QString buttonOperator = ((QPushButton *)sender())->text();

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

//displays proper number formating depending on the number given
void Calculator::NumPressed(){
    QPushButton *buttonPushed = (QPushButton *)sender();
    QString calcDisplay = ui->Display->text();
    QString buttonValue = buttonPushed->text();
    QString combinedNumber = calcDisplay + buttonValue;
    combinedValue = (calcDisplay + buttonValue).toDouble();

    if  (combinedNumber.contains('.') && (combinedNumber.indexOf('.') == 0)){
        ui->Display->setText(combinedNumber);
    }
    else if  (combinedNumber.contains('.') && (combinedNumber.indexOf('.') != 0)){
        ui->Display->setText(combinedNumber);
    }

    else if((calcDisplay.toDouble() == 0 ) || (calcDisplay.toDouble() == 0.0)){
        ui->Display->setText(buttonValue);
    }
    else if(combinedNumber.size() <= 16){
            ui->Display->setText(QString::number(combinedValue , 'G' , combinedNumber.size()));
    }
}

void Calculator::PrecentageButtonPressed(){
    double percentageValue = firstValue * ( ((ui->Display->text()).toDouble()) / 100 );
    ui->Display->setText(QString::number(percentageValue));
}

void Calculator::ReciporcalButtonPressed(){
    double reciporcalValue = 1.0 / ((ui->Display->text()).toDouble());
    ui->Display->setText(QString::number(reciporcalValue));
}
void Calculator::SquaredButtonPressed(){
    double squaredValue =  pow( (ui->Display->text()).toDouble() , 2.0);
    ui->Display->setText(QString::number(squaredValue));
}
void Calculator::SquareRootButtonPressed(){
    double rootValue =  sqrt( (ui->Display->text()).toDouble());
    ui->Display->setText(QString::number(rootValue));
}
void Calculator::DecimalButtonPressed(){
    QString decimalValue = ui->Display->text() + '.';
    ui->Display->setText(decimalValue);
}

// reset to original values
void Calculator::ClearButtonPressed(){
    firstValue = 0.0;
    secondValue = 0.0;
    solution = 0.0;
    ResetTrigger();
    ui->Display->setText(QString::number((firstValue)));
}

//deletes character at end of number string
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

//clear current user input
void Calculator::ClearEntryButtonPressed(){
    ui->Display->setText("");
}

void Calculator::NumSignButtonPressed(){
    double newDisplayVal = -1 * ((ui->Display->text()).toDouble());
    ui->Display->setText(QString::number(newDisplayVal));
}


