#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> 
#include <QVBoxLayout>  
#include <QFileDialog>  
#include <QFile>        
#include <QTextStream>  
#include <QMenuBar>     
#include <QMenu>        
#include <QAction>      

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // --- 1. СТВОРЮЄМО НАПИС ІЗ ЗАВДАННЯМ ПРОГРАМНО ---
    // (Тобі не треба додавати його в Qt Designer, код зробить все сам)
    QLabel *lbl_task = new QLabel(this);
    lbl_task->setText("ВАРІАНТ №8\nПри введенні тризначного числа програма переміщує цифру сотень у розряд одиниць. Результат виводиться у вікно.");
    lbl_task->setAlignment(Qt::AlignCenter);
    lbl_task->setWordWrap(true);
    lbl_task->setStyleSheet(
        "QLabel {"
        "   color: #d1d1d6; background-color: #26262b; border: 1px solid #3e3e44;"
        "   border-radius: 8px; padding: 15px; font-size: 15px; font-family: 'Arial'; font-weight: bold;"
        "}"
    );

    // --- 2. ПРОГРАМНЕ ВИРІВНЮВАННЯ ТА ВІДСТУПИ ---
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);
    
    // Додаємо віджети у правильному порядку (НАПИС ТЕПЕР ЗВЕРХУ!)
    mainLayout->addWidget(lbl_task);
    mainLayout->addWidget(ui->le_input);
    mainLayout->addWidget(ui->btn_calc);
    mainLayout->addWidget(ui->lbl_result);
    mainLayout->addWidget(ui->btn_load);

    mainLayout->setContentsMargins(40, 20, 40, 40);
    mainLayout->setSpacing(20);

    // Встановлюємо темний колір фону
    this->setStyleSheet("QMainWindow { background-color: #1a1a1e; }");
    this->resize(450, 580); 

    // --- 3. МЕНЮ ДЛЯ РОБОТИ З ФАЙЛАМИ ---
    QMenu *fileMenu = this->menuBar()->addMenu("Файл");
    QAction *actionLoad = new QAction("Завантажити з файлу", this);
    QAction *actionSave = new QAction("Зберегти у файл", this);
    fileMenu->addAction(actionLoad);
    fileMenu->addAction(actionSave);

    connect(actionLoad, &QAction::triggered, this, &MainWindow::action_load_triggered);
    connect(actionSave, &QAction::triggered, this, &MainWindow::action_save_triggered);

    this->menuBar()->setStyleSheet(
        "QMenuBar { background-color: #1a1a1e; color: #d1d1d6; font-size: 14px; font-family: 'Arial'; }"
        "QMenuBar::item:selected { background-color: #3e3e44; }"
        "QMenu { background-color: #26262b; color: #d1d1d6; border: 1px solid #3e3e44; }"
        "QMenu::item:selected { background-color: #4a90e2; color: #ffffff; }"
    );

    // --- 4. НАКЛАДАННЯ СТИЛІВ QSS (З виправленням шрифтів і підказок) ---
    
    // Поле введення (Виправляємо помилку з жорстким текстом)
    ui->le_input->clear(); // Примусово стираємо текст, якщо він був у Designer
    ui->le_input->setPlaceholderText("Введіть число"); // Ставимо правильну підказку, яка зникає
    ui->le_input->setMinimumHeight(55);
    ui->le_input->setAlignment(Qt::AlignCenter); 
    ui->le_input->setStyleSheet(
        "QLineEdit {"
        "   background-color: #26262b; color: #ffffff; border: 2px solid #3e3e44;"
        "   border-radius: 8px; font-size: 20px; font-family: 'Arial'; font-weight: bold;"
        "}"
        "QLineEdit:focus { border: 2px solid #4a90e2; }"
    );

    // Жовта кнопка "Порахувати"
    ui->btn_calc->setMinimumHeight(55);
    ui->btn_calc->setStyleSheet(
        "QPushButton {"
        "   background-color: #2d2d35; color: #ffffff; border: 2px solid #f1c40f;"  
        "   border-radius: 8px; font-size: 16px; font-family: 'Arial'; font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #3a3a45; border: 2px solid #f39c12; }"
        "QPushButton:pressed { background-color: #1e1e24; }"
    );

    // Зелене поле виведення результату (Фіксуємо максимальну висоту, щоб не роздувалося!)
    ui->lbl_result->setMinimumHeight(65);
    ui->lbl_result->setMaximumHeight(85); // <--- Ось це не дасть йому стати величезним
    ui->lbl_result->setAlignment(Qt::AlignCenter); 
    ui->lbl_result->setStyleSheet(
        "QLabel {"
        "   background-color: #26262b; color: #2ecc71; border: 2px solid #2ecc71;"  
        "   border-radius: 8px; font-size: 28px; font-family: 'Arial'; font-weight: bold;"
        "}"
    );

    // Червона кнопка "Очистити"
    ui->btn_load->setMinimumHeight(55);
    ui->btn_load->setStyleSheet(
        "QPushButton {"
        "   background-color: #2d2d35; color: #ff6b6b; border: 2px solid #4f4f64;"  
        "   border-radius: 8px; font-size: 16px; font-family: 'Arial'; font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #3d2d2d; border: 2px solid #ff4757; }"
        "QPushButton:pressed { background-color: #2b1e1e; }"
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear_data_fields() 
{
    ui->le_input->clear();
    ui->lbl_result->setText("0");
    ui->le_input->setFocus();
}

void MainWindow::on_btn_calc_clicked()
{
    int num, result;
    bool ok;
    num = ui->le_input->text().toInt(&ok);

    if (!ok || abs(num) < 100 || abs(num) > 999) {
        QMessageBox::warning(this, "Помилка введення", "Будь ласка, введіть коректне тризначне число!");
        clear_data_fields();
    } 
    else {
        int sign = (num < 0) ? -1 : 1;
        num = abs(num);
        int hundreds = num / 100;           
        int remainder = num % 100;          
        result = (remainder * 10 + hundreds) * sign; 
        ui->lbl_result->setText(QString::number(result));
    }
}

void MainWindow::on_btn_load_clicked()
{
    clear_data_fields(); 
}

void MainWindow::action_load_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Відкрити файл", QDir::currentPath(), "Текстові файли (*.txt);;Усі файли (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString data;
            in >> data; 
            ui->le_input->setText(data);
            file.close();
        } else {
            QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл!");
        }
    }
}

void MainWindow::action_save_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Зберегти файл", QDir::currentPath(), "Текстові файли (*.txt);;Усі файли (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "Вхідне число: " << ui->le_input->text() << "\n";
            out << "Результат: " << ui->lbl_result->text() << "\n";
            file.close();
            QMessageBox::information(this, "Успіх", "Дані успішно збережено у файл!");
        } else {
            QMessageBox::critical(this, "Помилка", "Не вдалося зберегти файл!");
        }
    }
}