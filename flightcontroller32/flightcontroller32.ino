

// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>




#define CE_PIN  22
#define CSN_PIN 21


const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char buf[40];

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

int val=0;

void setup() {

    Serial.begin(115200);
    
    pinMode(13,INPUT);
    pinMode(12,INPUT);
    pinMode(14,INPUT);
    pinMode(15,INPUT);
    pinMode(2,INPUT);
    pinMode(4,INPUT);
    

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {

    boolean enviar=false;
  
    String dato="";
 
    val=analogRead(A3);
    dato+=val;dato+=";";
    if((val<490)||(val>550)) { enviar=true; }

    val=analogRead(A0);val=4095-val;
    dato+=val;dato+=";";
    if((val<490)||(val>550)) { enviar=true; }

    val=analogRead(A7);val=4095-val;
    dato+=val;dato+=";";
    if((val<490)||(val>550)) { enviar=true; }

    val=analogRead(A6);
    dato+=val;dato+=";";
    if((val<490)||(val>550)) { enviar=true; }    

    if(digitalRead(13)==HIGH) { dato+="1;";} else {dato+="0;";}
    if(digitalRead(12)==HIGH) { dato+="1;";} else {dato+="0;";}
    if(digitalRead(14)==HIGH) { dato+="1;";} else {dato+="0;";}
    if(digitalRead(15)==HIGH) { dato+="1;";} else {dato+="0;";}
    if(digitalRead(2)==HIGH) { dato+="1;";} else {dato+="0;";}
    if(digitalRead(4)==HIGH) { dato+="1;";} else {dato+="0;";}
    

    dato+="@";
    
    dato.toCharArray(buf,dato.length());

    //Serial.println(dato);
    send();

    delay(100);
}

//====================

void send() {

    bool rslt;
    rslt = radio.write(&buf,sizeof(buf));
   
    Serial.print("Data Sent ");
    Serial.print(buf);
    if (rslt) {
        Serial.println("  Acknowledge received");        
    }
    else {
        Serial.println("  Tx failed");
    }
}
