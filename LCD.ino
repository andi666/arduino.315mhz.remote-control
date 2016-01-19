// *** LCD beschreiben ******************************************
void LCD_Ausgabe() {

    Millis = millis();
    if ( Millis - LCD_PreviousMillis >= LCD_interval ) {  
        LCD_PreviousMillis = Millis; 
        
        //lcd.clear();
  
        lcd.setCursor(0,0); 
        lcd.print("Remote");
  
        lcd.setCursor(0,1);
        lcd.print(Aktion);
 
        if (millis() - LCD_aktion > 333){ // *** loesche die anzeige wieder nach x ms
            lcd.setCursor(0,1);
            lcd.print("          ");
        }
        
    }  
        
     
    
 
} 
  
