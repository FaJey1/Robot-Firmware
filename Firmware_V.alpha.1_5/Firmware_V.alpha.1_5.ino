 /* Created specifically for the Faculty Computer Technology of RTU MIREA
 *Author IVBO-04-20
 * Pavel Tsyngaliov
 * Sergey Pivovarov
 * Victor Iliun
 * Vadim Lavrentiev
 * Stanislav Vasin
 */
#include <Servo.h> // подключаем библиотеку для сервопривода
/*#include <TMRpcm.h>*/ // библиотека для воспроизведения звуковых файлов
Servo servoHeadRotateRightLeft1, servoHeadRotateRightLeft2,servoHeadRotateUpDown;

String getButton, buttonStatus;
byte angleNowRightLeft1=75;
byte angleNowRightLeft2=75;
byte angleNowUpDown=75;
byte angleLimiterTop ;
byte angleLimiterLow;
// Управление шаговым двигателем
const byte MotorOneStepPin = 5;
const byte MotorOneDirectionPin = 6;
const byte MotorOneEnablePin = 7;
const byte MotorTwoStepPin = 8;
const byte MotorTwoDirectionPin = 9;
const byte MotorTwoEnablePin = 10;

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
  int headRotate(char button1, char button2, int angleTop, int angleLow)
  {
      if( button1 == '1' && button1 == '0' && angleRotate!=angleTop )
    {
        angleRotate+=5;
    }
      if( button1 == '0' && button1 == '1' && angleRotate!=angleLow )
    {
        angleRotate-=5; 
    }
    return angleRotate;
  }
};
class DriveTo // реализация управления гусеницами робота
{
  public: 
  int LetsGo()
  {
    if (Stepper1.distanceToGo() == 0)
    { //проверка, отработал ли двигатель предыдущее движение
    Stepper1.move(1600 * dir); //устанавливает следующее перемещение на 1600 шагов (если dir равен -1 будет перемещаться -1600 -> противоположное направление)
    dir = dir * (-1); //отрицательное значение dir, благодаря чему реализуется вращение в противоположном направлении
    delay(1000); //задержка на 1 секунду
    }
    Stepper1.run(); //запуск шагового двигателя. Эта строка повторяется вновь и вновь для непрерывного вращения двигателя
  }
    return 0;
  }
};

class HandsMove : public HeadRotate // реализация манипуляторов робота
{
  
};

class SoundVoice // реализация речи робота
{
  void VoiseWallE(int whatSound){
    switch(whatSound){
      case 1:{

        break;
      }
      case 2:{

        break;
      }
      case 3:{

        break;
      }
      case 4:{

        break;
      }
      case 5:{

        break;
      }
      case 6:{

        break;
      }
      default: break;
    }
  }
};

void setup() {
   Serial.begin(9600); //подключаем последовательный порт
   servoHeadRotateRightLeft1.attach(2);
   servoHeadRotateRightLeft2.attach(3);
   servoHeadRotateUpDown.attach(4);
   Stepper1.setMaxSpeed(2500); //устанавливаем максимальную скорость вращения ротора двигателя (шагов/секунду)
   Stepper1.setAcceleration(500); //устанавливаем ускорение (шагов/секунду^2)
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
  //A  W  S  D  F  T  G  H  J  I  K  L  V  B
  //0  1  2  3  4  5  6  7  8  9 10 11 12 13
   if (Serial.available()){
      getButton = Serial.readStringUntil('!');
     // Голова
      if((getButton[5] == '1' && getButton[6] == '0') || (getButton[5] == '0' && getButton[6] == '1')){
         if(getButton[5] == '1' && getButton[6] == '0'){
            buttonStatus = "Head up";
            Serial.println(buttonStatus);
         }
         if(getButton[5] == '0' && getButton[6] == '1'){
            buttonStatus = "Head down";
            Serial.println(buttonStatus);
         }
         angleNowUpDown = HeadServo1.headRotate(getButton[5], getButton[6], 135, 10);
         servoHeadRotateRightLeft1.write(angleNowUpDown);
         delay(100);
      }
      if((getButton[4] == '1' && getButton[7] == '0') || (getButton[4] == '0' && getButton[7] == '1')){
         if(getButton[4] == '1' && getButton[7] == '0'){
            buttonStatus = "Head 2 Right";
            Serial.println(buttonStatus);
         }
         if(getButton[4] == '0' && getButton[7] == '1'){
            buttonStatus = "Head 2 Left";
            Serial.println(buttonStatus);
         }
         angleNowUpDown = HeadServo3.headRotate(getButton[5], getButton[6], 135, 10);
         servoHeadRotateRightLeft1.write(angleNowUpDown);
         delay(100);
      }
      // Ходовая
      
      delay(10);
   }  
}
