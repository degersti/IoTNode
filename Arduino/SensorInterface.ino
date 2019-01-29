/*=======================================================
 * Author:      Markus Gerstenberg
 * Institution: FH Vorarlberg 2018
 * Project:     Developement of a small industrie 4.0 node
 *========================================================
 * This code is used to acquire values from a potentiometer 
 * and send them over uart to sensor-node
 */
#define STATUS_LED 9        // LED Output pin
#define ANALOG_PIN A0       // Analog pin fpr Potentiometer
#define MAX_VALUE 700       // Value for overhead
int sensorValue = 0;        // analog value variable
/*********************************************************/           
void setup() {
  /* initialize serial communications at 9600 Baud */
  Serial.begin(9600);           
  pinMode(STATUS_LED,OUTPUT);   
}
/*********************************************************/ 
void loop() {
  /* read the analog in value */
  sensorValue = analogRead(ANALOG_PIN);
  /* send value over uart */
  Serial.println(sensorValue);
  /* set LED to high if overheat is detected */
  if(sensorValue >= MAX_VALUE){
    digitalWrite(STATUS_LED, HIGH);
    }
  else{
    digitalWrite(STATUS_LED, LOW);
    }
  /* Wait 1/4 second */
  delay(250);
}
/*********************************************************/ 
