
## Python vs C


La sintassi di Python è simile a quella del C tranne che per le sequenti semplificazioni

 * Non è richiesto il `;` alla fine di ogni linea
 * invece delle `{ }` i blocchi sono evidenziati mediante indentazione (attenti all'editor) e con il carattere `:`
 * Le parentesi `( )` nei test degli `if`/`while`   non sono necessarie
 * `/` vs `//` per distinguere tra divisione e divisione intera. Per i commenti si usa il carattere `#` 
 * non ci sono  `++` e `--`
 * operatori logici si chiamano con il loro nome: `and`, `or`, `not` etc
 * Invece di `true`/`false`/`NULL` ci sono `True`/`False`/`None` 


Python è un linguaggio interpretato non compilato: molto più lento del C (fino a 100 volte); gli errori vengono segnalati a runtime con messaggi solitamente comprensibili.

Altra differenza sostanziale è che le variabili non hanno tipo e non vanno dichiarate.

Le stringhe sono immutabili e facili da usare. Non c'è il tipo carattere: un carattere è una stringa di lunghezza uno.

Gli interi hanno precisione illimitata: ci pensa l'interprete ad usare un numero adeguato di byte per rappresentare tutte le cifre (fate la prova con il fattoriale)

## Strutture di controllo e iterazione

 * if/else/elif
 * while/continue/break, esiste un comando else per i cicli, non esiste do
 * for è basato sul concetto di range, simile al for-each di Java

## Definizione e invocazione di funzioni

Esempio di funzione che dati due interi restituisce la somma e la stringa contenente la loro concatenazione. Non è una funzione molto sensata: serve per far vedere che è possibile restituire più di un oggetto anche di tipo diverso.

```python
# definizione 
def fun(a,b):
    return a+b,str(a) +str(b)

# invocazione funzione e stampa risultato
s,p = fun(3,5)
print(s,p)
```
## Costruzione stampa e modifica di una lista
```python
lista = [1,2,3,"ciao"]
print(lista[2:]) # estrae gli elementi da lista[2] alla fine 
lista[2] = 5
lista = lista + [34,40]
lista.append(35)
print(lista)
```

### Esempi di iterazione su una lista usando il ciclo for
```python
parole = ["casa","mare","sole"]
for x in parole:
    print(x.upper())
    x = "monti"
print(parole)
for i in range(len(parole)):
    print(parole[i].upper())
    i = 7
print(parole)

```
Nota: la parola chiave `in` si usa nei cicli for e per testare l'appartenenza. Verificatelo eseguendo lea seguenti istruzioni:
```python
print(4 in [1,2,3])
print(4 in [2,4,8])
```


## Dizionari

Sono equivalenti alle `map` di Java ma più semplici da usare 

```python
d = {"casa":3, "sole":4}
d["mare"] = 5
d["casa"] = 10
print(d)
for c in d:
    print("Alla chiave", c, "è associato il valore", d[c])
```

## Docstring

Una stringa delimitata da tre virgolette `"""` nella riga immediatamente successiva alla definizione di una funzione di chiama *docstring* e forma un commento che l'interprete associa alla funzione. Viene mostrata con il comando *help* e da alcuni editor specifici per python. Ad esempio

```python
def media(a,b):
  """Calcola la media artimetica"""
  return (a+b)/2

help(media)
Help on function media in module __main__:

media(a, b)
    Calcola la media aritmetica
```

## Esecuzione di programmi

Inizialmente eseguiremo i programmi chiamando le funzioni all'interno dell'interprete python (prompt `>>>`). L'interprete ha il vantaggio che permette di testare le singole istruzioni e di vedere il contenuto delle variabili.

Successivamente eseguiremo i programmi python dalla linea di comando del terminale (in questo caso vengono chiamati `script`). Per poterli eseguire dalla linea di comando è necessario che il file contenente il sorgente inizi con la linea
```python
#!/usr/bin/env python3
```
e che il file venga reso eseguibile con il comando `chmod(1)`