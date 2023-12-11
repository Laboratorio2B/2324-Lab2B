#! /usr/bin/env python3

# esempi fatti a lezione: premere Run per leggere il file
# dentro l'interprete (tab Console) e sperimentare

# tre modi diversi di delimitare una stringa
s1 = "ciao 1"
s2 = 'ciao 2'
s3 = """ciao!
sono una stringa come le altre ma contengo dei \\n al 
mio interno infatti sono chiamata stringa 'multiriga'"""

# i caratteri che non sono usati come delimitatori 
# possono comparire dentro la stringa
s4 = 'Zinédine  Zidane  detto "Zizou"'


# stampa delle stringhe definite prima altrimenti non sarebbero visualizzate 
# notiamo che la print di default aggiunge uno \n dopo aver stampato 
print(s1)
print(s2)
print(s3)
print(s4)
print("---- fine stringhe----") 


# esempio di ricorsione, asserzione, if/else/elsif  
def fatt(n):
  """calcola il fattoriale"""
  
  assert n>=0, "Argomento non puo essere negativo"
  if n==0: 
    return 1
  elif n==1:
    return 1
  elif n==2:
    return 2
  else: 
    return n*fatt(n-1)
  

# esempio ciclo while + else
def primo(n):
  assert n>1, "argomento deve essere >1"
  d=2
  while d*d<=n:
    if n%d==0:
      print(f"Il numero {n} è divisibile per {d}")
      break
    d += 1
  else:
    print(f"Il numero {n} è primo")
  return


# fattoriale senza ricorsione
# avendo lo stesso nome sovrascrive la
# precedente definizione di fatt() 
def fatt(n):
  assert n>=0, "Argomento non puo essere negativo"
  f = 1
  for i in range(2,n+1):
    f *= i
  return f
  

# esempio di uso del ciclo for decrescente
def contoallarovescia(n):
  """stampa i numeri da n a 0
  adando indietro di 1 alla volta"""
  
  tot = 0 
  for i in range(n,-1,-1):
    print(i)
    tot +=i 
  # due modi diversi per stampare la stessa informazione
  print( "fine, la somma è:", tot)  
  print(f"fine, la somma è: {tot}")
  
  
# esempio creazione e manipolazione lista
def esempio_lista():
  lista = [1,2,3,"ciao"]
  print(lista[2:]) # estrae gli elementi da lista[2] alla fine 
  lista[2] = 5
  lista = lista + [34,40]
  lista.append(35)
  print(lista)

# esempio for sugli elementi di una lista
def esempio_for_lista():
  parole = ["casa","mare","sole"]
  # prima versione senza usare un indice
  for x in parole:   # itera tra gli elementi di parole
    print(x.upper())
  print(parole)
  # seconda versione 
  for i in range(len(parole)): # itera tra 0 e len(parole)-1
    print(parole[i].upper())   # questo non modifica parole[i]
    parole[i] = parole[i] + str(i) # qui invece parole[i] cambia
  print(parole)
  
  
# la funzione main non ha particolari proprietà in python ...
def main(n):
  print(f"Fattoriale di {n}: {fatt(n)}")

  
# ma per analogia con il C spesso la usiamo 
# per far partire l'esecuzione del  programma
# ma deve essere fatto esplicitamente come qui sotto
main(100)  

