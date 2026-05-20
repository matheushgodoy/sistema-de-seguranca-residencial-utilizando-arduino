#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int pinLED = 13;
int pinSensorMovimento = 12;
int pinBuzzer = 11;
int pinSensorGas = A0;

void setup() {

  pinMode(pinLED, OUTPUT);
  pinMode(pinSensorMovimento, INPUT);
  pinMode(pinBuzzer, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sistema");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  delay(2000);
  lcd.clear();
}

void loop() {

  int movimento = digitalRead(pinSensorMovimento);
  int nivelGas = analogRead(pinSensorGas);

  Serial.print("Movimento: ");
  Serial.print(movimento);

  Serial.print(" | Gas: ");
  Serial.println(nivelGas);

  if (movimento == HIGH && nivelGas > 400) {

    digitalWrite(pinLED, HIGH);
    tone(pinBuzzer, 1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALERTA MAXIMO");
    lcd.setCursor(0, 1);
    lcd.print("RISCO ALTO");

    Serial.println("RISCO ALTO");

    delay(500);
  }

  else if (nivelGas > 400) {

    digitalWrite(pinLED, HIGH);
    tone(pinBuzzer, 700);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FUMACA/GAS");
    lcd.setCursor(0, 1);
    lcd.print("DETECTADO");

    Serial.println("FUMACA DETECTADA");

    delay(500);
  }

  else if (movimento == HIGH) {

    digitalWrite(pinLED, HIGH);
    noTone(pinBuzzer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MOVIMENTO");
    lcd.setCursor(0, 1);
    lcd.print("DETECTADO");

    Serial.println("MOVIMENTO DETECTADO");

    delay(500);
  }

  else {

    digitalWrite(pinLED, LOW);
    noTone(pinBuzzer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SISTEMA");
    lcd.setCursor(0, 1);
    lcd.print("SEGURO");

    Serial.println("SISTEMA SEGURO");

    delay(500);
  }
}
