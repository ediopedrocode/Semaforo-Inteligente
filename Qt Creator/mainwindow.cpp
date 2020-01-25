#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&serial,
            SIGNAL(readyRead()),
            this,
            SLOT(dados_recebidos()));

    for(auto& item : QSerialPortInfo::availablePorts())
           ui->box_serial->addItem(item.portName());

    for(auto& item : QSerialPortInfo::standardBaudRates())
           ui->box_velocidade->addItem(QString::number(item));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btn_conectar_clicked()
{
    serial.setPortName(ui->box_serial->currentText());
    serial.setBaudRate(ui->box_velocidade->currentText().toInt());

    if (serial.open(QIODevice::ReadWrite)){
        ui->status_porta->setText("Conectado");
    }
}

void MainWindow::dados_recebidos()
{
    auto data = serial.readAll();
    auto dados = QJsonDocument::fromJson(data).object().toVariantMap();

    if(dados.contains("QTD_VIA1")){
        ui->qtd_1->setText(dados["QTD_VIA1"].toString());
    }

    if(dados.contains("QTD_VIA2")){
        ui->qtd_2->setText(dados["QTD_VIA2"].toString());
    }

    if(dados.contains("ORDEM_AMARELO")){
        verif_status_amarelo = dados["ORDEM_AMARELO"].toInt();

        if(verif_status_amarelo == 1)
            ui->status_amarelo->setText("LIGADO");
        else
            ui->status_amarelo->setText("DESLIGADO");
    }

    if(dados.contains("ORDEM_VERMELHO")){
        verif_status_pedestres = dados["ORDEM_VERMELHO"].toInt();

        if(verif_status_pedestres == 1)
            ui->status_pedestres->setText("LIGADO");
        else
            ui->status_pedestres->setText("DESLIGADO");
    }
}

void MainWindow::on_btn_desconectar_clicked()
{
    serial.close();
    ui->status_porta->setText("Desconectado");
}

void MainWindow::on_botao_ligar_amarelo_clicked()
{
    serial.write("{\"ORDEM_AMARELO\": 1");
}

void MainWindow::on_botao_desligar_amarelo_clicked()
{
    serial.write("{\"ORDEM_AMARELO\": 0");
}

void MainWindow::on_botao_ligar_pedestres_clicked()
{
    serial.write("{\"ORDEM_VERMELHO\": 1");
}

void MainWindow::on_botao_desligar_pedestres_clicked()
{
    serial.write("{\"ORDEM_VERMELHO\": 0");
}
