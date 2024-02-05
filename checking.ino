int ldr=A0;//Set A0(Analog Input) for LDR.
int value;
float voltage;
float mg;
void setup() {
Serial.begin(9600);
pinMode(8,OUTPUT);
pinMode(7,OUTPUT);
}
//void loop (){}
void loop() {
 digitalWrite(8,HIGH);//Makes the LED glow in Dark
digitalWrite(7,LOW);
value=analogRead(ldr);//Reads the Value of LDR(light).
delay(1000);
int blue=value;
Serial.println("blue value is :");
Serial.println(blue);
digitalWrite(7,HIGH);
digitalWrite(8,LOW);
int green=analogRead(ldr);
Serial.println("green value is :");
Serial.println(green);
delay (1000);
int finale = blue - green; 
voltage= finale * (5.0/1023);
voltage = voltage +6;
mg= (-1.4* voltage) + 6.7;
Serial.println("bilirubin value is :");//Prints the value of LDR to Serial Monitor.
//Serial.println(value);
Serial.println(voltage);
Serial.println(mg);
delay(1000);

}

    
 
