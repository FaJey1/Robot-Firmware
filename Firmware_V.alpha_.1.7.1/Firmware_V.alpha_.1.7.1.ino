/* Created specifically for the Faculty Computer Technology of RTU MIREA
 *Author IVBO-03-20 and IVBO-01-20
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

//Переменные для ходовой
const byte stepPin_Right = 11;
const byte directionPin_Right = 12;
const byte enablePin_Right = 13;
const byte stepPin_Left = 5;
const byte directionPin_Left = 6;
const byte enablePin_Left = 7;
int delayTime = 2;

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
  HandsMove(byte angleNow=0, byte angleLimiterTop=10, byte angleLimiterLow=170) : HeadRotate(){}
  byte headRotate (char button1, char button2, byte angleTop, byte angleLow){}
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

   //Порты моторов
   pinMode(stepPin_Right, OUTPUT);
   pinMode(directionPin_Right, OUTPUT);
   pinMode(enablePin_Right, OUTPUT);
   pinMode(stepPin_Left, OUTPUT);
   pinMode(directionPin_Left, OUTPUT);
   pinMode(enablePin_Left, OUTPUT);
}

//Функции для движения
void stepper_on(){
  digitalWrite(enablePin_Right, HIGH);
  digitalWrite(enablePin_Left, HIGH);
}

void stepper_off(){
  digitalWrite(enablePin_Right, LOW);
  digitalWrite(enablePin_Left, LOW);
}

void forward_direction(){
  digitalWrite(directionPin_Right, LOW);
  digitalWrite(directionPin_Left, HIGH);
}

void backward_direction(){
  digitalWrite(directionPin_Right, HIGH);
  digitalWrite(directionPin_Left, LOW);
}

void stepper_run(){
  stepper_on();
  int delta_i = 0;
  for (int i = 0; i <= 200; i++){
    digitalWrite(stepPin_Right, HIGH);
    digitalWrite(stepPin_Left, HIGH);
    delay(delayTime);
    digitalWrite(stepPin_Right, LOW);
    digitalWrite(stepPin_Left, LOW);
    delay(delayTime);
    if (delayTime <= 5 && delayTime >= 2 && (i - delta_i >= 50)){
      delta_i = i;
      delayTime--;
    }
  }
}

void loop() {
  HeadRotate HeadServo1(angleNowRightLeft1, 0, 0), HeadServo2(angleNowRightLeft2, 0, 0), HeadServo3(angleNowUpDown, 0, 0);
  DriveTo MotorRigth, MotorLeft;
  HandsMove HandServo1(angleNowHandTogSep, 0, 0), HandServo2(angleNowHandTogSep, 0, 0);
  //A  W  S  D  F  T  G  H  J  I  K  L  V  B  O  P
  //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
   if (Serial.available()){
      getButton = Serial.readStringUntil('!');
                  buttonStatus = "Status Ok, master";
                  Serial.println(buttonStatus);
     // Голова
      if(((getButton[5] == '1' && getButton[6] == '0') || (getButton[5] == '0' && getButton[6] == '1'))  && (angleNowRightLeft2 >=60 || <=180)){
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
      if(((getButton[4] == '1' && getButton[7] == '0') || (getButton[4] == '0' && getButton[7] == '1'))  && (angleNowRightLeft2 >=30 || <=150)){
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
      if(((getButton[12] == '1' && getButton[13] == '0') || (getButton[12] == '0' && getButton[13] == '1')) && (angleNowRightLeft2 >=30 || <=150)){
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
      // Руки вместе/в стороны
      if ((getButton[8] == '1' && getButton[11] == '0') || (getButton[8] == '0' && getButton[11] == '1')){
        if(getButton[8] == '1' && getButton[11] == '0'){
          buttonStatus = "Hands separately";
          Serial.println(buttonStatus);
        }
        if(getButton[8] == '0' && getButton[11] == '1'){
          buttonStatus = "Hands together";
          Serial.println(buttonStatus);
        }
        angleNowHandTogSep = HandServo1.headRotate(getButton[8], getButton[11], 160, 10);
        servoHandTogSep1.write(angleNowHandTogSep);
        servoHandTogSep2.write(angleNowHandTogSep);
        // Руки вниз/вверх
        
        delay(20);
      }
      // Ходовая часть
      
      if (getButton[1] == '1' && getButton[2] == '0'){
        buttonStatus = "Moving foward";
        Serial.println(buttonStatus);
        forward_direction();
        stepper_run();
        
        //Для реализации поворотов
        if(getButton[0] == '1' && getButton[3] == '0'){
        buttonStatus = "Turn right";
        Serial.println(buttonStatus);
          
        }
        if(getButton[0] == '0' && getButton[3] == '1'){
        buttonStatus = "Turn left";
        Serial.println(buttonStatus);
          
        }
      }
      if (getButton[1] == '0' && getButton[2] == '1'){
        buttonStatus = "Moving backward";
        Serial.println(buttonStatus);
        backward_direction();
        stepper_run();
        
        //Для реализации поворотов
        if(getButton[0] == '1' && getButton[3] == '0'){
        buttonStatus = "Turn right";
        Serial.println(buttonStatus);
          
        }
        if(getButton[0] == '0' && getButton[3] == '1'){
        buttonStatus = "Turn left";
        Serial.println(buttonStatus);
          
        }
      }

      //Вращение на одном месте вправо
      if (getButton[0] == '1' && getButton[3] == '0'){
      buttonStatus = "Clockwise rotation";
      Serial.println(buttonStatus);
        
      }

      //Вращение на одном месте влево
      if (getButton[0] == '0' && getButton[3] == '1'){
      buttonStatus = "Counterclockwise rotation";
      Serial.println(buttonStatus);
        
      }
      
      delay(10);  
  }
}
