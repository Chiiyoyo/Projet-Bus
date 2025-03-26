#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>
#include "types.h"

/*  défini dans types.h
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tstation *pdata;              //attention à faire un malloc sur ce champ avant de s'en servir
} T_cellule;
typedef T_cellule* T_liste;
*/

void initListe(T_liste *l);
bool listeVide( T_liste l);

void afficheListe( T_liste l);

//Pour "AfficheListeV1" Vous avez le droit de lire directement dans la structure de données
//Utile pour afficher et debuguer les fonctions ci-dessous

T_liste ajoutEnTete(T_liste l, Tstation* mydata);
T_liste ajoutEnFin(T_liste l, Tstation* mydata);

Tstation* getPtrData(T_liste l);
T_liste getNextCell(T_liste l);
T_liste getPrevCell(T_liste l);
/* fin de tag ligne 50
T_liste ajoutEnN(T_liste l, int pos, Tstation* mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);

T_liste getptrFirstCell(T_liste l);
T_liste getptrLastCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);

void swapPtrData( T_liste source, T_liste destination );

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l); //utilisation de sizeof

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2); //on souhaite CREER une nouvelle liste sans modifier l1 et l2
T_liste addBehind(T_liste debut, T_liste suite);

T_liste findCell(T_liste l, Tstation* data);
int getOccurences(T_liste l, Tstation* data);  //nbre de fois que data est présent dans toute la liste l1

void afficheListeV2( T_liste l);
//Pour "AfficheListeV2", vous devez utiliser uniquement les fonctions écrites ci-dessus (interdiction de passer directement par les champs ptr de la SD)

début de tag ligne 16 */

#endif // LISTEDOUBLE_H_INCLUDED

