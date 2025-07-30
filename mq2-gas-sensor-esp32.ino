
#define AO_PIN 36  // Etiqueta para asociar el pin analógico del MQ2 a la ESP32

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(9600);
  
  // Establece la atenuación de la entrada analógica (para rango completo de voltaje)
  analogSetAttenuation(ADC_11db);

  Serial.println("Precalentando el sensor");
  delay(20000);  // Espera de 20 segundos para precalentamiento del sensor MQ2
}

void loop() {
  int gas = analogRead(AO_PIN);  // Lee el valor analógico del sensor MQ2

  Serial.print("Valor del sensor de gas MQ2: ");
  Serial.println(gas);

  delay(500);  // Espera 500 ms entre lecturas
}
