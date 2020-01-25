#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort serial;

    int verif_status_amarelo;
    int verif_status_pedestres;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_conectar_clicked();
    void dados_recebidos();

    void on_btn_desconectar_clicked();

    void on_botao_ligar_amarelo_clicked();

    void on_botao_desligar_amarelo_clicked();

    void on_botao_ligar_pedestres_clicked();

    void on_botao_desligar_pedestres_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
