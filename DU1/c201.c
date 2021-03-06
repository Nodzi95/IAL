
/* c201.c *********************************************************************}
{* T�ma: Jednosm�rn� line�rn� seznam
**
**                     N�vrh a referen�n� implementace: Petr P�ikryl, ��jen 1994
**                                          �pravy: Andrea N�mcov� listopad 1996
**                                                   Petr P�ikryl, listopad 1997
**                                P�epracovan� zad�n�: Petr P�ikryl, b�ezen 1998
**                                  P�epis do jazyka C: Martin Tu�ek, ��jen 2004
**	                                      �pravy: Bohuslav K�ena, ��jen 2015
**
** Implementujte abstraktn� datov� typ jednosm�rn� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je cel� ��slo typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou typu tList.
** Definici konstant a typ� naleznete v hlavi�kov�m souboru c201.h.
** 
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu s v��e
** uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ tList:
**
**      InitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DisposeList ... zru�en� v�ech prvk� seznamu,
**      InsertFirst ... vlo�en� prvku na za��tek seznamu,
**      First ......... nastaven� aktivity na prvn� prvek,
**      CopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DeleteFirst ... zru�� prvn� prvek seznamu,
**      PostDelete .... ru�� prvek za aktivn�m prvkem,
**      PostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      Copy .......... vrac� hodnotu aktivn�ho prvku,
**      Actualize ..... p�ep��e obsah aktivn�ho prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal�� prvek seznamu,
**      Active ........ zji��uje aktivitu seznamu.
**
** P�i implementaci funkc� nevolejte ��dnou z funkc� implementovan�ch v r�mci
** tohoto p��kladu, nen�-li u dan� funkce explicitn� uvedeno n�co jin�ho.
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

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* glob�ln� prom�nn� -- p��znak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
	L->Act = NULL;          //inicializace ukazatele na aktu�ln� a prvn� bu�ku
    L->First = NULL;
}

void DisposeList (tList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam L do stavu, v jak�m se nach�zel
** po inicializaci. Ve�ker� pam� pou��van� prvky seznamu L bude korektn�
** uvoln�na vol�n�m operace free.
***/
    tElemPtr ptr1;          //vytvo�en� pomocn�ho ukazatele
    L->Act = NULL;          //nastaven� ukazatele na aktu�ln� bu�ku do stavu po inicializaci
    ptr1 = L->First;        //
    while(ptr1){            //dokud ukazatel na prvn� bu�ku nebude NULL, tak bude uvol�ovat bu�ky z pam�ti
        L->First = ptr1->ptr;   //ulo�en� ukazatele na n�sleduj�c� bu�ku
        free(ptr1);             //uvoln�n�
        ptr1 = L->First;
    }
}

void InsertFirst (tList *L, int val) {
/*
** Vlo�� prvek s hodnotou val na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci Error().
**/
    tElemPtr ptr1;  //vytvo�en� nov�ho ukazatele
    if((ptr1 =  malloc(sizeof(*L))) == NULL){    //naalokov�n� pam�ti o velikosti struktury bu�ky (tElemPtr)
        Error();
        return;
    }
    else{
        ptr1->data = val;       //ulo�� hodnotu val do nov� bu�ky
        ptr1->ptr = L->First;   //nov� vytvoren� bu�ka bude ukazovat tam, kam ukazoval ukazatel na za��tek
        L->First = ptr1;        //nov� vytvo�en� bu�ka bude prvn� bu�ka v seznamu
    }
}

void First (tList *L) {
/*
** Nastav� aktivitu seznamu L na jeho prvn� prvek.
** Funkci implementujte jako jedin� p��kaz, ani� byste testovali,
** zda je seznam L pr�zdn�.
**/
    L->Act = L->First;          //nastaven� aktivity na prvn� prvek
}

void CopyFirst (tList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci Error().
**/
    if(L->First != NULL) *val = L->First->data;     //ulo�� data z prvn� bu�ky do val
    else Error();
}

void DeleteFirst (tList *L) {
/*
** Zru�� prvn� prvek seznamu L a uvoln� j�m pou��vanou pam�.
** Pokud byl ru�en� prvek aktivn�, aktivita seznamu se ztr�c�.
** Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
    if(L->First != NULL){               //o�et�en� nepr�zdnosti seznamu
        tElemPtr ptr1;
        if(L->Act == L->First){         //pokud byl prvn� mazan� prvek aktivn�, tak se aktivita ztr�c�
            L->Act = NULL;
        }
        ptr1 = L->First;                //nastaven� ukazatel�
        L->First = L->First->ptr;
        free(ptr1);                     //uvoln�n� bu�ky z pam�ti
    }
}	

void PostDelete (tList *L) {
/* 
** Zru�� prvek seznamu L za aktivn�m prvkem a uvoln� j�m pou��vanou pam�.
** Pokud nen� seznam L aktivn� nebo pokud je aktivn� posledn� prvek seznamu L,
** nic se ned�je.
**/
    if((L->Act != NULL) && (L->Act->ptr != NULL)){  //o�et�en� neaktivn�ho seznamu a toho, �e je bu�ka za aktivn� bu�kou (je co mazat)
        tElemPtr ptr1;
        ptr1 = L->Act->ptr;                         //nastaven� ukazatel�
        L->Act->ptr = ptr1->ptr;
        free(ptr1);                                 //uvoln�n� bu�ky z pam�ti
    }
}

void PostInsert (tList *L, int val) {
/*
** Vlo�� prvek s hodnotou val za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je!
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** zavol� funkci Error().
**/
    if(L->Act != NULL){
        tElemPtr ptr1;
        ptr1 =  malloc(sizeof(*L));         //alokace pam�ti pro novou bu�ku
        if(ptr1 == NULL){
            Error();
            return;
        }
        else{
            ptr1->data = val;               //nastaven� ukazatel�
            ptr1->ptr = L->Act->ptr;
            L->Act->ptr = ptr1;
        }
    }
}

void Copy (tList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam nen� aktivn�, zavol� funkci Error().
**/
    if(L->Act != NULL) *val = L->Act->data; //do val ulo�� data z aktivn� bu�ky
    else Error();
}

void Actualize (tList *L, int val) {
/*
** P�ep��e data aktivn�ho prvku seznamu L hodnotou val.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/
    if(L->Act != NULL){
        L->Act->data = val;                 //p�ep��e data v aktivn� bu�ky
    }
}

void Succ (tList *L) {
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** V�imn�te si, �e touto operac� se m��e aktivn� seznam st�t neaktivn�m.
** Pokud nen� p�edan� seznam L aktivn�, ned�l� funkce nic.
**/
    if(L->Act != NULL){
        if(L->Act->ptr == NULL) L->Act = NULL;  //pokud byla aktivn� bu�ka z�rove� posledn�, tak seznam ztr�c� aktivitu
        else L->Act = L->Act->ptr;              //nastaven� aktivity na dal�� bu�ku
    }
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivn�, vrac� nenulovou hodnotu, jinak vrac� 0.
** Tuto funkci je vhodn� implementovat jedn�m p��kazem return. 
**/
    if(L->Act != NULL) return 1;                //pokud je seznam aktivn� vrac� 1
    else return 0;                              //jinak 0
}

/* Konec c201.c */
