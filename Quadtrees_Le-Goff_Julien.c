#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { FALSE, TRUE} bool;

typedef struct bloc_image
{ 
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;

typedef bloc_image *image ;

image construit_Blanc(){
    return NULL;
}

image construit_Noir(){
    image tmp = (image) malloc(sizeof(bloc_image));
    tmp->toutnoir = TRUE;
    for (size_t i = 0; i < 4; i++)
        tmp->fils[i] = NULL;
    return tmp;
}

image construit_Composee(image i0,image i1,image i2,image i3){
    image tmp = (image) malloc(sizeof(bloc_image));
    tmp->toutnoir = FALSE;
    tmp->fils[0] = i0;
    tmp->fils[1] = i1;
    tmp->fils[2] = i2;
    tmp->fils[3] = i3;
    return tmp;
}

void aux_affiche_Normal(image img){
    if (img == NULL)
        printf("B");
    else if (img->toutnoir)
        printf("N");
    else{
        printf("(");
        for (size_t i = 0; i < 4; i++)
            aux_affiche_Normal(img->fils[i]);
        printf(")");
    }
}
void affiche_Normal(image img){
    aux_affiche_Normal(img);
    printf("\n");
}

void aux_affiche_Profondeur(image img, int prof){
    if (img == NULL)
        printf("B%d", prof);
    else if (img->toutnoir)
        printf("N%d", prof);
    else{
        printf("(");
        for (size_t i = 0; i < 4; i++)          
            aux_affiche_Profondeur(img->fils[i],prof+1);
        printf(")");
    }
}
void affiche_Profondeur(image img){
    aux_affiche_Profondeur(img, 0);
    printf("\n");
}
image aux_lecture(char *s, int *n){
    *n+=1;
    
    if (*(s+(*n)) == 'N')
        return construit_Noir();
    else if (*(s+(*n)) == 'B')
        return construit_Blanc();
    else if (*(s+(*n)) == '('){
        image temp1 = aux_lecture(s, n);
        image temp2 = aux_lecture(s, n);
        image temp3 = aux_lecture(s, n);
        image temp4 = aux_lecture(s, n);

        return construit_Composee(temp1, temp2, temp3, temp4);
    }
    else
        aux_lecture(s,n);
}
image lecture(char *s){
    int n = -1;
    return aux_lecture(s, &n);
}

bool estNoire(image img){
    if (img == NULL)
        return FALSE;
    else if (img->toutnoir)
        return TRUE;
    else
        return estNoire(img->fils[0]) && estNoire(img->fils[1]) && estNoire(img->fils[2]) && estNoire(img->fils[3]);
}

bool estBlanche(image img){
    if (img == NULL)
        return TRUE;
    else if (img->toutnoir)
        return FALSE;
    else
        return estBlanche(img->fils[0]) && estBlanche(img->fils[1]) && estBlanche(img->fils[2]) && estBlanche(img->fils[3]);
}

image diagonale(int p){
    if (p == 1)
        return construit_Composee(construit_Noir(),construit_Blanc(),construit_Blanc(),construit_Noir());
    else
        return construit_Composee(diagonale(p-1),construit_Blanc(),construit_Blanc(),diagonale(p-1));
}

/*void quartDeTour(image *img){
    if(*img == NULL)
        return;
    else if ((*img)->toutnoir)
        return;
    else{
        image temp0 = (*img)->fils[0];
        //image temp3 = (*img)->fils[3];
        
        (*img)->fils[0] = (*img)->fils[2];
        (*img)->fils[2] = (*img)->fils[3];
        (*img)->fils[3] = (*img)->fils[1];
        (*img)->fils[1] = temp0;

        for (size_t i = 0; i < 4; i++){
            /*if(((*img)->fils[i]) != NULL)
            {
                quartDeTour(&((*img)->fils[i]));
            }*/
            /*quartDeTour(&((*img)->fils[i]));
        }
    }
}*/
image quartDeTour(image img){
    if(img == NULL)
        return NULL;
    else if (img->toutnoir)
        return construit_Noir();
    else
        return construit_Composee(quartDeTour(img->fils[2]),quartDeTour(img->fils[0]),quartDeTour(img->fils[3]),quartDeTour(img->fils[1]));
}

void negatif(image *img){
    if (*img == NULL)
        *img = construit_Noir();
    else if ((*img)->toutnoir)
        *img = construit_Blanc();
    else{
        for (size_t i = 0; i < 4; i++)
            negatif(&(*img)->fils[i]);
    }
}

void simplifieProfP2(image *img, int p){    
    if (*img == NULL)
        return;
    else if ((*img)->toutnoir)
        return;
    else{
        if (p == 0){
            if(estNoire(*img)) ((*img)) = construit_Noir();
            else if(estBlanche(*img)) ((*img)) = construit_Blanc();
        }
        else{
            for (size_t i = 0; i < 4; i++){
                simplifieProfP2(&((*img)->fils[i]),p-1);
            }
        }
    }
}

bool incluse(image img1, image img2){
    if (img1 == NULL)
        return TRUE;
    else if (img1->toutnoir){
        if (img2 == NULL) return FALSE;
        else if (img2->toutnoir) return TRUE;
        else return FALSE;
    }
    else{
        if (img2 == NULL) return FALSE;
        else if (img2->toutnoir) return TRUE;
        else return incluse(img1->fils[0],img2->fils[0]) && incluse(img1->fils[1],img2->fils[1]) && incluse(img1->fils[2],img2->fils[2]) && incluse(img1->fils[3],img2->fils[3]);
    }
}
int maxInt(int n1, int n2){
    return (n1>n2)?n1:n2;
}
int hautMaxBlanc(image img){
    if (img == NULL)
        return 0;
    else if (img->toutnoir)
        return (-1);
    else{
        if ((img->fils[0]) == NULL && (img->fils[1]) == NULL && (img->fils[2]) == NULL && (img->fils[3]) == NULL) return 1;
        else if (estBlanche(img)) return 1 + maxInt(maxInt(maxInt(hautMaxBlanc(img->fils[0]),hautMaxBlanc(img->fils[1])),hautMaxBlanc(img->fils[2])),hautMaxBlanc(img->fils[3]));
        else return maxInt(maxInt(maxInt(hautMaxBlanc(img->fils[0]),hautMaxBlanc(img->fils[1])),hautMaxBlanc(img->fils[2])),hautMaxBlanc(img->fils[3]));;
    }
}

void blanchitProfP(image* img, int p, int x, int y){
    float pp = (pow(2,p)-1);
    if (x >= 0 && y >= 0 && x <= pp && y <= pp){
        if (p == 0)
            *img = NULL;
        else{
            int nbFils;
            if (x >= 0 && x < (pp/2)){
                if (y >= (pp/2) && y <= pp){
                    nbFils = 0;
                    y-=pp/2;
                }
                else
                    nbFils = 2;
            }
            else{
                if (y >= (pp/2) && y <= pp){
                    nbFils = 1;
                    x-=pp/2;
                    y-=pp/2;
                }
                else{
                    nbFils = 3;
                    x-=pp/2;
                }
            }
            if (img == NULL)
                *img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc());
            else if ((*img)->toutnoir)
                *img = construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir());
            
            blanchitProfP(&(*img)->fils[nbFils], p-1, x, y);
        }
    }
}
void echange(image *img1, image *img2){
    image temp = *img1;
    *img1 = *img2;
    *img2 = temp;
    free(temp);
}
// l'image 1 est au dessus de l'image 2
void tombe(image *img1, image *img2){
    /*if (img2 == NULL && img1 != NULL){
        image temp = *img1;
        *img1 = *img2;
        *img2 = temp;
    }*/
    if (img1 == NULL){
        return;
    }
    else{
        if ((*img1)->toutnoir){
            if (img2 == NULL){
                echange(img1, img2);
            }
            else if ((*img1)->toutnoir){
                return;
            }
            else{
                //chute(img2);
                tombe(&((*img2)->fils[0]),&((*img2)->fils[2]));
                tombe(&((*img2)->fils[1]),&((*img2)->fils[3]));
                echange(img1, img2);
            }
        }
        else{
            if (img2 == NULL){
                echange(img1, img2);
            }
            else if ((*img1)->toutnoir){
                return;
            }
            else{
                tombe(&((*img1)->fils[0]),&((*img1)->fils[2]));
                tombe(&((*img1)->fils[1]),&((*img1)->fils[3]));
                tombe(&((*img2)->fils[0]),&((*img2)->fils[2]));
                tombe(&((*img2)->fils[1]),&((*img2)->fils[3]));
                //chute(img1);
                //chute(img2);
                echange(&((*img1)->fils[1]),&((*img2)->fils[0]));
                echange(&((*img1)->fils[3]),&((*img1)->fils[2]));
                
                tombe(&((*img1)->fils[0]),&((*img1)->fils[2]));
                tombe(&((*img1)->fils[1]),&((*img1)->fils[3]));
                tombe(&((*img2)->fils[0]),&((*img2)->fils[2]));
                tombe(&((*img2)->fils[1]),&((*img2)->fils[3]));
                //chute(img1);
                //chute(img2);
                echange(&((*img1)->fils[1]),&((*img2)->fils[0]));
                echange(&((*img1)->fils[3]),&((*img1)->fils[2]));
            }
        }
    }
}
void chute(image *img){
    if (img == NULL){
        return;
    }        
    else if ((*img)->toutnoir){
        return;
    }
    else{
        tombe(&((*img)->fils[0]),&((*img)->fils[2]));
        tombe(&((*img)->fils[1]),&((*img)->fils[3]));
    }
}


int main(){
    //affiche_Normal(construit_Composee(construit_Noir(),construit_Noir(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Noir(),construit_Blanc(),construit_Blanc())));
    //affiche_Normal(construit_Blanc());
    //affiche_Normal(construit_Composee(construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc,construit_Noir(),construit_Blanc()),construit_Blanc(),construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Blanc(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Noir())),construit_Blanc(),construit_Noir())));
    /*affiche_Normal(construit_Composee(construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc()),construit_Blanc(),construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Blanc(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Noir())),construit_Blanc(),construit_Noir())));
    printf("\n");
    affiche_Profondeur(construit_Composee(construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc()),construit_Blanc(),construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Blanc(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Noir())),construit_Blanc(),construit_Noir())));
    */
    //affiche_Normal(lecture("(B,N,N,B"));

    //printf ("%d",estNoire(construit_Composee(construit_Noir(),construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir()),construit_Blanc())));
    //printf ("%d",estBlanche(construit_Composee(construit_Blanc(),construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc())));
    
    /*image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc());
    affiche_Normal(img);
    negatif(&img);
    printf("\n");
    affiche_Normal(img);*/

    //affiche_Normal(diagonale(3));
    //image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc());
    
    /*image img = construit_Composee(construit_Composee(construit_Noir(),construit_Blanc(),construit_Blanc(),construit_Noir()),construit_Blanc(),construit_Blanc(),construit_Blanc());
    //image img = construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Composee(construit_Noir(),construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir()),construit_Noir()),construit_Blanc()),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()))),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc()));
    //image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc());
    affiche_Normal(img);
    //quartDeTour(&img);
    affiche_Normal(quartDeTour(img));*/

    //image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Noir());
    //image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc());
    /*image img = construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Composee(construit_Noir(),construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir()),construit_Noir()),construit_Blanc()),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()))),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc()));
    affiche_Normal(img);
    simplifieProfP2(&img, 2);
    printf("\n");
    affiche_Normal(img);*/

    /*image img1 = construit_Composee(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Noir()),construit_Blanc(),construit_Blanc(),construit_Blanc());
    image img2 = construit_Composee(construit_Noir(),construit_Blanc(),construit_Blanc(),construit_Blanc());
    printf("inclus ? %d \n", incluse(img1,img2));*/

    //printf("inclus ? %d \n", incluse(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Noir()),construit_Blanc()));
    //printf("inclus ? %d \n", incluse(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc()));
    //printf("inclus ? %d \n", incluse(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Noir()),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc())));
    
    // p = 2
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()))));
    // p = 3
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc(),construit_Blanc()))));
    // p = 3
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc(),construit_Blanc()))));
    // p = 1
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc(),construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()))));
    // p = 1
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Noir(),construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()))));
    // p = -1
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir()))));
    // p = 0
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Noir()))));
    // p = 1
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc())));
    // p = 0
    //printf("Max hauteur blanc %d \n", hautMaxBlanc(construit_Blanc()));

    //image img = construit_Noir();
    //image img = construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir());
    //image img = construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Blanc());
    /*image img = construit_Composee(construit_Composee(construit_Noir(),construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Noir()),construit_Noir(),construit_Noir()),construit_Blanc(),construit_Noir(),construit_Blanc());
    affiche_Normal(img);
    //blanchitProfP(&img, 2, 0,3);
    blanchitProfP(&img, 2, 1, 3);
    printf("\n");
    affiche_Normal(img);*/

    //char s[] = "(NBN((BBBN)NNB))";
    //char s[] = "(N(BBBN)N((BB(BBBN)N)NNB))";
    /*char s[] = "(N(NB(NN(NNNN)N)B)(NBN(NBN(BBBB)))(BB(BBBB)B))";
    //char s[] = "(N(NB(NNBN)B)(NBN(NBN(BBBB)))(BB(BBBB)B))";
    //char s[] = "(B(NB(NNBN)B)BN";
    //char s[] = "";
    //char s[] = "((NBBB)NBN)";
    //char s[] = "((NNNN)NBN)";
    //char s[] = "(NNBN)";
    printf("%s \n", s);
    affiche_Normal(lecture(s));*/

    /*char s[] = "(N(NB(NN(NNNN)N)B)(NBN(NBN(BBBB)))(BB(BBBB)B))";
    //printf("%s \n", s);
    image img = lecture(s);
    
    printf("(N(NBNB)(NBN(NBN(BBBB)))(BBBB)) \n");

    simplifieProfP(&img, 2);
    affiche_Normal(img);*/

    /*image img1 = construit_Noir();
    image img2 = construit_Blanc();*/
    /*image img3 = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc());
    affiche_Normal(img3);
    //tombe(&img1,&img2);
    chute(&img3);
    printf("\n");
    affiche_Normal(img3);*/
}