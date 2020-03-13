# IPP_zadanie1
Zadanie 1 z przedmiotu 'Indywidualny Projekt Programistyczny'

Treść zadania:

Małe zadanie

Celem zadania jest napisanie programu opisującego zachowanie cząstki w pewnym wyimaginowanym świecie kwantowym. Cząstka może przebywać w czterech stanach kwantowych, oznaczanych liczbami 0, 1, 2 i 3. Kwantowa historia cząstki jest to niepusty ciąg kolejnych stanów kwantowych, w jakich cząstka przebywała, ale tylko niektóre kwantowe historie cząstki są dopuszczalne. Dopuszczalnej kwantowej historii cząstki można przypisać skwantowaną energię. Energię tę można zmieniać. Niedopuszczalna kwantowa historia cząstki nie może mieć przypisanej energii. Energie dwóch dopuszczalnych kwantowych historii cząstki mogą zostać zrównane, co oznacza, że zmiana energii dla jednej z tych historii powoduje też zmianę energii drugiej z nich. Relacja zrównania energii przypisanych historiom jest równoważnością.
Opis działania programu

Po uruchomieniu programu nie są dopuszczalne żadne kwantowe historie cząstki, zatem żadnej historii nie jest przypisana energia i żadne dwie energie nie są zrównane. W czasie działania program czyta ze standardowego wejścia i wykonuje następujące polecenia:

    DECLARE history – Powoduje, że każda kwantowa historia cząstki, będąca prefiksem podanej jako parametr history kwantowej historii cząstki, staje się dopuszczalna.

    REMOVE history – Powoduje, że każda kwantowa historia cząstki, mająca prefiks podany jako parametr history, przestaje być dopuszczalna.

    VALID history – Sprawdza, czy podana kwantowa historia cząstki jest dopuszczalna.

    ENERGY history energy – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta nie ma przypisanej energii, to przypisuje jej wartość energii podanej jako parametr energy. Jeśli ta kwantowa historia cząstki ma już przypisaną energię, to modyfikuje wartość tej energii.

    ENERGY history – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta ma przypisaną energię, to wypisuje wartość tej energii.

    EQUAL history_a history_b – Jeśli podane w parametrach history_a i history_b kwantowe historie cząstki są dopuszczalne, to: (a) jeśli chociaż jedna z nich ma przypisaną energię, zrównuje ich energie i domyka relację równoważności; (b) jeśli obie historie przed wykonaniem tego polecenia mają przypisane energie, to po wykonaniu polecenia energia przypisana tym historiom jest średnią arytmetyczną tych energii (z ewentualnym zaokrągleniem w dół); (c) jeśli obie historie są identyczne lub mają już zrównane energie, niczego nie zmienia.

Poprawne dane wejściowe spełniają następujące dodatkowe warunki:

    Parametr opisujący kwantową historię cząstki jest niepustym ciągiem składającym się z cyfr 0, 1, 2 i 3.
    Energia jest dziesiętną liczbą całkowitą z przedziału od 1 do 2^64 − 1.
    Nazwa polecenia i jego parametry są oddzielone pojedynczą spacją, a każdy wiersz wejścia zawiera co najwyżej jedno polecenie i kończy się linuksowym znakiem przejścia do nowej linii (znak \n w C, kod ASCII 10). Są to jedyne białe znaki występujące w wierszu.

Ponadto:

    Puste wiersze należy ignorować.
    Wiersze rozpoczynające się znakiem # należy ignorować.

Informacje wypisywane przez program i obsługa błędów

Program kwituje poprawne wykonanie polecenia, wypisując informację na standardowe wyjście:

    Dla polecenia innego niż polecenie VALID lub jednoparametrowe polecenie ENERGY wiersz ze słowem OK.
    Dla polecenia VALID wiersz ze słowem YES lub NO zależnie od wyniku tego polecenia.
    Dla jednoparametrowego polecenia ENERGY dziesiętną liczbę całkowitą będącą wartością energii.
    Każdy wiersz wyjścia powinien kończyć się linuksowym znakiem przejścia do nowej linii (znak \n w C, kod ASCII 10). Jest to jedyny biały znak, jaki może pojawić się na wyjściu.

Program wypisuje informacje o błędach na standardowe wyjście diagnostyczne:

    Dla każdego błędnego wiersza i dla każdego polecenia, które nie może być wykonane, gdyż nie spełnia wyżej opisanych warunków, np. z powodu złej liczby parametrów lub błędnej wartości parametru, należy wypisać wiersz ze słowem ERROR, zakończony linuksowym znakiem końca linii (znak \n w C, kod ASCII 10). Jest to jedyny biały znak, jaki może pojawić się na wyjściu.

Przykładowe dane

Przykładowe dane dla programu znajdują się w załączonych plikach.
Zakończenie programu

Program kończy się po przetworzeniu wszystkich poleceń z wejścia. Program powinien wtedy zwolnić całą zaalokowaną pamięć i zakończyć się kodem 0. Awaryjne zakończenie programu, np. na skutek niemożliwości zaalokowania potrzebnej pamięci, powinno być sygnalizowane kodem 1.
Makefile

Częścią zadania jest napisanie pliku makefile. W wyniku wywołania polecenia make powinien powstać program wykonywalny quantization. Jeśli któryś z plików źródłowych ulegnie zmianie, ponowne wpisanie make powinno na nowo stworzyć plik wykonywalny. Plik makefile powinien działać w następujący sposób:

    osobno kompiluje każdy plik .c,
    linkuje wszystkie pliki .o,
    przy zmianie w pliku .c lub .h wykonuje tylko niezbędne akcje,
    wywołanie make clean usuwa plik wykonywalny i dodatkowe pliki powstałe podczas kompilowania.

Docelowo pliki rozwiązania należy kompilować programem gcc z opcjami:

-Wall -Wextra -std=c11 -O2

Skrypt testujący

Osobną częścią zadania jest napisanie skryptu test.sh. Po wywołaniu

./test.sh prog dir

skrypt powinien uruchomić program prog dla wszystkich plików wejściowych postaci dir/*.in, porównać wyniki z odpowiadającymi im plikami dir/*.out i dir/*.err, a następnie wypisać, które testy zakończyły się powodzeniem, a które niepowodzeniem. Skrypt powinien akceptować parametry z dowolną ścieżką, jaką akceptuje powłoka.

Do wykrywania problemów z zarządzaniem pamięcią należy użyć programu valgrind.
Pozostałe wymagania

Rozwiązanie zadania powinno być napisane w języku C i korzystać z dynamicznie alokowanych struktur danych. Implementacja powinna być jak najefektywniejsza. Należy unikać zbędnego alokowania pamięci i kopiowania danych.

Kod programu program powinien być podzielony na moduły.

Moduł zwykle składa się z dwóch plików, np. x.c i x.h, gdzie x jest nazwą modułu, implementowanej przez ten moduł struktury danych lub tp. Plik nagłówkowy x.h zawiera deklaracje operacji, struktur udostępnianych przez moduł x, a plik x.c – ich implementację. W pliku nagłówkowym należy umieszczać jedynie deklaracje i definicje, które są częścią interfejsu tego modułu. Wszystkie szczegóły powinny być ukryte w pliku z implementacją.

Moduł może też składać się z samego pliku nagłówkowego, jeśli udostępnia jedynie definicje stałych bądź typów, lub funkcji, które sugerujemy kompilatorowi do rozwijania w miejscu wywołania (static inline).

Moduł może też składać się z samego pliku z implementacją, jeśli nie udostępnia żadnego interfejsu – żadne funkcje z tego modułu nie są wywoływane z innych modułów.

Ponadto rozwiązanie powinno zawierać pliki:

    makefile – Patrz punkt „makefile”.
    test.sh – Patrz punkt „skrypt testujący”.

Rozwiązanie należy oddać jako archiwum skompresowane programem zip lub parą programów tar i gzip.
Punktacja

Za w pełni poprawne rozwiązanie zadania implementujące wszystkie funkcjonalności można zdobyć maksymalnie 20 punktów. Rozwiązanie niekompilujące się będzie ocenione na 0 punktów. Punkty będą odejmowane za poniższe uchybienia:

    Za każdy test, którego program nie przejdzie, traci się do 1 punktu.
    Za problemy z zarządzaniem pamięcią można stracić do 6 punktów.
    Za niezgodną ze specyfikacją strukturę plików w rozwiązaniu można stracić do 4 punktów.
    Za złą jakość kodu, brzydki styl kodowania można stracić do 4 punktów.
    Za ostrzeżenia wypisywane przez kompilator można stracić do 2 punktów.
    Za brak lub źle działający makefile można stracić do 2 punktów.
    Za brak skryptu testującego lub błędy w tym skrypcie można stracić do 2 punktów.

Rozwiązania należy implementować samodzielnie pod rygorem niezaliczenia przedmiotu.

