#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){
*l=NULL;
}


bool listeVide( T_liste l){
    return (l==NULL);
}

void afficheListe( T_liste l){
    T_liste courant = l;
    while (courant!=NULL){
        afficheStation(courant->pdata);  //fourni par types.h
        courant=courant->suiv;
    }
}

T_liste ajoutEnTete(T_liste l, Tstation* mydata){
    T_liste nouv = (T_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport à la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation mémoire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //sécurise la présence de NULL sur le champ suiv, au cas où le ptr l n'aurait pas été  initialisé correctement via initListe
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = l;
        nouv->prec = NULL;
        l->prec = nouv;
    }
    return nouv;
}

T_liste ajoutEnFin(T_liste l, Tstation* mydata){
    T_liste nouv, courant=l;  //remarque: pas de malloc si on appelle ajoutEnTete

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        return ajoutEnTete(l, mydata);
    }
    else  // la liste n'etant pas vide,déplacment sur la derniere cellule, malloc et branchements
    {
        while (courant->suiv != NULL){
            courant=courant->suiv;
        }
        nouv = (T_liste)malloc(sizeof(struct T_cell));
        nouv->pdata=mydata;

        nouv->suiv = NULL;
        nouv->prec = courant;
        courant->suiv = nouv;
    }
    return l;  //la tête d'origine, qui n'a pas changé
}

Tstation* getPtrData(T_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non alloué");
        return NULL;
    }
    else
    {
        return l->pdata;
    }
}

T_liste getNextCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->suiv;
    }
}

T_liste getPrevCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->prec;
    }
}

//A vous la suite si besoin
