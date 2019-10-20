/*
char a;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() 
{
    if(Serial.available())
    {
      a = Serial.read();
      Serial.write(a);
      Serial.println("in if");
    } 
//    Serial.println("In loop");
//    Serial.write('U');
    delay(100); 

}
*/

int num=10; 
String my_name;
char count;
 
void setup() 
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Program start!");
}
void loop() 
{   
    num = 0;
    if((num = Serial.available()) > 0)
    {
      my_name = Serial.readStringUntil('\n');
//      Serial.print("Nice to meet you, " + my_name + "!  ");
//      Serial.println(" your name later count : ");
//      sprintf(count,"%d",num);
      Serial.print(my_name);
      Serial.print(my_name.length());
    }
//    for(int i=0;i<num;i++)
//    Serial.println("count no ");
//    delay(500);
}
