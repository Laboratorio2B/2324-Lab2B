# Pagine per approfondire:
# https://pytutorial-it.readthedocs.io/it/python3.11/classes.html
# https://docs.python.org/3/tutorial/classes.html
# https://docs.python.org/3/reference/datamodel.html

import sys, math

class Articolo:
    articoli_totali = 0  # attributo/variabile di classe, condiviso tra tutte le istanze

    def __init__(self, nome, prezzo, commenti=None): # commenti è un parametro opzionale
        """
        Metodo che viene chiamato durante la costruzione di una istanza di
        Articolo per impostarne lo stato iniziale.
        """
        self.nome = nome
        self.prezzo = prezzo
        if commenti is None:
            self.commenti = []
        else:
            self.commenti = commenti
        # ^^^ self.nome, .prezzo, .commenti sono attributi di istanza
        Articolo.articoli_totali += 1  # modifica dell'attributo di classe

    def valuta(self, utente, stelline):
        assert 1 <= stelline <= 5, "Stelline non valide"
        # ^^^ a <= x <= b è una sintassi ammessa in Python (in Java no; in C compila, ma non ha la semantica che ci si aspetta)
        self.commenti.append((utente, stelline))

    def valutazione_media(self):
        if len(self.commenti) == 0:
            return 0

        tot = 0
        for _, stelline in self.commenti: # _ si usa per convenzione per indicare che un valore (in questo caso l'utente) non ci interessa
            tot += stelline

        # oppure le tre righe qui sopra si possono semplificare con la seguente espressione
        # tot = sum(s for _, s in self.commenti)
        return tot / len(self.commenti)

    def sconta(self, percentuale):
        assert 0 <= percentuale <= 100, "Percentuale non valida"
        self.prezzo = self.prezzo - (self.prezzo * percentuale / 100)

    @staticmethod
    def prezzo_99_cent(prezzo):
        """
        Esempio di metodo statico. Nota che non c'è self come argomento.
        """
        nuovo_prezzo = math.floor(prezzo)
        nuovo_prezzo += 0.99
        return nuovo_prezzo

    def __str__(self):
        """
        Metodo chiamato da str(oggetto) e da print(oggetto).
        Solitamente si implementa restituendo una stringa con una 
        rappresentazione informale/leggibile dell'oggetto.
        """
        stelline_medie = self.valutazione_media()
        return f"{self.nome} - {self.prezzo}€ ({stelline_medie}/5)"

    # def __repr__(self):
    #     """
    #     Metodo chiamato da repr(oggetto), e dalla console REPL quando si
    #     scrive oggetto e si preme invio.
    #     Se possibile, l'implementazione deve restituire una stringa che,
    #     quando passata a eval(), ricostruisce l'oggetto.
    #     """
    #     return f"Articolo('{self.nome}', {self.prezzo}, {self.commenti})"

    def __eq__(self, altro):
        """Metodo chiamato dall'espressione oggetto == altro."""
        return self.nome == altro.nome and self.prezzo == altro.prezzo and self.commenti == altro.commenti

    # def __hash__(self):
    #     """
    #     Metodo chiamato da hash(oggetto). È necessario implementarlo,
    #     insieme a __eq__, se si vogliono inserire istanze di Articolo in
    #     collezioni basate su funzioni hash, come i dizionari e gli insiemi
    #     Python.
    #     L'implementazione deve garantire: a == b implica hash(a) == hash(b).
    #     """
    #     tupla_commenti = tuple(self.commenti) # trasformo la lista dei commenti in una tupla per poterla usare con hash()
    #     return hash((self.nome, self.prezzo, tupla_commenti))

    def __lt__(self, altro):
        """
        Metodo chiamato dall'espressione oggetto < altro. 
        Viene usato ad esempio da sorted(lista_di_oggetti_Articolo).
        """
        return self.nome < altro.nome

# --------------------------------------
# esempi creazione e modifica articoli
# --------------------------------------    
latte = Articolo("Latte 1LT", 1.20)
print(latte.prezzo)             # accedere a un attributo di istanza
latte.valuta("Mario", 5)        # chiamare un metodo di istanza
latte.valuta("Roberta", 2)
Articolo.prezzo_99_cent(6.55)   # chiamare un metodo statico
print(Articolo.articoli_totali) # accedere a un attributo di classe


# ---------------------
# ESEMPIO DI ALIASING 1
# ---------------------
latte2 = latte 
# latte e latte2 ora fanno riferimento allo stesso oggetto, ossia id(latte2) == id(latte)
latte2.prezzo = 1.50 
# ... quindi qui anche latte.prezzo == 1.50


# ---------------------
# ESEMPIO DI ALIASING 2
# ---------------------
def black_friday(articoli):
    for articolo in articoli:
        articolo.sconta(30)

cuffie = Articolo("Cuffie Bluetooth", 50)
pc = Articolo("PC portatile", 1200)
da_scontare = [cuffie, pc]
black_friday(da_scontare)
# ora cuffie e pc sono scontati del 30%


# ------------
# EREDITARIETÀ
# ------------
class Film(Articolo):
    def __init__(self, nome, prezzo, durata, commenti=None):
        super().__init__(nome, prezzo, commenti)
        self.durata = durata

    # Per esercitarsi: sovrascrivere __str__, __eq__, __hash__ per includere anche la durata


class Videogioco(Articolo):
    def __init__(self, nome, prezzo, piattaforma, commenti=None):
        super().__init__(nome, prezzo, commenti)
        self.piattaforma = piattaforma
        
    # Per esercitarsi: sovrascrivere __str__, __eq__, __hash__ per includere anche la piattaforma


cod = Videogioco("Call of Duty", 59.99, "PC")
avatar = Film("Avatar 2", 15.99, 120)
black_friday([cod, avatar])


# --------------------
# OPERATORI ARITMETICI
# --------------------

class Razionale:
    """
    Esempio di classe che definisce operatori artimetici.
    https://docs.python.org/3/reference/datamodel.html#emulating-numeric-types
    """

    def __init__(self, numeratore, denominatore):
        if denominatore==0:
            raise RuntimeError("Il denominator non può essere nullo")
        self.numeratore = numeratore
        self.denominatore = denominatore

    def __add__(self, altro):
        """Metodo chiamato dall'espressione oggetto + altro."""
        d = self.denominatore * altro.denominatore
        n = self.numeratore * altro.denominatore + altro.numeratore * self.denominatore
        return Razionale(n, d)

    def __mul__(self, altro):
        """Metodo chiamato dall'espressione oggetto * altro."""
        n = self.numeratore * altro.numeratore
        d = self.denominatore * altro.denominatore
        return Razionale(n, d)
    
    def __eq__(self, altro):
        return self.numeratore*altro.denominatore == altro.numeratore*self.denominatore

    def __str__(self):
        return f"{self.numeratore}/{self.denominatore}"
    
     # Per esercitarsi: implementare __sub__ e __lt__


r1 = Razionale(2, 3)
r2 = Razionale(1, 5)
print(r1 * r2)
