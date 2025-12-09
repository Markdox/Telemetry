#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// Definizione dei pin per la comunicazione seriale software
// GPS_RX_PIN (Arduino pin che RICEVE i dati dal GPS - deve essere un pin interrupt-capable)
// GPS_TX_PIN (Arduino pin che TRASMETTE al GPS - spesso non usato per sola lettura)
static const int GPS_RX_PIN = 4;
static const int GPS_TX_PIN = 3; 
static const long GPS_BAUD = 9600; // La maggior parte dei moduli GPS usa 9600 baud

// Crea gli oggetti per la comunicazione
SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN); // RX, TX
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200); // Seriale hardware per la comunicazione con il PC (monitor seriale)
  Serial.println(F("Avvio Lettura GPS...")); 
  ss.begin(GPS_BAUD); // Avvia la seriale software per il modulo GPS
}

void loop() {
  // Passa i dati dal modulo GPS (SoftwareSerial) alla libreria TinyGPSPlus
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  // Verifica se i dati di posizione sono stati aggiornati
  if (gps.location.isUpdated()) {
    Serial.println(F("-------------------------------------"));
    
    // Latitudine e Longitudine come float (Gradi Decimali)
    Serial.print(F("Latitudine (DD): "));
    Serial.println(gps.location.lat(), 6); // Stampa con 6 cifre decimali
    
    Serial.print(F("Longitudine (DD): "));
    Serial.println(gps.location.lng(), 6);
    
    // Altitudine
    if (gps.altitude.isValid()) {
        Serial.print(F("Altitudine (m): "));
        Serial.println(gps.altitude.meters());
    } else {
        Serial.println(F("Altitudine: Non valida"));
    }
    
    // Numero di satelliti
    Serial.print(F("Satelliti in uso: "));
    Serial.println(gps.satellites.value());
    
    // Ora e data
    if (gps.date.isValid() && gps.time.isValid()) {
      Serial.print(F("Data/Ora (UTC): "));
      Serial.print(gps.date.day());
      Serial.print(F("/"));
      Serial.print(gps.date.month());
      Serial.print(F("/"));
      Serial.print(gps.date.year());
      Serial.print(F(" "));
      Serial.print(gps.time.hour());
      Serial.print(F(":"));
      Serial.print(gps.time.minute());
      Serial.print(F(":"));
      Serial.println(gps.time.second());
    }
    
    Serial.println(F("-------------------------------------"));
  }
}