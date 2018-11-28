int LEDON = LOW;
int LEDOFF = HIGH;

int sensorPin = A0; //Kosteusanturin pinni 
int led = 13; //Ledin pinni
int thresholdUp = 400; //Kosteusarvon yläraja -> pumppu kiinni
int thresholdDown = 250; //Kosteusarvon alaraja -> pumppu päälle

void setup() {
  Serial.begin(9600); //
  pinMode(led, OUTPUT); //
}

void loop() {
  int sensorValue;
  String DisplayWords;

  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);

  if(sensorValue <= thresholdDown){
    
    //Määritetään viesti ja vilkku, kun kasvi tarvitsee vettä
    DisplayWords = "Kasvilla on jano!";                             
    digitalWrite(led, LEDON);   //Ledi päälle
      delay(500);              //Sekunnin viive 
    digitalWrite(led, LEDOFF); //Ledi pois päältä
      delay(500);              //Sekunnin viive
    Serial.print(DisplayWords); //Viesti muistutukseksi
  
  }else if (sensorValue >= thresholdUp){

    //Määritetään viesti, kun kasvin tarpeet tyydytetty
    DisplayWords = "Jano sammutettu!";
    Serial.print(DisplayWords);
  
  }else{

    Serial.print(DisplayWords);
        
  }

  delay(500); //Puolen sekunnin viive lukemisen helpottamiseksi

}
