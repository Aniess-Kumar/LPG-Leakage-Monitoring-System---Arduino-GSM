#include <SoftwareSerial.h>

SoftwareSerial gsm(7, 8);   // RX, TX

const int gasSensor = A0;
const int buzzer = 9;
const int led = 13;

int gasValue;
int threshold = 400;

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  pinMode(gasSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);

  delay(1000);
}

void loop() {

  gasValue = analogRead(gasSensor);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {

    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);

    Serial.println("LPG LEAK DETECTED!");

    sendSMS();

    delay(10000);
  }
  else {

    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);

    Serial.println("Gas Level Normal");
  }

  delay(1000);
}

void sendSMS() {

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");
  delay(1000);

  gsm.println("WARNING! LPG GAS LEAKAGE DETECTED. Please check immediately.");
  delay(500);

  gsm.write(26);   // CTRL+Z
  delay(5000);
}
