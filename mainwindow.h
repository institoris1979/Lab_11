#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_calc_clicked();   // Слот для кнопки "Порахувати"
    void on_btn_load_clicked();   // Слот для кнопки "Завантажити"
    void on_btn_save_clicked();   // Слот для кнопки "Зберегти"
    void clear_data_fields();     // Допоміжна функція очищення полів

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H