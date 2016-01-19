/**************************************************************
Taster abfragen , mit Entprellung

... ist HIGH, beia Auloesung wird er LOW
***************************************************************/ 
void taster() {
  
    int readingS1 = digitalRead(buttonPinS1);  
    if (readingS1 != lastButtonStateS1) {
        lastDebounceTimeS1 = millis(); // reset the debouncing timer
    }
    if ((millis() - lastDebounceTimeS1) > debounceDelayS1) {
        if (readingS1 != buttonStateS1) { // if the button state has changed:
            buttonStateS1 = readingS1;
            if (buttonStateS1 == LOW) {
                 code = "0101010101011100110000000"; // 24bit Tri-State 5594304
                
                signalausloesen(code); // *** fire!
                lcd.setCursor(0,1);
                
                lcd.print("S1");
                //Serial.println();
                Serial.print(">S1 , ");
                Serial.println(code);
                LCD_aktion = millis();
            }
        }
    }
    lastButtonStateS1 = readingS1;





    int readingS2 = digitalRead(buttonPinS2);  
    if (readingS2 != lastButtonStateS2) {
        lastDebounceTimeS2 = millis(); // reset the debouncing timer
    }
    if ((millis() - lastDebounceTimeS2) > debounceDelayS2) {
        if (readingS2 != buttonStateS2) { // if the button state has changed:
            buttonStateS2 = readingS2;
            if (buttonStateS2 == LOW) {
                code = "0101010101011100001100000"; // *** 24bit Tri-State 5594160
                signalausloesen(code); // *** fire!
                lcd.setCursor(0,1);
                
                lcd.print("S2");
                //Serial.println();
                Serial.print(">S2 , ");
                Serial.println(code);
                LCD_aktion = millis();
            }
        }
    }
    lastButtonStateS2 = readingS2;

 

    

}

