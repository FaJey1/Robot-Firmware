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
// Переменная ускорения
int *a = 0;

class HeadRotate // реализация изменения угла поворота
{
  private:
  byte angleRotate, angleTop, angleLow;
  public: 
  HeadRotate(byte angleNow, byte angleLimiterTop, byte angleLimiterLow)
  {
    this->angleRotate = angleNow;
    this->angleTop = angleLimiterTop;
    this->angleLow = angleLimiterLow;
    
  }
  byte headRotate(char button1, char button2, byte angleTop, byte angleLow)
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
  byte stepRight, stepLeft;
  char stepFoward,stepBack;
  int accelerationValue;
  public:
  DriveTo(char stepFoward = '5', char stepBack = '5'){
    this->stepFoward = stepFoward;
    this->stepBack = stepBack;
  }
  int Acceleration(int accelerationValue){
    if(stepFoward == '1' && stepFoward == '0'){
      this->accelerationValue+=5;
    }
    else if(stepFoward == '0' && stepFoward == '1'){
      this->accelerationValue-=5;
    }
    return accelerationValue;
  }
  byte Foward(){
    
    return 0;
  }
  byte TurnRight(){
    
    return 0;
  }
  byte TurnLeft(){
    
    return 0;
  }
  byte Back();
};

class HandsMove : public HeadRotate // реализация манипуляторов робота
{
  
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
   //MotorRight
   pinMode(MotorOneStepPin, OUTPUT);
   pinMode(MotorOneDirectionPin, OUTPUT);
   pinMode(MotorOneEnablePin, OUTPUT);
   //MotorLeft
   pinMode(MotorTwoStepPin, OUTPUT);
   pinMode(MotorTwoDirectionPin, OUTPUT);
   pinMode(MotorTwoEnablePin, OUTPUT);
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
  DriveTo Motor;
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
      // Подача питания на двигатель
      digitalWrite(MotorOneEnablePin, HIGH);
      digitalWrite(MotorTwoEnablePin, HIGH);
      // Направление вперед
      a = Motor.Acceleration(a);
      if(getButton[0] == '1' && getButton[1] == '0' && a == 0){
         digitalWrite(MotorOneDirectionPin, HIGH);
         digitalWrite(MotorTwoDirectionPin, HIGH);
      }
      // Направление назад
      if(getButton[0] == '0' && getButton[1] == '1' && a == 0){
         digitalWrite(MotorOneDirectionPin, LOW);
         digitalWrite(MotorTwoDirectionPin, LOW);
      }
      // Цикл движения c учетом направления
      for(int i = 0; i < a; i++){
         digitalWrite(MotorOneStepPin, HIGH);
         digitalWrite(MotorTwoStepPin, HIGH);
         delay(20);
         digitalWrite(MotorOneStepPin, LOW);
         digitalWrite(MotorTwoStepPin, LOW);
         delay(20);
      }
      delay(10);
   }  
}
