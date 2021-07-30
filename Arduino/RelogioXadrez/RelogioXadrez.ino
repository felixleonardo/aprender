//Relogio de Xadrez

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LCD(RS, E, D4, D5, D6, D7)


const int buzzer = 9; //Variável para o buzzer
int espera = 300;
int tempo = 0;
int minbrancas = 0;
int segbrancas = 0;
int minpretas = 0;
int segpretas = 0;
int inicio = 0;
int botaomais5 = 0;
int botaoinicio = 0;
int botaotroca = 0;
int jogador = 1;



void setup(){

    lcd.begin(16, 2);     //LCD com 16 colunas e 2 linhas
    lcd.setCursor(0,0);   //seta o cursor
    lcd.print("Relogio Xadrez"); //Mensagem de boas vindas com efeito scroll
    lcd.setCursor(2,1);
    lcd.print("by Leonardo");
    delay(3000);
    //Leva para esquerda
    for (int i=0; i<16; i++){
        lcd.scrollDisplayLeft();
        delay(100);
    }
    lcd.clear();            //Limpa o LCD

pinMode(6,INPUT_PULLUP); //Definição das entradas e saídas
pinMode(7,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
pinMode(8, OUTPUT);  
pinMode(buzzer,OUTPUT);
}


void loop() {
    if(inicio == 0){
        lcd.setCursor(0,0);
        lcd.print("Tempo:");
        lcd.setCursor(0,1);
        lcd.print(tempo);
        lcd.print(" Minutos");

        botaomais5 = digitalRead(6);
        if (botaomais5 == LOW){
            tempo = (tempo + 1);
            delay(espera);
        }
        botaoinicio = digitalRead(7);
        if (botaoinicio == LOW){
            inicio = 1;
            delay(espera);
            lcd.clear();
            minbrancas = tempo;
            minpretas = tempo;
         }
    }

    
    if(inicio == 1){
        lcd.setCursor(0,0);
        lcd.print("Brancas:   ");
        if(minbrancas<10){ lcd.print("0");}
        lcd.print(minbrancas);
        lcd.print(":");
        if(segbrancas<10){ lcd.print("0");}
        lcd.print(segbrancas);
        lcd.setCursor(0,1);
        lcd.print("Pretas:    ");
        if(minpretas<10){ lcd.print("0");}
        lcd.print(minpretas);
        lcd.print(":");
        if(segpretas<10){ lcd.print("0");}
        lcd.print(segpretas);
        botaotroca = digitalRead(10);
        if (botaotroca == LOW){
         jogador++;
         delay(espera);
        }
    if (jogador%2 == 0){
        if (segpretas == 0){
          minpretas--;
            if (minpretas < 0){
              inicio = 2;
            }
          segpretas = 60;
        }
        segpretas--;
        delay(1000);
    }else{
      if (segbrancas == 0){
        minbrancas--;
          if (minbrancas < 0){
            inicio = 2;
          }
        segbrancas = 60;        
      }
      segbrancas--;
      delay(1000);
    }
    }
    if (inicio == 2){
        if (minbrancas < 0){
            lcd.clear();
            lcd.print("Brancas perdeu!!!");
            digitalWrite(8,HIGH);  
            tone(buzzer,2581,500);   
            delay(100);
            //Desligando o buzzer.
            noTone(buzzer);
            delay(100);  
        }
        if (minpretas < 0){
            lcd.clear();
            lcd.print("Pretas perdeu!!!");
            digitalWrite(8,HIGH);  
            tone(buzzer,2581,500);   
            delay(100);
            //Desligando o buzzer.
            noTone(buzzer);
            delay(100);  

        }
    }
}
