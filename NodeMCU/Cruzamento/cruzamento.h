/*
 cruzamento.h
    Classe criada por: Édio Pedro, Fabrício Leitão e Gabriel Diniz
    Engenharia Elétrica - IFPB
    Última atualização: 22/01/2020
*/

#ifndef CRUZAMENTO_H
#define CRUZAMENTO_H

#include "Arduino.h"

#define pinAnalog A0
#define LUZ 100

class Cruzamento{
  private:
    //abaixo: pinos vermelho, amarelo e verde do semaforo primario e depois do secundário e posteriormente dois pinos de uso do multiplexador
    int r_1, y_1, g_1, r_2, y_2, g_2, g_P, m_1, m_2; 

    int time_millis;

    bool ldr_1_1;
    bool ldr_1_2;
    bool ldr_2_1;
    bool ldr_2_2;
    bool ldr_3_1;
    bool ldr_3_2;
    bool ldr_4_1;
    bool ldr_4_2;

    byte p0 = 0;
    byte p1 = 1;
    byte p2 = 2;
    byte p3 = 3;

    int contador_via1 = 0, contador_via2 = 0;
  public:
    Cruzamento();  
    Cruzamento(int r1, int y1, int g1, int r2, int y2, int g2, int gp, int m1, int m2);

    void LigarSemaforo();

    void liberarViaSecundaria();

    void abrirPedestres();

    void fecharPedestres();

    void amareloPiscando();

    void amareloParar();

    int getQtdViaSecundaria();

    int getQtdViaPrimaria();

    void ldrFalse();

    void verifSensors();

    void verifChegada();

    int leituraLdr1();

    int leituraLdr2();

    int analogMultiplexerRead(byte portRead);

    int estadoPedestres();

    int estadoAmarelo();

};

#endif
