#### clang-trans

MTK je aplikacija za metamorfno testiranje kompilatora, po čemu je i dobila naziv. Njen značajan deo čini transformator, čiji je cilj da generiše semantički ekvivalentne programe od nekog ulaznog. Za implementaciju transformacija korišćen je Clangov aplikativni programski interfejs prema apstraktnom sintaksnom stablu, a zatim je provereno da li se izvršivi kod sa optimizacijama isto ponaša.

Zavisnosti za transformator su clang-12, libclang-12-dev, llvm-12-dev. Neophodno je imati prevodilac Clang 12, kao i biblioteku (LibClang) i LLVM iste verzije, koja je najnovija stabilna u vreme pisanja rada. Za izgradnju se preporučuje upotreba sistema CMake, pomoću dostupne datoteke CMakeLists.txt. Primeri pokretanja i upotrebe izvršive verzije dati su u nastavku.

Sve transformacije dostupne su iz jednog programa, odnosno preko jednog izvršivog fajla. Rad glavne (main) funkcije zasnovan je na pomoćnim klasama MTKContext i MTKTransformer, koje rekurzivno posećuju AST stablo polaznog programa.

## Transformacija petlji :loop:
Prva implementirana transformacija je izmena petlji. Program transformiše sve petlje u C kodu u željeni tip – for, while, do-while. Za te potrebe koriste se klase Do2ForVisitor, For2DoVisitor, For2WhileVisitor, PrepForVisitor, While2DoVisitor i While2ForVisitor. Klasa PrepForVisitor priprema for petlje za dobru zamenu naredbe continue, dok ostale sprovode odgovarajuće transformacije. Tačne sheme izmena moguće je videti u svakom cpp fajlu.

Primer pokretanja (testiranja) transformatora:
```
./trans <ulaz> <izlaz> <do|while|for>
./trans whilefor.c samodo.c do
```

Na ovaj način će na osnovu koda whilefor.c biti formiran kod samodo.c koji sadrži isključivo petlje tipa do-while.

## Odmotavanje petlji :koko:
Sledeća implementirana transformacija je odmotavanje petlji. Program odmotava (unroll, unwind) petlje u C kodu, umnožavajući im telo n puta. Za te potrebe koristi se klasa LoopUnrollVisitor, čija se shema rada može videti u odgovarajućem cpp fajlu.

Primer pokretanja (testiranja) transformatora:
```
./trans <ulaz> <izlaz> o<n: uint>
./trans jednostruke.c trostruke.c o2
```

Na ovaj način će na osnovu koda jednostruke.c biti formiran kod trostruke.c u kome je telo svake petlje utrostručeno (dvaput odmotano).

## Transformacija uslova :grey_question:
Treća implementirana transformacija je izmena uslova. Program transformiše sve uslove u C kodu u željeni tip – if-then-else, switch-case-default. Za te potrebe koriste se klase PrepIfVisitor, PrepIffVisitor, PrepSwitchVisitor, If2SwitchVisitor i Switch2IfVisitor. Prve tri pripremaju if i switch naredbe za dobru zamenu naredbi break i continue, dok preostale sprovode odgovarajuće transformacije. Tačne sheme izmena moguće je videti u svakom cpp fajlu.

Primer pokretanja (testiranja) programa:
```
./trans <ulaz> <izlaz> <if|switch>
./trans ifswitch.c samoif.c if
```

Na ovaj način će na osnovu koda ifswitch.c biti formiran kod samoif.c koji sadrži isključivo uslove tipa if-then-else.

## Transformacija rekurzije :repeat:
Pretposlednja implementirana transformacija je izmena rekurzije. Program transformiše svu kontrolu toka sa repnim ponavljanjem u C kodu u željeni tip – iteracija, rekurzija. Za te potrebe koriste se klase Iter2RekVisitor, Rek2IterVisitor, FinIterVisitor i FinRekVisitor. Prve dve sprovode odgovarajuće transformacije, dok druge dve sprovode završne dorade, kako bi kod ostao sintakno i značenjski ispravan. Tačne sheme izmena moguće je videti u svakom cpp fajlu.

Primer pokretanja (testiranja) programa:
```
./trans <ulaz> <izlaz> <iter|rek>
./trans rekiter.c samoiter.c iter
```

Na ovaj način će na osnovu koda rekiter.c biti formiran kod samoiter.c koji sadrži isključivo iterativno repno ponavljanje (petlja tipa while).

## Imputacija koda :new:
Peta implementirana transformacija je imputacija koda. Program umeće (imputira) nove AST čvorove u C kod, menjajući pritom svaki n-ti već postojeći. Za te potrebe koristi se klasa CodeImputVisitor, pri čemu umetnuti kod ne menja semantiku polaznog programa, pošto se suštinski ne izvršava.

Primer pokretanja (testiranja) transformatora:
```
./trans <ulaz> <izlaz> u<n: uint>
./trans normal.c bloated.c u3
```

Na ovaj način će na osnovu koda normal.c biti formiran kod bloated.c koji sadrži mnogo više koda nego što je to neophodno, umetnunog nakon svake treće naredbe.

## Eliminacija petlji:
Poslednja šesta transformacija je eliminacija petlji. Petlje se eliminišu tako što se transformišu u semantički ekvivalentnu sekvencu labela, uslovnih i bezuslovnih skokova i samo tela petlji. Klase PrepWhile2GotoVisitor, PrepFor2GotoVisitor, PrepDo2GotoVisitor pripremaju telo petlje za transformaciju tako što menjaju break i continue naredbe sa skokovima na odgovarajuće labele petlje u kojima se nalaze. Zatim klase While2GotoVisitor, For2GotoVisitor i Do2GotoVisitor transformišu samu petlju u labele, uslovne i bezuslovne skokove.

Primer pokretanja (testiranja) transformatora
```
./ <ulaz> <izlaz> goto
./trans loops.c out_loops.c goto
```

## Podešavanje :memo:
Primer prevođenja programa sistemom CMake:
```
mkdir build
cd build
cmake ..
make
```

