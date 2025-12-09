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
ST:99,TP:123,BS:45,M:1,CS:67,OT:90,WT:85,RPM:4500,OP:50,SS:1,LT:43.123456,LG:12.654321\n

| Codice | Descrizione | Unità/Range | Note |
| :--- | :--- | :--- | :--- |
| **ST** | Sterzo | (0-1023) | Valore analogico. |
| **TP** | Acceleratore (Throttle Position) | (0-1023) | Valore analogico. |
| **BS** | Freno (Brake Status) | (0-1023) | Valore analogico. |
| **M** | Marce | (0-5) | 0=N, 1-5=Marce. |
| **CS** | Frizione (Clutch Status) | (0-1023) | Valore analogico. |
| **OT** | Temperatura Olio | (°C) | Placeholder. |
| **WT** | Temperatura Acqua | (°C) | Placeholder. |
| **RPM** | Giri Motore | (Giri/min) | Placeholder (800-9000). |
| **OP** | Pressione Olio | (bar) | Placeholder. |
| **SS** | Status (Faccina/Messaggio) | (0 / 1) | 0=Spenta/Triste, 1=Accesa/Felice. |
| **LT** | **Latitudine GPS** | (Gradi Decimali) | Precisione di 6 cifre decimali. |
| **LG** | **Longitudine GPS** | (Gradi Decimali) | Precisione di 6 cifre decimali. |

## 🧑‍💻 Dettagli di Implementazione

### Funzionamento Chiave

1.  **Parsing GPS non bloccante**: La funzione `while (ss.available() > 0) { gps.encode(ss.read()); }` legge in modo asincrono i dati dal GPS, impedendo al programma di bloccarsi in attesa di una riga NMEA completa.
2.  **Affidabilità GPS**: Il codice utilizza le variabili globali `last_lat` e `last_lng` per memorizzare l'ultima posizione valida. La telemetria invia sempre questa ultima posizione valida, garantendo che i campi **LT** e **LG** non siano mai vuoti, anche se l'aggiornamento GPS è lento.
3.  **snprintf per Efficienza**: Viene utilizzata la funzione `snprintf` per costruire l'intera stringa di telemetria (`telemetryMsg`) in un unico buffer. Questo riduce significativamente l'overhead della comunicazione seriale rispetto all'invio di molteplici frammenti di `XBee.print()`.
