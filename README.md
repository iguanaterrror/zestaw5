

# ASCII renderer


Zadanie na pracownie c++.
Program tworzy obrazki w formie plików ASCII.


Implementuje klasę Canvas na której jest tworzony obraz. 
Umożliwia dodanie figur - prostokąt, kwadrat, koło.
W pliku konfiguracyjnym podaje sie wymiary canvasu, nazwe pliku do jakiego ma byc zapisane, znak pustego pixela oraz nazwy i parametry figur jakie maja byc dodane do obrazu.

Aby skompilować program:

>g++ -o canvas canvas.cpp

Aby wykonać program:

>./canvas config.txt

W pliku *config.txt* można ustalić jakie figury i w jakim miejscu maja pojawic sie na canvasie.