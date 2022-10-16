
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
    struct BlocBis *pred;
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
/*       Implementation perso                    */
/*                                               */
/*************************************************/

bool aux_ZeroEnPositionUnOuDeuxOuTrois(Liste *L, int acc){
    if ( (*L) != NULL && acc < 3){
        printf("acc = %d | L = %d \n", acc, premier(*L));
        if(premier(*L) == 0)
            return TRUE;
        aux_ZeroEnPositionUnOuDeuxOuTrois(& ( (**L).suivant ), acc+1);
    }
    else
        return FALSE;
}
bool ZeroEnPositionUnOuDeuxOuTrois(Liste *L){
    if ( (*L) != NULL)
    {
        Liste temp = *L;
        return aux_ZeroEnPositionUnOuDeuxOuTrois(&temp, 0);
    }
    return FALSE;;
}

bool Pluscourte(Liste l1, Liste l2){
    if (l2 == NULL)
        return FALSE;
    if (l1 == NULL)
        return  TRUE;
    return Pluscourte(l1->suivant, l2->suivant);
}

/*
bool aux_ZeroEnPositionUnOuDeuxOuTrois(Liste *L, int acc){
    if ( (*L) != NULL && acc < 3){
        printf("acc = %d | L = %d \n", acc, premier(*L));
        if(premier(*L) == 0)
            return TRUE;
        aux_ZeroEnPositionUnOuDeuxOuTrois(& ( (**L).suivant ), acc+1);
    }
    else
        return FALSE;
}
bool ZeroEnPositionUnOuDeuxOuTrois(Liste *L){
    if ( (*L) != NULL)
    {
        Liste temp = *L;
        return aux_ZeroEnPositionUnOuDeuxOuTrois(&temp, 0);
    }
    return FALSE;;
}
*/

/*int aux_NombreDe0AvantPositionK(Liste *L, int K, int cpt){
    printf("cpt = %d | L = %d \n", cpt, premier(*L));
    if ((*L) == NULL)
        return cpt;
    /*if (K == 0 && premier(*L) == 0)
        return aux_NombreDe0AvantPositionK(&((**L).suivant), 0, cpt+1);
    else
        return aux_NombreDe0AvantPositionK(&((**L).suivant), K-1, cpt);*/
    /*if (K == 0)
    {
        return aux_NombreDe0AvantPositionK(&((**L).suivant), 0, cpt+1);
    }
        
    
}
int NombreDe0AvantPositionK(Liste *L, int K){
    if ((*L) == NULL)
        return 0;
    //Liste temp = *L;
    return aux_NombreDe0AvantPositionK(L, K, 0);
}*/

/*int NombreDe0AvantPositionKRec(Liste l, int k){   
    /*if (l != NULL){
        if (k == 0 && l->nombre == 0)
            return 1 + NombreDe0AvantPositionKRec(l->suivant, k);
        else
            return NombreDe0AvantPositionKRec(l->suivant, k-1);
    }
    return 0;*/

    /*if (l == NULL)
        return 0;
    if (k == 0 && l->nombre == 0)
            return 1 + NombreDe0AvantPositionKRec(l->suivant, k);
        else
            return NombreDe0AvantPositionKRec(l->suivant, k-1);
}

int NombreDe0AvantPositionKIter(Liste l, int k){
    int cpt = 0;

    while (l != NULL)
    {
        if (k == 0 && l->nombre == 0)
            cpt++;
        else
            k--;
        l = l->suivant;
    }
    return cpt;
}*/

int NombreDe0AvantPositionKRec(Liste l, int k){   
    if (l != NULL && k > 0){
        if (l->nombre == 0)
            return 1 + NombreDe0AvantPositionKRec(l->suivant, k-1);
        return NombreDe0AvantPositionKRec(l->suivant, k-1);
    }
    return 0;
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
/*double aux_suiteReelsRecTerFonc(int n, double x0){
    if (n != 0)
    {
        x0 = x0+2./x0;
        return aux_suiteReelsRecTerFonc(n-1, x0);
    }
    return x0;
}
double suiteReelsRecTerFonc(int n){
    return aux_suiteReelsRecTerFonc(n, 1.);
}
*/

int aux_NombreDe0AvantPositionKSousRecTer(Liste l, int k, int cpt){
    if (l != NULL && k > 0){
        if (l->nombre == 0)
            return aux_NombreDe0AvantPositionKSousRecTer(l->suivant, k-1, cpt+1);
        return aux_NombreDe0AvantPositionKSousRecTer(l->suivant, k-1, cpt);
    }
    return cpt;
}
int NombreDe0AvantPositionKSousRecTer(Liste l, int k){
    if (l == NULL)
        return 0;
    return aux_NombreDe0AvantPositionKSousRecTer(l, k, 0);
}
/*void aux_suiteReelsRecTerProc(int n, double *r){
    if (n != 0)
    {
        *r = *r+2./(*r);
        aux_suiteReelsRecTerProc(n-1, r);
    }
}
double suiteReelsRecTerProc(int n){
    double x0 = 1.;
    aux_suiteReelsRecTerProc(n, &x0);
    return x0;
}
*/
void aux_NombreDe0AvantPositionKSousProcTer(Liste l, int k, int *cpt){
    if (l != NULL && k > 0){
        if (l->nombre == 0){
            *cpt = *cpt+1;
        }
        aux_NombreDe0AvantPositionKSousProcTer(l->suivant, k-1, cpt);
    }
} 
int NombreDe0AvantPositionKSousProcTer(Liste l, int k){   
    if (l == NULL)
        return 0;
    int cpt = 0;
    aux_NombreDe0AvantPositionKSousProcTer(l, k, &cpt);
    return cpt;
}


/*int NombreDe0ApresRetroPositionKIter(Liste l, int k){   
    if (l != NULL){
        if (l->nombre == 0 && k <= 1)
            return 1 + NombreDe0AvantPositionKRec(l->suivant, k-1);
        return NombreDe0AvantPositionKRec(l->suivant, k-1);
    }
    return 0;
}*/

/*int NombreDe0ApresRetroPositionKIter(Liste l, int k){
    int cpt = 0;

    while (l != NULL)
    {
        //printf("k = % d\n", k);
        if (k == 1 && l->nombre == 0)
            cpt++;
        else
            k--;
        //printf("cpt = % d\n", cpt);
        l = l->suivant;
    }
    return cpt;
}*/

/*int NombreDe0ApresRetroPositionKRec(Liste l, int k){   
    if (l != NULL){
        printf("l = %d |cpt = %d |k = %d \n", l->nombre, cpt, k);
        if (l->nombre == 0 && k == 0){
            return 1 + NombreDe0ApresRetroPositionKRec(l->suivant, k);
        }
            
        return NombreDe0ApresRetroPositionKRec(l->suivant, k-1);
    }
    return 0;
}*/

/*void NombreDe0ApresRetroPositionKRec(Liste l, int *k){   
    if (l != NULL && *k != 0){
        if (l->nombre == 0 && *k > 0){
            *k = *k + 1;
        }
            
        NombreDe0ApresRetroPositionKRec(l->suivant, k-1);
        printf("l = %d | k = %d \n", l->nombre, k);
    }
}*/

/*save en version procédurale*/
/*void aux_NombreDe0ApresRetroPositionKRec(Liste l, int *k, int *cpt){   
    //printf(" l = %d \n", l->nombre);
    if (l != NULL){    
        if (*k != 0 && l->nombre == 0)
            *cpt = *cpt + 1;      
        aux_NombreDe0ApresRetroPositionKRec(l->suivant, k, cpt);
        *k = *k - 1;
        printf("l = %d |cpt = %d |k = %d \n", l->nombre, *cpt, *k);
    }
}*/
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

Liste FctBegayeRec(Liste l){
    if (l!= NULL){
        printf(" l = %d \n", l->nombre);
        if (l->nombre > 0)
            return ajoute(l->nombre, ajoute(l->nombre, FctBegayeRec(l->suivant)));
        return FctBegayeRec(l->suivant);
    }
    Liste l2;
    initVide (&l2) ;
    return l2;
}

void aux_FctBegayeRecTer(Liste l, Liste *l2){
    if (l!= NULL){
        //printf(" l = %d \n", l->nombre);
        aux_FctBegayeRecTer(l->suivant, l2);
        if (l->nombre > 0)
            *l2 = ajoute(l->nombre, ajoute(l->nombre, *l2));
    }
}
Liste FctBegayeRecTer(Liste l){
    Liste l2;
    initVide (&l2) ;
    if (l != NULL)
        aux_FctBegayeRecTer(l, &l2);
    return l2;
}

/*if (l!= NULL){
        printf(" l = %d \n", l->nombre);
        if (l->nombre > 0)
            return ajoute(l->nombre, ajoute(l->nombre, FctBegayeRecProc(l->suivant)));
        return FctBegayeRecProc(l->suivant);
    }
    Liste l2;
    initVide (&l2) ;
    return l2;*/
/*Liste FctBegayeRecIter(Liste l){
    
    Liste l2;
    initVide (&l2) ;
    //l2 = ajoute(158, l2);
    while (l != NULL)
    {
        //printf(" l = %d \n", l->nombre);
        if (l->nombre > 0)
            l2 = ajoute(l->nombre, ajoute(l->nombre, l2));
        /*if (l->nombre > 0){
            l2 = ajoute(l->nombre, l2);
            l2 = ajoute(l->nombre, l2);
        }*/
        /*l = l->suivant;
    }
    //affiche_rec(l2);
    return l2;
}*/

Liste FctBegayeIter(Liste l){
    Liste temp;
    initVide (&temp);
    Liste l2;
    initVide (&l2);
    //l2 = ajoute(158, l2);
    /*while (l != NULL)
    {
        //printf(" l = %d \n", l->nombre);
        if (l->nombre > 0){
            /*l2->suivant = l->nombre;
            l2->suivant->suivant = NULL;*/
            /*l2 = ajoute(l->nombre, ajoute(l->nombre, l2));
        }
            //l2 = ajoute(l->nombre, ajoute(l->nombre, l2));
        l = l->suivant;
    }*/

    //version facile
    while (l != NULL)
    {
        //printf(" l = %d \n", l->nombre);
        if (l->nombre > 0){
            temp = ajoute(l->nombre, temp);
        }
        l = l->suivant;
    }
    
    while(temp != NULL){
        l2 = ajoute(temp->nombre, ajoute(temp->nombre, l2));
        //l2 = ajoute(temp->nombre, l2);
        temp = temp->suivant;
    }
    return l2;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void ProcBegaye(Liste *L){
    Liste temp;
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
/*Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}*/

// void initListeVide( Liste *LL)
// { //initVideListe
//     *LL = NULL ;
// }

// /* Ajoute une liste d'entier (l) au début de la liste de liste (ll) */
// ListeListe ajouteListe(Liste l, ListeListe ll)
// {
//     ListeListe tmp = (ListeListe) malloc(sizeof(Listes)) ;
//     tmp->liste = l;
//     tmp->suivant = ll ;
//     return tmp ;
// }

// void empileListe(Liste l, ListeListe *LL)
// {
//       *LL = ajouteListe(l,*LL) ; 
// }

// ListeListe suiteListe(ListeListe ll)
// {
//     return ll->suivant ;
// }

// void depileListe(ListeListe *LL)
// {
//     ListeListe tmp = *LL ;
//     *LL = suiteListe(*LL) ;
//     free(tmp) ;
// }

// bool estVideListe(ListeListe ll)
// {
//     return ll == NULL ;
// }

// void VideListeListe(ListeListe *LL)
// {
//     if(NOT(estVideListe(*LL)))
//     {
//         depileListe(LL);
//         VideListeListe(LL);
//     }
      
// }

// void afficheListe_rec(ListeListe ll)
// {
//     if(estVideListe(ll))
//         printf(" --Fin de la liste de liste-- \n");
//     else
//     {
//         //printf("%d ", premier(ll));
//         affiche_rec(ll->liste);
//         printf("\n");
//         afficheListe_rec(suiteListe(ll));
//     }
// }

// ////////////////////////////////////////////////////////////////////////////////////////////////

// Liste Concat(Liste l1, Liste l2){
//     /*if (L1 == NULL)
//         return L2;
//     //L2 = ajoute(L1->nombre,L2);
//     Concat(L1->suivant, L2);
//     return ajoute(L1->nombre,L2);*/

//     if (l1 == NULL){
//         return l2;
//     }
//     return ajoute(l1->nombre,Concat(l1->suivant,l2));
// }

// ListeListe AETTL(int x, ListeListe ll){
//     if(ll == NULL)
//         return NULL;
//     return (ajoute(x, ll->liste), AETTL(x, ll->suivant));
//     //return (ajoute(x, &(ll->liste)), AETTL(x, ll->suivant));
// }

// /*ListeListe ATP(int x, ListeListe ll){
//     if(ll == NULL) {
//         ListeListe ll2;
//         initVide(&ll2);
//         Liste l2;
//         initVide(&l2);
//         return ajoute(ajoute(x,l2), ll2);
//     }
//     return ajoute(ajoute(x,ll), AETTL(
        
    
// }*/

// ListeListe ATP(int x, Liste l){
//     if(l == NULL) {
//         ListeListe ll2;
//         initListeVide(&ll2);
//         Liste l2;
//         initVide(&l2);
//         return ajouteListe(ajoute(x,l2), ll2);
//     }
//     return ajouteListe(ajoute(x,l), AETTL(l->nombre, ATP(x, l->suivant)));  
// }

// ListeListe ATLTP(int x, ListeListe ll){
//     if(ll == NULL){
//         /*ListeListe ll2;
//         initListeVide(&ll2);
//         return ll2;*/
//         return NULL;
//     }
//     return Concat( (ATP(x, ll->liste)), ATLTP(x, ll->suivant));
// }

// ListeListe Permutations(int n){
//     if(n == 0){
//         //return NULL;
//         ListeListe ll2;
//         initListeVide(&ll2);
//         return ll2;
//     }
//     return ATLTP(n, Permutations(n-1));
// }
/*
Liste FctBegayeRec(Liste l){
    if (l!= NULL){
        printf(" l = %d \n", l->nombre);
        if (l->nombre > 0)
            return ajoute(l->nombre, ajoute(l->nombre, FctBegayeRec(l->suivant)));
        return FctBegayeRec(l->suivant);
    }
    Liste l2;
    initVide (&l2) ;
    return l2;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////

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

ListeBis predBis(ListeBis l)
{
    return l->pred;
}

ListeBis ajouteBis(int x, ListeBis l)
{
    ListeBis tmp = (ListeBis) malloc(sizeof(BlocBis)) ;
    tmp->nombre = x;
    tmp->suivant = l;
    tmp->pred = NULL;
    //printf("%d ", tmp->nombre);
    //printf("%d ", (tmp->suivant)->pred);
    /*ListeBis tmp2 = (tmp->suivant);
    printf("%d ", tmp2->pred);*/
    //tmp->suivant->pred = tmp ;
    return tmp ;
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
        //printf("yo");
        printf("%d ", premierBis(l));
        affiche_recBis(suiteBis(l));
    }
}

void affiche_enversBis(ListeBis l)
{
    if(predBis(l) == NULL)
        printf("\n");
    else
    {
        printf("%d ", premierBis(l));
        affiche_enversBis(predBis(l));
    }
}

void affiche_rec_revBis(ListeBis l)
{
    if(estVideBis(l)){
        printf("\n");
        affiche_enversBis(l);
    }
        
    else
    {
        printf("%d ", premierBis(l));
        affiche_rec_revBis(suiteBis(l));
    }
}


void supp(ListeBis *L){
    ListeBis temp = *L;
    /**L->suivant->pred = temp->pred;
    *L->pred->suivant = temp->suivant;*/
    *suiteBis(predBis(*L)) = *temp->pred;
    *predBis(suiteBis(*L)) = *temp->suivant;
    //free(temp);
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

int main(int argc, char** argv)
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

    //printf("reponse = %d",ZeroEnPositionUnOuDeuxOuTrois(&l1));

    //printf("reponse = %d \n",Pluscourte(l1,l2));

    //printf("nb de 0 = %d \n",NombreDe0AvantPositionK(&l3,6));
    /*printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKRec(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKIter(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKSousRecTer(l3,6));
    printf("nb de 0 avant k = %d \n",NombreDe0AvantPositionKSousProcTer(l3,6));*/
    
    //printf("nb de 0 apres k = %d \n",NombreDe0ApresRetroPositionKRec(l4,6));


    /*affiche_rec(FctBegayeRec(l5));
    affiche_rec(FctBegayeRecTer(l5));    
    affiche_rec(FctBegayeIter(l5));*/

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
    ////////////////////////////////////////////////////////////////

    ListeBis lb1;
    initVideBis(&lb1);
    empileBis(5, &lb1);
    empileBis(8, &lb1);

    affiche_recBis(lb1);

    VideListeBis(&lb1);

    ////////////////////////////////////////////////////////////////

    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    VideListe(&l5);

    
    return 0;
}





