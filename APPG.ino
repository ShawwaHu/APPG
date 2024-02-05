#include <OneWire.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
char keys[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte RP[4]={2,3,4,5};
byte CP[4]={6,7,8,A2};
Keypad keypad =Keypad(makeKeymap(keys), RP, CP,4,4);
int senRead= A1; 
int transistor = 13; 
int buzzer = 12; 
int var=0;
int tempe = 10;
int blueLed = 9;
int photodiode = 11; 
int counter = 0; 
int attempts = 0; 
int max_attempts = 3; 
String mymints;
int minutes = 0;  
String mysecs; 
int seconds = 0; 
long int total_seconds = 0; 
int secflag = 0; 
int timer_started_flag = 0; 
// Tracks the time since last event fired
unsigned long previousMillis=0;
unsigned long int previoussecs = 0; 
unsigned long int currentsecs = 0; 
unsigned long currentMillis = 0;
int interval= 1 ; // updated every 1 second
int tsecs = 0; 
bool temp=false;
float voltage=0;
float concentration=0;
bool brake=false;


void setup() {
  sensors.begin();
  pinMode(blueLed,OUTPUT);
//  pinMode(photodiode,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(transistor, OUTPUT);
  digitalWrite(transistor, LOW);
  digitalWrite(blueLed, LOW);
  //digitalWrite(photodiode,HIGH);
  lcd.begin();
  lcd.backlight();
  lcd.print("Welcome to APPG");
  delay(2000);
  lcd.clear();
  lcd.print("A: Checking");
  lcd.setCursor(0,1);
  lcd.print("B: Treating");
  Serial.begin(9600);
  
}


void loop() {
//  MeasureCon();
    char key = keypad.getKey();
    while (key == 'A'){
     MeasureCon();} 
    while (key == 'B'){
      digitalWrite(blueLed,LOW);
      keypadfunction();}
      }

     
void keypadfunction()
{ 
  noTone(12);
  lcd.setCursor(0,0);
  lcd.print("Enter Minutes");
 char key = keypad.getKey();
  while (key == 'A'){loop();}
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
    
  }
  
  if (key == '1')
  {
 
    mymints = mymints + 1;   
  }
  
    if (key == '2')
  {
 
    mymints = mymints + 2;  
  }
  
  if (key == '3')
  {
 
    mymints = mymints + 3; 
  }
  
   if (key == '4')
  {
  
    mymints = mymints + 4;  
  }
  
  if (key == '5')
  {
  
    mymints = mymints + 5;
  }
  
   if (key == '6')
  {
   
    mymints = mymints + 6; 
  }
  
   if (key == '7')
  {
 
    mymints = mymints + 7; 
  }
 
   if (key == '8')
  {
 
    mymints = mymints + 8; 
  }
  
  if (key == '9')
  {
 
    mymints = mymints + 9;
  }
             
                 if (key == '0')
  {
 
    mymints = mymints + 0; 
  }

 
                    if (key == '#')
  {
 
    counter = 0;
    mymints = ""; 
    minutes = 0;  
    mysecs = ""; 
    seconds = 0; 
    secflag = 0;  
    noTone(12); 
    lcd.clear(); 
    lcd.setCursor(0,0); 
    keypadfunction();; 
  }
  
  
        if (key == '*')
  {
lcd.clear();     
minutes = mymints.toInt();
Serial.println(minutes);
lcd.clear(); 
lcd.print("Minutes: "); 
lcd.setCursor(0,1); 
lcd.print(minutes); 
mymints = ""; // empty the string
delay(2000); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Enter Seconds:");
 while (key == 'A'){loop();}
counter = 0; 
secflag = 1; 
 
while(secflag == 1)
{
forSeconds(); 
}    
  }  
   
}
 
void forSeconds()
{ 
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }
  
  if (key == '1')
  {
 
   mysecs = mysecs + 1;   
  }
  
    if (key == '2')
  {
 
   mysecs = mysecs + 2;  
  }
  
  if (key == '3')
  {
 
    mysecs = mysecs + 3; 
  }
  
   if (key == '4')
  {
  
    mysecs = mysecs + 4;  
  }
  
  if (key == '5')
  {
  
    mysecs = mysecs + 5;
  }
  
   if (key == '6')
  {
   
    mysecs = mysecs + 6; 
  }
  
   if (key == '7')
  {
 
    mysecs = mysecs + 7; 
  }
 
   if (key == '8')
  {
 
    mysecs = mysecs + 8; 
  }

if (key == '9')
  {
 
    mysecs = mysecs + 9;
  }
             
                 if (key == '0')
  {
 
    mysecs = mysecs + 0; 
  }

if (key == '#')
  {
 
    counter = 0;
    mymints = ""; 
    minutes = 0;  
    mysecs = ""; 
    seconds = 0; 
    secflag = 0;  
    noTone(12);
    lcd.clear(); 
    lcd.setCursor(0,0); 
    keypadfunction(); 
  }
  
  
  
        if (key == '*')
  {
 //
lcd.clear();     
seconds = mysecs.toInt();
Serial.println(seconds);
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("Seconds: "); 
lcd.setCursor(0,1); 
lcd.print(seconds); 
mysecs = ""; // empty the string
total_seconds = (minutes * 60) + seconds ;
counter = 0;
secflag = 0; 
timer_started_flag = 1;
 
lcd.clear();
lcd.print("T Seconds:");
lcd.setCursor(11,0);
lcd.print( total_seconds );
delay(3000); 
while( timer_started_flag == 1)
{
   char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
 
  }
 
   if (key == '#')
  {
 
    counter = 0;
    mymints = ""; 
    minutes = 0;  
    mysecs = ""; 
    seconds = 0; 
    secflag = 0;  
    total_seconds = 0; 
    timer_started_flag = 0;
    noTone(12);
    lcd.clear(); 
    lcd.setCursor(0,0); 
    keypadfunction();
  }

 
         //  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("Timer=");
  lcd.setCursor(7,0); 
  lcd.print( total_seconds );
  lcd.setCursor(12,0);
  lcd.print("S");
  lcd.setCursor(0,1);
  lcd.print("Temp=");
  sensors.requestTemperatures(); 
  float t=sensors.getTempCByIndex(0); 
  lcd.print(t);
  lcd.setCursor(12,1);
  lcd.print("C   ");
  //run
  if( total_seconds > 0)
  {
    digitalWrite(transistor, HIGH); 
    printT();
  //lcd.print("load ON "); 
  }
 
    if( total_seconds <= 0)
  {
    total_seconds = 0; 
    digitalWrite(transistor, LOW);
    tone(12,1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("End of session"); 
    
  }
 
     currentMillis = millis();
   currentsecs = currentMillis / 1000; 
    if ((unsigned long)(currentsecs - previoussecs) >= interval) {
      total_seconds = total_seconds - 1;
      lcd.clear(); 
      previoussecs = currentsecs;
    }
}
 
  }  
  
  
}
void printT(){
        char key = keypad.getKey();
        sensors.requestTemperatures(); 
        float t=sensors.getTempCByIndex(0); 
        lcd.setCursor(6,1);
        lcd.print(t);
        Serial.println(t);
        if (key == 'A'){
           lcd.clear();
           brake = false;}
           if (brake == false){
           lcd.clear();
           loop();
    }
        if(t>40.0||t<0.0){
               char key = keypad.getKey();
               counter = 0;
               mymints = ""; 
               minutes = 0;  
               mysecs = ""; 
               seconds = 0; 
               secflag = 0;  
               lcd.clear();
               tone(12,1000); 
               digitalWrite(transistor, LOW);
               lcd.setCursor(0,0); 
               lcd.print("WARNING");
               lcd.setCursor(0,1);
               lcd.print("TEMPERATURE:");
               lcd.setCursor(12,1);
               lcd.print(t);
               delay(6000); 
               total_seconds = 0; 
               timer_started_flag = 0;
               lcd.setCursor(0,0);
                if (key == 'A'){
                   lcd.clear();
                   brake = false;}
                   if (brake == false){
                   lcd.clear();
                   digitalWrite(blueLed,LOW);
                   loop();
                   while (key == 'B'){loop();}
                          } 
}
        }
void MeasureCon(){
   
    char key = keypad.getKey();
     while (key == 'B'){loop();}
    int val=analogRead(senRead);
    Serial.println(val);
    digitalWrite(blueLed,HIGH); 
    lcd.setCursor(3,0);
    delay (200);
    voltage= val*(5.0/1023.0);
    concentration=((-1.4*voltage)+6.7);
    concentration = concentration - 2;
    delay (1000);
    //concentration= map(concentration,-27,27,0,20);
  //  while (key == 'A'){
  
  lcd.clear();    
  lcd.setCursor(0,0);
  lcd.print("C= ");
  lcd.print(concentration); 
  Serial.println("concentration: ");
  Serial.println(concentration);
  Serial.println("voltage: ");
  Serial.println(voltage);
  lcd.setCursor(9,0);
  lcd.print("mg/dL");  
  lcd.setCursor(0,1);
  //lcd.print(voltage);
  if (key == 'B'){
    lcd.clear();
    brake = true;}
  if (brake == true){
    lcd.clear();
    loop();
    while (key == 'B'){loop();}
    }
    }
