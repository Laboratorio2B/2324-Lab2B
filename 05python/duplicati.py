#!/usr/bin/env python3
"""
Esempio di script per la ricerca di file duplicati


Comandi per la gestione di file e directory

os.getcwd()       # restituisce directory corrente
os.chdir(path)    # cambia directory
os.listdir(path)  # elenca file (restituisce lista di stringhe)
os.access(path)   # verifica i permessi  
os.path.getsize(path) # dimensione file
os.path.exists(path)  # vero se il file/directory esiste  
os.path.isfile(path)  # vero se regular file
os.path.isdir(path)   # vero se directory
os.path.islink(path)  # vero se symbolic link
os.path.join(nome_dir,nome_file) # combina nome dir e file
os.path.abspath(path) # restituisce path assoluto
os.path.realpath(path) # restituisce nome canonico eliminando link simbolici

Lista completa dei comandi su:
  https://docs.python.org/3/library/os.html
  https://docs.python.org/3/library/os.path.html

Per informazioni sui permessi dei file o come 
cambiarli: `man chmod` 
"""
import os, os.path, sys, subprocess


def main(nomedir):
  """Lancia ricerca ricorsiva su nomedir"""
  if not os.path.exists(nomedir):
    print("Il nome che mi hai passato non esiste")
    sys.exit(1)
  if not os.path.isdir(nomedir):
    print("Il nome che mi hai passato esiste, ma non è una directory")
    sys.exit(1)
  nomeabs = os.path.abspath(nomedir)
  diz = {}
  cerca_duplicati(nomeabs,diz,set())
  print(diz)
  for dim in sorted(diz):
    if len(diz[dim])>1:
      print(f"Dimensione {dim}:")
      # cerca duplicati nell'insieme diz[dim]
      visualizza_duplicati(diz[dim])



def visualizza_duplicati(lista):
  """Dato un insieme di file visualizza quali di loro sono dei duplicati"""
  
  assert len(lista)>1, "Devo essere chiamato con lista con + di 1 elemento"
  for i in range(len(lista)):
    for j in range(i+1,len(lista)):
      # esegue il confronto fra lista[i] e lista[j] con il comando cmp
      comando = ["cmp", lista[i], lista[j]]
      r = esegui(comando)
      if r.returncode == 0:
        # cmp restituisce 0 -> i file sono uguali 
        print(f"{lista[i]}\n  identico a:\n{lista[j]}\n")
        # passa al file successivo
        break
      

def cerca_duplicati(nome,diz,dir_esplorate):
  """Associa in diz ad ogni lunghezza di file i nomi di tutti i file
 di quella lunghezza tra quelli nella directory nome e sottodirectory """
  
  assert os.path.isdir(nome), "Argomento deve essere una directory"
  print(f"Begin: {nome}",file=sys.stderr)
  # ottiene il contenuto della directory 
  listafile = os.listdir(nome)
  for f in listafile:
    nomecompleto = os.path.join(nome,f)
    # verifica se il file è accessibile
    if not os.access(nomecompleto,os.F_OK):
      print("!! Broken link:", nomecompleto, file=sys.stderr)
      continue
    # distinguo tra file normali e directory
    if not os.path.isdir(nomecompleto):
      nuovadim = os.path.getsize(nomecompleto)
      if nuovadim in diz: # esiste chiave nuovadim in diz?
        diz[nuovadim].append(nomecompleto)
      else:
        diz[nuovadim] = [nomecompleto]
    else:
      # nomecompleto è una directory possibile chiamata ricorsiva
      if not os.access(nomecompleto, os.R_OK | os.X_OK):
        print(f"!! Directory {nomecompleto} non accessibile",file=sys.stderr)
        continue
      nomereal = os.path.realpath(nomecompleto)
      if nomereal in dir_esplorate:
        print(f"!! Directory {nomereal} già esplorata",file=sys.stderr)
        continue
      dir_esplorate.add(nomereal)
      # directory nuova e accessibile: esegui ricorsione
      cerca_duplicati(nomecompleto,diz,dir_esplorate)
  # ciclo for su i file di questa directory terminato     
  print(f"End: {nome}",file=sys.stderr)


# esegue un comando della shell in un sottoprocesso 
# stdout e stderr del sottoprocesso sono memorizzati nel risultato
def esegui(comando):
  """Esegui comando e restituisci il corrispondente CompletedProcess"""
  return subprocess.run(comando, capture_output=True,encoding="utf-8")

  
# verifico argomenti sulla linea di comando
# e faccio partire la ricerca dei duplicati
if len(sys.argv) == 2:
    main(sys.argv[1])
else:
    print("Uso:", sys.argv[0], "nome_directory")


