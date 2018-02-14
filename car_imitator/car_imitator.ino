#include <Servo.h>
//#include <SimpleTimer.h>


#define FORWARD 2// двигатель вперед
#define BACK 3// двигатель назад
#define LIGTHS 4//фары
//#define BRAKE 5//тормоз
#define HELM 6



//кнопки для имитации поступления сигнала
#define HELM_RIGTH_BUTTON 8// РУЛЬ ВПРАВО
#define HELM_LEFT_BUTTON 9// руль влево
#define FORWARD_BUTTON 10// двигатель вперед
#define BACK_BUTTON 11// двигатель назад
#define LIGTH_BUTTON 12//фары
#define BRAKE_BUTTON 13// тормоз


Servo helm;//имитация руля
int helmAngle = 90;
unsigned long int timeMillis, timePreview;
bool ON;


void setup()
{
  Serial.begin(9600);
  pinMode(FORWARD, OUTPUT);
  pinMode(BACK, OUTPUT);
  pinMode(LIGTHS, OUTPUT);
  pinMode(HELM, OUTPUT);
  //  pinMode(BRAKE, OUTPUT);
  /*
    pinMode(FORWARD_BUTTON,  INPUT_PULLUP);
    pinMode(BACK_BUTTON, INPUT_PULLUP);
    pinMode(LIGTH_BUTTON, INPUT_PULLUP);
    pinMode(BRAKE_BUTTON, INPUT_PULLUP);
    pinMode(HELM_RIGTH_BUTTON, INPUT_PULLUP);
    pinMode(HELM_LEFT_BUTTON, INPUT_PULLUP);
  */
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
*/
int incomingByte = 0;
void loop()
{

  if (Serial.available() > 0) {
    // считываем входящий байт:
    incomingByte = Serial.read();
  }
  if (timeMillis % 100 == 0)
  {
    //Serial.println(100);
    timePreview = millis();
    if (incomingByte==54) MoveHelmToRigth();
    if (incomingByte==55) MoveHelmToLeft();
   
  }
  if (timeMillis % 500 == 0)
  {
   //Serial.println(500);
    timePreview = millis();
    if (incomingByte==49) MotorForward();
    if (incomingByte==50) MotorBack();
    if (incomingByte==51) MotorOff();
  }
  if (timeMillis % 1000 == 0)
  {
    //Serial.println(1000);
    timePreview = millis();
    if (incomingByte==52) LigthOn();
    if (incomingByte==53) LigthOff();
  }
  incomingByte = 0;
  Serial.flush();
}

void MotorForward() {
  digitalWrite(BACK, LOW);
  // delay(1);
  digitalWrite(FORWARD, HIGH);
  Serial.println("Едем вперед ВЖЖЖЖЖЖ...");
}
void MotorBack() {
  digitalWrite(FORWARD, LOW);
  //delay(1);
  digitalWrite(BACK, HIGH);
  Serial.println("Едем назад ЖВВВВВВВ...");
}

void MotorOff() {
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACK, LOW);
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
  int angle = getHelmAngle() + 20;
  setHelmAngle(angle);
  helm.write(getHelmAngle());
  Serial.println("Лево руля");
  
}

void MoveHelmToRigth() {
  int angle = getHelmAngle() - 20;
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
  if (angle > 180 || angle < 0)
    return;
  else (helmAngle = angle);
}

