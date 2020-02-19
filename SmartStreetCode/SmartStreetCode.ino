//leds yellow wire
int led1 = 3; //pwm pin
int led2 = 6;

//vcc nd gnd of soner from analog pins
//echo blue wire, trig green wire
int echo1 = 2;
int echo2 = 8;
int trig1 = 4;
int trig2 = 9;

//ldr white wire
int ldr = A3;

//variables for distance
int dist1, dist2;

//variables to count enter and exit
static int enter = 0;
static int ex = 0;

//distance calculation of US1
void sensor1check()
{
  digitalWrite(trig1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  int duration= pulseIn(echo1,HIGH);
  dist1=(0.034*duration)/2;  
}

//distance calculation of US2
void sensor2check()
{
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
  int duration= pulseIn(echo2,HIGH);
  dist2=(0.034*duration)/2;
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin (9600);
  pinMode (led1,OUTPUT);
  pinMode (led2,OUTPUT);
  pinMode (echo1,INPUT);
  pinMode (echo2,INPUT);
  pinMode (trig1,OUTPUT);
  pinMode (trig2,OUTPUT);
  pinMode (ldr,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
  //read data from LDR
  int ldrStatus = analogRead (ldr);
  
  //check Darkness
  if (ldrStatus <=300)
  {
    //digitalWrite(led1,HIGH);
    analogWrite(led1, 2);
    analogWrite(led2,2);
    //LED in Dim mode
    sensor1check();
    
    //check object entered
    if(dist1 >= 2 && dist1 <= 17) //roadwidth 15 cm
    {
      //object entered
      enter++;  
      while( enter !=ex){
        digitalWrite(led1,HIGH);
        //LED in High mode
        sensor2check();
        //check if object exited
        if(dist2 >= 2 && dist2 <= 17) 
        {
          //object exited
          delay(500);
          ex++; 
          
          //digitalWrite(led2,HIGH);
        }
      }
      digitalWrite(led2,HIGH);
      
      analogWrite(led1, 2);
      delay(10000);
 //LED in Dim mode
    } 
 /*   if(ex==1)
{     sensor2check();
      if(dist2>=2 && dist2<=17){
      digitalWrite(led2,HIGH);
        ex++;
      }
}*/
  }
  else
  { 
   digitalWrite(led2,LOW); 
    digitalWrite(led1, LOW); //in Daylight
  }
}
