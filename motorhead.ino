#include <NewPing.h> 
#include<Servo.h>

/*Aqui se configuran los pines donde debemos conectar el sensor*/
#define TRIGGER_PIN  22
#define ECHO_PIN     6
#define MAX_DISTANCE 400


 
/*Crear el objeto de la clase NewPing*/
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servoMotor;
// Motors Constrains

/*Motor #1*/
  int ENA = 2;
  int IN1 = 46;
  int IN2 = 47;

/*Motor #2*/
  int ENB = 4;
  int IN3 = 48; 
  int IN4 = 49;
  
  int left=0;
  int right =0;
  int front = 0;
  
void setup() {
  Serial.begin(9600);
  
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN4, OUTPUT);     
  pinMode (IN3, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

   servoMotor.attach(9);
   servoMotor.write(90);

}
 
void loop() {
 Serial.print("Distancia ");
 Serial.println(sonar.ping_median()/US_ROUNDTRIP_CM);

if((sonar.ping_median()/US_ROUNDTRIP_CM)<= 40){front = 1;}else{front = 0;}
if(front == 0)
{
  
    
    Adelante();
    Serial.println("Avanzando");
    Serial.println(" ");
    Serial.print(left);
    Serial.print(front);
    Serial.print(right);
    Serial.println(" ");  
}else{

  
  Serial.println(" ");
  Serial.print(left);
  Serial.print(front);
  Serial.print(right);
  Serial.println(" ");  
  scaning();

  servoMotor.write(90);    
    }
}


void girarDerecha(){
  Derecha();
  delay(230);
  left  =0;
  right =0;
  front =0;
}


void girarIzquierda(){
  Izquierda();
  delay(230);
  left   =0;
  right  =0;
  front  =0;
}


void reversa(){
  Atras();
  delay(4000);
  left   =0;
  right  =0;
  front  =0;  
  
}
void scaning(){
  
  Serial.println("Other case begin ###");
  Serial.println(sonar.ping_median()/US_ROUNDTRIP_CM);
  Parar();
  delay(500);
  servoMotor.write(0);
  delay(1000);
  if((sonar.ping_median()/US_ROUNDTRIP_CM) <= 40){
    left = 1;
   }
  servoMotor.write(180);
  delay(2000);
  if((sonar.ping_median()/US_ROUNDTRIP_CM) <= 40){
    right = 1;
   }
   delay(500);
  Serial.println(front);
  Serial.println("Other case end  @@@");

Serial.println("Giro desicion");
if(left == 1 && right == 0  ){
    Serial.println("giro a la derecha");
    girarDerecha();
    return;
  }


  if(left == 0 && right == 1 ){ girarIzquierda(); return;}
  if(left == 0 && right == 0 ){ girarDerecha(); return;}
  if(left == 1 && right == 1 ){reversa(); return;}
  
}

void Adelante(){
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
  analogWrite (ENA, 255); //Velocidad motor A

    
  digitalWrite (IN2, HIGH);
  digitalWrite (IN1, LOW);
  analogWrite (ENB, 255); //Velocidad motor B

 }

void Atras(){
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH); 
  analogWrite (ENA, 255); //Velocidad motor A

    
  digitalWrite (IN2, LOW);
  digitalWrite (IN1, HIGH);
  analogWrite (ENB, 255); //Velocidad motor B
 }

void Derecha(){

 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255); //Velocidad motor B
}

void Izquierda(){
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite (ENA, 255); //Velocidad motor A
  
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);  
  analogWrite (ENB, 255); //Velocidad motor B
}

void Parar(){

 digitalWrite (IN3, LOW);
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 digitalWrite (IN4, LOW);
  
}
