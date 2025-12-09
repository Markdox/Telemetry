/*
Author: Marco Dottori
Creation date: 12/11/2025
Description: Programma di test per inviare tutti i dati di telemetria
             richiesti in un unico messaggio formattato.

## COSE DA INVIARE (come da richiesta)
- Sterzo (Radio code => ST) *Codice inventato*
- Accelleratore (Radio code => TP)
- Freno (Radio code => BS)
- Marce (Radio code => M)
- Frizione (Radio code => CS)
- Temperatura Olio (Radio code => OT)
- Temperatura Acqua (Radio code => WT)
- Giri motore (100Hz) (Radio code => RPM)
- Pressione Olio (Radio code => OP)
- Faccina (Radio code => SS) *Codice inventato* (0=Triste/Spenta, 1=Felice/Accesa)
*/

#include <SoftwareSerial.h> // Include SoftwareSerial library
#include <TinyGPSPlus.h>

SoftwareSerial XBee(10, 11); // Define SoftwareSerial pins: DOUT = 10, DIN = 11
static const int GPS_RX_PIN = 4;
static const int GPS_TX_PIN = 3; 
static const long GPS_BAUD = 9600; // La maggior parte dei moduli GPS usa 9600 baud

// Crea gli oggetti per la comunicazione
SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN); // RX, TX
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200); // Start communication with the PC for debugging
  XBee.begin(115200);   // Start communication with the XBee module
  ss.begin(GPS_BAUD); // Avvia la seriale software per il modulo GPS
  randomSeed(analogRead(0)); // Seed the random number generator
}

void loop() {

  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  // 1. Genera placeholder per tutti i sensori
  int valSterzo = random(0, 1024);     // ST
  int valAccell = random(0, 1024);     // TP
  int valFreno = random(0, 1024);      // BS
  int valMarce = random(0, 6);         // M (N, 1-5)
  int valFrizione = random(0, 1024);   // CS
  int valTempOlio = random(20, 140);   // OT
  int valTempAcqua = random(20, 120);  // WT
  int valGiri = random(800, 9000);     // RPM
  int valPressOlio = random(0, 100);   // OP
  int valStatus = random(0, 2);        // STATUS (0=Spenta/Triste, 1=Accesa/Felice)

  
  // Inizia a stampare sul monitor seriale per il debug
  Serial.print("Invio: ");

  // Invia i dati all'XBee (e contemporaneamente al Serial monitor)
  
  // Sterzo (ST)
  XBee.print("S:");
  XBee.print(valSterzo);

  Serial.print("S:");
  Serial.print(valSterzo);

  // Accelleratore (TP)
  XBee.print(",T:");
  XBee.print(valAccell);
  Serial.print(",T:");
  Serial.print(valAccell);

  // Freno (BS)
  XBee.print(",B:");
  XBee.print(valFreno);
  Serial.print(",B:");
  Serial.print(valFreno);

  // Marce (M)
  XBee.print(",G:");
  XBee.print(valMarce);
  Serial.print(",G:");
  Serial.print(valMarce);

  // Frizione (CS)
  XBee.print(",C:");
  XBee.print(valFrizione);
  Serial.print(",C:");
  Serial.print(valFrizione);

  // Temperatura Olio (OT)
  XBee.print(",OT:");
  XBee.print(valTempOlio);
  Serial.print(",OT:");
  Serial.print(valTempOlio);

  // Temperatura Acqua (WT)
  XBee.print(",WT:");
  XBee.print(valTempAcqua);
  Serial.print(",WT:");
  Serial.print(valTempAcqua);

  // Giri motore (RPM)
  XBee.print(",R:");
  XBee.print(valGiri);
  Serial.print(",R:");
  Serial.print(valGiri);

  // Pressione Olio (OP)
  XBee.print(",OP:");
  XBee.print(valPressOlio);
  Serial.print(",OP:");
  Serial.print(valPressOlio);



  // Faccina/Status (STATUS)
  XBee.print(",P:");
  XBee.print(gps.location.lat(), 6);
  XBee.print("-");
  XBee.print(gps.location.lng(), 6);

  Serial.print(",P:");
  Serial.print(gps.location.lat(), 6);
  Serial.print("-");
  Serial.print(gps.location.lng(), 6);


  // 3. Invia il carattere 'newline' per terminare il messaggio
  //    Questo dice al ricevitore che il messaggio è finito.
  XBee.print("\n");
  Serial.print("\n"); // A capo anche nel monitor seriale

  delay(10); 

}