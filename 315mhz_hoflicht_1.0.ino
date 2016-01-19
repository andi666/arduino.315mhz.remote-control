/*******************************************************************
Hoflicht , 315MHz AM , 2 Tasten-FB

laut: RF code sniffer: Protocol: 1 (https://github.com/sui77/rc-switch)

(A)s1:  24bit - Tri-State? "0101010101011100110000000" (dez: 5594304)
(B)s2:  24bit - Tri-State? "0101010101011100001100000" (dez: 5594160)

  24bit Tri-State
  eine Impulslänge ca. 0.48 ms

  '1' = 2xH + 1xL
  '0' = 1xH + 2xL

19-JAN-2016 andreas langkath , info@langkath.de

video: https://youtu.be/5DRBpCffIdQ
code: https://github.com/andi666/arduino.315mhz.remote-control

only for fun , under MIT license
*********************************************************************************************/
#include <Wire.h>   
#include <LiquidCrystal_I2C.h> // *** i2c-LCD!! -> SCL = A5 , SDA = A4
 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

static int TxPin = 6; // *** Pin.D6 = Tx
 
 
char* code; // *** nur dieser aendert sich je taste
 
int anazhl;
int n;
const int buttonPinS1 = 2;  // *** SW = D2
const int buttonPinS2 = 3;  // *** SW = D3
 

int buttonStateS1;             // the current reading from the input pin
int lastButtonStateS1 = HIGH;   // the previous reading from the input pin
long lastDebounceTimeS1 = 0;  // the last time the output pin was toggled
long debounceDelayS1 = 10;    // the debounce time; increase if the output flickers

int buttonStateS2;             // the current reading from the input pin
int lastButtonStateS2 = HIGH;   // the previous reading from the input pin
long lastDebounceTimeS2 = 0;  // the last time the output pin was toggled
long debounceDelayS2 = 10;    // the debounce time; increase if the output flickers

 
char* Aktion;
 
unsigned long LCD_aktion;
unsigned long Millis; 
unsigned long LCD_PreviousMillis;
long LCD_interval = 500; // *** LCD aktualisierung in ms

int LED_pin = 13;  // *** LED HERZSCHLAG
int LED_status = LOW;  // *** used to set the LED
long LED_setZeit = 0;  // *** will store last time LED was updated
long LED_interval = 666;  // *** (1000) LED-HERZSCHALG-Intervall (milliseconds)
int alte_sekunde; 

byte Herz[8] = {
  B00000,
  B01010,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
  B00000
};



void setup() {
 
   
   Serial.begin(57600); // *** 9600, 57600
   Serial.println();
   Serial.println(">start.");
   
   pinMode(LED_pin, OUTPUT); // *** für LED HERZSCHLAG
   lcd.begin(20,4);   // initialize the lcd for 20 chars 4 lines, turn on backlight (muss vor der Sonderzeichendefinierung stehen!)
   lcd.createChar(1,Herz); // *** eigene Sonder-Zeichen erstellen
   
   pinMode(buttonPinS1, INPUT);  // *** Taster aktivieren
   pinMode(buttonPinS2, INPUT);  // *** Taster aktivieren
 
   pinMode(TxPin, OUTPUT);  // *** Tx

   digitalWrite(TxPin, LOW );
    
   lcd.clear();
   //*** blink backlicht ****************************************
  for(int i = 0; i< 3; i++)  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); 
 
  
  
}  
 
void loop() {
   
  LED_HERZSCHLAG();    
  taster();
 
  LCD_Ausgabe() ;
  digitalWrite(TxPin, LOW ); // *** wichtig, damit das signal wirklich aus ist! 

}  

