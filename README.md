
# Begriffserklärung

**Mikrocontroller**

Mikrocontroller ist normalerweise eine Platine, an der einen Prozessor mit eingebauten Arbeits-, Programmspeicher und auch Peripheriemodulen ist. Für diesen Projekt wird der Mikrocontroller "BLE-33 Sense" von Arduino benutzt. An diesem Board ist ein integriertes Inertialsensoren (LSM9DS1), die Erdbeschleunigung, Winkelbeschleunigung und magnetisches Feld messen können, zusammengebaut.  

Ref: [Wikipedia](https://de.wikipedia.org/wiki/Mikrocontroller)

--- 
**Digitalsensoren**

Ein Digitalsensor ist ein elektronischer Sensor, bei dem analogen Daten digital umgewandelt und übertragen. In der Industrie werden normalerweise Digitalsensoren zur Prozesssteuerung benutzt. Diese Steuerungsprozess wird auch als "Digitale Signalverarbeitung" genannt.

---
**Digitale Signalverarbeitung**

Digitale Signalverarbeitung (DSV) ist ein Teilgebiet der Nachrichtentechnik und beschäftigt sich mit der Erzeugung und Verarbeitung von digitalen Signale. Anwendungen für DSV umfasst sich über die Speicherung, Übermittlung, und Transformation von Informationen in der Form von digitalen, zeitdiskreten Signalen.

---
**Digitales, Zeitdiskretes Signal**

Unter Digitales Signal versteht man einen Fluß von Datenwerte, die mit Dualzahl oder Binärzahl dargestellt. Digitales Signal ist zeitdiskret, in dem die Form des Signals aus vielen Abtasten mit äquidsitanten Zeitpunkten definiert ist. 

---
**Digitales Filter**

Ein digitales Filter ist einen Filter, deren durchgehende Werte mathematisch manipuliert wird, diese Manipulation von Werten werden normalerweise in dem Signalprozessor des Sensoren oder Mikrocontroller gemacht werden. Im Vergleich zu einem Digital-filter ist ein analoges Filter, deren Realisierung mit passiven elektronischen Bauelementen wie Kondensatoren, Spülen, Widerständen und auch Operationsverstärker. 

---
**Complementary-filter**

Ein Complementary-Filter ist ein Filter, das aus verschiedenen Filtern ausgebaut. Diese verschiedenen Filter haben dann seine eigene Verhältnis und die komplementieren sich einander bei dem Ausgabewert, jedoch müssen jede zugewiesene Filterverhältnis zum 1, wenn sie summiert wird. Das Verhältnis von den Filtern müssen aber durch Versuche optimiert werden. 

Relevante Filtern für die Sensoren, die in diesem Projekt sind Hochpass- und Tiefpass-Filter für Gyroskop und Accelerometer. 

---
**Hochpass-Filter**

Ein Hochpassfilter erlaubt kurzzeitiges Signal ungeschwächt zu erlauben und dämpft Signale mit tieferen Frequenzen. In dem Projekt wird ein Hochpassfilter für Gyroskop benutzt, um den Drift und Geräusche während der Messung von dem Gyorskop zu unterdrücken. 

---
**Gyroskop**

Ein Gyorskop oder Drehratensensor misst die Winkelgeschwindigkeit um eine definierte Achse in rad/s oder °/s. Ein Drehratensensor hat normalerweise eine Drift, die wenn nicht korrigiert werden, wird zu Messabweichungen führen können. 

---
**Tiefpass-Filter**

Ein Tiefpass-Filter ist ein Filter, der Signalanteile mit niedrigen Frequenz passieren lassen und Anteile mit höheren Frequenzen dämpft. 

In diesem Projekt wird das Tiefpass-Filter zu einem Accelerometer implementiert. 

---
**Accelerometer**

Ein Accelerometer ist ein Sensor, der seine Beschleunigung misst. Der Accelerometer misst seine Beschleunigung mit der Einheit von g und beträgt (gerundet) von 9,81m.s^-2. 

Ref: [Wikipedia](https://de.wikipedia.org/wiki/Beschleunigungssensor)

---
**Drift**

Drift ist eine langsame Änderung der Messwerte eines Sensor. 

---
**Rauschen**

Rauschen ist im Allgemein eien Störung in dem Signal mit unspezifizertem Frequenzspektrum.

--- 
**Zustandsmaschine**

[noch nicht]

---
# Herleitung

### Winkelberechnung für Gyroskop
Formel ist hier gegeben: https://electronics.stackexchange.com/questions/83464/measuring-angle-using-gyro-sensor

### Winkelberechnung für Accelerometer
Die Herletiung mit Trigonometrie liegt hier: https://www.analog.com/en/app-notes/an-1057.html

### Complementary-Filter
Ist schon in einem Dokument geschrieben.

---
# Was noch nicht geschrieben werden? 

- [ ] Inhaltsverzeichnis
- [ ] Abbildungsverzeichnis
- [ ] Tabellenverzeichnis
- [ ] Begriffserklärung (Habe schon hier ein bisschen gemacht)
  - [X] Mikrocontroller
  - [X] Digitalsensoren
  - [X] Digitale Signalverarbeitung
  - [X] Digitales Signal
  - [X] Digitales FIlter
  - [X] Complementary Filter
  - [X] Hochpass
  - [X] Gyroskop
  - [X] Tiefpass
  - [X] Accelerometer
  - [ ] Zustandsmaschine
- [ ] Einleitung
- [ ] Tabelle: benutzte Kennzeichen
- [ ] Winkelberechnung für Gyroskop (Formel ist schon oben gegeben)
- [ ] Winkelberechnung für Accelerometer (Formel und Methode schon in dem Link gegeben)
- [x] Filterherleitung
- [ ] Bilder, um die benutzte Orientation zu erklären (Kann mit Fotos oder direkt aus dem Datenblatt auszunehmen)
- [ ] Versuche/Ergebnisse?
- [ ] Zusammenfassung
- [ ] Referenzen
- [ ] Anhang
