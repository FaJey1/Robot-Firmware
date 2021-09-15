// Created specifically for the Department of Computer Engineering of RTU MIREA
/*Author
 * Pavel Tsyngaliov
 * Victor Ilyin
 * Ivan Kuleshov
 */
#include <Servo.h> // подключаем библиотеку для сервопривода
Servo servoHeadRotateRightLeft1, servoHeadRotateRightLeft2,servoHeadRotateUpDown;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
byte byteButton;
int buttonRightLeft1; // освобождаем память в контроллере для переменой
int angleNowRightLeft1=90;
int angleNowRightLeft2=90;
int angleNowUpDown=45;

class HeadRotate // реализация изменения угла поворота
{
  public:
  int angleNow;
  int headRotateRightLeft(int Button, int angleNow)
  {
      if( Button == 70 && (angleNow!=0 || angleNow!=180) )
    {
        angleNow+=10;
    }
      if( Button == 72 && (angleNow!=0 || angleNow!=180))
    {
        angleNow-=10; 
    }
    return angleNow;
  }
  
};
class DriveTo // реализация управления гусеницами робота
{
  public: 
  int LetsGo()
  {
    return 0;
  }
};

class HandsMove : public HeadRotate // реализация манипуляторов робота
{
  
};

class SoundVoice // реализация речи робота
{
  
};

void setup() {
   Serial.begin(9600); // подключаем последовательный порт
   servoHeadRotateRightLeft1.attach(2);
   servoHeadRotateRightLeft2.attach(3);
   servoHeadRotateUpDown.attach(4);
}

void loop() {
   HeadRotate HeadServo1;
   if (Serial.available()) 
   {
      /*mySerial.readBytes((byte*)&byteButton, sizeof(byteButton));*/
      buttonRightLeft1 = Serial.read();
      Serial.write(buttonRightLeft1);
   }
    angleNowRightLeft1=HeadServo1.headRotateRightLeft(buttonRightLeft1, angleNowRightLeft1);
    servoHeadRotateRightLeft1.write(angleNowRightLeft1);
    delay(250);
}
