/*
 cruzamento.cpp
    Classe criada por: Édio Pedro, Fabrício Leitão e Gabriel Diniz
    Engenharia Elétrica - IFPB
    Última atualização: 22/01/2020
*/

#include "Arduino.h"
#include "cruzamento.h"

Cruzamento::Cruzamento(){
  
}

Cruzamento::Cruzamento(int r1, int y1, int g1, int r2, int y2, int g2, int gp, int m1, int m2){
    r_1 = r1;
    y_1 = y1;
    g_1 = g1;
    r_2 = r2;
    y_2 = y2;
    g_2 = g2; 
    g_P = gp;
    m_1 = m1;
    m_2 = m2;
 
    pinMode(r_1, OUTPUT);
    pinMode(y_1, OUTPUT);
    pinMode(g_1, OUTPUT);
    pinMode(r_2, OUTPUT);
    pinMode(y_2, OUTPUT);
    pinMode(g_2, OUTPUT);
    pinMode(g_P, OUTPUT);
    pinMode(m_1, OUTPUT);
    pinMode(m_2, OUTPUT);
    pinMode(pinAnalog, INPUT);
}

void Cruzamento::LigarSemaforo(){
        digitalWrite(r_1, LOW);
        digitalWrite(y_1, LOW);
        digitalWrite(g_1, HIGH);
        digitalWrite(r_2, HIGH);
        digitalWrite(y_2, LOW);
        digitalWrite(g_2, LOW);

        ldrFalse();
}

void Cruzamento::liberarViaSecundaria(){

    time_millis = 0;
  
    ldrFalse();

    for(int i = 0; time_millis <= 35600; i++){
    
        if(time_millis == 0 ){
            digitalWrite(g_1, LOW);
        }
    
        if(time_millis == 500 ){
            digitalWrite(g_1, HIGH);
        }

        if(time_millis == 3000 ){
            digitalWrite(r_2, LOW);
        }

        if(time_millis == 3500 ){
            digitalWrite(r_2, HIGH);
        }

        if(time_millis == 5500 ){
            digitalWrite(g_1, LOW);
            digitalWrite(y_1, HIGH);
        }
    
        if(time_millis == 8500 ){
            digitalWrite(y_1, LOW);
            digitalWrite(r_1, HIGH);
        }

        if(time_millis == 10500 ){
            digitalWrite(r_2, LOW);
            digitalWrite(g_2, HIGH);
        }

        if(time_millis == 25000){
            digitalWrite(g_2, LOW);
        }

        if(time_millis == 25500 ){
            digitalWrite(g_2, HIGH);
        }

        if(time_millis == 28000 ){
            digitalWrite(r_1, LOW);
        }

        if(time_millis == 28500 ){
            digitalWrite(r_1, HIGH);
        }

        if(time_millis == 30500 ){
            digitalWrite(g_2, LOW);
            digitalWrite(y_2, HIGH);
        }
    
        if(time_millis == 33500 ){
            digitalWrite(y_2, LOW);
            digitalWrite(r_2, HIGH);
        }

        if(time_millis == 35500 ){
            digitalWrite(r_1, LOW);
            digitalWrite(g_1, HIGH);
        }

        verifSensors();

        delay(250);
        time_millis = time_millis + 250;
    }

    ldrFalse();
}


void Cruzamento::abrirPedestres(){
    time_millis = 0;
    
    ldrFalse();

    for(int i=0; time_millis<=22500; i++){

        if(time_millis == 0 ){
            digitalWrite(g_1, LOW);
        }
    
        if(time_millis == 500 ){
            digitalWrite(g_1, HIGH);
        }
    
        if(time_millis == 5500 ){
            digitalWrite(g_1, LOW);
            digitalWrite(y_1, HIGH);
        }
    
        if(time_millis == 8500 ){
            digitalWrite(y_1, LOW);
            digitalWrite(r_1, HIGH);
        }
        
        if(time_millis == 10500){
            digitalWrite(g_P, HIGH);
        }

        verifSensors();

        delay(250);
        time_millis = time_millis + 250;
    }
    
    ldrFalse();
}

void Cruzamento::fecharPedestres(){
    time_millis = 0;
    
    ldrFalse();

    for(int i=0; time_millis <=6100; i++){
        if(time_millis == 0){
            digitalWrite(g_P, LOW);
        }
        
        if(time_millis == 500){
            digitalWrite(g_P, HIGH);
        }

        if(time_millis == 1000){
            digitalWrite(g_P, LOW);
        }
    
        if(time_millis == 1500){
            digitalWrite(g_P, HIGH);
        }
    
        if(time_millis == 2000){
            digitalWrite(g_P, LOW);
        }

        if(time_millis == 2500){
            digitalWrite(g_P, HIGH);
        }

        if(time_millis == 3000){
            digitalWrite(g_P, LOW);
        }
    
        if(time_millis == 3500){
            digitalWrite(g_P, HIGH);
        }
    
        if(time_millis == 4000){
            digitalWrite(g_P, LOW);
        }

        if(time_millis == 6000){
            digitalWrite(r_1, LOW);
            digitalWrite(g_1, HIGH);
        }

        verifSensors();

        delay(250);
        time_millis = time_millis + 250;
    }

    ldrFalse();
}

void Cruzamento::amareloPiscando(){   
    digitalWrite(g_1, LOW);
    digitalWrite(r_2, LOW);
    delay(300);
    digitalWrite(y_1, LOW);
    digitalWrite(y_2, LOW); 
    delay(500);
    digitalWrite(y_1, HIGH);
    digitalWrite(y_2, HIGH);  
}

void Cruzamento::amareloParar(){
    
    digitalWrite(y_1, LOW);
    digitalWrite(y_2, LOW);
    digitalWrite(r_2, HIGH);
    digitalWrite(g_1, HIGH);
}

int Cruzamento::getQtdViaPrimaria(){
    return contador_via1;
}

int Cruzamento::getQtdViaSecundaria(){
    return contador_via2;
}

void Cruzamento::ldrFalse(){
    ldr_1_1 = false;
    ldr_1_2 = false;
    ldr_2_1 = false;
    ldr_2_2 = false;
    ldr_3_1 = false;
    ldr_3_2 = false;
    ldr_4_1 = false;
    ldr_4_2 = false;    
}

void Cruzamento::verifSensors(){

    //  Verificação do 1º sensor:

    if(analogMultiplexerRead(p0) < LUZ){
        ldr_1_1 = true;
    }
    
    if(ldr_1_1 == true && analogMultiplexerRead(p0) >= LUZ){
        ldr_1_2 = true;
    }

    if(ldr_1_1 == true && ldr_1_2 == true){
        contador_via2 = contador_via2 + 1;
        ldr_1_1 = false;
        ldr_1_2 = false;
    }

    //  Verificação do 2º sensor:

    if(analogMultiplexerRead(p1) < LUZ){
        ldr_2_1 = true;
    }
    
    if(ldr_2_1 == true && analogMultiplexerRead(p1) >= LUZ){
        ldr_2_2 = true;
    }

    if(ldr_2_1 == true && ldr_2_2 == true){
        contador_via1 = contador_via1 + 1;
        ldr_2_1 = false;
        ldr_2_2 = false;
    }

    //  Verificação do 3º sensor:

    if(analogMultiplexerRead(p2) < LUZ){
        ldr_3_1 = true;
    }
    
    if(ldr_3_1 == true && analogMultiplexerRead(p2) >= LUZ){
        ldr_3_2 = true;
    }

    if(ldr_3_1 == true && ldr_3_2 == true){
        contador_via2 = contador_via2 + 1;
        ldr_3_1 = false;
        ldr_3_2 = false;
    }

    //  Verificação do 4º sensor:

    if(analogMultiplexerRead(p3) < LUZ){
        ldr_4_1 = true;
    }
    
    if(ldr_4_1 == true && analogMultiplexerRead(p3) >= LUZ){
        ldr_4_2 = true;
    }

    if(ldr_4_1 == true && ldr_4_2 == true){
        contador_via2 = contador_via2 + 1;
        ldr_4_1 = false;
        ldr_4_2 = false;
    }
}

void Cruzamento::verifChegada(){
    
    if(analogMultiplexerRead(p0) < LUZ and estadoPedestres() == 0 and estadoAmarelo() == 0){
        liberarViaSecundaria();
    }
}

int Cruzamento::leituraLdr1(){
    return analogMultiplexerRead(p0);
}

int Cruzamento::leituraLdr2(){
    return analogMultiplexerRead(p1);
}

int Cruzamento::analogMultiplexerRead(byte portRead){
  digitalWrite(m_1, bitRead(portRead, 0));
  digitalWrite(m_2, bitRead(portRead, 1));
  delay(1);

  return  analogRead(pinAnalog);  
}

int Cruzamento::estadoPedestres(){
    if(digitalRead(g_P) == HIGH){
        return 1;
    }else{
        return 0;
    }
}

int Cruzamento::estadoAmarelo(){
    if(digitalRead(r_1) == LOW and digitalRead(g_1) == LOW and digitalRead(r_2) == LOW and digitalRead(g_2) == LOW){
        return 1;
    }else{
        return 0;
    }
}
