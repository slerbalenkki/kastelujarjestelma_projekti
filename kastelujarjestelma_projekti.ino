#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int LEDON = LOW;
int LEDOFF = HIGH;

int sensorPin = A0;       //Kosteusanturin pinni 
int led = 13;             //Ledin pinni
int thresholdUp = 400;    //Kosteusarvon yläraja -> pumppu kiinni
int thresholdDown = 250;  //Kosteusarvon alaraja -> pumppu päälle

void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Hello beautiful!"); 
  delay(2000);
}

void loop() {
  int sensorValue;
  String DisplayWords;

  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);

  if(sensorValue >= thresholdDown){
    
    //Määritetään viesti ja vilkku, kun kasvi tarvitsee vettä
    DisplayWords = "Kasvilla jano!";                             
    digitalWrite(led, LEDON);   //Ledi päälle
      delay(500);               //Viive 
    digitalWrite(led, LEDOFF);  //Ledi pois päältä
      delay(500);               //Viive
    Serial.print(DisplayWords); //Viesti muistutukseksi
    lcd.setCursor(0, 0);
    lcd.print(DisplayWords);
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
  
  }else if (sensorValue <= thresholdUp){

    //Määritetään viesti, kun kasvin tarpeet tyydytetty
    DisplayWords = "Jano sammutettu!";
    Serial.print(DisplayWords);
    digitalWrite(led, LEDOFF);  //Ledi pois päältä, kun kasvi ei tarvitse vettä
    lcd.setCursor(0, 0);
    lcd.print(DisplayWords);
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
  }else{

    Serial.print(DisplayWords);
        
  }

  delay(500); //Viive lukemisen helpottamiseksi

}
