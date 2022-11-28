#include <stdio.h>
#include <stdlib.h>

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

void affiche_Normal(image img){
    if (img == NULL)
        printf("B");
    else if (img->toutnoir)
        printf("N");
    else{
        printf("(");
        for (size_t i = 0; i < 4; i++)          
            affiche_Normal(img->fils[i]);
        printf(")");
    }
}
void aux_affiche_Profondeur(image img, int prof){
    if (img == NULL)
        printf("B%d ", prof);
    else if (img->toutnoir)
        printf("N%d ", prof);
    else{
        printf("( ");
        for (size_t i = 0; i < 4; i++)          
            aux_affiche_Profondeur(img->fils[i],prof+1);
        printf(")");
    }
}
void affiche_Profondeur(image img){
    aux_affiche_Profondeur(img, 0);
    printf("\n");
}
/* a finir*/
image lecture(char s[]){
    return NULL;
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

}

void quartDeTour(image *img){

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
    //printf("ici %d \n",(*img)->toutnoir);
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

    /*affiche_Normal(
        construit_Composee(construit_Noir(),
            construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc()),
            construit_Blanc(),
            construit_Composee(construit_Noir(),
                construit_Composee(construit_Noir(),construit_Noir(),construit_Blanc(),
                    construit_Composee(construit_Noir(),construit_Blanc(),construit_Noir(),construit_Noir())),
        construit_Blanc(),construit_Noir())));*/
    //printf ("%d",estNoire(construit_Composee(construit_Noir(),construit_Noir(),construit_Composee(construit_Noir(),construit_Noir(),construit_Noir(),construit_Noir()),construit_Blanc())));
    //printf ("%d",estBlanche(construit_Composee(construit_Blanc(),construit_Noir(),construit_Composee(construit_Blanc(),construit_Blanc(),construit_Blanc(),construit_Blanc()),construit_Blanc())));
    image img = construit_Composee(construit_Blanc(),construit_Blanc(),construit_Noir(),construit_Blanc());
    affiche_Normal(img);
    negatif(&img);
    printf("\n");
    affiche_Normal(img);
    
}