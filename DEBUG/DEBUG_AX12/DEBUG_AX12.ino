#include "AX12_CAN.h"

AX12_CAN AX12;

void setup(){
  Serial.begin(115200);
}

void loop(){
  
  while( 1 ) {
    Serial.println( "coucher" );
    AX12.setPosition(6, 200, 138, 1023);
    delay( 2500 );
    
    Serial.println( "lever" );
    AX12.setPosition(6, 500, 138, 1023);
    delay( 2500 );
  }
  
  Serial.println( "Descendre tous" );
  for( int i = 1; i <= 4; i++ ){
  Serial.println( i );
    AX12.setPosition(i, 230, 138, 1023);
    delay( 800 );
  }
  AX12.setPosition(201, 230, 138, 1023);

    
  delay( 2500 );

  
  Serial.println( "Monter tous" );
  AX12.setPosition(201, 620, 138, 1023);
  delay( 800 );
  AX12.setPosition(201, 620, 138, 1023);

    
  delay( 2500 );
  
  
  Serial.println( "Moyen tous" );
  AX12.setPosition(201, 450, 95, 1023);
  delay( 800 );
  AX12.setPosition(201, 450, 95, 1023);

    
  delay( 2500 );

  
  Serial.println( "Monter tous" );
  AX12.setPosition(201, 620, 138, 1023);
  delay( 800 );
  AX12.setPosition(201, 620, 138, 1023);

    
  delay( 2500 );
}


