#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "ligneBus.h"
#include "listeDouble.h"

Tbus creeBus( int idBus, TlisteStation start ){
    Tbus myBus = (Tbus)malloc(sizeof(Typebus));
    myBus->idBus = idBus;
    busSurStation( myBus, start, depart_vers_arrivee);
    busSurLigneX ( myBus, getIdLigneTroncon(getPtrData(getNextTroncon(start))));
    return myBus;
}


Tstation *creeArret( int posX, int posY, char* nomStation, int idStation){
    Tstation* newStation = (Tstation*)malloc(sizeof(Tstation));

    newStation->arret_ou_troncon = ARRET;

    //champs utiles si ARRET
    newStation->posX = posX;
    newStation->posY = posY;
    strcpy(newStation->nomStation, nomStation);
    newStation->idStation = idStation;

    //champs non utiles si ARRET
    newStation->depart = NULL;
    newStation->arrivee = NULL;
    newStation->coutTemps = 0;
    newStation->coutDistance = 0;
    newStation->idLigneBus= -1;  //id inexistant
    return newStation;
}

Tstation *creeTroncon(int idLigneBus, Tstation* depart, Tstation *arrivee, int coutTemps, int coutDistance){
    Tstation* newStation = (Tstation*)malloc(sizeof(Tstation));

    newStation->arret_ou_troncon = TRONCON;

    //champs non utiles si TRONCON
    newStation->posX = 0;
    newStation->posY = 0;
    strcpy(newStation->nomStation, "");
    newStation->idStation = -1;  //id inexistant

    //champs utiles si TRONCON
    newStation->idLigneBus=idLigneBus;
    newStation->depart = depart;
    newStation->arrivee = arrivee;
    newStation->coutTemps = coutTemps;
    newStation->coutDistance = coutDistance;
    return newStation;
}

TlisteStation creeLigneDeBus1(){
    TlisteStation newLigne;
    Tstation *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(10,10,"Charles de Gaulle",1);
    arr = creeArret(300,400,"Jules Ferry",2);
    troncon = creeTroncon(1,dep,arr,35,280);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(10,410,"Jacques Brel",3);
    troncon = creeTroncon(1,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(200,350,"Saint Exupery",4);
    troncon = creeTroncon(1,dep,arr,45,200);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(500,410,"Stalingrad",5);
    troncon = creeTroncon(1,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}


TlisteStation creeLigneDeBus2(){
    TlisteStation newLigne;
    Tstation *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(10,100,"Republique",6);
    arr = creeArret(30,300,"Jules Ferry",7);
    troncon = creeTroncon(2,dep,arr,35,280);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(100,40,"PLace d'armes",8);
    troncon = creeTroncon(2,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(300,30,"Place de l'etoile",9);
    troncon = creeTroncon(2,dep,arr,45,200);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(400,210,"Bobigny",10);
    troncon = creeTroncon(2,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}

TlisteStation creeLigneDeBus3(){
    TlisteStation newLigne;
    Tstation *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(150,10,"Clemenceau",11);
    arr = creeArret(300,100,"Montmartre",12);
    troncon = creeTroncon(3,dep,arr,35,280);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(600,610,"Tour eiffel",13);
    troncon = creeTroncon(3,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(70,350,"Les invalides",14);
    troncon = creeTroncon(3,dep,arr,45,200);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(150,510,"Gare du nord",15);
    troncon = creeTroncon(3,arr,dep,40,160);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}


void afficheConsoleLigneBus( TlisteStation l){
    afficheListe(l);
}

TlisteStation getNextStation( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getNextCell(l) )) return NULL;  //nous sommes sur un terminus
                    else return getNextCell( getNextCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante étant un TRONCON
            }
            else return getNextCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

TlisteStation getNextTroncon( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                return getNextCell(l);  //la prochaine cellule est un TRONCON, peut être égale à NULL si on est sur un terminus
            }
            else{
                    printf("\n(getNextTroncon) erreur algo, on est deja sur un troncon");
                    return l;  //on retourne le troncon actuel
            }
    }
}

TlisteStation getPreviousStation( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getPrevCell(l) )) return NULL;  //nous sommes sur un terminus
                    return getPrevCell( getPrevCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante étant un TRONCON
            }
            else return getPrevCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

bool ligneBusVide( TlisteStation l){
    return listeVide( l );
}

int getPosXListeStation( TlisteStation myStationInListe ){
    return getPosXStation(getPtrData(myStationInListe));
}

int getPosYListeStation( TlisteStation myStationInListe ){
    return getPosYStation(getPtrData(myStationInListe));
}

void deplaceBus(Tbus myBus, TsensParcours sens_deplacement, int *incXSprite, int *incYSprite){
    TlisteStation dest;
    int xdep, ydep, xarr, yarr, pas;
    float ratio;
    pas = 2;  //équivalent au parametre d'erreur dans le tracé de Segment de Bresenham
    //https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham


    if (sens_deplacement == depart_vers_arrivee) dest = getNextStation(getActualStation(myBus));
        else dest = getPreviousStation(getActualStation(myBus));

    //par défaut: pas de déplacement du bus
    *incXSprite = 0; *incYSprite = 0;

    //si un prochain arret existe?
    if (ligneBusVide(dest)){
        //printf("\nBus id%d est au terminus de la ligne %d sur la station id=%d %s", getIdBus(myBus), getIdLigneActuelleDuBus(myBus),getIdStation(getPtrData(getActualStation(myBus))),getNomStation(getPtrData(getActualStation(myBus))));
    }
    else //s'il existe:
    {
        //soit on est arrivé, soit on est en cours de trajet
        //récupération des coordonnées
        xdep = getPosXBus(myBus);
        ydep = getPosYBus(myBus);
        xarr = getPosXListeStation(dest);
        yarr = getPosYListeStation(dest);

        //sommes-nous arrivés?
        if ((abs(xdep-xarr)<=pas) && (abs(ydep-yarr)<=pas)){
            //alors mise à jour de la station actuelle du bus
            setActualStation( myBus, dest );
            printf("\nLe Bus id%d arrive sur la station id%d %s",getIdBus(myBus),getIdStation(getPtrData(getActualStation(myBus))),getNomStation(getPtrData(getActualStation(myBus))));
        }
        else{
            //sinon on calcule les offsets de déplacements pour la boucle main qui réalise les affichages
            ratio = (float)(abs(yarr-ydep))/(float)(abs(xarr-xdep)); //div euclydienne

            //algo de Bresenham "simplifié de façon ad hoc" et non optimisé (à cause des floats)
            if (xarr>xdep) *incXSprite = pas;
            else if (xarr<xdep) *incXSprite = -pas;

            if (yarr>ydep) *incYSprite = (int)((float)(pas) * ratio);             //pour un déplacement proportionnel en Y selon Y/X
            else if (yarr<ydep) *incYSprite = (int)((float)(-pas) * ratio);

            //remmarque: si xarr==ydep alors *incXSprite reste à 0, idem en Y

            //maj des coord du bus
            setPosXBus(myBus, getPosXBus(myBus) + *incXSprite);
            setPosYBus(myBus, getPosYBus(myBus) + *incYSprite);
        }
    }
}

//Setteurs
void setActualStation( Tbus myBus, TlisteStation arrivalStation );
void setPosXBus(Tbus myBus, int newX);
void setPosYBus(Tbus myBus, int newY);
void setIdLigneBus(Tbus myBus, int idLigne);
void setSensParcours(Tbus myBus, TsensParcours sens );

void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation);


void busSurStation( Tbus myBus, TlisteStation myStation, TsensParcours sens){

    //Exemple encapsulation: on a préféré les fonctions setteurs à un accés direct aux champs

    setPositionSurLaLigneDeBus( myBus, myStation);
    //myBus->positionSurLaLigneDeBus = myStation;  //interdit

    setSensParcours( myBus, sens);
    //myBus->sensParcours = sens;

    setPosXBus( myBus, getPosXListeStation( myStation ) );
    //myBus->posXBus = getPosXListeStation( myStation );

    setPosYBus( myBus, getPosYListeStation( myStation ) );
    //myBus->posYBus = getPosYListeStation( myStation );

    //idem : on passe ci-dessous par les getteurs et non par un accés direct via les champs
    printf("\nBus id%d est en (x = %d, y = %d) sur la ligne %d, station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(myStation)));
}

void busSurLigneX( Tbus myBus, int idLigneX ){
    setIdLigneBus(myBus, idLigneX);
}

TlisteStation stationSuivantePourLeBus(Tbus myBus){
    TlisteStation prochaineStation;
    if (getSensParcours(myBus)==depart_vers_arrivee) prochaineStation = getNextStation(getActualStation(myBus));
    else prochaineStation = getPreviousStation(getActualStation(myBus));
    return prochaineStation;
}

void afficheCoordonneesBus( Tbus myBus ){
    char *nomProchaineStation;
    TlisteStation prochaineStation = stationSuivantePourLeBus(myBus);

    if (ligneBusVide(prochaineStation)) printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s (Terminus)", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getActualStation(myBus))));
    else {
            nomProchaineStation = getNomStation(getPtrData(prochaineStation));
            printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s, prochaine station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getActualStation(myBus))), nomProchaineStation);
    }
}


//Créer ci-dessous vos fonctions
