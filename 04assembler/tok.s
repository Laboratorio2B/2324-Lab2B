@; funzione analoga alla strtok() tranne che ammette un singolo
@; delimitatore invece che una stringa di possibili delimitatori 

@; prototipo formato C:
@;   char *miatok(char *s, int delim);

@; input:  r0 = s, r1 = delimitatore
@; output: r0 = pubtatore inzio next token o NULL se non ce ne sono
@; salvo in statica dove dove riprendere la tokenizzazione
@; l'intero 0 indica il valore NULL del C  

@; corrispondenza fra le variabili del miatok() in C
@; e i registri:
@;   r0 -> s     indirizzo stringa in output (viene modificato)
@;   r1 -> d     delimitatore 
@;   r2 -> &ultimapos    indirizzo variabile per riprendere tokenizzazione 
@;   r3 -> t     puntatore ausialirio, per trovare la fine del token


    .data
statica:    
    .word 0     @; area di memoria dove viene salvato da
                @; dove riprendere la tokenizzazione
                @; oppure NULL se è il parsing è completato
                @; inizialmente è NULL perché non c'è un parsing in sospeso
    
    .text
    .global miatok
    .type miatok, %function
    
miatok: 
    cmp r1,#0           @; il delimitatore deve essere !=0
    moveq r0, #10
    beq exit            @; if(r1=='\0') exit(10)

    @; metto in r2 l'indirizzo di statica
    @; e non lo modifico mai
    ldr   r2,=statica   @; r2 = &statica

    @; if r0==NULL carico l'ultima posizione
    cmp r0,#0
    ldreq r0,[r2]       @; metto in r0 l'indirizzo memorizzato in statica
                        @; (cioè recupero dove ero arrivato alla fine
                        @; del token precedente) in C sarebbe r0 = *r2
    cmp r0,#0           @; se in statica c'era NULL nessun parsing in sospeso
    moveq pc,lr         @; return NULL
                
    @; esegue il parsing da r0 in poi
saltadelimitatore:    
    ldrb r12,[r0]       @; legge carattere dalla posizione r0, in C r12 = *((char *) r0)
    cmp r12,r1          @; salta caratteri fino a che non si incontra
    addeq r0,r0,#1      @; un carattere diverso da r1 (il delimitatore)
    beq saltadelimitatore
    
    @; ho trovato qualcosa != delimitatore
    cmp r12,#0          @; fine stringa?
    moveq r0,#0
    streq r0,[r2]       @; metto NULL in statica, in C sarebbe *r2 = NULL
    moveq pc,lr         @; return NULL
    
    @; trovato carattere diverso da fine stringa
    @; possiamo restituire un nuovo token
    @; in r0 ho l'indirizzo del primo carattere del token 
    @; quindi non lo modifico 
    mov r3,r0           @; uso r3 per avanzare nel token
avanti: 
    ldrb r12, [r3,#1]!  @; r12 = *(++r3) (legge il prossimo carattere)
    cmp r12,#0          @; fine stringa?
    moveq r3,#0         @; scrivo NULL in statica 
    streq r3,[r2]       @; perché non ci sono altri token
    moveq pc,lr         @; return r0 = inizio del token     
    cmp r12,r1          @; se r12!=delimitatore
    bne avanti          @; considero carattere successivo
    @; trovato delimitatore in [r3], il token è finito
    mov r1,#0           @; r1 non mi serve più e lo sovrascrivo 
    strb r1,[r3]        @; scrivo '\0' sopra il delimitatore
    add r3,r3,#1        @; r3++ puntatore a carattere dopo delimitatore
    str r3, [r2]        @; salvo puntatore r3 in statica
    mov pc,lr           @; return r0 (indirizzo del primo carattere del token)
