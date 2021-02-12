/*
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Arduino pin 6 -> HX711 CLK
 Arduino pin 5 -> HX711 DOUT
 Arduino pin 5V -> HX711 VCC
 Arduino pin GND -> HX711 GND 
*/

#include "HX711.h"

HX711 scale(5, 6);

float calibration_factor = 21.8; // this calibration factor is adjusted according to my load cell
//antara 21-22
//21.8 sudah mendekati

float units;  //bentuk gram

float ounces;

  long zero_factor;

void setup() {
  Serial.begin(9600);

  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

//tare
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

 zero_factor = scale.read_average(); //Get a baseline reading

  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
//tare

}

void loop() 
{

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");

  units = scale.get_units(), 10;

//kurang dari 0
  if (units < 0)
  {
    units = 0.00;
  }
//kurang dari 0

  ounces = units * 0.035274;

  Serial.print(units);
  Serial.print(" grams"); 


  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();




  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 0.1;      // 1 ke 0.1 ke 0.01
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 0.1;
  }
  
  
  delay(1000);
  
  
//  scale.power_down();			        // put the ADC in sleep mode
 // delay(1000);
  //scale.power_up();

}
