#include "mainwindow.h"
#include "ui_mainwindow.h"



double num_first;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // соеденяем нажатие на кнопку с методом для обработки нажатий(старый метод connect)
    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus_minus,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mult,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_devide,SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_devide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//MARK: Обработка всех нажатий на цифры
void MainWindow::digits_numbers()
{
    // отслеживаем кнопку на которую нажали
    QPushButton *button = (QPushButton *)sender(); //возвращает кнопку на которую нажали
    QString new_label;
    double all_numbers;

    if(ui->result_label->text().contains(".") && button->text() == "0") {
        new_label = ui->result_label->text() + button->text();
    } else {
        all_numbers = (ui->result_label->text() + button->text()).toDouble();
        new_label = QString::number(all_numbers, 'g', 15); //превращаем числа в строку
    }

    ui->result_label->setText(new_label);
}

//MARK: Точка
void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_label->text().contains('.'))) {
         ui->result_label->setText(ui->result_label->text() + ".");
    }

}

//MARK: (+/-), %
void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;
    double all_numbers;

    if(button->text() == "+/-") {
        all_numbers = (ui->result_label->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers, 'g', 15);

        ui->result_label->setText(new_label);
    } else if (button->text() == "%") {
        all_numbers = (ui->result_label->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers, 'g', 15);

        ui->result_label->setText(new_label);
    }

}

//MARK: математические операции(+,-,*,/)
void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    num_first = ui->result_label->text().toDouble();

    ui->result_label->setText("");

    button->setChecked(true);

}

//MARK: AC(очистить)
void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_devide->setChecked(false);

    ui->result_label->setText("0");

}

//MARK: равно(=)
void MainWindow::on_pushButton_equal_clicked()
{
    double label_number, number_second;
    QString new_label;

    number_second = ui->result_label->text().toDouble();


    if(ui->pushButton_plus->isChecked()) {
        label_number = num_first + number_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->result_label->setText(new_label);
        ui->pushButton_plus->setChecked(false);

    } else if(ui->pushButton_minus->isChecked()) {
        label_number = num_first - number_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->result_label->setText(new_label);
        ui->pushButton_minus->setChecked(false);

    } else if(ui->pushButton_mult->isChecked()) {
        label_number = num_first * number_second;
        new_label = QString::number(label_number, 'g', 15);
        ui->result_label->setText(new_label);
        ui->pushButton_mult->setChecked(false);

    } else if(ui->pushButton_devide->isChecked()) {
        if(number_second == 0) {
            ui->result_label->setText("0");
        } else {
            label_number = num_first / number_second;
            new_label = QString::number(label_number, 'g', 15);
            ui->result_label->setText(new_label);
        }
        ui->pushButton_devide->setChecked(false);
    }

}
