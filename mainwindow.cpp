#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> 
#include <QVBoxLayout> 
#include <QLabel>
#include <QFileDialog>  // Для вибору файлу
#include <QFile>        // Для роботи з файлами
#include <QTextStream>  // Для читання/запису тексту
#include <QMenuBar>     // Для верхнього меню
#include <QMenu>        // Для пунктів меню
#include <QAction>      // Для дій меню

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow { background-color: #1a1a1e; }");
    this->resize(450, 580); 

    // --- СТВОРЕННЯ МЕНЮ ДЛЯ РОБОТИ З ФАЙЛАМИ (ПУНКТ С*) ---
    QMenu *fileMenu = this->menuBar()->addMenu("Файл");
    QAction *actionLoad = new QAction("Завантажити з файлу", this);
    QAction *actionSave = new QAction("Зберегти у файл", this);
    
    fileMenu->addAction(actionLoad);
    fileMenu->addAction(actionSave);

    connect(actionLoad, &QAction::triggered, this, &MainWindow::action_load_triggered);
    connect(actionSave, &QAction::triggered, this, &MainWindow::action_save_triggered);

    this->menuBar()->setStyleSheet(
        "QMenuBar { background-color: #1a1a1e; color: #d1d1d6; font-size: 14px; }"
        "QMenuBar::item:selected { background-color: #3e3e44; }"
        "QMenu { background-color: #26262b; color: #d1d1d6; border: 1px solid #3e3e44; }"
        "QMenu::item:selected { background-color: #4a90e2; color: #ffffff; }"
    );
    // ------------------------------------------------------

    // Створюємо менеджер компоновки
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(20);                     
    layout->setContentsMargins(40, 20, 40, 40); 

    // 1. Опис завдання
    QLabel *taskLabel = new QLabel(this);
    taskLabel->setText("ВАРІАНТ №8\nПри введенні тризначного числа програма переміщує цифру сотень у розряд одиниць. Результат виводиться у вікно."); 
    taskLabel->setAlignment(Qt::AlignCenter);
    taskLabel->setWordWrap(true); 
    taskLabel->setStyleSheet(
        "QLabel {"
        "   color: #d1d1d6;"             
        "   background-color: #26262b;"
        "   border: 1px solid #3e3e44;"
        "   border-radius: 8px;"
        "   padding: 15px;"              
        "   font-size: 16px;"            
        "   font-family: 'Arial';"
        "   font-weight: bold;"          
        "}"
    );
    layout->addWidget(taskLabel);       

    // 2. Поле введення чисел
    ui->le_input->setMinimumHeight(55);  
    ui->le_input->clear();               
    ui->le_input->setAlignment(Qt::AlignCenter); 
    ui->le_input->setPlaceholderText("Введіть число"); 
    ui->le_input->setStyleSheet(
        "QLineEdit {"
        "   background-color: #26262b;"
        "   color: #ffffff;"
        "   border: 2px solid #3e3e44;"
        "   border-radius: 8px;"
        "   font-size: 20px;"            
        "   font-weight: bold;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4a90e2;"  
        "}"
    );

    // 3. Кнопка "Порахувати" (Жовта)
    ui->btn_calc->setMinimumHeight(55);
    ui->btn_calc->setStyleSheet(
        "QPushButton {"
        "   background-color: #2d2d35;"
        "   color: #ffffff;"
        "   border: 2px solid #f1c40f;"  
        "   border-radius: 8px;"
        "   font-size: 16px;"           
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3a3a45;"  
        "   border: 2px solid #f39c12;"  
        "}"
        "QPushButton:pressed {"
        "   background-color: #1e1e24;"
        "}"
    );

    // 4. Вікно результатів (Зелене)
    ui->lbl_result->setMinimumHeight(65);
    ui->lbl_result->setAlignment(Qt::AlignCenter); 
    ui->lbl_result->setStyleSheet(
        "QLabel {"
        "   background-color: #26262b;"
        "   color: #2ecc71;"             
        "   border: 2px solid #2ecc71;"  
        "   border-radius: 8px;"
        "   font-size: 28px;"            
        "   font-weight: bold;"
        "}"
    );

    // 5. Кнопка "Очистити" (Червона)
    ui->btn_load->setMinimumHeight(55);
    ui->btn_load->setText("Очистити");
    ui->btn_load->setStyleSheet(
        "QPushButton {"
        "   background-color: #2d2d35;"
        "   color: #ff6b6b;"             
        "   border: 2px solid #4f4f64;"  
        "   border-radius: 8px;"
        "   font-size: 16px;"           
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3d2d2d;"  
        "   border: 2px solid #ff4757;" 
        "}"
        "QPushButton:pressed {"
        "   background-color: #2b1e1e;"
        "}"
    );

    // Ховаємо невикористовувану кнопку збереження (бо тепер є меню)
    ui->btn_save->hide();

    // Додаємо всі елементи на форму
    layout->addWidget(ui->le_input);
    layout->addWidget(ui->btn_calc);
    layout->addWidget(ui->lbl_result);
    layout->addWidget(ui->btn_load);

    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функція повного очищення полів
void MainWindow::clear_data_fields() 
{
    ui->le_input->clear();
    ui->lbl_result->setText("0");
    ui->le_input->setFocus(); 
}

// Логіка обчислень для Варіанта №8
void MainWindow::on_btn_calc_clicked()
{
    int num, result;
    bool ok;

    num = ui->le_input->text().toInt(&ok);

    // Перевірка на тризначність та коректність вводу
    // Використовуємо abs() для підтримки від'ємних чисел (опціонально, але правильно)
    if (!ok || abs(num) < 100 || abs(num) > 999) {
        QMessageBox::warning(this, "Помилка введення", "Будь ласка, введіть коректне тризначне число!");
        clear_data_fields();
    } 
    else {
        // Зберігаємо знак числа
        int sign = (num < 0) ? -1 : 1;
        num = abs(num);

        // Логіка переміщення цифри сотень у розряд одиниць
        int hundreds = num / 100;           // Отримуємо першу цифру
        int remainder = num % 100;          // Отримуємо дві останні цифри
        result = (remainder * 10 + hundreds) * sign; // Формуємо нове число і повертаємо знак

        ui->lbl_result->setText(QString::number(result));
    }
}

// Кнопка "Очистити" (старий слот btn_load)
void MainWindow::on_btn_load_clicked()
{
    clear_data_fields(); 
}

// Порожній слот для прихованої кнопки
void MainWindow::on_btn_save_clicked()
{
    // Функція прихована
}

// --- РЕАЛІЗАЦІЯ РОБОТИ З ФАЙЛАМИ (ПУНКТ С*) ---

void MainWindow::action_load_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Відкрити файл", QDir::currentPath(), "Текстові файли (*.txt);;Усі файли (*)");
    
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString data;
            in >> data; // Зчитуємо перше слово/число з файлу
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
            out << "Input Number: " << ui->le_input->text() << "\n";
            out << "Result: " << ui->lbl_result->text() << "\n";
            file.close();
            QMessageBox::information(this, "Успіх", "Дані успішно збережено у файл!");
        } else {
            QMessageBox::critical(this, "Помилка", "Не вдалося зберегти файл: \n" + file.errorString());
        }
    }
}