 /* Created specifically for the Faculty Computer Technology of RTU MIREA
 *Author IVBO-04-20
 * Pavel Tsyngaliov
 * Sergey Pivovarov
 * Victor Iliun
 * Vadim Lavrentiev
 * Stanislav Vasin
 */
#include <Servo.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
//#include <TMRpcm.h>*/ // библиотека для воспроизведения звуковых файлов

Servo servoHeadRotateRightLeft1, servoHeadRotateRightLeft2,servoHeadRotateUpDown;
Servo servoHandTogSep1, servoHandTogSep2, servoHandUpDown1, servoHandUpDown2;

// Системные переменные
String getButton, buttonStatus;
byte angleLimiterTop ;
byte angleLimiterLow;
// Управление головой
byte angleNowRightLeft1=75;
byte angleNowRightLeft2=75;
byte angleNowUpDown=75;
// Управление руками робота
byte angleNowHandUpDown = 10;
byte angleNowHandTogSep = 75;

class HeadRotate // реализация изменения угла поворота
{
  private:
  byte angleRotate, angleTop, angleLow;
  public: 
  HeadRotate(byte angleNow=0, byte angleLimiterTop=10, byte angleLimiterLow=170)
  {
    this->angleRotate = angleNow;
    this->angleTop = angleLimiterTop;
    this->angleLow = angleLimiterLow;
    
  }
  byte headRotate(char button1, char button2, byte angleTop, byte angleLow)
  {
      if( button1 == '1' && button1 == '0' && angleRotate<angleTop )
    {
        angleRotate+=5;
    }
      if( button1 == '0' && button1 == '1' && angleRotate>angleLow )
    {
        angleRotate-=5; 
    }
    return angleRotate;
  }
};
class DriveTo // реализация управления гусеницами робота
{
  
};

class HandsMove : public HeadRotate // реализация манипуляторов робота
{
  // нет реализации в данной версии
};

class SoundVoice // реализация речи робота
{
  void VoiseWallE(byte whatSound){
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
   servoHandTogSep1.attach(5);
   servoHandTogSep2.attach(6);
   servoHandUpDown1.attach(7);
   servoHandUpDown2.attach(8);
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
  DriveTo MotorRigth, MotorLeft;
  HandsMove HandServo1(), HandServo2();
  //A  W  S  D  F  T  G  H  J  I  K  L  V  B  O  P
  //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
   if (Serial.available()){
      getButton = Serial.readStringUntil('!');
                  buttonStatus = "vityalox";

                  Serial.println(buttonStatus);
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
         servoHeadRotateUpDown.write(angleNowUpDown);
         delay(20);
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
         angleNowRightLeft1 = HeadServo2.headRotate(getButton[4], getButton[7], 160, 10);
         servoHeadRotateRightLeft1.write(angleNowRightLeft1);
         delay(20);
      }
      if((getButton[12] == '1' && getButton[13] == '0') || (getButton[12] == '0' && getButton[13] == '1')){
         if(getButton[12] == '1' && getButton[13] == '0'){
            buttonStatus = "Head 3 Right";
            Serial.println(buttonStatus);
         }
         if(getButton[12] == '0' && getButton[13] == '1'){
            buttonStatus = "Head 3 Left";
            Serial.println(buttonStatus);
         }
         angleNowRightLeft2 = HeadServo3.headRotate(getButton[12], getButton[13], 160, 10);
         servoHeadRotateRightLeft2.write(angleNowRightLeft2);
         delay(20);
      }
      // Ходовая
      
      // Реализация рук робота
      if ((getButton[8] == '1' && getButton[11] == '0') || (getButton[8] == '0' && getButton[11] == '1')){
        if(getButton[8] == '1' && getButton[11] == '0'){
          buttonStatus = "Hands separately";
          Serial.println(buttonStatus);
        }
        if(getButton[8] == '0' && getButton[11] == '1'){
          buttonStatus = "Hands together";
          Serial.println(buttonStatus);
        }
        //angleNowHandTogSep = HandServo1.headRotate(getButton[8], getButton[11], 160, 10);
        servoHandTogSep1.write(angleNowHandTogSep);
        servoHandTogSep2.write(angleNowHandTogSep);
        delay(20);
      }
      delay(10);  
  }
}
