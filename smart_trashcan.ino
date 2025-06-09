#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int IR1 = 2;  // Define pin 2 as IR1 input pin for IR sensor
const int IR2 = 3;  // Define pin 3 as IR2 input pin for IR sensor

const int IN1 = 6;  // Define pin 6 as IN1 motor driver input pin for motor
const int IN2 = 7;  // Define pin 7 as IN2 motor driver input pin for motor

void setup() {
  // put your setup code here, to run once:
  pinMode(IR1, INPUT);  // Set IR1 pin as input
  pinMode(IR2, INPUT);  // Set IR2 pin as input
  pinMode(IN1, OUTPUT); // Set IN1 pin as output
  pinMode(IN2, OUTPUT); // Set IN2 pin as output
  Serial.begin(9600);  // Initialize serial communication with baud rate 9600

  lcd.init();  // Initialize the LCD display
  lcd.clear(); // Clear the LCD display
  lcd.backlight();  // Turn on the LCD backlight
  lcd.clear();  // Clear the LCD display
  lcd.setCursor(0, 0);  // Set cursor to character 0 on line 0
  lcd.print("SMART DUST");  // Display "SMART DUST" on the LCD

  lcd.setCursor(0, 1);  // Set cursor to character 0 on line 1
  lcd.print("BIN");  // Display "BIN" on the LCD
  delay(1000);  // Delay for 1 second
  digitalWrite(IN1, LOW);  // Set IN1 pin to LOW (stop motor)
  digitalWrite(IN2, LOW);  // Set IN2 pin to LOW (stop motor)
}

void loop() {
  // Check if IR1 sensor detects an obstacle
  if (digitalRead(IR1) == 0) {
    digitalWrite(IN1, LOW);  // Set IN1 pin to LOW (stop motor)
    digitalWrite(IN2, HIGH);  // Set IN2 pin to HIGH (rotate motor in one direction)

    lcd.clear();  // Clear the LCD display
    lcd.backlight();  // Turn on the LCD backlight
    lcd.clear();  // Clear the LCD display
    lcd.setCursor(0, 0);  // Set cursor to character 0 on line 0
    lcd.print("DUST BIN");  // Display "DUST BIN" on the LCD

    lcd.setCursor(0, 1);  // Set cursor to character 0 on line 1
    lcd.print("OPEN");  // Display "OPEN" on the LCD
    delay(1500);  // Delay for 1.5 seconds (lid open duration)

    digitalWrite(IN1, LOW);  // Set IN1 pin to LOW (stop motor)
    digitalWrite(IN2, LOW);  // Set IN2 pin to LOW (stop motor)
    delay(2000);  // Delay for 2 seconds (lid open duration)

    lcd.clear();  // Clear the LCD display
    lcd.backlight();  // Turn on the LCD backlight
    lcd.clear();  // Clear the LCD display
    lcd.setCursor(0, 0);  // Set cursor to character 0 on line 0
    lcd.print("DUST BIN");  // Display "DUST BIN" on the LCD

    lcd.setCursor(0, 1);  // Set cursor to character 0 on line 1
    lcd.print("CLOSING");  // Display "CLOSING" on the LCD

    digitalWrite(IN1, HIGH);  // Set IN1 pin to HIGH (rotate motor in the opposite direction)
    digitalWrite(IN2, LOW);  // Set IN2 pin to LOW (rotate motor in the opposite direction)
    delay(1500);  // Delay for 1.5 seconds (lid closing duration)

    digitalWrite(IN1, LOW);  // Set IN1 pin to LOW (stop motor)
    digitalWrite(IN2, LOW);  // Set IN2 pin to LOW (stop motor)
    delay(1000);  // Delay for 1 second (lid closed duration)
  }

  // Check if IR2 sensor detects an obstacle (dustbin full)
  if (digitalRead(IR2) == 0) {
    lcd.clear();  // Clear the LCD display
    lcd.backlight();  // Turn on the LCD backlight
    lcd.clear();  // Clear the LCD display
    lcd.setCursor(0, 0);  // Set cursor to character 0 on line 0
    lcd.print("DUST BIN");  // Display "DUST BIN" on the LCD

    lcd.setCursor(0, 1);  // Set cursor to character 0 on line 1
    lcd.print("FULL");  // Display "FULL" on the LCD
    delay(1000);  // Delay for 1 second
  }

  // Check if IR2 sensor does not detect an obstacle (dustbin empty)
  if (digitalRead(IR2) == 1) {
    lcd.clear();  // Clear the LCD display
    lcd.backlight();  // Turn on the LCD backlight
    lcd.clear();  // Clear the LCD display
    lcd.setCursor(0, 0);  // Set cursor to character 0 on line 0
    lcd.print("DUST BIN");  // Display "DUST BIN" on the LCD

    lcd.setCursor(0, 1);  // Set cursor to character 0 on line 1
    lcd.print("EMPTY");  // Display "EMPTY" on the LCD
  }
}

