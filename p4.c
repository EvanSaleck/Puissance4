/**
 * \page Programme permettant de jouer au puissance 4 en mode console 
 *                                                                     
 * \author SALECK Evan
 * 
 * \version 1.0.0                                                 
 *                                                                     
 * \date 19 novembre 2022                                              
 *                                                                     
 * \brief Programme de puissance 4 en mode console                    
 *                                                                     
 *                                                                     
*/

/*********************************
 **  Inclusion des bibliothèques *
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/********************************************
 **  Définition des constantes du programme *
*********************************************/
/**Déclaration du caractère du premier pion */ const char PION_A ='X'; 

/**Déclaration du caractère du second pion */ const char PION_B ='O'; 

/**Déclaration du caractère inconnu si il y'a match nul */ const char INCONNU =' '; 

/**Déclaration d'un caractère vide pour remplir le tableau au début de chaques parties */ const char VIDE =' '; 

 /**Déclaration d'un entier qui permet de faire -3 afin de permettre le fonctionnement de EstVainqueur'*/ const int P4 = 3; 

/***************************************************
 ** Définition des constantes de taille du tableau *
***************************************************/
/**
 * \def NBLIG
 * 
 * \brief Définition du nombre de lignes du tableau
 * 
*/
#define NBLIG  6

/**
 * \def NBCOL
 * 
 * \brief Définition du nombre de colonnes du tableau
 * 
*/
#define NBCOL  7

/**Déclaration de la constante permettant de faire commencer notre pion au milieu*/ const int COLONNE_DEBUT =NBCOL/2; 
/*****************************************************
 ** Déclaration d'un nouveau type pour notre tableau *
*****************************************************/

/**
 * \typedef t_tableau
 * 
 * \brief Déclaration du nouveau type pour notre tableau
*/
typedef char t_tableau[NBLIG][NBCOL];

/*********************************
 ** Prédéclaration des fonctions *
*********************************/

/** Procédure qui initialise la grille */ void initGrille(t_tableau*);
/**  Procédure qui affiche la grille*/ void afficher(t_tableau, char, int );
/** Fonction booléene qui renvoie vrai si grille pleine ou faux sinon*/ bool grillePleine(t_tableau);
/**  Procédure qui donne au joueur la possibilité de jouer */ void jouer(t_tableau*, char , int *, int *);
/** Permet de choisir une colonne*/ int choisirColonne(t_tableau,char , int );
/** Trouver la ligne correspondant à la colonne choisie*/ int trouverLigne(t_tableau,int );
/** Renvoie vrai si 4 pions alligné à partir d'un point ou faux sinon*/ bool estVainqueur(t_tableau,int , int );
/** Affiche le gagnant de la partie ou si il y a match nul*/ void finDePartie(char );

   


/*********************************
 **         PROGRAMME PRINCIPAL  *
*********************************/

/**
 * \fn int main
 * \brief Appelle toutes les fonctions du programme dans l'ordre requis et affiche le vainqueur
 * \return Code de sortie du programme : sortie normale
*/

int main()
{
    char vainqueur; 
    int ligne, colonne;
    t_tableau grille;
    initGrille(&grille);
    vainqueur = INCONNU;
    afficher(grille, PION_A, COLONNE_DEBUT);  
   
    while  ((vainqueur == INCONNU) &&  !(grillePleine(grille))){
        jouer(&grille,PION_A,&ligne, &colonne);
        afficher(grille,PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille,ligne,colonne)){
            vainqueur= PION_A;

        }else if (!grillePleine(grille))
            {
                jouer(&grille,PION_B,&ligne, &colonne);
                afficher(grille, PION_A,COLONNE_DEBUT);
                if(estVainqueur(grille,ligne,colonne)){
                    vainqueur = PION_B;
                }
            }
    }
    finDePartie(vainqueur);
    return EXIT_SUCCESS;
}

/*****************************************
 *          Déclaration des fonctions    *
*****************************************/

/** 
 * \fn initGrille
 * \brief Initialise la grille à vide
 * \param t_tableau grille : tableau à initialiser
 * 
 * Initialise la grille à vide, rajoute a chaque case le caractère VIDE
*/

void initGrille(t_tableau *grille){
    for (int i =0; i< NBLIG;i++){
        for(int y =0; y <NBCOL; y++){
            *grille[i][y]= VIDE;
        }
    }
}

/** 
 * \fn afficher
 * 
 * \brief Affiche la grille avec les pions joués par les joueurs
 * 
 * \param t_tableau grille : tableau à afficher
 * 
 * \param char pion : pion du joueur 
 * 
 * \param int colonne : colonne de départ
 * 
 * Affiche la grille et les pions joués ainsi que le pion au dessus de la colonne de départ
*/


void afficher(t_tableau grille, char pion, int colonne){
   
    system("cls");
    char tab[NBCOL];
    for (int i =0; i < 7; i++){
        tab[i] = ' ';
    }
    tab[colonne]=pion;
    printf("| 0 | 1 | 2 | 3 | 4 | 5 | 6 | \n");
    printf("| %c | %c | %c | %c | %c | %c | %c |", tab[0],tab[1], tab[2],tab[3], tab[4],tab[5], tab[6]);
    printf("\n-----------------------------");
    for (int x =0; x<6;x++){
           
            printf("\n| %c | %c | %c | %c | %c | %c | %c |",grille[x][0],grille[x][1],grille[x][2],grille[x][3],grille[x][4],grille[x][5],grille[x][6]);
            printf("\n-----------------------------");

    }
    printf("\n| 0 | 1 | 2 | 3 | 4 | 5 | 6 | \n");
}

/** 
 * \fn grillePleine
 * 
 * \brief Vérifie si la grille est pleine
 * 
 * \param t_tableau* grille : tableau à vérifie
 * 
 * \return bool : vrai si la grille est pleine, faux sinon
 * 
 * Vérifie si la grille est pleine en regardant case par case si elle est vide ou non
*/


bool grillePleine(t_tableau grille){
    bool plein = true;
   
    for (int i =0; i< 6;i++){
        for(int y =0; y <NBCOL; y++){
            if (grille[i][y]==VIDE){
                plein = false;  
            }
        }
    }
    return plein;
}

/**
 * \fn jouer
 * 
 * \brief Procédure principale permettant le jeu 
 * 
 * \param t_tableau* grille : tableau à initialiser
 * 
 * \param char pion : pion du joueur
 * 
 * \param int* ligne : ligne du pion
 * 
 * \param int* colonne : colonne du pion
 * 
 * Permet au joueur de jouer en appelant les deux fonctions permettant de choisir (choisirColonne & trouverLigne) ou le joueur veut placer son pion
*/

void jouer(t_tableau *grille, char pion, int *ligne, int *colonne){
    *colonne = choisirColonne(*grille, pion, COLONNE_DEBUT);
    *ligne = trouverLigne(*grille,*colonne);
    *grille[*ligne][*colonne]=pion;
}

/** 
 * \fn choisirColonne
 * 
 * \brief Permet au joueur de choisir une colonne
 * 
 * \param t_tableau* grille : tableau à initialiser
 * 
 * \param char pion : pion du joueur
 * 
 * \param int colonne : colonne de départ
 * 
 * \return int : colonne choisie
 * 
 * Permet au joueur de choisir une colonne en affichant la grille et en demandant à l'utilisateur de choisir une colonne avec 'q" et 'd' pour se déplacer et 'espace' pour valider
*/

int choisirColonne(t_tableau grille,char pion, int colonne){
    char choix;
    ;
    do{
        printf("\nJoueur %c : Choisissez d pour avancer votre pion à droite et q pour avancer à gauche \n et appuyez sur la barre 'ESPACE' valider le choix \n", pion);
        scanf("%c", &choix);
        if ((choix == 'd')&& (colonne < 6)) {
            colonne++;
        }
        else if ((choix == 'q')&& (colonne > 0)){
            colonne--;
        }else{
            colonne = colonne;
        }
    afficher(grille, pion, colonne);

    }while(choix != VIDE);

    if (grille[0][colonne] != VIDE){
        return choisirColonne(grille,pion,colonne);
    }
    return colonne;

}

/**
 * \fn trouverLigne
 * 
 * \brief Permet de trouver la ligne du pion
 * 
 * \param t_tableau* grille : tableau à initialiser
 * 
 * \param int colonne : colonne du pion
 * 
 * \return int : ligne du pion
 * 
 * Permet de trouver la ligne du pion en regardant la première case vide de la colonne
*/

int trouverLigne(t_tableau grille,int colonne){
    int ligne = -1;
    int i =0;
        while((grille[i][colonne] !='X' || grille[i][colonne] !='O') && (i <6)){
            if (grille[i][colonne]==' '){
                ligne++;
            }
            i++;
        }
    return ligne;
}

/** 
 * \fn estVainqueur
 * 
 * \brief Vérifie si le joueur a gagné
 * 
 * \param t_tableau* grille : tableau à initialiser
 * 
 * \param int ligne : ligne du pion
 * 
 * \param int colonne : colonne du pion
 * 
 * \return bool : vrai si le joueur a gagné, faux sinon
 * 
 * Vérifie si le joueur a gagné en regardant si il y a 4 pions alignés que ce soir en diagonale, horizontal, vertical
*/

bool estVainqueur(t_tableau grille,int ligne, int colonne){
    bool vainqueur = false;
    int compt =0;
    int c = colonne -P4;
    int l = ligne-P4;
    char test_joueur=grille[ligne][colonne];

    // test horizontal
    while (!vainqueur && c < NBLIG){
        if(grille[ligne][c]== test_joueur && grille[ligne][c+1]== test_joueur){
            compt++;
            if (compt ==P4){
                vainqueur = true;
            }  
        }
        else{
            compt =0;
        }
        c++;
    }
   
    //test vertical
    compt =0;
    while (!vainqueur && l < NBLIG){
        if(grille[l][colonne]== test_joueur && grille[l+1][colonne]==test_joueur ){
            compt++;  
            if(compt ==P4){
               
                vainqueur = true;
            }
        }else{
            compt =0;
        }
        l++;
    }
    // test diagonale
    compt =0;
    c=colonne -P4;
    l=ligne -P4;
    while (!vainqueur &&(c <colonne +P4 && l <ligne +P4)){
        if (grille[l][c]==test_joueur && grille[l+1][c+1]==test_joueur){
            compt++;
            if(compt == P4){
                vainqueur = true;
            }

        }else{
            compt =0;
        }
        c++;
        l++;

    }
   
    for (int i = 0; i < NBCOL - P4; i++) {
        for (int j = P4; j < NBCOL; j++) {
            if (grille[i][j] == test_joueur && grille[i + 1][j - 1] == test_joueur && grille[i + 2][j - 2] == test_joueur && grille[i + 3][j - 3] == test_joueur
            ) {
                vainqueur = true;
            }
        }
    }
    return vainqueur;
}

/** 
 * \fn finDePartie
 * 
 * \brief Affiche le message de fin de partie
 * 
 * \param char pion : pion du joueur
 * 
 * Affiche le message de fin de partie en fonction du pion vainqueur
*/


void finDePartie(char pion){
    if (pion =='X'){
        printf("Le vainqueur est le joueur X \n");
    }else if ( pion =='O'){
        printf("Le vainqueur est le joueur O \n");
    }else{
        printf("Match Nul ! \n");
    }
}
