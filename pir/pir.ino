// C++ code
//

#define pinPir 2
#define pinLed 3

int valorPir;

void setup()
{
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  pinMode(pinPir, INPUT);
}

void loop()
{
 valorPir = digitalRead(pinPir);
  
  if(valorPir == HIGH){
  	digitalWrite(pinLed, HIGH);
  }
  else{
  	digitalWrite(pinLed, LOW);
  }
}