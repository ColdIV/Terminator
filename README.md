# Terminator
## Ordnerstruktur
### cgi-bin/
In diesen Ordner kommen die fertigen \*.exe Dateien, diese werden allerdings nicht hochgeladen und müssen Lokal selbst kompiliert werden.
### htdocs/
Hier kommen die HTML Dateien rein
### src/
In diesen Ordner kommen die \*.cpp und \*.h Dateien


## Todo
- Login mit sessions
- nach Datum sortieren
- 2 Stukturen Login/Termin
- Termine anlegen, löschen, suchen, ausgeben
- Passwort anlegen, ändern
- input fehlerprüfung
- html überarbeiten (ohne bootstrap)
-----
## Voransgehensweise
### HTML Grundgerüst
überarbeiten (ggf ohne bootstrap)

### CGI :
- Formelemente durch string übertragen
- Dateioperation
  
## Aufgaben:
  
### Wassi:
- appointments und nutzer brauchen eine id um die appointments den nutzern zuzuordnen
- strukturen login / termin (liste)
- login
- reg/passs ändern 
- verknüpfung cgi - html
 
### joshua:
- vergleichfunktions für sortierung (getTimestamp ist schon da, also kaum noch aufwand)
- cookies (https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm)
- ~~strukturen einzeln an datei anhängen / ändern (denke ist unnötig, evtl später)~~ ist egal!
- getTimestamp und ggf formParser in helper.h auslagern
- ~~ggf password hashen~~ (benötigt openssl, müsste man erst nachfragen)
- ~~Funktion Datei~~
- ~~string parser~~
  
