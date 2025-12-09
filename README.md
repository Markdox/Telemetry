# 🏎️ Telemetria per Racing Team Perugia - Unità DAQ di Bordo

Questo repository contiene il codice sorgente per l'unità di acquisizione dati (DAQ) e trasmissione telemetrica a bordo veicolo, sviluppato per il **Racing Team di Perugia**.

Il programma è scritto per **Arduino** e gestisce la lettura dei dati dai sensori di bordo, la raccolta delle informazioni GPS e l'invio di tutti i parametri in un unico messaggio seriale verso un modulo radio **XBee** per la ricezione in tempo reale al box.

## ⚙️ Configurazione Hardware

Il codice utilizza la comunicazione seriale software per gestire contemporaneamente il modulo GPS e il modulo XBee, liberando la seriale hardware (pin 0 e 1) per il debugging.

| Componente | Connessione su Arduino (SoftwareSerial) | Baud Rate |
| :--- | :--- | :--- |
| **Modulo Radio XBee** | D10 (RX) / D11 (TX) | 115200 |
| **Modulo GPS** | D4 (RX) / D3 (TX) | 9600 |

## 📚 Dipendenze Necessarie

Per compilare ed eseguire il codice sono richieste le seguenti librerie:

1.  **SoftwareSerial**: (Standard nell'IDE Arduino). Gestisce le porte seriali virtuali sui pin D3/D4 e D10/D11.
2.  **TinyGPSPlus**: (Installabile tramite Gestore Librerie). Essenziale per l'interpretazione efficiente dei dati NMEA del GPS.

## 📝 Protocollo del Messaggio di Telemetria

Tutti i dati vengono inviati in un **unico messaggio formattato** (chiave:valore), separati da virgole e terminato da un carattere di *newline* (`\n`).

**Esempio di stringa completa:**
