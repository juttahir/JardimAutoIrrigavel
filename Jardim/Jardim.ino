#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

DS1302 rtc (6, 7, 8);              //Criação do objeto do tipo DS3231

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

  rtc.halt(false);
  rtc.writeProtect(false);
  lcd.backlight();
  lcd.init();
  lcd.begin(16, 2);
  //comment this section later
  // rtc.setDOW(FRIDAY);      //name of the day of the week
  //rtc.setTime(15, 28, 0);  //Hour, Min, Sec 
  //rtc.setDate(30, 6, 2023); //Day, Month, Year
  
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

    for(int i = 0; i < 5; i++){
      lcd.setCursor(0,1);
      lcd.print("Hora:");
      lcd.setCursor(5, 1);
      lcd.print(rtc.getTimeStr());
      lcd.setCursor(0, 0);
      lcd.print("Data:");
      lcd.setCursor(5,0);
      lcd.print(rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, '/'));
      //lcd.setCursor(13,1);
      //lcd.print(rtc.getDOWStr());
      delay (1000); 
      lcd.clear();
    }
     
    for(int i = 0; i < 5; i++){
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
        lcd.clear();
        while(horas == 13 && minutos == 0){
        Serial.println("Irrigando plantas");
        lcd.print("Irrigando plantas");
        digitalWrite(Borrifador01, LOW);
        digitalWrite(Borrifador02, LOW);
        break;
        }
      if(!horas == 13 && !minutos == 0){    
        digitalWrite(Borrifador01, HIGH);
        digitalWrite(Borrifador02, HIGH);
      }   
       
      lcd.clear();  
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