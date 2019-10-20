#include <TimedAction.h>

#define LED_100   11
#define LED_500   12
#define LED_1000  10


void Led_100_Thread_fun()
{
  digitalWrite(LED_100, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_100, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
  while(1); 
}

void Led_500_Thread_fun()
{
  digitalWrite(LED_500, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_500, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}

void Led_1000_Thread_fun()
{
 digitalWrite(LED_1000, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(1000);                       // wait for a second
 digitalWrite(LED_1000, LOW);    // turn the LED off by making the voltage LOW
 delay(1000);                       // wait for a second  
}

TimedAction Led_100_Thread = TimedAction(50,Led_100_Thread_fun);
TimedAction Led_500_Thread = TimedAction(50,Led_500_Thread_fun);
TimedAction Led_1000_Thread = TimedAction(50,Led_1000_Thread_fun);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1000, OUTPUT);
  pinMode(LED_500, OUTPUT);
  pinMode(LED_100, OUTPUT);
}

void loop() {
  Led_100_Thread.check();
  Led_500_Thread.check();
  Led_1000_Thread.check();
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
}
