#include <Wire.h>
#include <LiquidCrystal_SR.h>


// Defining LCD and Pins for interfacing.
//74hc595 pin connection in array sequence : ( 14/data enable, 11/clock, 12/latch)
LiquidCrystal_SR lcd(2, 4, 3);


void setup(){

lcd.begin(16,2); // Initializing LCD
//lcd.home (); // Setting Cursor at Home i.e. 0,0

}

void loop()

{
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" >> Subscribe <<"); // Print Something on LCD
lcd.setCursor(3,1);
lcd.print("Neuro Tech ");


delay(2000); // Waiting for a while


lcd.clear(); // Clearing LCD
lcd.setCursor(0,0);
lcd.print("Thanks for"); // Print Something on LCD
lcd.setCursor(5,1);
lcd.print("watching");
delay(2000); // Waiting for a while


}
