	
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Bohuslav Køena, øíjen 2015
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** U¾iteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slou¾í pro odli¹ení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Va¹ím úkolem je implementovat následující operace, které spolu
** s vý¹e uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DLDisposeList ... zru¹ení v¹ech prvkù seznamu,
**      DLInsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      DLInsertLast .... vlo¾ení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zru¹í první prvek seznamu,
**      DLDeleteLast .... zru¹í poslední prvek seznamu, 
**      DLPostDelete .... ru¹í prvek za aktivním prvkem,
**      DLPreDelete ..... ru¹í prvek pøed aktivním prvkem, 
**      DLPostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlo¾í nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal¹í prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu, 
**      DLActive ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funkcí nevolejte ¾ádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam 
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak o¹etøení chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    L->Act = NULL;                  //nastavení ukazatelù na hodnotu NULL
    L->First = NULL;
    L->Last = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru¹ené prvky seznamu budou korektnì
** uvolnìny voláním operace free. 
**/
    tDLElemPtr ptr1;
    L->Act = NULL;
    ptr1 = L->First;
    while(ptr1){                    //dokud není ukazatel na první buòku seznamu roven NULL, tak uvolòuje buòky v pamìti
        L->First = ptr1->rptr;
        free(ptr1);
        ptr1 = L->First;
    }
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo¾í nový prvek na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
	tDLElemPtr ptr1;
	if((ptr1 = malloc(sizeof(*L))) == NULL){    //alokace místa pro novou buòku
        DLError();
        return;
	}
    ptr1->data = val;                           //hodnotu val ulo¾í do nové buòky
    ptr1->lptr = NULL;                          //levý ukazatel nové buòky bude ukazovat na nic(NULL)
    ptr1->rptr = L->First;                      //pravý ukazatel nové buòky bude ukazovat tam, kam ukazoval ukazatel na první buòku
    if(L->First != NULL){
        L->First->lptr = ptr1;                  //pokud nebyl seznam prázdný, nastavý levý ukazatel první buòky na novou buòku
    }
    else{
        L->Last = ptr1;                         //jinak nastaví ukazatel na poslední buòku na novì vytvoøenou buòku
    }
    L->First = ptr1;                            //nastaví ukazatel na první buòku v seznamu na novou buòku
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo¾í nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/ 	
    tDLElemPtr ptr1;
	if((ptr1 = malloc(sizeof(*L))) == NULL){    //alokace pamìti pro novou buòku
        DLError();
        return;
	}
	ptr1->data = val;                           //nastavení uakzatelù
	ptr1->lptr = L->Last;
	ptr1->rptr = NULL;
	if(L->Last != NULL){
        L->Last->rptr = ptr1;
	}
	else{
        L->First = ptr1;
	}
	L->Last = ptr1;
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
    L->Act = L->First;                          //nastaví aktivitu seznamu na první buòku
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
    L->Act = L->Last;                           //nastaví aktivitu seznamu na poslední buòku
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->First != NULL){
        *val = L->First->data;                  //ulo¾í data z první buòky v seznamu do val
    }
    else DLError();
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->First != NULL){
        *val = L->Last->data;                   //ulo¾í data z poslední buòky v seznamu do val
    }
    else DLError();
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru¹í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/
    if(L->First != NULL){                       //o¹etøení prázdného seznamu
        tDLElemPtr ptr1;
        if(L->Act == L->First){                 //pokud byla mazaní buòka aktivní, tak seznam ztrácí aktivitu
            L->Act = NULL;
        }
        if(L->First == L->Last){                //pokud to je poslední buòka v seznamu, vznikne prázdný seznam
            L->First = NULL;
            L->Last = NULL;
        }
        else{
            ptr1 = L->First;                    //do pomocného ukazatele vlo¾ím ukazatel na první buòku
            ptr1->rptr->lptr = NULL;            //levý ukazatel, co ukazuje na mazanou buòku nastavím na NULL
            L->First = ptr1->rptr;              //ukazatel na první buòku v seznamu bude ten, co byl napravo od mazané buòky
        }
        free(ptr1);                             //uvolním buòku z pamìti
    }
}	

void DLDeleteLast (tDLList *L) {
/*
** Zru¹í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/ 
    if(L->First != NULL){                       //symetrická funkce k DLDeleteFirst
        tDLElemPtr ptr1;
        if(L->Act == L->Last){
            L->Act = NULL;
        }
        if(L->Last == L->First){
            L->Last = NULL;
            L->First = NULL;
        }
        else{
            ptr1 = L->Last;
            ptr1->lptr->rptr = NULL;
            L->Last = ptr1->lptr;
        }
        free(ptr1);
    }
}

void DLPostDelete (tDLList *L) {
/*
** Zru¹í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/
    if(L->Act != NULL){
        if(L->Act != L->Last){
            tDLElemPtr ptr1;
            ptr1 = L->Act->rptr;                        //nastavení ukazatelù
            L->Act->rptr = ptr1->rptr;
            if(ptr1->rptr == NULL) L->Last = L->Act;
            else ptr1->rptr->lptr = L->Act;
            free(ptr1);
        }
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zru¹í prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/
    if(L->Act != NULL){
        if(L->Act != L->First){
            tDLElemPtr ptr1;
            ptr1 = L->Act->lptr;                        //nastavení ukazatelù
            L->Act->lptr = ptr1->lptr;
            if(L->First == ptr1) L->First = L->Act;
            else ptr1->lptr->rptr = ptr1->rptr;
            free(ptr1);
        }
    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if(L->Act != NULL){
        tDLElemPtr ptr1;
        if((ptr1 = malloc(sizeof(*L))) == NULL){
            DLError();
            return;
        }
        ptr1->data = val;
        ptr1->lptr = L->Act;                        //nastavení ukazatelù
        ptr1->rptr = L->Act->rptr;
        L->Act->rptr = ptr1;
        if(L->Act == L->Last) L->Last = ptr1;
        else ptr1->rptr->lptr = ptr1;
    }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if(L->Act != NULL){
        tDLElemPtr ptr1;
        if((ptr1 = malloc(sizeof(*L))) == NULL){
            DLError();
            return;
        }
        ptr1->data = val;
        ptr1->rptr = L->Act;                            //nastavení ukazatelù
        ptr1->lptr = L->Act->lptr;
        L->Act->lptr = ptr1;
        if(L->Act == L->First) L->First = ptr1;
        else ptr1->lptr->rptr = ptr1;
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
    if(L->Act != NULL){
        *val = L->Act->data;                            //do val ulo¾í data z aktivní buòky
    }
    else DLError();
}

void DLActualize (tDLList *L, int val) {
/*
** Pøepí¹e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
    if(L->Act != NULL){
        L->Act->data = val;                             //pøepí¹e data v aktivní buòce
    }
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/
    if(L->Act != NULL){
        if(L->Act != L->Last){                          //pokud je aktivita na poslední buòce, seznam ztrácí aktivitu
            L->Act = L->Act->rptr;                      //pøesune aktivitu na buòku vpravo
        }
        else L->Act = NULL;
    }
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/
    if(L->Act != NULL){
        if(L->Act != L->First){                         //pokud je aktivita na první buòce, seznam ztrácí aktivitu
            L->Act = L->Act->lptr;                      //pøesune aktivitu na buòku vlevo
        }
        else L->Act = NULL;
    }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním pøíkazem return.
**/
    if(L->Act != NULL) return 1;                        //pokud je seznam aktivní, funkce vrací 1
    else return 0;
}

/* Konec c206.c*/
