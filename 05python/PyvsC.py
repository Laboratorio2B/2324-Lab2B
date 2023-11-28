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
  d=2
  while d*d<=n:
    if n%d==0:
      print(f"Il numero {n} è dvisibile per {d}")
      break
    d += 1
  else:
    print(f"Il numero {n} è primo")
  return


# esempio di uso del ciclo for descrescente
def contoallarovescia(n):
  """stampa i numeri da n a 0"""
  
  tot = 0 
  for i in range(n,-1,-1):
    print(i)
    tot +=i 
  # due modi diversi per stampare la stessa informazione
  print( "fine, la somma è:", tot)  
  print(f"fine, la somma è: {tot}")
  
  
  
# la funzione main non ha particolari proprietà...
def main(n):
  print(f"Fattoriale di {n}: {fatt(n)}")
  
# ... ma in questo caso la invochiamo dopo averne letto la definizione 
main(100)  

