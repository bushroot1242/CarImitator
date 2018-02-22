#include <Servo.h>
//#include <SimpleTimer.h>


#define LIGTHS 2//фары
#define HELM 3//руль
#define BREAK 4//тормоз
#define DRIVE 5//двигатель
#define SOUND 6//гудок
#define RIGTH_LIGTH 13//Поворотники
#define LEFT_LIGTH 12



Servo helm;//имитация руля
int helmAngle = 25;
unsigned long int timeMillis, timePreview;

void setup()
{
  
  Serial.begin(9600);
  pinMode(LIGTHS, OUTPUT);
  pinMode(HELM, OUTPUT);
  pinMode(BREAK, OUTPUT);
  pinMode(DRIVE, OUTPUT);
  

  helm.attach(HELM);

  MoveToAngle(helmAngle);//начальное положение руля - колеса прямо

}
/*
  1."forward" - едем вперед
  2."back" - едем назад
  3."motor off" - выключить мотор
  4."ligth on" - фары включить
  5."ligth off" - фары выключить
  6."helm left" - лево руля (вешаем на прерывание)
  7."helm rigth" - право руля(вешаем на прерывание)
  8.Sound - звуковой сигнал
*/
int incomingByte = 0;
void loop()
{
  Voice();
  /*
  if (Serial.available() > 0) {
    // считываем входящий байт:
    incomingByte = Serial.read();
  }
  if (timeMillis % 100 == 0)
  {
    //Serial.println(100);
    timePreview = millis();
    if (incomingByte == 54) MoveHelmToRigth();
    if (incomingByte == 55) MoveHelmToLeft();
    if (incomingByte == 56) Voice();

  }
  if (timeMillis % 500 == 0)
  {
    //Serial.println(500);
    timePreview = millis();
    if (incomingByte == 49) MotorForward();
    if (incomingByte == 50) MotorBack();
    if (incomingByte == 51) MotorOff();
  }
  if (timeMillis % 1000 == 0)
  {
    //Serial.println(1000);
    timePreview = millis();
    if (incomingByte == 52) LigthOn();
    if (incomingByte == 53) LigthOff();
  }
 
  incomingByte = 0;
  Serial.flush();
  */
}

void MotorForward() {
  digitalWrite(BREAK, LOW);
  analogWrite(DRIVE, 240);
  Serial.println("Едем вперед ВЖЖЖЖЖЖ...");
}
void MotorBack() {
  digitalWrite(BREAK, LOW);
  analogWrite(DRIVE, 140);
  Serial.println("Едем назад ЖВВВВВВВ...");
}

void MotorOff() {
  analogWrite(DRIVE, 0);
  digitalWrite(BREAK, HIGH);
  Serial.println("Стоим((");
}
void LigthOn() {
  digitalWrite(LIGTHS, HIGH);
  Serial.println("Фары включены");
}
void LigthOff() {
  digitalWrite(LIGTHS, LOW);
  // Serial.print("Фары выключены");
}
void BrakOff() {
  // digitalWrite(BRAKE,HIGH);//потому что пнп транзистор, других тупо не было
}
void BrakOn() {
  // digitalWrite(LIGTHS,LOW);//потому что пнп транзистор, других тупо не было
}
//во избежании вской херни, работать с рулем через методы moveHelmToLeft и Rigth, ну или через геттеры и сеттеры на крайняк
void MoveHelmToLeft() {
  int angle = getHelmAngle() + 10;
  setHelmAngle(angle);
  helm.write(getHelmAngle());
  Serial.println("Лево руля");

}

void Voice() {
  int cur = millis();
  Serial.println("Би-Би");
  //tone(SOUND, 1000);
  digitalWrite(SOUND, HIGH);
  while (millis() - cur < 1000) {
  }
 //noTone(SOUND);
}

void MoveHelmToRigth() {
  int angle = getHelmAngle() - 10;
  setHelmAngle(angle);
  helm.write(getHelmAngle());
  Serial.println("Право руля");
}

void MoveToAngle(int angle) {
  helm.write(angle);
  setHelmAngle(angle);
  Serial.println("Руль в положении ");
  Serial.print(angle);
  Serial.println(" градусов");
}

int getHelmAngle() {
  return helmAngle;
}
void setHelmAngle(int angle) {
  if (angle > 50 || angle < 0)
    return;
  else (helmAngle = angle);
}

