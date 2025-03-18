
# Graf jimp2

Program generuje macierz sąsiedztwa na podstawie danych podanych przez użytkownika. Możliwe jest podawania danych w postaci liczbowej lub tekstowej.

## Instalacja

#### Uwaga! Do używania funkcjonalności llm należy pobrać [ollama](https://github.com/ollama/ollama)

Pobierz projekt

```bash
  git clone https://github.com/julian428/jimp2-graf
```

W pobranym folderze

Do kompilacji programu potrzebne jest [nix-shell](https://nixos.org/download/#nix-install-windows) oraz połączenie z internetem.

```bash
  make
```

#### Dla funkcjonalności llm
```bash
ollama serve
```

## Używanie/Przykłady

```bash
./graph 6 0 0
```

Powyższe polecenie wygeneruje losową macierz sąsiedztwa. Ten graf nie jest skierowany.

Macierz z zapisanego pliku:
```text
0 011100
1 100111
2 010100
3 111001
4 101101
5 110000
```

---

```bash
        |
./graph 6 0 0
```

Pierwsza liczba musi być dodatnią liczbą całkowitą i wskazuje ona na liczbę krawędzi grafu.

---

```bash
          |
./graph 6 0 0
```

Druga liczba może być __0__, __1__ albo __2__ i wskazuje na to czy:

__0__ - macierz generowana losowo.

__1__ - macierz podawana przez użytkownika.

__2__ - macierz generowana przez LLM.

---

```bash
            |
./graph 6 0 0
```

Trzecia liczba może być __0__ albo __1__ gdzie:

__0__ - graf nie skierowany.

__1__ - graf skierowany.

### Zamiast liczb można napisać proźbę

```bash
./graph Stwórz graf z 6 krawędziami który jest skierowany
```

Po chwili czekania na odpowiedź plik z macierzą zostanie zapisany.

```text
0 0101
1 1001
2 1001
3 0000
```

Niestety jak widać poprawność macierzy zależy głównie od tego jaki llm mamy zainstalowany. W typ przypadku użyłem [jmcastagnetto/deepseek-r1-distill-llama-8b](https://ollama.com/jmcastagnetto/deepseek-r1-distill-llama-8b) oraz od języka którym wysyłamy zapytanie.

---

Jeżeli wiemy jakimi zwrotami najczęściej będzie się zwracać użytkownik możemy zmienić nazwę parametrów w plikach z zapytanniami json.

```json
"properties": {
			"vertesies": {
				"type": "integer"
			},
			"directional": {
				"type": "boolean"
			}
		},

```

na przykład zamiast 'vertesies' 'edges' będzie używany częściej czyli:

```json
"properties": {
			~~ "vertesies": { ~~
            "edges": {
				"type": "integer"
			},
			"directional": {
				"type": "boolean"
			}
		},

```
## Zmiana używanego modelu llm

#### Dla generowania parametrów z proźby

otwórz plik

```bash
ścieżka_do_programu/data/inputRequest.json
```

Należy zmienić wartość __model__ na wybrany model llm.

```json
{
  "model": "jmcastagnetto/deepseek-r1-distill-llama-8b"
}
```

#### Dla generowania grafu

otwórz plik

```bash
ścieżka_do_programu/data/generationRequest.json
```

Należy zmienić wartość __model__ na wybrany model llm.

```json
{
  "model": "jmcastagnetto/deepseek-r1-distill-llama-8b"
}
```

#### Struktura pliku z grafem.

```bash
|
0 0101
1 0010
2 0000
3 0110
```

W pierwszej kolumnie macierzy znajduje się informacja o wierzchołku który jest opisywany.

---

```bash
  ||||
0 0101
1 0010
2 0000
3 0110
```

Kolejne n wartości w wierszu oznacza czy aktualny wierzchołek jest połączony z innym wierzchołkiem, są one numerowane tak samo:

```bash
  0123
  ||||
0 0101
1 0010
2 0000
3 0110
```

#### Zapisanie do pliku.

Program automatycznie zapisuje macierz sąsiedztwa do pliku o nazwie `graph-dd.mm.YYYY@HH:MM.txt`.

Gdzie:

__dd__ - dzień

__mm__ - miesiąc

__YYYY__ - rok

__HH__ - godziny

__MM__ - minuty

np.: 

```bash
graph-11.03.2025@11:21.txt
```

__!Nazwa pliku do którego zapisany został aktualny graf jest wypisywana przez program!__
