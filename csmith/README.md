# CSmith (linux)

[CSmith](https://embed.cs.utah.edu/csmith/) je alat koji generiše random C programe koji su u skladu sa C99 standardnom. Ovaj alat ima primenu kod testiranja kompilatora. Uspešno je pronađeno
nekoliko bagova korišćenjem ovog alata za `gcc` i `clang`.

## Instalacija

Instalacija alata za generisanje nasumičnih programa.
```
sudo apt-get install csmith
```

## Korišćenje 

Generisanje programa:
- `csmith > out.c`
- ili `csmith -o out.c`

Pregled opcija:
- `csmith --help`

### Kompilacija generisanih programa

Generisane programe nije moguće prevesti bez [CSmith](https://embed.cs.utah.edu/csmith/) biblioteke:
- Komanda `gcc out.c` daje sledeći izlaz:
```
out.c:10:10: fatal error: csmith.h: No such file or directory
   10 | #include "csmith.h"
      |          ^~~~~~~~~~
compilation terminated.
```

### Privremeno podešavanje alata

Ako se kompilacija pokreće iz direktorijuma gde se nalazi ovaj README.md, onda da se iskoristi relativna putanja: `gcc out.c -Iinclude/csmith-2.3.0`

### Trajno podešavanje alata

- Neophodno je da se apsolutna putanja sačuva kao promenljiva okruženja. Apsolutna putanja može da se vidi preko komande: `realpath include/csmith-2.3.0`. 
- Postavljanje promenljive okruženja: `export CSMITH_PATH=[DOBIJENA_PUTANJA]`.
- Kompilacija: `gcc out.c -I$CSMITH_PATH` (radi iz bilo kojeg `cwd`).
- Nameštanje promenljive okruženja koja zauvek važi: 
    * `vim ~/.profile` (ili bilo koji editor)
    * Na dnu datoteke napisati dodati `export CSMITH_PATH=[DOBIJENA_PUTANJA]`
    * `vim ~/.bashrc` (isto kao za `~/.profile`)
    * Ako koristimo `zsh`, onda treba isto da uradimo i za `vim ~/.zprofile`

