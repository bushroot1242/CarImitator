#include <Servo.h>


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

void setup() 
{

  Serial.begin(9600);
  pinMode(FORWARD, OUTPUT);
  pinMode(BACK, OUTPUT);
  pinMode(LIGTHS, OUTPUT);
  pinMode(HELM, OUTPUT);
//  pinMode(BRAKE, OUTPUT);
  
  pinMode(FORWARD_BUTTON,  INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(LIGTH_BUTTON, INPUT_PULLUP);
  pinMode(BRAKE_BUTTON, INPUT_PULLUP);
  pinMode(HELM_RIGTH_BUTTON, INPUT_PULLUP);
  pinMode(HELM_LEFT_BUTTON, INPUT_PULLUP);

  helm.attach(HELM);
  
  MoveToAngle(helmAngle);//начальное положение руля - колеса прямо
  
}

void loop() 
{
 if(!digitalRead(FORWARD_BUTTON)) MotorForward();
 
 if(!digitalRead(BACK_BUTTON)) MotorBack();

 if(digitalRead(BACK_BUTTON) && digitalRead(FORWARD_BUTTON))  MotorOff();
 
 if(!digitalRead(LIGTH_BUTTON)) LigthOn();
 else LigthOff();

 //if(!digitalRead(BRAKE_BUTTON)) BrakOn();

if(!digitalRead(HELM_RIGTH_BUTTON)) MoveHelmToRigth();
if(!digitalRead(HELM_LEFT_BUTTON)) MoveHelmToLeft();

 
}

void MotorForward(){
  digitalWrite(BACK,LOW);
 // delay(1);
  digitalWrite(FORWARD,HIGH);
  Serial.println("Едем вперед ВЖЖЖЖЖЖ...");
}
void MotorBack(){
  digitalWrite(FORWARD,LOW);
   //delay(1);
  digitalWrite(BACK, HIGH);
  Serial.println("Едем назад ЖВВВВВВВ...");
}

void MotorOff(){
   digitalWrite(FORWARD,LOW);
   digitalWrite(BACK, LOW);
   Serial.println("Стоим((");
}
void LigthOn(){
 digitalWrite(LIGTHS, HIGH);
 Serial.println("Фары включены");
}
void LigthOff(){
 digitalWrite(LIGTHS, LOW);
// Serial.print("Фары выключены");
}
void BrakOff(){
// digitalWrite(BRAKE,HIGH);//потому что пнп транзистор, других тупо не было
}
void BrakOn(){
// digitalWrite(LIGTHS,LOW);//потому что пнп транзистор, других тупо не было
}
//во избежании вской херни, работать с рулем через методы moveHelmToLeft и Rigth, ну или через геттеры и сеттеры на крайняк
void MoveHelmToLeft(){
  int angle = getHelmAngle()+20;
  setHelmAngle(angle);
  helm.write(getHelmAngle());
  Serial.println("Лево руля");
}

void MoveHelmToRigth(){
  int angle = getHelmAngle()-20;
  setHelmAngle(angle);
  helm.write(getHelmAngle());
  Serial.println("Право руля");
}

void MoveToAngle(int angle){
  helm.write(angle);
  setHelmAngle(angle);
  Serial.println("Руль в положении ");
  Serial.print(angle);
  Serial.println(" градусов");
}

int getHelmAngle(){
  return helmAngle;
}
void setHelmAngle(int angle){
  if(angle>180 || angle<0)
  return;
  else (helmAngle = angle);
}

