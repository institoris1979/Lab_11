#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> 
#include <QFileDialog>  
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QVBoxLayout> 
#include <QLabel>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ==========================================
    // НАЛАШТУВАННЯ СТИЛЬНОГО ТЕМНОГО ІНТЕРФЕЙСУ
    // ==========================================
    this->setStyleSheet("QMainWindow { background-color: #1a1a1e; }");
    this->resize(450, 520); 

    // --- ВЕРХНЄ МЕНЮ (Виконання пункту С* методички) ---
    QMenuBar *topMenu = new QMenuBar(this);
    topMenu->setStyleSheet("QMenuBar { background-color: #2d2d35; color: white; font-size: 13px; padding: 3px; }");
    this->setMenuBar(topMenu);
    
    QMenu *fileMenu = topMenu->addMenu("Файл");
    
    // Дія "Завантажити" у меню
    QAction *actLoad = fileMenu->addAction("Завантажити дані з файлу");
    connect(actLoad, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Завантажити", QDir::currentPath(), "TXT (*.txt)");
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString s_num;
                in >> s_num; 
                ui->le_input->setText(s_num);
                file.close();
            }
        }
    });

    // Дія "Зберегти" у меню
    QAction *actSave = fileMenu->addAction("Зберегти результат у файл");
    connect(actSave, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getSaveFileName(this, "Зберегти", QDir::currentPath(), "TXT (*.txt)");
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << "Вхідне число: " << ui->le_input->text() << "\n";
                out << "Результат: " << ui->lbl_result->text() << "\n";
                file.close();
            }
        }
    });
    // --------------------------------------------------

    // Створюємо менеджер компоновки
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(20);                     
    layout->setContentsMargins(40, 20, 40, 40); 

    // 1. Блок з умовою задачі (Варіант 8)
    QLabel *taskLabel = new QLabel(this);
    taskLabel->setText("ВАРІАНТ №8\nДано тризначне число. У ньому закреслили першу зліва цифру і приписали її справа. Вивести отримане число."); 
    taskLabel->setAlignment(Qt::AlignCenter);
    taskLabel->setWordWrap(true); // Дозволяємо перенесення тексту на нові рядки
    taskLabel->setStyleSheet(
        "QLabel {"
        "   color: #d1d1d6;"             
        "   background-color: #26262b;"
        "   border: 1px solid #3e3e44;"
        "   border-radius: 8px;"
        "   padding: 12px;"
        "   font-size: 13px;"            
        "   font-family: 'Arial';"
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

    // Ховаємо невикористовувану кнопку
    ui->btn_save->hide();

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

    if (!ok || num < 100 || num > 999) {
        QMessageBox::warning(this, "Помилка введення", "Будь ласка, введіть коректне тризначне число!");
        clear_data_fields();
    } 
    else {
        int hundreds = num / 100;           
        int remainder = num % 100;          
        result = remainder * 10 + hundreds; 

        ui->lbl_result->setText(QString::number(result));
    }
}

void MainWindow::on_btn_load_clicked()
{
    clear_data_fields(); 
}

void MainWindow::on_btn_save_clicked()
{
    // Порожній слот
}