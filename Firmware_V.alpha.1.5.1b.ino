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
Servo HandRight1, HandLeft1, HandRight2, HandLeft2;

String getButton, buttonStatus;
// Управление головой
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
int *a1 = 0;
int *a2 = 0;
// Управление руками робота
byte angleNowHandUpDown = 10;
byte angleNowHandRightLeft = 75;

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
  //char stepRight, stepLeft;
  //char stepFoward,stepBack;
  int accelerationValue;
  public:
  /*DriveTo(char stepFoward = '5', char stepBack = '5', char stepRight, char stepLeft){
    this->stepFoward = stepFoward;
    this->stepBack = stepBack;
    this->stepRight = stepRight; 
    this->stepLeft = stepLeft;
  }*/
  int Acceleration(int accelerationValue, char stepFoward, char stepBack){
    if(stepFoward == '1' && stepBack == '0'){
      this->accelerationValue+=5;
    }
    else if(stepFoward == '0' && stepBack == '1'){
      this->accelerationValue-=5;
    }
    return accelerationValue;
  }
};

class HandsMove : public HeadRotate // реализация манипуляторов робота
{
  // хз что писать
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
   //HandRight
   HandRight1.attach(11);
   HandRight2.attach(13);
   //HandLeft
   HandLeft1.attach(12);
   HandLeft2.attach(14);
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
  DriveTo Motor;
  HandsMove HandServo1(angleNowHandUpDown, 0, 0), HandServo2(angleNowHandRightLeft, 0, 0);
  //A  W  S  D  F  T  G  H  J  I  K  L  V  B  O  P
  //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
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
      a1 = Motor.Acceleration(a1, getButton[1], getButton[2]);
      a2 = Motor.Acceleration(a2, getButton[1], getButton[2]);
      // учет поворота
      int cof = 2; // коэф нужно посчитать как R1/R2, где R -- радиус при повороте
      if (getButton[0] == '1' && getButton[3] == '0'){
        a1 = cof*(*a2);
      }
      if (getButton[0] == '0' && getButton[3] == '1'){
        a2 = cof*(*a1);
      }
      if(getButton[1] == '1' && getButton[2] == '0' && a1 == 0 && a2 == 0){
         digitalWrite(MotorOneDirectionPin, HIGH);
         digitalWrite(MotorTwoDirectionPin, HIGH);
      }
      // Направление назад
      if(getButton[1] == '0' && getButton[2] == '1' && a1 == 0 && a2 ==0){
         digitalWrite(MotorOneDirectionPin, LOW);
         digitalWrite(MotorTwoDirectionPin, LOW);
      }
      // Цикл движения c учетом направления
      if(a1 >= a2){
        for(int i = 0; i < a1; i++){
          digitalWrite(MotorOneStepPin, HIGH);
           for(int i = 0; i < a2; i++){
              digitalWrite(MotorTwoStepPin, HIGH);
              digitalWrite(MotorTwoStepPin, LOW);
              delay(20);
          }
          digitalWrite(MotorOneStepPin, LOW);
          delay(20);
        }
      }
      else if(a1 < a2){
        for(int i = 0; i < a2; i++){
          digitalWrite(MotorTwoStepPin, HIGH);
           for(int i = 0; i < a1; i++){
              digitalWrite(MotorOneStepPin, HIGH);
              digitalWrite(MotorOneStepPin, LOW);
              delay(20);
          }
          digitalWrite(MotorTwoStepPin, LOW);
          delay(20);
        }
      }
      // Реализация рук робота
      /*if (){
        
      }*/
      delay(10);  
  }
}
