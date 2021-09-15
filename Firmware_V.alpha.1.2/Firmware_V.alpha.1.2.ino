/* Created specifically for the Faculty Computer Technology of RTU MIREA
 *Author IVBO-04-20
 * Pavel Tsyngaliov
 * Sergey Pivovarov
 * Victor Iliun
 * Vadim Lavrentiev
 * Stanislav Vasin
 */
#include <Servo.h> // подключаем библиотеку для сервопривода
#include <SoftwareSerial.h>
/*#include <TMRpcm.h>*/ // библиотека для воспроизведения звуковых файлов
Servo servoHeadRotateRightLeft1, servoHeadRotateRightLeft2,servoHeadRotateUpDown;
SoftwareSerial mySerial(10, 11);
byte byteButton;
int button;
int angleNowRightLeft1=75;
int angleNowRightLeft2=75;
int angleNowUpDown=75;
int angleLimiterTop ;
int angleLimiterLow;

class HeadRotate // реализация изменения угла поворота
{
  private:
  int angleRotate, angleTop, angleLow;
  public:
  HeadRotate(int angleNow, int angleLimiterTop, int angleLimiterLow)
  {
    this->angleRotate = angleNow;
    this->angleTop = angleLimiterTop;
    this->angleLow = angleLimiterLow;
    
  }
  int headRotate(int button, int angleTop, int angleLow)
  {
      if( (button == 70) && angleRotate!=angleTop )
    {
        angleRotate+=5;
    }
    else
    {
        angleRotate-=5;
    }
      if( (button == 72) && angleRotate!=angleLow )
    {
        angleRotate-=5; 
    }
    else
    {
        angleRotate+=5;
    }
    return angleRotate;
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
   Serial.begin(9600); //подключаем последовательный порт
   mySerial.begin(4000);
   servoHeadRotateRightLeft1.attach(2);
   servoHeadRotateRightLeft2.attach(3);
   servoHeadRotateUpDown.attach(4);
}

void loop() {
   HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
   /*if (Serial.available()) 
   {*/
       /*mySerial.readBytes((byte*)&byteButton, sizeof(byteButton));
         button = (int)byteButton; Serial.write(button);*/
       button= Serial.read();
   if(button == 70 || button == 72)
   {
      angleLimiterTop = 160;
      angleLimiterLow = 10;
      angleNowRightLeft1=HeadServo1.headRotate(button, angleLimiterTop, angleLimiterLow);
      servoHeadRotateRightLeft1.write(angleNowRightLeft1);
      delay(150);
   }
   if(button == 71 || button == 84 )
   {
      angleLimiterTop = 135;
      angleLimiterLow = 30;
      angleNowUpDown=HeadServo3.headRotate(button, angleLimiterTop, angleLimiterLow);
      servoHeadRotateUpDown.write(angleNowUpDown);
      delay(150);
   }
}
