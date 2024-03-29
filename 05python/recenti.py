#!/usr/bin/env python3
"""
Esempio di script per la navigazione del filesystem
e di gestione dei tempi di modifica dei file


Comandi per la gestione dei tempi

time.localtime()  # converte secondi da epoch in un oggetto struct_time 
time.asctime()    # converte un oggetto struct_time in ascii
time.mktime()     # inverso di time.localtime() struct_time -> secondi da epoch


Comandi per la gestione di file e directory

os.getcwd()       # restituisce directory corrente
os.chdir(path)    # cambia directory
os.listdir(path)  # elenca file (restituisce lista di stringhe)
os.access(path)   # verifica i permessi 
os.path.getsize(path)  # dimensione file
os.path.exists(path)   # vero se il file/directory esiste  
os.path.isfile(path)   # vero se regular file
os.path.isdir(path)    # vero se directory
os.path.islink(path)   # vero se symbolic link
os.path.join(nome_dir,nome_file) # combina nome dir e file
os.path.abspath(path)  # restituisce path assoluto
os.path.realpath(path) # restituisce nome canonico eliminando link simbolici
os.path.getmtime(path) # istante ultima modifica in secs da epoch

Lista completa dei comandi su:
  https://docs.python.org/3/library/time.html
  https://docs.python.org/3/library/os.html
  https://docs.python.org/3/library/os.path.html
"""
import os, os.path, sys, time

def main(nomedir,g):
  """Lancia ricerca ricorsiva su nomedir"""
  if not os.path.exists(nomedir):
    print("Il nome che mi hai passato non esiste")
    sys.exit(1)
  if not os.path.isdir(nomedir):
    print("Il nome che mi hai passato esiste, ma non è una directory")
    sys.exit(1)
  nomeabs = os.path.abspath(nomedir)
  limite  = time.mktime(time.localtime()) - g*24*3600
  elenco = cerca_recenti(nomeabs,limite,set())
  print("------------------------") 
  print(f"Ci sono {len(elenco)} file più recenti di {g} giorni");
  for f in elenco:
    data = time.asctime(time.localtime(os.path.getmtime(f)))
    print(f"{data} {f}")
  

# funzione ricorsiva per cercare i file modificati dopo limite
def cerca_recenti(nome,datalimite,giaesplorati):
  """restituisce la lista dei file modificati dopo datalimite
 tra quelli nella directory nome e sue sottodirectory"""
  
  assert os.path.isdir(nome), "Argomento deve essere una directory"
  print(f"Begin: {nome}",file=sys.stderr)
  # inizializzo la lista di output inizialmente vuota
  recenti = []
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
      temposec = os.path.getmtime(nomecompleto)
      if temposec >= datalimite:
        recenti.append(nomecompleto)
    else:
      # nomecompleto è una directory possibile chiamata ricorsiva
      if not os.access(nomecompleto, os.R_OK | os.X_OK):
        print(f"!! Directory {nomecompleto} non accessibile",file=sys.stderr)
        continue
      nomereal = os.path.realpath(nomecompleto)
      if nomereal in giaesplorati:
        print(f"!! Directory {nomereal} già esplorata",file=sys.stderr)
        continue
      giaesplorati.add(nomereal)
      # directory nuova e accessibile: esegui ricorsione
      recenti_subdir = cerca_recenti(nomecompleto,datalimite, giaesplorati)
      # concateno al risultato
      recenti += recenti_subdir
  # ciclo for su i file di questa directory terminato     
  print(f"End: {nome}",file=sys.stderr)
  return recenti

# invoca main passando il nome di una directory e un numero di giorni
# (anche frazionario)
if len(sys.argv) == 3:
    main(sys.argv[1], float(sys.argv[2]))
else:
    print("Uso:", sys.argv[0], "nome_directory numero_giorni")
