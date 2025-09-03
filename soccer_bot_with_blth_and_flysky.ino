
#include <IBusBM.h>

#define lf 10
#define lb 11

#define rf 5
#define rb 6

#define sp 8


int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;
int ch5 = 0;
int ch6 = 0;


int pwm = 255;
char ascicode;


int sv;



int leftmspeed = 0;
int rightmspeed = 0;
int rightm;
int leftm;
int leftmspeedf;
int rightmspeedf;
int leftmspeed1 = 0;
int rightmspeed1= 0;

IBusBM ibus;

int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 

bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup()
{
  
  Serial.begin(115200);
  ibus.begin(Serial1);

  pwm =255;

  pinMode (rb , OUTPUT);
  pinMode (rf , OUTPUT);
  pinMode (lf , OUTPUT);
  pinMode (lb , OUTPUT);
  pinMode (sp , INPUT_PULLUP);
  

  
  
}

void forward()
{
  analogWrite (lf , pwm);
  analogWrite (lb , 0);
  
  
  analogWrite (rf , pwm);
  analogWrite (rb , 0);
  
  
}


void backward()
{
  analogWrite (lf , 0);
  analogWrite (lb , pwm);

  
  
  analogWrite (rf , 0);
  analogWrite (rb , pwm);
    

  
}

void right()
{
  analogWrite (lf , pwm);
  analogWrite (lb , 0);

  
  
  analogWrite (rf , 0);
  analogWrite (rb , pwm);
  
  
}


void left ()
{
  analogWrite (lf , 0);
  analogWrite (lb , pwm);

  


  
  analogWrite (rf , pwm);
  analogWrite (rb , 0);
   
  
}

void forwardright()
{
   analogWrite (lf , pwm);
  analogWrite (lb , 0);
  
  
  analogWrite (rf , 0);
  analogWrite (rb , 0);
  
  
}

void forwardleft()
{
   analogWrite (lf , 0);
  analogWrite (lb , 0);

  
  
  analogWrite (rf , pwm);
  analogWrite (rb , 0);
  
  
}

void backwardright()
{
  analogWrite (lf , 0);
  analogWrite (lb , pwm);

  
  
  analogWrite (rf , 0);
  analogWrite (rb , 0); 

  
}


void backwardleft ()
{
  analogWrite (lf , 0);
  analogWrite (lb , 0);

  

  
  analogWrite (rf , 0);
  analogWrite (rb , pwm);
    
  
}

void stop()
{
  analogWrite (lf , 0);
  analogWrite (lb , 0);

 

  
  analogWrite (rf , 0);
  analogWrite (rb , 0);
  
  
}



void loop ()
{
  sv = digitalRead(sp);

  Serial.println (sv);

  if (sv==1)
  {
    ch1 = readChannel (0 , -100 , 100 , 0);
 ch2 = readChannel (1 , -100 , 100 , 0);
 ch3 = readChannel (2 , 0 , 155 , 0);
 ch4 = readChannel (3 , -100 , 100 , 0);
 ch5 = readChannel (4 , -100 , 100 , 0);
 ch6 = readSwitch (5 , false);

 


 leftmspeed = ch3;
 rightmspeed = ch3;
 
 
 if (ch6)                          //spin mode
 {

  Serial.println("Spin mode");
  
                                       
  if (ch4>0){
    analogWrite (lf, leftmspeed);
    analogWrite (lb , 0);              // right spin
    analogWrite (rb,rightmspeed );
    analogWrite (rf , 0);
  }

  else if (ch4<0) {
    analogWrite (lf, 0);
    analogWrite (lb , leftmspeed);
    analogWrite (rf, rightmspeed);     // left spin
    analogWrite (rb , 0);
  }

   else if (ch4 == 0 ){
     analogWrite (lf, 0);
    analogWrite (lb , 0);            // stop spin
    analogWrite (rf, 0);
    analogWrite (rb , 0); 
  }
  

  
  
  leftmspeed = leftmspeed + abs (ch4);         // spin mode speed
  rightmspeed = rightmspeed + abs (ch4); 
 

 }

 else                                       // normal mode
 {

   if (ch2>0)
   {
    analogWrite (lf, leftmspeed1);
    analogWrite (lb , 0);              // forward
    analogWrite (rb, 0 );
    analogWrite (rf , rightmspeed1);
   }

   else if (ch2<0){
    analogWrite (lf, 0);
    analogWrite (lb , leftmspeed1);              //backward
    analogWrite (rb, rightmspeed1);
    analogWrite (rf , 0);
   }

   else if (ch2==0){

    analogWrite (lf, 0);
    analogWrite (lb , 0);              // normal stop
    analogWrite (rb, 0 );
    analogWrite (rf , 0);
    
   }


   rightm = ch3 + abs (ch2);       
   leftm = ch3 + abs(ch2);

   rightmspeedf = leftm - ch1;       //left / right direction speed
   leftmspeedf= rightm + ch1;

 

    rightmspeed1 = constrain (rightmspeedf , 0 ,255);
    leftmspeed1 = constrain (leftmspeedf , 0 , 255);

    Serial.print("left =");
    Serial.print (leftmspeed1);
    Serial.print ("     Right");
    Serial.println (rightmspeed1);

 }
  }

 if (sv==0 )
 {
  ascicode = Serial.read();

  Serial.println (ascicode );

   if(ascicode == '0'){
  pwm = 0; }
 else if(ascicode == '1'){
  pwm = 30; }
 else if(ascicode == '2'){
  pwm = 60; }
 else if(ascicode == '3'){
  pwm = 90; }
 else if(ascicode == '4'){
  pwm = 120; }
 else if(ascicode == '5'){
  pwm = 150; }
 else if(ascicode == '6'){
  pwm = 180; }
 else if(ascicode == '7'){
  pwm = 210; }
 else if(ascicode == '8'){
  pwm = 240; }
 else if(ascicode == '9'){
  pwm = 255; }
   

   switch (ascicode)
{
  case 'F' : forward()           ; break ;
  case 'B' : backward()          ; break ;
  case 'L' : left()              ; break ;
  case 'R' : right()             ; break ;
  case 'G' : forwardleft()       ; break ;
  case 'I' : forwardright()      ; break ;
  case 'H' : backwardleft()      ; break ;
  case 'J' : backwardright()     ; break ;
  case 'S' : stop()              ; break ;
  case 'D' : stop()              ; break ;
  default  :                       break ;
  
}
 }

  
  
}
