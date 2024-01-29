#! /usr/bin/env python3
"""
Esercizio che costruisce una classifica dati i 
risultati di un insieme di partite scritte in un file


Uso un dizionario per rappresentare la classifica con
  chiave: nome squadra 
  valore: array di 3 elementi: [punteggio, gol fatti, gol subiti]
Per convenzione se una squadra non è nel dizionario 
assumiamo abbia punteggio 0 e 0 gol fatti o subiti

La classifica finale viene costruita ordinando 
le squadre per punteggio e differenza reti
Le squadre che hanno gli stessi punti e differenza
reti sono ordinate lessicograficamente 
(ad esempio Livorno e Parma)

sorting howto:
https://docs.python.org/3/howto/sorting.html

with statement
https://realpython.com/python-with-statement/
"""


# import necessario per leggere gli argomenti 
# sulla linea di comando in sys.argv
import sys


def aggiorna_classifica(c,s1,g1,s2,g2):
  """Aggiorna per s1 e s2 i punti i gol fatti e subiti. 
  Per ogni squadra nella classifica associo al nome 
  l'array di 3 elementi: [punti, gf, gs]"""
  # calcolo i punti assegnati alle squadre
  if g1>g2:
    p1=3
    p2=0
  elif g1<g2:
    p1=0
    p2=3
  else:
    p1=p2=1
  # aggiorno punti e gol delle due squadre
  if s1 in c:
    stat = c[s1] # stat è una tripletta
    stat[0] += p1
    stat[1] += g1
    stat[2] += g2
    c[s1] = stat
  else:
    c[s1] = [p1,g1,g2] # prima occorrenza di s1
  if s2 in c:
    stat = c[s2] # stat è una tripletta
    stat[0] += p2
    stat[1] += g2
    stat[2] += g1
    c[s2] = stat
  else:
    c[s2] = [p2,g2,g1] # prima occorrenza di s2


def crea_classifica(f):
  """legge le righe dei risultsti dal file f
  e aggiorna e crea la classifica risultante"""
  c = {}     # crea classifica vuota
  for linea in f:
    # suddivido la stringa in corrispondenza degli spazi
    a = linea.split()
    if len(a) == 0:
      continue   # linea senza risultati
    if len(a) != 4:
      raise RuntimeError(f"Linea non corretta: {linea}")
    # la linea ha 4 componenti, procediamo a valutare la partita
    g1 = int(a[0])
    g2 = int(a[1]) 
    aggiorna_classifica(c, a[2], g1, a[3], g2) 
  return c
  
  
# stampa in maniera incolonnata nome, punti, gol fatti e gol subiti   
def stampa_squadra(nome,punti,golf,gols):
  # <12 vuol dire usare 12 spazi e giustificare a sinistra
  # >2 vuol dire usare   2 spazi e giustificare a destra 
  print(f"{nome:<12} {punti:>2}  {golf:>2}  {gols:>2}")  
  

def main(nomefile):
  with open(nomefile,"r") as f:
    # viene restituito il dizionario c contenente la classifica
    c = crea_classifica(f)
  # all'uscita del with il file f viene automaticamente chiuso
  squadre = list(c) # crea un array con le chiavi
  squadre.sort()    # ordina lessicograficamente
  # ordina per valori decrescenti di punti e differenza reti
  # per ogni squadra x c[x] è l'array con punti,golfatti,golsubiti
  # quindi c[x][0] sono i punti, c[x][1]-c[x][2] la differenza reti
  # Usiamo il fatto che gli array di 2 elementi sono confrontati
  # componente per componente
  squadre.sort(key=lambda x: [c[x][0], c[x][1]-c[x][2]], reverse=True)
  # stampa intestazione classifica
  print("-----------------------")
  print("Squadra      Pu  GF  GS")
  print("-----------------------")
  # stampo la classifica secondo l'ordinamento ottenuto
  for s in squadre:
    stampa_squadra(s,c[s][0],c[s][1],c[s][2])
  return


if len(sys.argv)==2:
  main(sys.argv[1])
else:
  print(f"Uso:\n\t{sys.argv[0]} nomefile")
  
