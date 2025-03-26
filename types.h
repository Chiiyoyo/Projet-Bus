#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef enum type_noeud {ARRET, TRONCON} TypeNoeud;

typedef struct T_station { //représente UN TRONCON (entre deux arrêts) ou UN ARRET (cad une station de la ligne de bus)

    TypeNoeud arret_ou_troncon;

    //données utiles si le Noeud est un TRONCON
    int idLigneBus;                    //numéro de la ligne de bus par laquelle on arrive sur la station
    struct T_station* depart;          // pointeurs sur les stations de départ et d'arrivée du tronçon
    struct T_station* arrivee;
    int coutTemps;                     // coût en temps de parcours (en secondes)
    int coutDistance;                  // coût en distance (en mètres)
    int tempsCumule, distanceCumule;   // champs utiles pour déterminer le meilleur itinéraire

    //données utiles si le Noeud est un ARRET
    int posX, posY;                    //coordonnées sur le plan de la ville
    char nomStation[30];
    int idStation;                     //numéro unique et non liée à une ligne, une ligne de bus étant constituée d'une suite de d'id stations: exemple : 3  - 7 - 1 - 5

    //champs utiles pour les tris
    //int coutMaintenance;                //en Kilo euro, une valeur entre 10 et 100  (A VOUS DE GERER)
    //t_date dateDerniereMaintenance      //t_date est à définir, doit permettre de stocker une date jour/mois/année, y mettre une date aléatoire (A VOUS DE GERER)

    //struct T_station* correspondances; //égale à NULL si pas de correspondance, sinon égale à une liste de TRONCONS
    //int coutCumule;                    //pour le calcul du plus court chemin, algo de Djikstra

} Tstation;


//type pour la liste doublement chainée, utilisé daans listeDouble.h/.c
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tstation *pdata;              //attention à faire un malloc sur ce champ avant de s'en servir
} T_cellule;
typedef T_cellule* T_liste;


//Une liste de stations  (basée sur listeDouble.h/.c)
typedef T_liste TlisteStation;  //T_liste et TlisteStation sont équivalents, cad pointeur sur Tcellule

//une ligne de bus
typedef struct{
    int idLigneBus;  //donnée qui sera dupliquée dans chaque troncon de la ligne (pour aider au debugage et pour aider à la gestion des correspondances)
    char *nomLigne;
    TlisteStation depart;   //peut etre parcouru dans les deux sens
    TlisteStation arrivee;
} TligneBus;

typedef enum{ depart_vers_arrivee, arrivee_vers_depart} TsensParcours;

typedef struct{
    int idBus;
    TlisteStation positionSurLaLigneDeBus;  //la derniere station atteinte (dans la liste) du bus est dans le champ pdata, stocké dans un Tcellule
    int posXBus, posYBus;                   //coord du bus pixel par pixel pour les trajets
    int idLigneBusActuelle;                 //un bus suit une ligne de bus à un instant t et peut en changer
    TsensParcours sensParcours;
} Typebus;

typedef Typebus *Tbus;

//affichage
void afficheStation( Tstation *station );

//Getteurs
int getIdStation( Tstation *myStation );
char *getNomStation( Tstation *myStation);
int getPosXStation( Tstation *myStation );
int getPosYStation( Tstation *myStation );
int getIdLigneTroncon(Tstation *myStation);
TypeNoeud getTypeNoeud(Tstation *myStation);

int getPosXBus( Tbus myBus );
int getPosYBus( Tbus myBus );
int getIdBus( Tbus myBus );
int getIdLigneActuelleDuBus( Tbus myBus );
TsensParcours getSensParcours(Tbus myBus);
TlisteStation getActualStation( Tbus myBus );
int getIdLigneBus(Tbus myBus);

//Setteurs
void setActualStation( Tbus myBus, TlisteStation arrivalStation );
void setPosXBus(Tbus myBus, int newX);
void setPosYBus(Tbus myBus, int newY);
void setIdLigneBus(Tbus myBus, int idLigne);
void setSensParcours(Tbus myBus, TsensParcours sens );
void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation);

#endif // TYPES_H_INCLUDED
