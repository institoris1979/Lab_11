#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ==========================================
    // НАЛАШТУВАННЯ СТИЛЬНОГО ТЕМНОГО ІНТЕРФЕЙСУ
    // ==========================================
    this->setStyleSheet("QMainWindow { background-color: #1a1a1e; }");
    this->resize(450, 480);

    // Створюємо менеджер компоновки з оптимальними відстанями
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(25);
    layout->setContentsMargins(40, 35, 40, 45);

    // 1. Чіткий білий заголовок угорі вікна
    QLabel *titleLabel = new QLabel(this);
    titleLabel->setText("РГР 311 Пасніченко М");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #ffffff;"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   font-family: 'Arial';"
        "}"
        );
    layout->addWidget(titleLabel);

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

    // 3. Кнопка "Порахувати" з ЖОВТОЮ рамкою
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

    // 4. Окно результатів (Label) з ЗЕЛЕНОЮ рамкою
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

    // 5. Кнопка "Очистити" з червоним акцентом при наведенні
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

    // Приховуємо невикористовувану кнопку збереження
    ui->btn_save->hide();

    // Додаємо елементи в менеджер компоновки
    layout->addWidget(ui->le_input);
    layout->addWidget(ui->btn_calc);
    layout->addWidget(ui->lbl_result);
    layout->addWidget(ui->btn_load);

    // Прив'язуємо компоновку до вікна
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

// Математична логіка Варіанта №8
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

// Кнопка "Очистити" працює через скидання полів
void MainWindow::on_btn_load_clicked()
{
    clear_data_fields();
}

// Порожній слот для прихованої кнопки
void MainWindow::on_btn_save_clicked()
{
    // Кнопка прихована
}