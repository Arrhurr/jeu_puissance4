#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define NBLIG 6
#define NBCOL 7

const char PION_A='X';
const char PION_B='O';
const char VIDE=' ';
const char INCONNU =' ';
const int COLDEB=NBCOL/2;

typedef char Grille [NBLIG][NBCOL];

void initGrille(Grille tab);  //fait
void afficher(Grille tab,char J,int c); //fait
bool grillePleine(Grille tab);           //fait
void jouer(Grille tab,char J,int *ligne,int *colonne); //fait
int choisirColonne(Grille tab,char J,int c);//fait
int trouverLigne(Grille tab,int colonne);//fait
bool estVainqueur(Grille tab,int ligne,int colonne);//pas fait
void finDePartie(char J);//fait

int main()
{
    char vainqueur;
    int ligne,colonne;
    Grille g;

    initGrille(g);
    printf("Votre partie de puissance 4 va commencer...\nLes jetons du joueur 1 sont representes par : O\nLes jetons du joueur 2 sont representes par : X\nPour visionner les regles taper 0 quand c'est a votre tour et pour arreter la partie taper -1 a votre tour.\nBonne partie et que le meilleur gagne.\n");
    vainqueur=INCONNU;
    while(vainqueur==INCONNU && !grillePleine(g)){
        jouer(g,PION_A,&ligne,&colonne);
        if(estVainqueur(g,ligne,colonne)){
            vainqueur=PION_A;
        }
        else if(!grillePleine(g)){
            jouer(g,PION_B,&ligne,&colonne);
            if(estVainqueur(g,ligne,colonne)){
                vainqueur=PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    return EXIT_FAILURE;
}

void initGrille(Grille tab){
    int i,j;
    for (i=0;i<NBLIG;i++){
        for (j=0;j<NBCOL;j++){
            tab[i][j]=VIDE;
        }
    }
}

void afficher(Grille tab,char J,int c){
    int i,j,e;
    printf("  1   2   3   4   5   6   7  \n");
    for(e=0;e<NBCOL;e++){
         if(e==c){
            printf("  %c ",J);
        }
        else{
            printf("    ");
        }
    }
    printf("\n");
    for (i=0;i<NBLIG;i++){
        printf("+---+---+---+---+---+---+---+\n");
        for (j=0;j<NBCOL;j++){
            if (j==0){
                printf("| %c |",tab[i][j]);
            }
            else{
                printf(" %c |",tab[i][j]);
            }
        }
        printf("\n");
    }
    printf("+---+---+---+---+---+---+---+\n");
    if(J==PION_A){
        printf("Joueur 1 : Dans quelle colonne voulez vous mettre votre jeton ? :");
    }
    else if(J==PION_B){
        printf("Joueur 2 : Dans quelle colonne voulez vous mettre votre jeton ? :");
    }
}

bool grillePleine(Grille tab){
    int i;
    bool w;
    w=true;
    for (i=0;i<NBCOL;i++){
        if (tab[0][i]==VIDE){
            w=false;
        }
    }
    return w;
}

int choisirColonne(Grille tab, char J,int c){
    char a,entre;
    int i;
    i=c;
    while (a!=VIDE){
        afficher(tab,J,i);
        scanf("%c%c",&a,&entre);
        if (a=='q' && i>0){
            i--;
        }
        else if(a=='d' && i<NBCOL-1){
            i++;
        }
        else if(a=='-'){
            exit(1);
        }
        else if(a=='0'){
            printf("Le but du puissance 4 est d'aligner 4 jeton du meme joueur a l'horizontal, a la vertical et en diagonale sans laisser l'adversaire aligner ses 4 jetons. \n");
        }
    }
    return i;
}

int trouverLigne(Grille tab,int c){
    int i,j;
    j=-1;
    i=NBLIG-1;
    while(i>=0 && j==-1)
    {
        if (tab[i][c]==VIDE){
            j=i;
        }
        i--;
    }
    return j;
}

void finDePartie(char J){
    if(J==PION_A){
        printf("Le joueur 1 gagne !");
    }
    else if(J==PION_B){
        printf("Le joueur 2 gagne !");
    }
    else{
        printf("Tableau plein, il n'y a pas de gagnant, c'est un match nul.");
    }
}

void jouer(Grille tab,char J,int *ligne,int *colonne){
    *colonne=COLDEB;
    *ligne=-1;
    while(*ligne==-1){
        *colonne=choisirColonne(tab,J,*colonne);
        *ligne=trouverLigne(tab,*colonne);
    }
    tab[*ligne][*colonne]=J;
}

bool estVainqueur(Grille tab,int ligne,int colonne){
    bool gagnant,oppose;
    oppose=true;
    int i,compt,comptopp;
    char J;
    J=tab[ligne][colonne];
    i=0;
    gagnant=false;
    if(tab[ligne+1][colonne-1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (ligne+i<NBLIG && colonne-i>-1 && oppose){
                if (tab[ligne+i][colonne-i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<=3-compt;i++){
                if (ligne-i>-1 && colonne+i<NBCOL && oppose){
                    if(tab[ligne-i][colonne+i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    oppose=true;
    if(tab[ligne+1][colonne+1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (ligne+i<NBLIG && colonne+i<NBCOL && oppose){
                if (tab[ligne+i][colonne+i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<=3-compt;i++){
                if (ligne-i>-1 && colonne-i>-1 && oppose){
                    if(tab[ligne-i][colonne-i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    oppose=true;
    if(tab[ligne][colonne+1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (colonne+i<NBCOL-1 && oppose){
                if (tab[ligne][colonne+i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<=3-compt;i++){
                if (colonne-i>-1 && oppose){
                    if(tab[ligne][colonne-i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    oppose=true;
    if(tab[ligne][colonne-1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (colonne-i>-1 && oppose){
                if (tab[ligne][colonne-i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<=3-compt;i++){
                if (colonne+i<NBCOL-1 && oppose){
                    if(tab[ligne][colonne+i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    oppose=true;
    if(!gagnant && tab[ligne-1][colonne]==J && ligne<NBLIG-4){ 
        for(i=1;i<4;i++){
            if (tab[ligne-i][colonne]!=J){
                oppose=false;
            }
        }
        if (oppose){
            gagnant=true;
        }
    }
    oppose=true;
    if(tab[ligne-1][colonne-1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (ligne-i>-1 && colonne-i>-1 && oppose){
                if (tab[ligne-i][colonne-i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<3;i++){
                if (ligne+i<NBLIG && colonne+i<NBCOL && oppose){
                    if(tab[ligne+i][colonne+i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    oppose=true;
    if(tab[ligne-1][colonne+1]==J){
        compt=0;
        comptopp=0;
        for(i=1;i<4;i++){
            if (ligne-i>-1 && colonne+i<NBCOL && oppose){
                if (tab[ligne-i][colonne+i]!=J){
                    oppose=false;
                
                }
                else{
                compt=compt+1;
                }
            }
        }
        oppose=true;
        if (compt<3){
            for(i=1;i<=3-compt;i++){
                if (ligne+i<NBLIG && colonne-i>-1 && oppose){
                    if(tab[ligne+i][colonne-i]!=J){
                        oppose=false;
                    }
                    else{
                        comptopp=comptopp+1;
                    }
                }
            }
        }
        if(compt+comptopp==3){
            gagnant=true;
        }
    }
    return gagnant;
}