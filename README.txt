Kompilator JFTT 2022
Autor: Piotr Żuk
Nr indeksu: 254617
Opis plików:
-lookupTab.cpp - zawiera reprezentację tablicy symboli w formie listy, funkcje pomocnicze (operacje na tablicy)
-codeGenerator.cpp - zawiera niektóre funkcje pomocnicze, oraz handle komend ASSIGN READ i WRITE
-Conditions.cpp - zawiera reprezentację Condition jak i handle komend tworzących pętle i IFy
-errorHandler.cpp - prosta funkcja przyjmująca wiadomość błędu i wypisująca ją kończąc działanie kompilatora
-Expressions.cpp - zawiera reprezentację expression, funkcje pomocnicze dla expression, handle dla komend PLUS MINUS TIMES DIV oraz MOD
-Values.cpp - zawiera reprezentację value, funkcje pomocnicze do wczytywania jej z lookupTable, oraz generowanie liczby w kodzie maszynowym
-lexter.l - lekser 
-bison.ypp - parser - tutaj pozwoliłem sobie na dodanie do gramatyki nieterminala iterator, aby przy tworzeniu FORa parser generował iterator do pamięci, nie zmienia to początkowej gramatyki, a pozwala parserowi na wywołanie generowania iteratora przed generowaniem komend w forze
Instrukcja:
1. make - używamy make aby skompilować pliki kompilatora
2. ./kompilator plik_wejściowy.imp plik_wyjściowy.mr - wrzucamy do kompilacji plik_wejściowy_imp i otrzymujemy plik wyjściowy plik_wyjściowy.mr z kodem maszynowym
3. ./maszyna-wirtualna plik_wyjściowy.mr - używając maszyny wirtualnej (lub maszyny wirtualnej z biblioteką cln) uruchamiamy plik z kodem maszynowym
