#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define AO_PIN 36    // Pin analógico donde se conecta el MQ2
#define BUZZER 17    // Pin digital donde se conecta el buzzer

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C y dimensiones del LCD

void setup() {
  // Inicializa comunicación serial
  Serial.begin(9600);

  // Inicializa pantalla LCD
  lcd.begin();
  lcd.backlight();  // Enciende luz de fondo del LCD

  // Configura el buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Configura atenuación para lectura ADC (rango 0–3.3V)
  analogSetAttenuation(ADC_11db);

  // Mensaje de precalentamiento
  Serial.println("Precalentando el sensor");
  lcd.clear();
  lcd.print("Inicializando...");
  delay(20000);  // Espera de 20 segundos para precalentar el sensor MQ2
}

void loop() {
  lcd.clear();  // Limpia la pantalla LCD

  int gas = analogRead(AO_PIN);  // Lee el valor del sensor MQ2

  if (gas > 2000) {
    // Si el valor supera el umbral, activa alarma
    Serial.print("¡Alerta! Valor del sensor de gas MQ2: ");
    Serial.println(gas);

    lcd.setCursor(0, 0);
    lcd.print("ALERTA!");
    lcd.setCursor(0, 1);
    lcd.print("Gas a: ");
    lcd.print(gas);
    lcd.print("/4095");

    digitalWrite(BUZZER, HIGH);  // Enciende buzzer
    delay(250);
    // digitalWrite(BUZZER, LOW);  // Descomenta si quieres parpadeo
    // delay(250);
  } else {
    // Si el valor está dentro del rango normal
    Serial.print("Valor del sensor de gas MQ2: ");
    Serial.println(gas);

    lcd.setCursor(0, 0);
    lcd.print("Midiendo...");
    lcd.setCursor(0, 1);
    lcd.print("Gas a: ");
    lcd.print(gas);
    lcd.print("/4095");

    digitalWrite(BUZZER, LOW);  // Apaga el buzzer
    delay(500);
  }
}
