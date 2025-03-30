<div align="justify">

# Instrukcja uruchomienia
Program uruchamiany jest za pomocą pliku wykonywalnego SO2_1.exe
```
./SO2_1.exe [liczba filozofów] [-d]
```
- `liczba filozofów` - dowolna liczba całkowita z przedziału <2, `MAX_INT`>, określa liczbę siedzących przy stole filozofów, domyślna wartość = 5,
- `-d` - flaga oznaczająca tryb tekstowy, wtedy za każdym razem gdy filozof zmienia swój stan informuje to w terminalu (albo myśli, albo je)  

# 📌 Opis problemu
Problem jedzących filozofów to klasyczne zagadnienie z zakresu programowania
współbieżnego i synchronizacji procesów, zaproponowane przez Edsgera Dijkstrę 
w 1965 roku. Przedstawia on sytuację, w której pięciu filozofów siedzi przy 
okrągłym stole. Między każdym z nich znajduje się jeden widelec, a zatem w 
sumie jest ich pięć. Filozofowie na przemian myślą i jedzą, przy czym do 
spożycia posiłku potrzebne są im dwa widelce – jeden znajdujący się po lewej 
stronie, a drugi po prawej.

Ponieważ widelce są współdzielone przez sąsiadujących ze sobą filozofów, 
konieczna jest synchronizacja dostępu do tych zasobów. Jeżeli każdy z 
filozofów jednocześnie podniesie jeden widelec (np. lewy) i będzie czekał 
na dostępność drugiego (prawego), system znajdzie się w stanie zakleszczenia
(deadlock). Nikt nie będzie w stanie kontynuować działania, ponieważ każdy 
proces czeka na zasób zajęty przez inny.

Problem ten stanowi model wielu rzeczywistych sytuacji związanych z dostępem
do współdzielonych zasobów w systemach informatycznych. Może to dotyczyć 
procesów w systemie operacyjnym, które rywalizują o urządzenia 
wejścia-wyjścia, transakcji w bazach danych blokujących te same rekordy, 
czy też wątków w aplikacjach wielowątkowych próbujących uzyskać dostęp do 
współdzielonej pamięci.

Oprócz zakleszczenia, problem ten ilustruje również inne trudności 
charakterystyczne dla programowania współbieżnego – takie jak zagłodzenie 
(sytuacja, w której niektóre procesy nigdy nie uzyskują dostępu do zasobu) 
czy brak sprawiedliwości (nieproporcjonalne przydzielanie zasobów). W związku 
z tym znalezienie poprawnego rozwiązania tego problemu ma istotne znaczenie 
nie tylko teoretyczne, ale i praktyczne.

W literaturze istnieje wiele sposobów rozwiązania problemu filozofów. Do 
najprostszych należy podejście asymetryczne, w którym niektórzy filozofowie
podnoszą najpierw lewy, a inni najpierw prawy widelec, co eliminuje możliwość
zakleszczenia. Inną metodą jest wprowadzenie centralnego arbitra – np. 
„kelnera”, który kontroluje, kto i kiedy może rozpocząć jedzenie. Bardziej 
złożone algorytmy, takie jak rozwiązanie Chandy-Misra, opierają się na 
rozproszonej kontroli i priorytetach, a ich celem jest nie tylko unikanie 
zakleszczeń, ale też minimalizacja opóźnień i zwiększenie sprawiedliwości.

# 🧵 Wątki i ich rola

- `Philosopher::problem`- wątek oznacza jednego filozofa który musi pomyśleć i zjeść,
czeka na wolne widelce i informuje o swoim stanie,
- `table` - wątek służący wyświetlaniu tabeli ze "statystykami" filozofów

# 🔒 Sekcje krytyczne i ich rozwiązania

| **Sekcja**                               | **Zasób chroniony**      | **Mechanizm**              | **Miejsce**                                 |
|------------------------------------------|--------------------------|----------------------------|---------------------------------------------|
| Zajmowanie widelców                      | `leftFork`, `rightFork`  | `std::mutex`, `lock_guard` | `Philosopher::eat()`                        |
| Aktualizacja i dostęp do liczby posiłków | `count_meals`            | `std::mutex`, `lock_guard` | `increment_meals()`, `get_meals()`          |
| Dostęp do wyjścia standardowego          | `std::cout`              | `std::mutex`, `lock_guard` | `Philosopher::eat()`,`Philosopher::think()` |

Sekcje krytyczne są zabezpieczone za pomocą `std::mutex` i `std::lock_guard`, co gwarantuje bezpieczeństwo współbieżne i brak zakleszczeń.

# ♾️ Deadlock

Deadlock jest unikany poprzez zapewnienie jednego "leworęcznego" filozofa.

</div>