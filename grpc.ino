#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int lightPin = 0;
const int temperaturePin = 1;

int lightLevel;
int calibratedlightLevel; // used to store the scaled / calibrated lightLevel
int maxThreshold = 0;     // used for setting the "max" light level
int minThreshold = 1023;   // used for setting the "min" light level

void setup()
{

  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();  //Clear any old data displayed on the LCD

}

void loop()
{

 lightLevel = analogRead(lightPin);
 lcd.setCursor(0, 0);
 lcd.print("LIGHT: ");
 lcd.print(lightLevel);

 float voltage, degreesC, degreesF;
 voltage = getVoltage(temperaturePin); //Measure the voltage at the analog pin
 degreesC = (voltage - 0.5) * 100.0; // Convert the voltage to degrees Celsius
 degreesF = degreesC * (9.0 / 5.0) + 32.0; //Convert degrees Celsius to Fahrenheit
 lcd.setCursor(0,1);
 lcd.print("TEMP: ");
 lcd.print(degreesF);
 
 delay(1000);
 
}

float getVoltage(int pin)   //Function to read and return
              //floating-point value (true voltage)
              //on analog pin 
{

  return (analogRead(pin) * 0.004882814); 
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}

//not used yet
void autoRange()
{
  if (lightLevel < minThreshold)  // minThreshold was initialized to 1023 -- so, if it's less, reset the threshold level.
    minThreshold = lightLevel;

  if (lightLevel > maxThreshold)  // maxThreshold was initialized to 0 -- so, if it's bigger, reset the threshold level.
    maxThreshold = lightLevel;

  // Once we have the highest and lowest values, we can stick them
  // directly into the map() function.
  // 
  // This function must run a few times to get a good range of bright and dark values in order to work.

  lightLevel = map(lightLevel, minThreshold, maxThreshold, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
}


