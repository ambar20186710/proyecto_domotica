#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 7
#define pinPirCalle 2
#define pinLedCalle 3
#define pinPirPatio 4
#define pinLedPatio 5

int valorPirPatio;
int valorPirCalle;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia
Servo miServo;  // Crear instancia del servo

bool tarjetaAutorizada = false;
unsigned long tiempoUltimaLectura = 0;
const unsigned long tiempoEspera = 5000;  // 5 minutos en milisegundos

// Define dos conjuntos de códigos autorizados
byte uidAutorizado1[] = {0x01, 0x63, 0x30, 0x1D};
byte uidAutorizado2[] = {0xA3, 0xF8, 0x8C, 0xAC};

void setup() {
  Serial.begin(9600);
  miServo.write(75);  // Iniciar comunicación serial
  SPI.begin();         // Iniciar la comunicación SPI
  mfrc522.PCD_Init();  // Iniciar el lector RFID
  miServo.attach(SERVO_PIN);  // Adjuntar el servo al pin 3
  Serial.println("Listo para leer tarjetas RFID...");
  pinMode(pinLedCalle, OUTPUT);
  pinMode(pinPirCalle, INPUT);
  pinMode(pinLedPatio, OUTPUT);
  pinMode(pinPirPatio, INPUT);
}

void loop() {
//Inicio PIR
  valorPirCalle = digitalRead(pinPirCalle);
  valorPirPatio = digitalRead(pinPirPatio);
  
  if(valorPirCalle == HIGH){
  	digitalWrite(pinLedCalle, HIGH);
  }
  else{
  	digitalWrite(pinLedCalle, LOW);
  }

  if(valorPirPatio == HIGH){
  	digitalWrite(pinLedPatio, HIGH);
  }
  else{
  	digitalWrite(pinLedPatio, LOW);
  }
//Final pir

//RFID
  // Verificar si hay una tarjeta presente
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Mostrar el número de identificación de la tarjeta
    Serial.print("Número de identificación de la tarjeta: ");
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    // Verificar si la tarjeta es autorizada
    if (esTarjetaAutorizada(mfrc522.uid.uidByte, mfrc522.uid.size)) {
      tarjetaAutorizada = true;
      tiempoUltimaLectura = millis();  // Actualizar el tiempo de la última lectura
      moverServo(0);  // Mover el servo a 90 grados
      Serial.print("Motor");
    }

    delay(1000);  // Esperar un segundo antes de leer la próxima tarjeta
  }

  // Verificar si ha pasado el tiempo de espera y revertir el estado del servo
  if (tarjetaAutorizada && (millis() - tiempoUltimaLectura >= tiempoEspera)) {
    tarjetaAutorizada = false;
    moverServo(75);  // Volver el servo a la posición original (0 grados)
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

bool esTarjetaAutorizada(byte *uid, byte bufferSize) {
  // Comparar el UID de la tarjeta con los dos conjuntos de UID autorizados
  return (memcmp(uid, uidAutorizado1, sizeof(uidAutorizado1)) == 0 || memcmp(uid, uidAutorizado2, sizeof(uidAutorizado2)) == 0);
}

void moverServo(int angulo) {
  miServo.write(angulo);  // Mover el servo al ángulo especificado
  delay(500);  // Pequeño retardo para asegurar que el servo tenga tiempo de moverse
}
