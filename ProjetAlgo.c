#include <stdio.h>
#include <stdlib.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then

typedef enum { false, true } bool;

int fact(int n){
     return n > 1?(n * fact(n-1)):1;
}

float sommeInf(){
    int f = 1;
    float res = 1.;
    for (int i = 2; i < 13; i++)
    {        
        printf("res1 = %20.18f\n", res);
        res += (1./(f));
        f *= i; 
    }
    return res;
}

void suite(){
    double x0 = sommeInf() - 1.;

    printf("%.16f",sommeInf());
    for (int i = 1; i < 50; i++)
    {
        x0 = ((i*x0)-1.);
        printf("res2 = %f, iter %d\n", x0, i);
    }
}

///////////////////* POWER *////////////////////

/*double power1(int x, int n){
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return power1(x,n-1) * x;
    }
}*/

double pow1(int x, int n){
    if (n == 0)
    {
        return 1.;
    }
    else
    {
        return (pow1(x,n-1) * x);
    }
}
double power1(int x, int n){
    if (n < 0)
    {
        return 1./pow1(x,abs(n));
    }
    else
    {
        return pow1(x,n);
    }
}

double power2(int x, int n){
    double r = 1.;
    int n2 = abs(n);
    while (n2 > 0)
    {
        r *= x;
        n2--;
    }
    if (n < 0)
        return 1./r;
    return r;
}

void pow3(int x, int n, double *r){
    if (n != 0)
    {
        *r *= x;
        pow3(x, n-1, r);
    }
}
double power3(int x, int n){
    double r = 1;
    pow3(x,n,&r);
    return r;
}

double pow4(int x, int n, double r){
    if (n == 0)
        return r;
    else
        return pow4(x, n-1, r*x);
}
double power4(int x, int n){
    return pow4(x,n,1.);
}

/*int pow4(int x, int n, int r){
    if (n == 0)
    {
        return r;
    }
    else
    {
        pow4(x, n-1, r*x);
    }
}
int power4(int x, int n){
    return pow4(x,n,1);
}*/


double power5(int x, int n){
    if (n == 0)
    {
        return 1;
    }
    else
    {
        if (n%2 == 0)
        {
            return power5(x, n / 2) * power5(x, n / 2);
        }
        else
        {
            return power5(x, n / 2) * power5(x, n / 2) * x;
        }
    }
}

double power6(int x, int n){
    if (n == 0)
    {
        return 1.;
    }
    else
    {
        double y = power6(x, n / 2);
        if (n%2 == 0)
        {
            return y * y;
        }
        else
        {
            return y * y * x;
        }
    }
}

double power7(int x, int n){
    if (n == 0)
    {
        return 1;
    }
    else
    {
        if (n%2 == 0)
        {
            return power7(x*x,n/2);
        }
        else
        {
            return power7(x*x,n/2) * x;
        }
    }
}

double pow8(int x, int n, double r){
    if (n == 0)
    {
        return r;
    }
    else
    {
        if (n%2 == 0)
        {
            return pow8(x*x,n/2,r);
        }
        else
        {
            return pow8(x*x,n/2,r*x);
        }
    }
}
double power8(int x, int n){
    return pow8(x,n,1.);
}

void pow9(int x, int n, double *r){
    if (n != 0)
    {
        if (n%2 != 0)
        {
            *r *= x;
        }
        pow9(x*x,n/2,r);
    }
}
double power9(int x, int n){
    double r = 1.;
    pow9(x,n,&r);
    return r;
}

double power10(double x, int n){
    double r = 1.;
    while (n != 0)
    {
        if (n % 2 != 0)
        {
            r *= x;
        }
        n *= 0.5;
        x *= x;
    }
    return r;
}

////////////////////////////////////////////////

void suitePuissances(){
    double N = 0.;
    for (int i = 0; i < 25; i++)
    {
        N = power1(10,i);
        printf("10^%d = %f\n", i, power10((1+(1./N)),N));
    }
}

////////////////////////////////////////////////

int ackermann1(int m, int n){
    if (m == 0)
        return n+1;
    else
    {
        int r = 1;
        for (int i = 1; i <= n+1; i++)
        {
            r = ackermann1(m-1,r);
        }
        return r;
    }
}

int ackermann2(int m, int n){
    if (m == 0)
        return n+1;
    else{
        if (n == 0)
            return ackermann2(m-1,1);
        else
            return ackermann2(m-1,ackermann2(m,n-1));
    }
}

void ackerValues(){
    for (int i = 0; i <= 5; i++)
    {
        printf("acker n°1 A(%d,0) : %d \n", i, ackermann1(i,0));
        printf("acker n°2 A(%d,0) : %d \n", i, ackermann2(i,0));
    }
}

double suiteReelsIter(int n){
    double x0 = 1;

    for (int i = 1; i <= n; i++)
    {
        x0 = x0 + 2./x0;
    }
    return x0;
}

double suiteReelsRec(int n){
    if (n == 0)
        return 1;
    else{
        double res = suiteReelsRec(n-1);
        return res + 2./res;
    }
}

double aux_suiteReelsRecTerFonc(int n, double x0){
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

void aux_suiteReelsRecTerProc(int n, double *r){
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


int main(int argc, char const *argv[]){
        printf("res = %20.18f\n", sommeInf());
        /**
         * On peut voir que la formule tend vers 2.718282
        **/  

        //suite();
        /**
         * On utilisant un float on constate qu'à partir de la 39ème itération le programme n'affiche plus la suite des résultats
         * On utilisant un double au lieu d'un float, on peut voir que le programme ne plante plus pour les 50 premières itérations, on peut voir que ça tend vers l'infini.
         **/

        //// Partie sur les fonctions Power
        /*printf("res1 = %f\n", power1(2,6));
        printf("res2 = %f\n", power2(2,6));
        printf("res3 = %f\n", power3(2,6));
        printf("res4 = %f\n", power4(2,6));
        printf("res5 = %f\n", power5(2,6));
        printf("res6 = %f\n", power6(2,6));
        printf("res7 = %f\n", power7(2,6));
        printf("res8 = %f\n", power8(2,6));
        printf("res9 = %f\n", power9(2,6));
        printf("res10 = %f\n", power10(2,6));

        printf("res-1 = %f\n", power1(2,-6));
        printf("res-2 = %f\n", power2(2,-6));*/


        //// Partie pour la suite de puissance de 10
        //suitePuissances();
        
        /*printf("res1 = %f\n", power1(10,9));
        printf("res2 = %f\n", power2(10,9));
        printf("res3 = %f\n", power3(10,9));
        printf("res4 = %f\n", power4(10,9));
        printf("res5 = %f\n", power5(10,9));
        printf("res6 = %f\n", power6(10,9));
        printf("res7 = %f\n", power7(10,9));
        printf("res8 = %f\n", power8(10,9));
        printf("res9 = %f\n", power9(10,9));        
        printf("res10 = %f\n", power10(10,9));

        printf("\n \n");

        printf("res1 = %f\n", power1(10,12));
        printf("res2 = %f\n", power2(10,12));
        printf("res3 = %f\n", power3(10,12));
        printf("res4 = %f\n", power4(10,12));
        printf("res5 = %f\n", power5(10,12));
        printf("res6 = %f\n", power6(10,12));
        printf("res7 = %f\n", power7(10,12));
        printf("res8 = %f\n", power8(10,12));
        printf("res9 = %f\n", power9(10,12));        
        printf("res10 = %f\n", power10(10,12));*/

        /////////////////////////////////////////////

        //suitePuissances();
        /**
         * la suite semble tendre vers 2.718282 comme pour "e"
         * On peut apercevoir un probleme a partir 10^10, la calcul commence a descendre pour finalement bloquer a 1.0
         * */ 

        /*printf("acker1 = %d\n", ackermann1(1,0));
        printf("acker2 = %d\n", ackermann2(1,0));

        printf("acker1 = %d\n", ackermann1(2,1));   
        printf("acker2 = %d\n", ackermann2(0,4));*/

        //ackerValues();

        /**
         * Pour le calcul de (6,0), le programme tourne sans donner de résultat.
         * La version récursive ne fonctionne pas et renvoie le code d'erreur : "3221225725", car on atteint la limite de la récusrion.
         */

        /*printf("ouais %f\n",suiteReelsIter(100));
        printf("ouais2 %f\n",suiteReelsRec(100));
        printf("ouais3 %f\n",suiteReelsRecTerFonc(100));
        printf("ouais4 %f\n",suiteReelsRecTerProc(100));*/
        

    return 0;
}