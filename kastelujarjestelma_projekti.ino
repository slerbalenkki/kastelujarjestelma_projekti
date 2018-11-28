#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int LEDON = LOW;
int LEDOFF = HIGH;

int SENON = HIGH;
int SENOFF = LOW;

//int senPlus = 10;
const int senPlus = 10;   //Kosteusanturin plus-pinnin ulostulo
int senState = HIGH;
unsigned long previousMillis = 0;
const long interval = 5000;

int sensorPin = A0;       //Kosteusanturin 5v sisääntulo 
int led = 13;             //Ledin pinni
int thresholdUp = 400;    //Kosteusarvon yläraja -> pumppu kiinni
int thresholdDown = 250;  //Kosteusarvon alaraja -> pumppu päälle
int sensorValue;



void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  pinMode(senPlus, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Hello beautiful!"); 
  delay(2000);
}


//Määritetään viesti ja vilkku, kun kasvi tarvitsee vettä
void Jano(){
    String DisplayWords;
    DisplayWords = "Kasvilla jano!";                             
    /*digitalWrite(led, LEDON);   //Ledi päälle
      delay(500);               //Viive 
    digitalWrite(led, LEDOFF);  //Ledi pois päältä
      delay(500);               //Viive*/
    Serial.print(DisplayWords); //Viesti muistutukseksi
    lcd.setCursor(0, 0);
    lcd.print(DisplayWords);
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
}


//Määritetään viesti, kun kasvin tarpeet on tyydytetty
void kyllainen(){
    String DisplayWords;
    DisplayWords = "Jano sammutettu!";
    Serial.print(DisplayWords);
    digitalWrite(led, LEDOFF);  //Ledi pois päältä, kun kasvi ei tarvitse vettä
    lcd.setCursor(0, 0);
    lcd.print(DisplayWords);
    lcd.setCursor(0, 1);
    lcd.print(sensorValue);
}


/*Määritetään sensorin virransyöttö
void   
  digitalWrite(senPlus, SENON);
*/  

void anturi(){

  sensorValue = analogRead(sensorPin); 
  Serial.println(sensorValue);
  if(sensorValue >= thresholdDown){  
    Jano(); 
  }else if (sensorValue <= thresholdUp){
    kyllainen(); 
  }else{
    String DisplayWords;
    Serial.print(DisplayWords);
  }
}


void loop() {
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >=interval){
    previousMillis = currentMillis;

    if(senState == HIGH) {
      senState = LOW;
      digitalWrite(senPlus, SENON);
           
    }else{
      anturi();
      senState = HIGH;
      digitalWrite(senPlus, SENOFF);
    }
  }
  

  //delay(500); //Viive lukemisen helpottamiseksi
  
}
