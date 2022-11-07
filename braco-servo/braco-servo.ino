#include <Servo.h>

#define pinServ1 2
#define pinServ2 3
#define pinServ3 4
#define pinServ4 5

#define pot1 A0
#define pot2 A1
#define pot3 A2
#define pot4 A3

Servo serv1, serv2, serv3, serv4;

int motor1, motor2, motor3, motor4;

unsigned long mostradorTimer = 1;
const unsigned long intervaloMostrador = 5000;

void setup()
{
	Serial.begin(9600);
	serv1.attach(pinServ1);
	serv2.attach(pinServ2);
	serv3.attach(pinServ3);
	serv4.attach(pinServ4);
}

void loop()
{
	motor1 = map(analogRead(pot1), 0, 1023, 0, 180);
	motor2 = map(analogRead(pot2), 0, 1023, 0, 180);
	motor3 = map(analogRead(pot3), 0, 1023, 85, 180);
	motor4 = map(analogRead(pot4), 0, 1023, 0, 43);

	serv1.write(motor1);
	serv2.write(motor2);
	serv3.write(motor3);
	serv4.write(motor4);

	if ((millis() - mostradorTimer) >= intervaloMostrador)
	{

		Serial.println("**********************************************");

		Serial.print("Pot1:");
		Serial.print(analogRead(pot1));
		Serial.print(" Angulo Motor1:");
		Serial.println(motor1);

		Serial.print("Pot2:");
		Serial.print(analogRead(pot2));
		Serial.print(" Angulo Motor2:");
		Serial.println(motor2);

		Serial.print("Pot3:");
		Serial.print(analogRead(pot3));
		Serial.print(" Angulo Motor3:");
		Serial.println(motor3);

		Serial.print("Pot4:");
		Serial.print(analogRead(pot4));
		Serial.print(" Angulo Motor4:");
		Serial.println(motor4);

		mostradorTimer = millis();
	}

	delay(100);
}
