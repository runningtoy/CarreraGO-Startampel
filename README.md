# CarreraGO-Startampel
Dieses Projekt entstand kurz vor Weihnachten 2020, als mein Vater seine alte Carrera-Bahn wiederaufbaute und ich mich dazu entschied, ihm als Weihnachtsgeschenk (innerhalb von nur ca. einem Tag) eine Startampel zu bauen. Das ganze hab ich auch in einem [Video](https://youtu.be/q5Slh3TaYYY) dokumentiert, welches sich aber als Anleitung für einen Nachbau vermutlich nur bedingt eignet. Deswegen hier der Versuch einer strukturierteren und ausführlicheren Dokumentation:

1. [Material](#material)
2. [Hardware](#hardware)
3. [Software](#software)
4. [Gehäuse](#gehäuse)

Sollte es weitere Fragen, Anregungen oder Feedback geben bin ich am besten über die [Youtube-Kommentare](https://youtu.be/q5Slh3TaYYY) oder [Twitter](https://twitter.com/FeilerMoritz) zu erreichen. Viel Spaß beim Nachbauen! 

---
## Material:

- Arduino Nano
- 10x RGB-LED (common anode)
- Lochrasterplatine 
- 5x 33 Ohm Widerstände
- 5x 180 Ohm Widerstände
- aktiver Piezo Buzzer
- Schaltlitze
- Stift- und Buchsenleiste

Neben den aufgelisteten Materialen ist eigentlich nur ein Lötkolben, Lötzinn sowie die entsprechende Software zum Hochladen des Arduino-Programms notwendig. Das Gehäuse der Startampel habe ich an einem Creality Ender-3 ausgedruckt. Alternativ hierzu lässt sich die Konstruktion auch aus Holz, Pappe oder ähnlichem bauen. 

---
## Hardware
Die Hardware ist eigentlich ziemlich überschaubar: Die Startampel soll zwei Reihen mit je 5 Led-Lichtern haben. Die LEDs der unteren Reihe sollen einzeln ansteuerbar sein und sowohl grün als auch rot aufleuchten können. Die obere Reihe muss nur grün leuchten. Wer zu wenig RGB-LEDs zur Hand hat oder sich diese für Projekte aufheben möchte, bei denen diese auch tatsächlich in vollem Umfang genutzt werden, kann also bei der oberen Reihe auch normale grüne LEDs verwenden.

Die Verschaltung der 5 Spalten ist identisch und funktioniert wie folgt: Die gemeinsame Anode der unteren RGB-LED wird mit der 5V-Versorgungsspannung des Arduinos verbunden. Die "rote Kathode" der RGB-LED wird über einen Vorwiderstand (180Ω) mit einem digitalen Ausgang des Nanos verbunden. Hinter die "grüne Kathode" wird die obere LED in Reihe geschaltet (entweder nur der grüne Teil einer RGB-LED oder eine normale grüne LED). Auch hier wird nach einem Vorwiderstand, diesmal 33Ω, ein digitaler Ausgang des Arduinos verbunden. 

Um alles möglichst kompakt zu gestalten, habe ich die Verkabelung auf zwei xxXxxmm Lochrasterplatinen verteilt, welche mit Stift- und Buchsenleisten zusammengesteckt werden. Den Buzzer habe ich nicht auf der Platine verlötet, sondern im Gehäuse montiert. Auch er wird 

Eine Sache, die ich in meinem Video nicht gemacht habe, aber im Nachhinein empfehlen würde ist das hinzufügen eines externen Reset-Tasters für den Arduino. Dazu muss nur ein Taster zwischen den Pins RESET und GND des Nanos verbunden werden. Dies erleichtert den Neustart des Mikrocontrollers und damit des Countdowns erheblich. Momentan ist bei meiner Startampel ein Aus- und Wiedereinstecken des USB-Kabels die einzige Möglichkeit einen neuen Countdown zu starten. 

---
## Software
Die Startsequenz der Ampel soll folgendermaßen ablaufen:
- alle roten LEDs an (10 Sekunden)
- alle LEDs aus (5 Sekunden)
- Start Countdown
- nacheinander Aufleuchten der roten LEDs (1/Sekunde)
- zufallsgenerierte Pause (0,1 - 0,8 Sekunden)
- Aufleuchten aller grünen LEDs (2 Sekunden)
- alle LEDs aus

Als erstes wird die Pinbelegung der roten und grünen LEDs in einem Array gespeichert. Auch der Buzzer wird einem Arduino-Ausgang zugeordnet. 
In der setup()-Funktion des Programms werden diese Pins als Ausgänge deklariert und alle LEDs ausgeschaltet. Da die gemeinsame Anode der RGB-LEDs mit +5V verbunden sind, muss die Spannung an den Ausgängen des Arduinos auch +5V (HIGH) sein, damit kein Strom fließt und die LEDs ausgeschaltet sind.

In der loop()-Funktion beginnt die Countdown Sequenz. Da die Pinbelegung der LEDs in Arrays gespeichert wurde können wir die Software hier durch for-Schleifen vereinfachen. Wir iterieren zuerst durch alle roten LEDs und setzten die entsprechenden Pins auf LOW um die LEDs anzuschalten. Nach 10 Sekunden schalten wir diese wieder aus. Nach weiteren 5 Sekunden werden die roten LEDs nacheinander wieder eingeschaltet, dazu warten wir nach jeder Iteration je eine Sekunde.
Sobald alle roten LEDs aufgeleuchtet sind, und die zufallsgenerierte Pause vorbei ist, werden **zuerst** alle roten LEDs ausgeschaltet bevor alle grünen LEDs angeschaltet - Das Rennen kann beginnen. 

Zwei Sekunden später wird die Ampel ausgeschaltet. 

> **ACHTUNG:** Der Arduino kann maximal 200mA Strom zur Verfügung stellen bevor er beschädigt wird. Bei einem Leuchtdiodenstrom von ca. 20mA ist dieses Limit erreicht, sollten alle roten und grünen LEDs gleichzeitig eingeschaltet werden. Zwar haben wir durch die etwas zu großen Widerstände einen gewissen Puffer, ich würde aber trotzdem dazu raten, einen solchen Fall in der Software nicht zuzulassen. 

--- 
## Gehäuse
Hier gibt es viele verschiedene Möglichkeiten. Wie bereits erwähnt, habe ich das Gehäuse an meinem 3D-Drucker ausgedruckt. Die .stl-Dateien, sowie alle originalen Solidworks CAD-Dateien sind im _Gehäuse_-Ordner zu finden. Auch die Schablone die ich zum Ausrichten der LEDs verwendet habe findet ihr dort. Solltet ihr keinen 3D-Drucker haben lässt sich das Gehäuse mit ein bisschen handwerklichem Geschick und Kreativität bestimmt auch aus Holz, Pappe oder ähnlichem Material selber bauen. 

