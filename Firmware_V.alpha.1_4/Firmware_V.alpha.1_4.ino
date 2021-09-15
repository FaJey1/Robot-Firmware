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

String getButton, buttonStatus;
byte angleNowRightLeft1=75;
byte angleNowRightLeft2=75;
byte angleNowUpDown=75;
byte angleLimiterTop ;
byte angleLimiterLow;
// Управление шаговым двигателем
const byte stepPin = 5;
const byte directionPin = 6;
const byte enablePin = 7;
// Выдержка для регулировки скорости вращения
byte delayTime = 20;


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
  int headRotate(String button, int angleTop, int angleLow)
  {
      if( (button == "70") && angleRotate!=angleTop )
    {
        angleRotate+=5;
    }
    else
    {
        angleRotate-=5;
    }
      if( (button == "72") && angleRotate!=angleLow )
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
   servoHeadRotateRightLeft1.attach(2);
   servoHeadRotateRightLeft2.attach(3);
   servoHeadRotateUpDown.attach(4);
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
   if (Serial.available()) 
   {
      getButton = Serial.readStringUntil('!');
      if(getButton == "70" || getButton == "72"){ // Поворот головы вправо/влево
        angleLimiterTop = 160;
        angleLimiterLow = 10;
        if (getButton == "70"){
          buttonStatus = "Head right";
          Serial.println(buttonStatus);
          angleNowRightLeft1=HeadServo1.headRotate(getButton, angleLimiterTop, angleLimiterLow);
          servoHeadRotateRightLeft1.write(angleNowRightLeft1);
          delay(150);
        }
        if (getButton == "72"){
          buttonStatus = "Head left";
          Serial.println(buttonStatus);
          angleNowRightLeft1 = HeadServo1.headRotate(getButton, angleLimiterTop, angleLimiterLow);
          servoHeadRotateRightLeft1.write(angleNowRightLeft1);
          delay(150);
        }
      }
      if(getButton == "71" || getButton == "84"){ // Поворот головы вверх/вниз
        angleLimiterTop = 135;
        angleLimiterLow = 30;
        if (getButton == "84"){
          buttonStatus = "Head up";
          Serial.println(buttonStatus);
          angleNowRightLeft1 = HeadServo1.headRotate(getButton, angleLimiterTop, angleLimiterLow);
          servoHeadRotateRightLeft1.write(angleNowRightLeft1);
          delay(150);
        }
        if (getButton == "71"){
          buttonStatus = "Head down";
          Serial.println(buttonStatus);
          angleNowRightLeft1 = HeadServo3.headRotate(getButton, angleLimiterTop, angleLimiterLow);
          servoHeadRotateRightLeft1.write(angleNowRightLeft1);
          delay(150);
        }
      }
      delay(50);
   }  
}
