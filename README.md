# NAGYHÁZI SPECIFIKÁCIÓ

## A program célja
A feladat egy barkochba játék készítése. A játék során a felhasználó gondol egy
dologra, lehet az bármi és a program megpróbálja kitalálni mire gondolt. Ennek
érdekében a számítógép eldöntendő kérdéseket tesz fel a felhasználónak, amik
megválaszolása után a számítógép rákérdez egy dologra, amiről úgy gondolja
az a helyes megoldás.

## A játék menete
A játék elindítása után a felhasználónak eldöntendő kérdéseket kell
megválaszolnia, egészen addig amíg a program rá nem kérdez a megoldásra.
Ha a számítógép megfejtése helyes volt, a játék véget ér. Amennyiben
tévedett, a felhasználónak meg kell adnia egy új kérdést, ami az általa gondolt
dologra igaz, de a számítógép által javasolt dologra hamis és meg kell adja,
mire gondolt. Ilyenkor a gép vesztett, de tovább tanult.

## A program használata
A felhasználó a megjelenő terminálban olvashatja a kérdéseket, itt adhat rájuk
választ és itt adhat meg új kérdést és a hozzá tartozó választ is. A program
képes fájlba elmenteni a tanítás eredményét és képes betölteni is azt. 

# TERVEZETT MEGOLDÁS

## Tervezett osztályok
A kérdések és sejtések heterogén kollekcióját egy bináris fában tárolja a
program. A bal oldali ágon az igaz, a jobb oldali ágon a hamis válaszhoz tartozó
következő csomópont / levél található

## A program futásának logikája
A program a futása során egy bináris fát fog bejárni, a felhasználó által érkezett
Igaz / Hamis válaszok által kijelölt irányban. Ha egy következő csomópontra lép
felteszi az ott található újabb kérdést. Ha fogalomhoz érkezik akkor rákérdez az
általa sejtett megoldásra, ha eltalálta a játék véget ér. Ha nem a felhasználó új
kérdést adhat az adatbázishoz.

![by Demeter Zalán](https://i.imgur.com/xKF2sXo.png)