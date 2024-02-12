"""
Esempio definizione di una classe in python con particolare riferimento ai metodi 
__eq__ e __hash__ per la gestione di liste, set(), e dizionari  

Per approfondire:
https://docs.python.org/3/reference/datamodel.html#special-method-names
"""

import time

class Vip:

  def __init__(self,n,c):
    """Costruisci  il vip dato nome e cognome"""
    self.nome = n
    self.cognome = c

  def riposa(self,t):
    """riposa per un numero assegnato di secondi"""
    print(self.nome, "...")
    time.sleep(t)
    print("...", self.cognome)

  def __str__(self):
    """metodo invocato da print/str/etc"""
    return self.nome + " " +self.cognome
  
  def __eq__(self,v):
    """ metodo invocato da =="""
    return self.nome == v.nome and self.cognome == v.cognome
    
  def __hash__(self):
    """metodo necessario per usare i Vip in set 
    e come chiavi di dict"""
    # print(f"Hash invocato da {self}")
    return hash((self.nome,self.cognome));


# esempi di operazioni con elementi della classe
totti = Vip("Francesco","Totti")
renga = Vip("Francesco","Renga")
chiara = Vip("Chiara","Ferragni")
capitano = Vip("Francesco","Totti")
# crea lista 
isola = [totti, Vip("Ilary","Blasi")]
# crea set
stadio = {Vip("Francesco","Totti"), Vip("Ilary","Blasi")}
# crea dizionario
followers = {Vip("Chiara","Ferragni"):3000} 
