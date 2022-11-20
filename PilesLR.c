
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sel syntaxique                 */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


typedef struct Listes
{
    Liste liste;
    struct Listes *suivant;
} Listes;

typedef Listes *ListeListe ;

typedef struct BlocBis
{
    int nombre;
    struct BlocBis *suivant;
    struct BlocBis **pred;
    //struct BlocBis *pred;
} BlocBis;

typedef BlocBis *ListeBis ;


/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*       Implementations perso                   */
/*                                               */
/*************************************************/

bool aux_ZeroEnPositionUnOuDeuxOuTrois(Liste l, int acc){
    if ( acc >= 3){
        return FALSE;
    }
    else{
        printf("acc = %d | l = %d \n", acc, l->nombre);
        if(l->nombre == 0)
            return TRUE;
        aux_ZeroEnPositionUnOuDeuxOuTrois(l->suivant, acc+1);
    }   
}
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l){
    if ( l == NULL){
        return FALSE;;
    }
    else{
        return aux_ZeroEnPositionUnOuDeuxOuTrois(l, 0);
    }
}

bool Pluscourte(Liste l1, Liste l2){
    if (l2 == NULL)
        return FALSE;
    if (l1 == NULL)
        return  TRUE;
    return Pluscourte(l1->suivant, l2->suivant);
}

int NombreDe0AvantPositionKRec(Liste l, int k){   
    if (l == NULL || k <= 0){
        return 0;
    }
    else{
        if (l->nombre == 0)
            return 1 + NombreDe0AvantPositionKRec(l->suivant, k-1);
        return NombreDe0AvantPositionKRec(l->suivant, k-1);
    }
}

int NombreDe0AvantPositionKIter(Liste l, int k){
    int cpt = 0;

    while (l != NULL && k > 0)
    {
        if (l->nombre == 0)
            cpt++;
        k--;
        l = l->suivant;
    }
    return cpt;
}

int aux_NombreDe0AvantPositionKSousRecTer(Liste l, int k, int cpt){
    if (l == NULL || k <= 0){
        return cpt;
    }
    else{
        if (l->nombre == 0)
            return aux_NombreDe0AvantPositionKSousRecTer(l->suivant, k-1, cpt+1);
        return aux_NombreDe0AvantPositionKSousRecTer(l->suivant, k-1, cpt);
    }
}
int NombreDe0AvantPositionKSousRecTer(Liste l, int k){
    return aux_NombreDe0AvantPositionKSousRecTer(l, k, 0);
}

void aux_NombreDe0AvantPositionKSousProcTer(Liste l, int k, int *cpt){
    if (l != NULL && k > 0){
        if (l->nombre == 0){
            *cpt = *cpt+1;
        }
        aux_NombreDe0AvantPositionKSousProcTer(l->suivant, k-1, cpt);
    }
} 
int NombreDe0AvantPositionKSousProcTer(Liste l, int k){   
    /*if (l == NULL)
        return 0;*/
    int cpt = 0;
    aux_NombreDe0AvantPositionKSousProcTer(l, k, &cpt);
    return cpt;
}

/*
void aux_NombreDe0ApresRetroPositionKRec(Liste l, int *k, int *cpt){   
    if (l != NULL){
        aux_NombreDe0ApresRetroPositionKRec(l->suivant, k, cpt);
        if (*k != 0){
            if (l->nombre == 0)
                *cpt = *cpt + 1;
            printf("l = %d |cpt = %d |k = %d \n", l->nombre, *cpt, *k);
            *k = *k - 1;
        } 
    }
}
int NombreDe0ApresRetroPositionKRec(Liste l, int k){
    if(l == NULL)
        return 0;
    int cpt = 0;
    aux_NombreDe0ApresRetroPositionKRec(l, &k, &cpt);
    return cpt;
}
*/

void aux_NombreDe0ApresRetroPositionKRec(Liste l, int *k, int *cpt){   
    if (l != NULL){
        *cpt = 0;
        aux_NombreDe0ApresRetroPositionKRec(l->suivant, k, cpt);
        if (*k != 0){
            if (l->nombre == 0)
                *cpt = *cpt + 1;
            printf("l = %d |cpt = %d |k = %d \n", l->nombre, *cpt, *k);
            *k = *k - 1;
        } 
    }
}
int NombreDe0ApresRetroPositionKRec(Liste l, int k){
    /*if(l == NULL)
        return 0;*/
    //int cpt = 0;
    int cpt;
    aux_NombreDe0ApresRetroPositionKRec(l, &k, &cpt);
    return cpt;
}

Liste FctBegayeRec(Liste l){
    if (l== NULL){
        return NULL;
    }
    else{
        printf(" l = %d \n", l->nombre);
        if (l->nombre > 0)
            return ajoute(l->nombre, ajoute(l->nombre, FctBegayeRec(l->suivant)));
        return FctBegayeRec(l->suivant);
    }
}

/*void aux_FctBegayeRecTer(Liste l, Liste *l2){
    if (l!= NULL){
        //printf(" l = %d \n", l->nombre);
        aux_FctBegayeRecTer(l->suivant, l2);
        if (l->nombre > 0)
            *l2 = ajoute(l->nombre, ajoute(l->nombre, *l2));
    }
}
Liste FctBegayeRecTer(Liste l){
    Liste l2 = NULL;
    //initVide (&l2) ;
    //if (l != NULL)
    aux_FctBegayeRecTer(l, &l2);
    return l2;
}*/

/*Liste aux_FctBegayeRecTer(Liste l, Liste l2){
    if (l!= NULL){
        //printf(" l = %d \n", l->nombre);
        //aux_FctBegayeRecTer(l->suivant, l2);
        if (l->nombre > 0)
            return ajoute(l->nombre, ajoute(l->nombre, aux_FctBegayeRecTer(l->suivant, l2)));
        return aux_FctBegayeRecTer(l->suivant, l2);
    }
    return NULL;
}
Liste FctBegayeRecTer(Liste l){
    return aux_FctBegayeRecTer(l, NULL);
}*/

void aux_FctBegayeRecTer(Liste l, Liste *l2){
    if (l!= NULL){
        aux_FctBegayeRecTer(l->suivant, l2);
        if (l->nombre > 0)
            *l2 = ajoute(l->nombre, ajoute(l->nombre, *l2));
    }
    /*if (l!= NULL){
        if (l->nombre > 0)
            aux_FctBegayeRecTer(l->suivant, ajoute(l->nombre, ajoute(l->nombre, *l2)));
        aux_FctBegayeRecTer(l->suivant, l2);
    }*/
    /*if (l!= NULL){
        if (l->nombre > 0)
            *l2 = ajoute(l->nombre, ajoute(l->nombre, *l2));
        aux_FctBegayeRecTer(l->suivant, l2);
    }*/
}
Liste FctBegayeRecTer(Liste l){
    Liste l2 = NULL;
    //initVide (&l2) ;
    //if (l != NULL)
    aux_FctBegayeRecTer(l, &l2);
    return l2;
}
/***/

/*Liste ElimineToutesOccurences(int x, Liste *L){
    if ((*L)==NULL){
    }
    else{
        if (x == premier(L))
        {
            depile(L);
            ElimineToutesOccurences();
        }        
    }    
}*/

/***/

Liste FctBegayeIter1(Liste l){
    Liste temp = NULL;;
    Liste l2 = NULL;
    
    //version facile
    while (l != NULL)
    {
        if (l->nombre > 0){
            temp = ajoute(l->nombre, temp);
        }
        l = l->suivant;
    }
    
    while(temp != NULL){
        l2 = ajoute(temp->nombre, ajoute(temp->nombre, l2));
        temp = temp->suivant;
    }
    return l2;
}

Liste FctBegayeIter(Liste l){
    //Liste l2 = NULL;
    //Liste *temp = &l2;;
    Liste *temp = NULL;
    //Liste *l2 = &temp;
    Liste l2 = NULL;
    //int compteur = 0;

    while (l != NULL)
    {
        if (l->nombre > 0){
            /*temp = ajoute(l->nombre, ajoute(l->nombre, NULL));
            l2 = temp;
            l2 = l2->suivant->suivant;*/
            //temp = NULL; pas utile de le mettre a NULL puisque qu'il sera ecrasé a la prochaine passe
            /**temp = ajoute(l->nombre, ajoute(l->nombre, *temp));
            //l2 = temp;
            *temp = (*temp)->suivant->suivant;*/
            //temp->suivant = ajoute(l->nombre, ajoute(l->nombre, NULL));
            /*temp = ajoute(l->nombre, ajoute(l->nombre, NULL));
            if (l2 == NULL)
            {
                l2 = &temp;
            }
            //l2 = temp;
            temp = temp->suivant->suivant;
            temp = ajoute(28, ajoute(28, NULL));
            temp->suivant->suivant = ajoute(00, NULL);*/

            
            if (l2 == NULL){
                l2 = ajoute(l->nombre, ajoute(l->nombre, NULL));
                temp = &l2;
            }
            else{
                *temp = ajoute(l->nombre, ajoute(l->nombre, NULL));
            }
            //l2 = temp;
            temp = &((*temp)->suivant->suivant);
            //temp = ajoute(28, ajoute(28, NULL));
            //temp->suivant->suivant = ajoute(00, NULL);
        }
        l = l->suivant;
    }
    return l2;
    //return (*l2);
    //return temp;
    
    //version facile
    /*while (l != NULL)
    {
        if (l->nombre > 0){
            temp = ajoute(l->nombre, temp);
        }
        l = l->suivant;
    }
    
    while(temp != NULL){
        l2 = ajoute(temp->nombre, ajoute(temp->nombre, l2));
        temp = temp->suivant;
    }*/
    /*
    bon debut
    while (l != NULL)
    {
        if (l->nombre > 0){
            temp = ajoute(l->nombre, ajoute(l->nombre, NULL));
            l2->suivant = temp;
            l2 = l2->suivant->suivant;
            //temp = NULL; pas utile de le mettre a NULL puisque qu'il sera ecrasé a la prochaine passe

        }
        l = l->suivant;
    }*/

    
}

////////////////////////////////////////////////////////////////////////////////////////////////

void ProcBegaye(Liste *L){
    if ((*L) != NULL){
        ProcBegaye((&(**L).suivant));
        int temp = premier(*L);
        depile(L);
        if (temp > 0){
           empile(temp, L);
           empile(temp, L);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************/
/*                                               */
/*     Fonctions pour le type ListeListe         */
/*                                               */
/*************************************************/

/* Ajoute une liste d'entier (l) au début de la liste de liste (ll) */
ListeListe ajouteListe(Liste l, ListeListe ll)
{
    ListeListe tmp = (ListeListe) malloc(sizeof(Listes)) ;
    tmp->liste = l;
    tmp->suivant = ll ;
    return tmp ;
}

void afficheListe_rec(ListeListe ll)
{
    if(ll == NULL)
        printf(" --Fin de la liste de liste-- \n");
    else
    {
        printf("[ ");
        affiche_rec(ll->liste);
        //printf(" \n");
        afficheListe_rec(ll->suivant);
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************/
/*                                               */
/*     Fonctions pour la fonction permutation    */
/*                                               */
/*************************************************/

ListeListe Concat(ListeListe l1, ListeListe l2){
    if (l1 == NULL){
        return l2;
    }
    return ajouteListe(l1->liste,Concat(l1->suivant,l2));
}

ListeListe AETTL(int x, ListeListe ll){
    if(ll == NULL)
        return NULL;
    return ajouteListe(ajoute(x, ll->liste), AETTL(x, ll->suivant));
}

ListeListe ATP(int x, Liste l){
    if(l == NULL) {
        ListeListe ll2 = NULL;
        Liste l2 = NULL;
        return ajouteListe(ajoute(x,l2), ll2);
    }
    return ajouteListe(ajoute(x,l), AETTL(l->nombre, ATP(x, l->suivant)));  
}

ListeListe ATLTP(int x, ListeListe ll){
    if(ll == NULL){
        return NULL;
    }
    return Concat( (ATP(x, ll->liste)), ATLTP(x, ll->suivant));
}

ListeListe Permutations(int n){
    if(n == 0){
        return ajouteListe(NULL,NULL);
    }
    return ATLTP(n, Permutations(n-1));
}

////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************/
/*                                               */
/*     Fonctions pour le type ListeBis           */
/*                                               */
/*************************************************/

void initVideBis( ListeBis *L)
{
    *L = NULL ;
}

bool estVideBis(ListeBis l)
{
    return l == NULL ;
}

int premierBis(ListeBis l)
{
    return l->nombre; 
}

ListeBis suiteBis(ListeBis l)
{
    return l->suivant;
}

ListeBis* predBis(ListeBis l)
{
    return l->pred;
}

ListeBis ajouteBis(int x, ListeBis l)
{
    ListeBis tmp = (ListeBis) malloc(sizeof(BlocBis)) ;
    tmp->nombre = x;
    tmp->suivant = l;
    tmp->pred = NULL;

    if(l != NULL){
        //l->pred = tmp; 
        l->pred = &(tmp->suivant);
    }
    return tmp;
}

void empileBis(int x, ListeBis *L)
{
    *L = ajouteBis(x,*L) ; 
}

void depileBis(ListeBis *L)
{
    ListeBis tmp = *L ;
    *L = suiteBis(*L) ;
    //*L->pred = NUll;
    free(tmp) ;
}

void VideListeBis(ListeBis *L)
{
    if(NOT(estVideBis(*L)))
    {
        depileBis(L);
        VideListeBis(L);
    }
}

void affiche_recBis(ListeBis l)
{
    if(estVideBis(l))
        printf("\n fin \n");
    else
    {
        printf("%d ", premierBis(l));
        affiche_recBis(suiteBis(l));
    }
}

void supp(ListeBis *L){
    ListeBis temp = *L;
    
    if(temp->suivant == NULL){
        if (temp->pred == NULL)
            (*L) = NULL;
        else
            *((*L)->pred) = NULL;
    }
    else{
        if (temp->pred == NULL){
            (*L)->suivant->pred = NULL;
            (*L) = (*L)->suivant;
        }
        else{
            (*L)->suivant->pred = temp->pred;
            *((*L)->pred) = temp->suivant;
        }
    }
    free(temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main()
{
    /*Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);*/

    Liste l1;
    initVide (&l1) ;
    /*empile(3, &l) ;
    empile(4, &l) ;
    empile(0, &l) ;
    empile(2, &l) ;
    empile(8, &l) ;*/
    empile(2, &l1) ;
    empile(0, &l1) ;
    empile(2, &l1) ;
    empile(2, &l1) ;
    empile(1, &l1) ;

    Liste l2;
    initVide (&l2) ;
    empile(4, &l2) ;
    empile(4, &l2) ;
    empile(4, &l2) ;
    empile(0, &l2) ;
    empile(2, &l2) ;
    empile(8, &l2) ;

    Liste l3;
    initVide (&l3) ;
    empile(0, &l3) ;
    empile(1, &l3) ;
    empile(0, &l3) ;
    empile(0, &l3) ;
    empile(0, &l3) ;
    empile(9, &l3) ;
    empile(6, &l3) ;
    empile(5, &l3) ;
    empile(0, &l3) ;
    empile(2, &l3) ;

    Liste l4;
    initVide (&l4) ;
    empile(2, &l4) ;
    empile(0, &l4) ;
    empile(5, &l4) ;
    empile(6, &l4) ;
    empile(9, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(1, &l4) ;
    empile(0, &l4) ;
    /*empile(3, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(5, &l4) ;
    empile(0, &l4) ;*/

    /*empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;
    empile(0, &l4) ;*/

    Liste l5;
    initVide (&l5) ;
    empile(8, &l5) ;
    empile(8, &l5) ;
    empile(-2, &l5) ;
    empile(6, &l5) ;
    empile(0, &l5) ;
    empile(1, &l5) ;
    empile(2, &l5) ;

    Liste l6;
    initVide (&l6) ;
    empile(3, &l6) ;
    empile(0, &l6) ;
    empile(0, &l6) ;
    empile(5, &l6) ;

    //printf("reponse = %d",ZeroEnPositionUnOuDeuxOuTrois(l1));

    //printf("reponse = %d \n",Pluscourte(l1,l2));

    //printf("nb de 0 = %d \n",NombreDe0AvantPositionK(&l3,6));
    /*printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKRec(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKIter(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKSousRecTer(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKSousProcTer(l3,6));*/
    
    //printf("nb de 0 apres k = %d \n",NombreDe0ApresRetroPositionKRec(l4,6));


    /*affiche_rec(FctBegayeRec(l5));
    affiche_rec(FctBegayeRecTer(l5));  */  
    affiche_rec(FctBegayeIter(l5));

    /*affiche_rec(l5);
    ProcBegaye(&l5);
    affiche_rec(l5);*/


    /*affiche_rec(l1);
    affiche_rec(l2);
    affiche_rec(Concat(l1,l2));*/

    /*ListeListe ll1;
    initListeVide(&ll1) ;
    empileListe(l1, &ll1);
    empileListe(l2, &ll1);

    afficheListe_rec(ll1);
    VideListeListe(&ll1);*/
    /*ListeListe ll = Permutations(4);
    afficheListe_rec(ll);*/
    
    // afficheListe_rec(ATLTP(2,ajouteListe(ajoute(5,NULL),NULL)));

    /*ListeListe ll01 = NULL;
    Liste l01 = NULL;
    Liste l02 = NULL;
    Liste l03 = NULL;
    empile(8,&l01);
    empile(3,&l01);

    empile(2,&l02);
    
    empile(9,&l03);
    empile(7,&l03);
    empile(5,&l03);
    ll01 = ajouteListe(NULL,ll01);
    ll01 = ajouteListe(l01,ll01);
    ll01 = ajouteListe(l02,ll01);
    ll01 = ajouteListe(l03,ll01);
    afficheListe_rec(ATLTP(4,ll01));*/
    // afficheListe_rec(ATP(2,ajoute(5,NULL)));
    // afficheListe_rec(AETTL(2,ajouteListe(ajoute(5,NULL),NULL)));
    // afficheListe_rec(Concat(ajouteListe(ajoute(5,NULL),NULL),ajouteListe(ajoute(5,NULL),NULL)));

    ////////////////////////////////////////////////////////////////

    /*ListeBis lb1;
    initVideBis(&lb1);
    empileBis(5, &lb1);
    empileBis(8, &lb1);
    empileBis(1, &lb1);

    affiche_recBis(lb1);
    supp(&lb1->suivant->suivant);
    supp(&lb1->suivant);
    supp(&lb1);
    affiche_recBis(lb1);

    VideListeBis(&lb1);
*/
    ////////////////////////////////////////////////////////////////

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    VideListe(&l5);

    
    return 0;
}





