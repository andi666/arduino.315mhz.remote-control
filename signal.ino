void signalausloesen(char* code){
 
    fire_init();
    fire_code(code);
    
    digitalWrite(TxPin, LOW );  
    delay(100); 
    
    fire_code(code);

    digitalWrite(TxPin, LOW );  
    delay(100); 

    fire_code(code);
 
}


void fire_code(char* code){ // *** code absenden
  
    anazhl = strlen(code);  
    n = 0;
    while (n < anazhl){
 
        if ( code[n] == 49 ) { 

          // *** '1' , 24bit Tri-State?
          digitalWrite(TxPin, HIGH );
          delayMicroseconds(1490);  
          digitalWrite(TxPin, LOW );  
          delayMicroseconds(460);  
          
        } else {
          // *** '0' , 24bit Tri-State?
          digitalWrite(TxPin, HIGH );
          delayMicroseconds(495);  
          digitalWrite(TxPin, LOW );  
          delayMicroseconds(1420);  
        }
         
        n++;
    }
     
}

void fire_init(){ // *** init absenden

     // hierbei eigendlich kein init von noeten...
    digitalWrite(TxPin, LOW );  
    delayMicroseconds(1000); 

}
    
 

