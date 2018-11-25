# auto-cheatsheet
Automatycznie tworzenie ściąg na linuxie

### Instalacja na Ubuntu-podobnych systemach:
```
wget -O - https://raw.githubusercontent.com/tonowak/auto-cheatsheet/master/install.sh | bash
```

### Uruchamianie

Wystarczy w folderze auto-cheatsheet wpisać komendę:
```
make
```
Program poprosi o liczbę kolumn, zalecane jest 4 albo 5.

## Używanie

Program pobiera materiał z pliku input.txt i tworzy plik output.pdf. Przykład wyjaśniający składnie znajduje się w domyślnym input.txt. Większy przykład znajduje się w input_big_example.txt. Zalecane jest tworzenie materiału w google docs, gdzie można używać list punktowanych/myślników, a następnie przekopiowanie tego do programu. W przypadku errora, powinien istnieć plik "log", który należy mi wysłać (zazwyczaj oznacza to jakiś niedozwolony plik w input.txt)

