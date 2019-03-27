# Gruppe36-OOP

Prosjektmappe for gruppe 36 i objekt-orientert programmering ved NTNU Gjøvik våren 2018.

Sindre Garmo
mail: sindregarmo@hotmail.com
mobil: 95471962

Fredrik Røstad
mail: fredrikrostad@gmail.com / frer@stud.ntnu.no
mobil: 91999509

Stig Thomas Gulbrandsen
mail: 13stigul@gmail.com
mobil: 47627252









//////////////////////////////////////////////////////
Beskrivelse av filformatene

spillere.dta

Denne fila består av to ting, fyrst eit tall som seier kor mange spelare fila inneheld, også ein spelarbolk, som inneheld nummeret, namnet og adressa til spelaren. Spelarbolken er repetert like mange gonger som talet øverst i fila

Antall spelare
– 
Nummeret til spelaren
Namnet til spelar
Adresse til spelar
–



idrettene.dta

Fyrst kjem talet på idrettar som skal lesast inn. Så kjem det ein bolk der fyrst namnet på idretten står, så kjem tabelltypa, før antall divisjonar kjem til slutt. Om talet på divisjonar er større enn 0, så kjem det bolkar med divisjonsinfo etterpå. Den har namnet på divisjonen, og antall lag. Om lag er større enn 0, så kjem lagbolken.  Denne inneheld namnet på laget, adressa til laget, talet på spelare, nummeret til spelarane og talet på uregisterte spelare. I idrettene.dta er dette talet ALLTID null. Etter alle laga, så kjem resultata for divisjonen. Fyrst så kjem det eit null-tal eller eit eit-tall, som represeterer kampstatusen. 0 om kampen ikkje er spelt, 1 om kampen er spelt. Etter det kjem datoen til kampen. Om kampstatusen er 1 så kjem antall heimemål, antall bortemål, normaltid-status I form av eit 1-tal eller eit 0-tal, dei som scora for heimelaget, og dei som scora for bortelaget. Etter divisjonen kjem infoen om ein ny divisjon, og etter all infoen om alle divisjonane innanfor ein idrett, så kjem ein ny idrett, med sine divisjonar, lag og resultater. 

Antall idretter
–
Namnet på idretten
Tabelltype
Talet på divisjonar/avdelingar
–
Namnet på divisjonen
Talet på lag i divisjonen
–
Namnet på laget
Adressa til laget
Talet på spelare på laget
Nummeret på spelarane på ei linje
Talet på uregisterte spelare (I idrettene.dta er denne alltid 0, men den må vere med ettersom idrettene.dta og ny_div brukar same funksjon for innlesing)
–
Kampstatus (0 om kampen ikkje er spelt enda, 1 om kampen er spelt)
Kampdato
– (om kampstatus er 1)
Antall heimemål
Antall bortemål
Normaltidstatus (1 om kampen var ferdig etter normaltid, 0 om den ikkje vart det)
Om heimemål er over 0, så kjem alle målscorarane for heimelaget på denne linja
Om bortemål er over 0 så kjem alle målscorarane for heimelaget på denne linja
–




“ny_div”.dta

Øverst I divisjonsfilane er talet på lag I divisjonen. Deretter kjem lag-bolken, som er lik som I idrettene.dta, med unntak av at talet på uregistrete spelare kan vere over 0. Om det er det, så kjem det ein spelar-bolk, som er lik spelar-bolken I spillere.dta. Etter alle spillerbolkene innad I eit lag, så kjem det neste laget I divisjonen. Etter infoen om laga kjem terminlista, og denne er heilt lik som i idrettene.dta

Talet på lag
–
Namnet til laget
Adressa til laget
Antall spelere
Spelar-nr
Talet på uregistrerte spelare
– 
Nr til spelar
Namnet til spelar
Adressa til spelar
–
Kampstatus (0 om kampen ikkje er spelt enda, 1 om kampen er spelt)
Kampdato
– (om kampstatus er 1)
Antall heimemål
Antall bortemål
Normaltidstatus (1 om kampen var ferdig etter normaltid, 0 om den ikkje vart det)
Om heimemål er over 0, så kjem alle målscorarane for heimelaget på denne linja
Om bortemål er over 0 så kjem alle målscorarane for heimelaget på denne linja
–

resultater.dta

Fyrst er talet på antall idrettar som fila har informasjon om. Deretter går den inn I ein idrettsbolk, som leser inn namnet på idretten og antall divisjonar. Så leses antallet forskjellige datoer det er innafor divisjonen. Deretter kor mange kampar det er på ein bestemt dato, samt dato. Så kjem alle kampane på denne datoen, med heimelaget, bortelaget, antall mål til begge lag, normaltidstatus, og målscorare. Etter alle kampane på ein bestemt dato, kjem alle kampane på neste dato. Etter alle datoane så kjem neste divisjon, og etter alle divisjonane så kjem neste idrett. 

Antall forskjellige idrettar
–
Namnet på idretten
Antall divisjonar
–
Antall forskjellige datoar
–
Antall kampar på ein bestemt dato
Dato
– 
Heimelag
Bortelag
Antall mål til heimelaget
Antall mål til bortelaget
Normaltidstatus (1 eller 0)
Målscorare på heimelaget
Målscorare på bortelaget


spillere.dta – eksempel


10
1
Arne
Lom
2
Bent
Otta
3
Cato
Sel
4
Dagor
Vågå
5
Erik
Vinstra
6
Finn
Garmo
7
Geir
Skjåk
8
Hans
Lillehammer
9
Geir
Otta
10
Hans
Trondheim
idrettene.dta – eksempel

4
Basketball
A
0
Fotball
B
2
1. Div
3
Start
Kristiansand
1
7
0
Sogndal
Sogndal
2
4 10
0
Vålrenga
Oslo
2
1 9
0
0
01022018
0
08022018
0
15022018
0
22022018
0
01032018
0
08032018
Elite
3
Rosenborg
Trondheim
5
1 2 3 4 5
0
Brann
Bergen
3
2 4 6
0
Viking
Stavanger
5
6 7 8 9 10
0
0
01012018
1
08012018
0
4
1
6 7 9 10
1
15012018
2
3
1
2 2
1 2 5
0
22012018
0
29012018
1
05022018
0
0
1
Håndball
A
0
Ishockey
C
0

“ny_div”.dta – eksempel

3
AA
Alesund
3
1 2 3
2
11
Terje
Oslo
12
Guttorm
Molde
BB
Hamar
7
4 5 6 7 8 9 10
2
13
Aslak
Kristiansand
14
Kristian
Kristiansund
CC
Skien
2
2 5
2
15
Erling
Valdres
16
Bob
Harstad
0
01012018
0
08012018
0
15012018
0
22012018
0
29012018
0
05022018

resultater.dta – eksempel

1
Fotball
1
1. Div
6
1
01022018
Start
Sogndal
0
1
1
4
1
08022018
Start
Vålrenga
3
1
1
7 7 7
9
1
15022018
Sogndal
Start
0
0
1
1
22022018
Sogndal
Vålrenga
2
0
1
4 10
1
01032018
Vålrenga
Start
3
1
1
1 1 9
7
1
08032018
Vålrenga
Sogndal
0
0
1


