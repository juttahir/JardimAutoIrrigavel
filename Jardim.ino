#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

DS3231 rtc (A1, A2);              //Criação do objeto do tipo DS3231

const int pinoSensor = A0;
int valorLido;

int Borrifador01 = 4;
int Borrifador02 = 5;

int analogSoloSeco = 1023; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 0; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

int umidadeSolo = 55;

int LeituraSolo = analogRead(pinoSensor);
int Limite = 100;
int idealPlantas = 75;

void setup(){

 Serial.begin(115200); // Set baud rate for communication
  rtc.begin();            //Inicialização do RTC DS3231
  rtc.setTime(11,43,0);   //Configurando valores iniciais 
  rtc.setDate(25,12,2022);   //Configurando valores iniciais 
                                         //do RTC DS3231
 lcd.init();
  
 pinMode(Borrifador01, OUTPUT);
 pinMode(Borrifador02, OUTPUT);
 Serial.begin(9600); //INICIALIZA A SERIAL
 Serial.println("Lendo a umidade do solo Bonsai...");
 delay(2000);
}

void loop(){

    lcd.clear();

    Time t = rtc.getTime();

    int horas = t.hour;
    int minutos = t.min;
    int segundos = t.sec;

    int data = t.date; 

  Serial.print(data);       //Imprimindo o Dia
  Serial.print(" ");
  Serial.print(horas);      //Imprimindo a Hora
  Serial.print(":");
  Serial.print(minutos);    //Imprimindo o Minuto
  Serial.print(":");
  Serial.print(segundos);   //Imprimindo o Segundo
  Serial.println("");
  delay(1000);              //Tempo p atualização do valor enviado pela porta


    Serial.print("Hora:  ");
    Serial.print(rtc.getTimeStr()); // Use getTimeStr to get time from the RTC
    Serial.print("Data: ");
    Serial.print(rtc.getDateStr()); // Use getDatwStr to get date from the sensor
    delay(1000);
     
     valorLido = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco);
     valorLido = map(valorLido,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco);
     Serial.print("Umidade do solo das plantas: ");
     Serial.print(valorLido);
     Serial.println("%");
     lcd.setBacklight(HIGH);
     lcd.setCursor(0,0);
     lcd.print("Umidade do solo");
     lcd.setCursor(0,1);
     lcd.print("Plantas: ");
     lcd.print(valorLido);
     lcd.print("%");
     delay(1000);
     
    if(horas == 13 && minutos == 0){
      while(valorLido != idealPlantas){
      Serial.println("Irrigando plantas");
      lcd.print("Irrigando plantas");
      digitalWrite(Borrifador01, LOW);
      digitalWrite(Borrifador02, LOW);
      break;
      }
    if(horas == 13 && minutos == 1){    
      digitalWrite(Borrifador01, HIGH);
      digitalWrite(Borrifador02, HIGH);
    }     
  }

  // if(valorLido <= umidadeSolo){
  //    while(valorLido != idealPlantas){
  //    Serial.println("Irrigando plantas");
  //    lcd.print("Irrigando plantas");
  //    digitalWrite(Borrifador01, LOW);
  //    digitalWrite(Borrifador02, LOW);
  //    break;
  //    }
  // }
  // if(valorLido >= idealPlantas){
  //    digitalWrite(Borrifador01, HIGH);
  //    digitalWrite(Borrifador02, HIGH);
  // }
  }