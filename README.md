# Terminator
## Ordnerstruktur
### cgi-bin/
In diesen Ordner kommen die fertigen \*.exe Dateien, diese werden allerdings nicht hochgeladen und müssen Lokal selbst kompiliert werden.
### cgi-bin/templates/
Hier kommen die HTML Dateien rein
### htdocs/
Hier kommen die Bilder und CSS Dateien rein
### src/
In diesen Ordner kommen die \*.cpp und \*.h Dateien

__________________________________________________________________
## Todo
- HTML Terminausgabe ist sieht kaputt aus (tabelle sieht kacke aus)
- icons überprüfen (ist fa im head.html eingebunden?)
- ~~HTML Template durchgehen, manche sehen kaputt aus~~
- ~~Passwort ändern~~
- ~~Passwort ändern testen~~
- ~~Passwort ändern formular template~~
- ~~Logo einfügen~~
- Logo positionieren
- Terminator überschrift unter logo
- terminator zitate einfügen (z.b. logout -> hasta la vista baby)
- Buttons und Links rot einfärben (generell blau zu rot)

## Todo nice to have
- sonderzeichen prüfen (hinzufügen von terminen)
- ~~max eingabelänge für passwort und nutzername~~
- Max. Eingabelänge beschränken
- ~~sessions~~
- ~~ggf sortieren~~
- termin bearbeiten (werte eingefügt haben)
__________________________________________________________________
## Aufgaben:
  
### Wassi:
- priorität: icons, terminausgabe, logo, überschrift, ... rest
- logo, überschrift (terminator), buttons, ...
- siehe oben
- ~~appointments und nutzer brauchen eine id um die appointments den nutzern zuzuordnen~~
- ~~strukturen login / termin (liste)~~
- ~~login~~
- ~~reg(done)/passs ändern~~
- ~~erledigt:terminverwaltung anlegen, löschen, ausgeben, ändern, html body tag userid~~
- ~~html templates(done/erweiterbar)~~

- ~~html templates ergänzen: login fehlgeschlagen, registrieren fehlgeschlagen (evtl noch mehr ergänze ich dann)
- ~~**bitte beachten**, habe die html templates nach cgi-bin/templates/ verschoben, weil ich im c code was angepasst habe, die werden jetzt nur noch über C eingebunden und nicht über htdocs aufgerufen
- ~~wir könnten evtl die templates nochmal grafik mäßig überarbeiten, wenn wir das "Terminator" logo nutzen wollen xD Muss aber nicht, finds auch cool so wies ist
- ~~bei den formularen muss jetzt überall **method="post"** ergänzt werden und bei action muss jetzt z.b. wenn login aufgerufen wird **action="?page=login** stehen, die links werde ich wahrscheinlich aber selber anpassen bei action
- ~~glaub das war alles, ansonsten ergänz ichs xD
 
### joshua:
- ~~sortieren (uhrzeit fehlt)~~
- ~~sessions~~
- siehe oben
- ~~\_CRT_SECURE_NO_WARNINGS entfernen und fehler beheben~~
- ~~cpp zu schönen header dateien machen (login, )~~
- ~~vergleichfunktions für sortierung (getTimestamp ist schon da, also kaum noch aufwand)~~
- ~~cookies (https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm)~~
- ~~strukturen einzeln an datei anhängen / ändern (denke ist unnötig, evtl später)~~ ist egal!
- ~~getTimestamp und ggf formParser in helper.h auslagern~~
- ~~add writeSingleStruct() (und namenändern), mit seek end kann man am ende anhängen~~ BULLSHIT
- ggf password hashen (benötigt openssl, wäre ok) ggf eigene verschlüsselung (klingt als wäre das bonus)
- ~~Funktion Datei~~
- ~~string parser~~
- ~~getdescription terminverwaltung~~
  
