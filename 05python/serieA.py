#! /usr/bin/env python3
"""
Esercizio che costruisce una classifica dati i 
risultati di un insieme di partite scritte in un file

Mantengo la classifica come dizionario che associa
  squadra -> punti
se la squadra non compare nel dizionario 
assumiamo abbia 0 punti

sorting howto:
https://docs.python.org/3/howto/sorting.html

with statement
https://realpython.com/python-with-statement/#managing-resources-in-python
"""

"""
Uso un dizionario per rappresentare la classifica
chiave: squadra, valore: punteggio
convenzione se una squadra non è nel dizionario ha punteggio 0
"""

import sys

  
    
def main(nomefile):
  pass


if len(sys.argv)==2:
  main(sys.argv[1])
else:
  print(f"Uso:\n\t{sys.argv[0]} nomefile")
  
