	
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                            �pravy: Bohuslav K�ena, ��jen 2015
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu, 
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek, 
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku, 
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu, 
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem, 
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu, 
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funkc� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
    L->Act = NULL;                  //nastaven� ukazatel� na hodnotu NULL
    L->First = NULL;
    L->Last = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free. 
**/
    tDLElemPtr ptr1;
    L->Act = NULL;
    ptr1 = L->First;
    while(ptr1){                    //dokud nen� ukazatel na prvn� bu�ku seznamu roven NULL, tak uvol�uje bu�ky v pam�ti
        L->First = ptr1->rptr;
        free(ptr1);
        ptr1 = L->First;
    }
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	tDLElemPtr ptr1;
	if((ptr1 = malloc(sizeof(*L))) == NULL){    //alokace m�sta pro novou bu�ku
        DLError();
        return;
	}
    ptr1->data = val;                           //hodnotu val ulo�� do nov� bu�ky
    ptr1->lptr = NULL;                          //lev� ukazatel nov� bu�ky bude ukazovat na nic(NULL)
    ptr1->rptr = L->First;                      //prav� ukazatel nov� bu�ky bude ukazovat tam, kam ukazoval ukazatel na prvn� bu�ku
    if(L->First != NULL){
        L->First->lptr = ptr1;                  //pokud nebyl seznam pr�zdn�, nastav� lev� ukazatel prvn� bu�ky na novou bu�ku
    }
    else{
        L->Last = ptr1;                         //jinak nastav� ukazatel na posledn� bu�ku na nov� vytvo�enou bu�ku
    }
    L->First = ptr1;                            //nastav� ukazatel na prvn� bu�ku v seznamu na novou bu�ku
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/ 	
    tDLElemPtr ptr1;
	if((ptr1 = malloc(sizeof(*L))) == NULL){    //alokace pam�ti pro novou bu�ku
        DLError();
        return;
	}
	ptr1->data = val;                           //nastaven� uakzatel�
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
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
    L->Act = L->First;                          //nastav� aktivitu seznamu na prvn� bu�ku
}

void DLLast (tDLList *L) {
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
    L->Act = L->Last;                           //nastav� aktivitu seznamu na posledn� bu�ku
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
    if(L->First != NULL){
        *val = L->First->data;                  //ulo�� data z prvn� bu�ky v seznamu do val
    }
    else DLError();
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
    if(L->First != NULL){
        *val = L->Last->data;                   //ulo�� data z posledn� bu�ky v seznamu do val
    }
    else DLError();
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita 
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
    if(L->First != NULL){                       //o�et�en� pr�zdn�ho seznamu
        tDLElemPtr ptr1;
        if(L->Act == L->First){                 //pokud byla mazan� bu�ka aktivn�, tak seznam ztr�c� aktivitu
            L->Act = NULL;
        }
        if(L->First == L->Last){                //pokud to je posledn� bu�ka v seznamu, vznikne pr�zdn� seznam
            L->First = NULL;
            L->Last = NULL;
        }
        else{
            ptr1 = L->First;                    //do pomocn�ho ukazatele vlo��m ukazatel na prvn� bu�ku
            ptr1->rptr->lptr = NULL;            //lev� ukazatel, co ukazuje na mazanou bu�ku nastav�m na NULL
            L->First = ptr1->rptr;              //ukazatel na prvn� bu�ku v seznamu bude ten, co byl napravo od mazan� bu�ky
        }
        free(ptr1);                             //uvoln�m bu�ku z pam�ti
    }
}	

void DLDeleteLast (tDLList *L) {
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/ 
    if(L->First != NULL){                       //symetrick� funkce k DLDeleteFirst
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
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
**/
    if(L->Act != NULL){
        if(L->Act != L->Last){
            tDLElemPtr ptr1;
            ptr1 = L->Act->rptr;                        //nastaven� ukazatel�
            L->Act->rptr = ptr1->rptr;
            if(ptr1->rptr == NULL) L->Last = L->Act;
            else ptr1->rptr->lptr = L->Act;
            free(ptr1);
        }
    }
}

void DLPreDelete (tDLList *L) {
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
**/
    if(L->Act != NULL){
        if(L->Act != L->First){
            tDLElemPtr ptr1;
            ptr1 = L->Act->lptr;                        //nastaven� ukazatel�
            L->Act->lptr = ptr1->lptr;
            if(L->First == ptr1) L->First = L->Act;
            else ptr1->lptr->rptr = ptr1->rptr;
            free(ptr1);
        }
    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
    if(L->Act != NULL){
        tDLElemPtr ptr1;
        if((ptr1 = malloc(sizeof(*L))) == NULL){
            DLError();
            return;
        }
        ptr1->data = val;
        ptr1->lptr = L->Act;                        //nastaven� ukazatel�
        ptr1->rptr = L->Act->rptr;
        L->Act->rptr = ptr1;
        if(L->Act == L->Last) L->Last = ptr1;
        else ptr1->rptr->lptr = ptr1;
    }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
    if(L->Act != NULL){
        tDLElemPtr ptr1;
        if((ptr1 = malloc(sizeof(*L))) == NULL){
            DLError();
            return;
        }
        ptr1->data = val;
        ptr1->rptr = L->Act;                            //nastaven� ukazatel�
        ptr1->lptr = L->Act->lptr;
        L->Act->lptr = ptr1;
        if(L->Act == L->First) L->First = ptr1;
        else ptr1->lptr->rptr = ptr1;
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
    if(L->Act != NULL){
        *val = L->Act->data;                            //do val ulo�� data z aktivn� bu�ky
    }
    else DLError();
}

void DLActualize (tDLList *L, int val) {
/*
** P�ep�e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
    if(L->Act != NULL){
        L->Act->data = val;                             //p�ep�e data v aktivn� bu�ce
    }
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/
    if(L->Act != NULL){
        if(L->Act != L->Last){                          //pokud je aktivita na posledn� bu�ce, seznam ztr�c� aktivitu
            L->Act = L->Act->rptr;                      //p�esune aktivitu na bu�ku vpravo
        }
        else L->Act = NULL;
    }
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/
    if(L->Act != NULL){
        if(L->Act != L->First){                         //pokud je aktivita na prvn� bu�ce, seznam ztr�c� aktivitu
            L->Act = L->Act->lptr;                      //p�esune aktivitu na bu�ku vlevo
        }
        else L->Act = NULL;
    }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivn�, vrac� nenulovou hodnotu, jinak vrac� 0.
** Funkci je vhodn� implementovat jedn�m p��kazem return.
**/
    if(L->Act != NULL) return 1;                        //pokud je seznam aktivn�, funkce vrac� 1
    else return 0;
}

/* Konec c206.c*/
