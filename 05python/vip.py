"""
Esempio definizione di una classe in python con particolare riferimento ai metodi 
__eq__ e __hash__ per la gestione di liste, set(), e dizionari  

Per approfondire:
https://docs.python.org/3/reference/datamodel.html#special-method-names
"""

import time

class Vip:

  def __init__(self,n,c,citta="Roma"):
    """Costruisci  il vip dato nome e cognome
    se non viene fornita la residenza viene assegnata a Roma"""
    self.nome = n
    self.cognome = c
    self.residenza = citta


  def riposa(self,t):
    """riposa per un numero assegnato di secondi"""
    print(self.nome, "...")
    time.sleep(t)
    print("...", self.cognome)

  def __str__(self):
    """metodo invocato da print/str/etc"""
    return self.nome + " " +self.cognome +f" ({self.residenza})"
  
  def __eq__(self,v):
    """ metodo invocato da =="""
    return self.nome == v.nome and self.cognome == v.cognome and self.residenza == v.residenza
    
  def __hash__(self):
    """metodo necessario per usare i Vip in set 
    e come chiavi di dict"""
    h = hash((self.nome,self.cognome,self.residenza))
    # per debug mostriamo l'oggetto e il corrispondente hash
    print(f"Hash({self}) --> {h}")
    return h


# esempi di operazioni con elementi della classe
totti = Vip("Francesco","Totti")
renga = Vip("Francesco","Renga")
chiara = Vip("Chiara","Ferragni","Milano")
capitano = Vip("Francesco","Totti")
# crea lista 
isola = [totti, Vip("Ilary","Blasi")]

# crea set
stadio = {Vip("Francesco","Totti"), Vip("Ilary","Blasi")}


# crea dizionario
followers = {Vip("Chiara","Ferragni","Milano"):3000}
# cambiando la residenza la chiave chiara non viene più trocata
print(chiara in followers)
chiara.residenza = "Monza"
print(chiara in followers)
# la morale è che per non avere problemi 
# gli oggetti memorizzati in set() o usati
# come chiavi nei dizionari devono essere immutabili 
# Ad esempio: stringhe e interi o tuple (contenti oggetti immutabili)
 
