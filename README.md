# Viktorīna

Izglītojošas spēles un lietotāju pārvaldības sistēma  
RTU Liepājas akadēmijas studiju darbs  
Autori: Patriks Kulinskis, Elvijs Gorbunovs, Ēriks Ercums

---

## Apraksts

**"Viktorīna"** ir C++ izstrādāta konsoles lietotne, kas apvieno lietotāju pārvaldību ar izglītojošu viktorīnas tipa spēli. Sistēmā ir divas lietotāju lomas:

- **Redaktors** – var veidot, rediģēt un dzēst spēles un jautājumus, kā arī apskatīt sekmju žurnālu un rangu tabulu.
- **Spēlētājs** – var spēlēt izveidotās spēles, apskatīt savus sasniegumus un labākos rezultātus.

Projekts izmanto **SQLite** datubāzi lietotāju profilu glabāšanai, paroles tiek droši uzglabātas ar hash palīdzību.

---

## Funkcionalitāte

- Lietotāja profila izveide un pieslēgšanās
- Lietotāju lomu sadalījums (Redaktors, Spēlētājs)
- Spēles izveide, labošana, jautājumu pievienošana/rediģēšana/dzēšana (Redaktors)
- Spēles spēlēšana ar jautājumu atbildēšanu (Spēlētājs)
- Spēles protokols ar darbību pierakstu un laika uzskaiti
- Spēlētāju sekmju žurnāls (pieejams tikai redaktoram)
- Katram spēlētājam savs labāko spēļu saraksts
- Labāko spēlētāju rangu tabula
- Sasniegumu sistēma spēlētājiem
- Datu glabāšana datubāzē un teksta failos

---

## Lietošana

1. Kompilējiet projektu ar C++17 standartu.
2. Palaidiet izpildāmo failu.
3. Reģistrējieties vai pieslēdzieties kā spēlētājs vai redaktors.
4. Izvēlieties darbības atbilstoši lomai.

---

## Tehniskā informācija

- Kods rakstīts C++
- Lietotāju dati tiek glabāti SQLite datubāzē (`lietotaji.db`)
- Rangu tabula tiek glabāta datubāzē (`RanguTabula.db`)
- Spēļu protokoli tiek saglabāti arī teksta failos (`lietotajuProtokoli/`)
- Paroļu hashing veikts ar **bcrypt**
- Konsole: `system("cls")` ekrāna tīrīšanai (Windows)

---

## Bibliotēkas

- [sqlite3](https://www.sqlite.org/)
- [bcrypt](https://github.com/hilch/Bcrypt.cpp)

---
