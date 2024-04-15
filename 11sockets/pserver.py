#! /usr/bin/env python3

# esempio di server legge due interi e  
# restituisce l'elenco dei primi tra questi interi
import sys, struct, socket, argparse


# descrizione del programma utilizzata da argparse
Description = """
Esempio di server python che legge due interi e resitituisce
l'elenco dei primi compresi tra questi interi"""

# default HOST e PORT da cui ricevere le connessioni 
# i valori modificabili dalla linea di comando con i paramnetri -a e -p
HOST = "127.0.0.1"  
PORT = 65432        



# main del server
def main(host,port):
  print(f"In attesa da {host} sulla porta {port}") 
  # creiamo il server socket
  with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    try:
      # permette di riutilizzare la porta se il server viene chiuso
      server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
      server.bind((host, port))
      server.listen()
      while True:
        print("In attesa di un client...")
        # mi metto in attesa di una connessione
        conn, addr = server.accept()
        # lavoro con la connessione appena ricevuta
        # durante la gestione il server non accetta nuove connessioni
        gestisci_connessione(conn,addr)
    # esempio gestione di SIGINT attraverso una eccezione
    # ctrl-C ha l'effetto di chiudere il server
    except KeyboardInterrupt:
      pass
    print('Va bene smetto...')
    # shutdown del server (la close viene fatta dalla with)  
    server.shutdown(socket.SHUT_RDWR)



# gestisci una singola connessione
# con un client
def gestisci_connessione(conn,addr): 
  # L'uso di with serve solo a garantire che
  # conn venga chiusa all'uscita del blocco
  with conn:  
    print(f"Contattato da {addr}")
    # ---- attendo due interi da 32 bit, quindi 8 byte in totale
    data = recv_all(conn,8)
    assert len(data)==8
    # ---- decodifico i due interi dal network byte order
    inizio  = struct.unpack("!i",data[:4])[0]
    fine = struct.unpack("!i",data[4:])[0]
    print("Ho ricevuto i valori", inizio,fine)
    # ---- calcolo elenco dei primi
    primi = elenco_primi(inizio, fine)
    # ---- invio risultato in formato preceduto da lunghezza
    conn.sendall(struct.pack("!i",len(primi))) #lunghezza
    for p in primi:
      conn.sendall(struct.pack("!i",p))       # singoli valori 
    # ---- ricevo la somma dei primi trovati
    data = recv_all(conn,8)
    somma = struct.unpack("!q",data)[0]
    if somma == sum(primi):
      print(f"Somma corretta ricevuta da {addr}")   
    print(f"Finito con {addr}")
 


# Riceve esattamente n byte dal socket conn e li restituisce
# il tipo restituto è "bytes": una sequenza immutabile di valori 0-255
# Lancia una eccezione se la connessione viene chiusa prima di aver
# ricevuto tutti i byte
def recv_all(conn,n):
  chunks = b''
  bytes_recd = 0
  while bytes_recd < n:
    # riceve blocchi di al più 1024 byte
    chunk = conn.recv(min(n - bytes_recd, 1024))
    if len(chunk) == 0:
      raise RuntimeError("socket connection broken")
    chunks += chunk
    bytes_recd = bytes_recd + len(chunk)
    assert bytes_recd == len(chunks)
  return chunks
 

# restituisce lista dei primi in [a,b]
def elenco_primi(a,b):
  ris = []
  for i in range(a,b+1):
    if primo(i):
      ris.append(i);
  return ris


# dato un intero n>0 restituisce True se n e' primo
# False altrimenti
def primo(n):
    assert n>0, "L'input deve essere positivo"
    if n==1:
        return False
    if n==2:
        return True
    if n%2 == 0:
        return False
    assert n>=3 and n%2==1, "C'e' qualcosa che non funziona"
    for i in range(3,n//2,2):
        if n%i==0:
            return False
        if i*i > n:
            break    
    return True


# questo codice viene eseguito solo se il file è eseguito direttamente
# e non importato come modulo con import da un altro file
if __name__ == '__main__':
  # parsing della linea di comando vedere la guida
  #    https://docs.python.org/3/howto/argparse.html
  parser = argparse.ArgumentParser(description=Description, formatter_class=argparse.RawTextHelpFormatter)
  parser.add_argument('-a', help='host IP address', type = str, default=HOST)  
  parser.add_argument('-p', help='port', type = int, default=PORT) 
  args = parser.parse_args()
  main(args.a,args.p)

