#include <Arduino_FreeRTOS.h>
#define LED_100   11
#define LED_500   12
#define LED_1000  10

void Led_100_Thread_fun(void *pvParameters);
void Led_500_Thread_fun(void *pvParameters);
void Led_1000_Thread_fun(void *pvParameters);

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1000, OUTPUT);
  pinMode(LED_500, OUTPUT);
  pinMode(LED_100, OUTPUT);
  xTaskCreate(Led_100_Thread_fun ,(const portCHAR *)"100", 128, NULL, 2, NULL );
  xTaskCreate(Led_500_Thread_fun ,(const portCHAR *)"500", 128, NULL, 2, NULL );
  xTaskCreate(Led_1000_Thread_fun ,(const portCHAR *)"1000", 128, NULL, 2, NULL );
}



void loop()
{
  // Empty. Things are done in Tasks.
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void Led_100_Thread_fun(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
  digitalWrite(LED_100, HIGH);
  vTaskDelay( 100 / portTICK_PERIOD_MS );
  digitalWrite(LED_100, LOW);
  vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
   
}

void Led_500_Thread_fun(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
  digitalWrite(LED_500, HIGH);
  vTaskDelay( 500 / portTICK_PERIOD_MS ); 
  digitalWrite(LED_500, LOW); 
  vTaskDelay( 500 / portTICK_PERIOD_MS );                
  }
}

void Led_1000_Thread_fun(void *pvParameters)
{
  (void) pvParameters;
  while(1)
  {
 digitalWrite(LED_1000, HIGH);   // turn the LED on (HIGH is the voltage level)
 vTaskDelay( 1000 / portTICK_PERIOD_MS );
 digitalWrite(LED_1000, LOW);    // turn the LED off by making the voltage LOW
 vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
