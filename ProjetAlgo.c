#include <stdio.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then

typedef enum { false, true } bool;

/*#define FALSE 0
#define TRUE !(FALSE)*/

int fact(int n){
     return n > 1?(n * fact(n-1)):1;
}

float sommeInf(){
    int f = 1;
    float res = 1.;
    for (int i = 2; i < 12; i++)
    {        
        printf("res1 = %f\n", res);
        res += (1./(f));
        f *= i; 
    }
    return res;
}

double aux(int i, double x){
    if (i < 1) //i < 50
    {
        printf("res2 = %f\n", x);
        aux(i++,(i*x)-1);
    }
}

double suite(){
    double x0 = sommeInf() - 1;
    //printf("x0 = %f \n", x0);
    aux(0,x0);
}

///////////////////* POWER *////////////////////

/*int power1(int x, int n){
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return power1(x,n-1) * x;
    }
}*/

int power1(int x, int n){
    int n2 = abs(n);
    if (n2 == 0)
    {
        return 1;
    }
    else
    {
        return power1(x,n-1) * x;
    }
}

double power2(int x, int n){
    int r = 1;
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

int pow3(int x, int n, int *r){
    if (n != 0)
    {
        *r *= x;
        pow3(x, n-1, r);
    }
}
int power3(int x, int n){
    int r = 1;
    pow3(x,n,&r);
    return r;
}

int pow4(int x, int n, int r){
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
}


int power5(int x, int n){
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

int power6(int x, int n){
    if (n == 0)
    {
        return 1;
    }
    else
    {
        int y = power6(x, n / 2);
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

int power7(int x, int n){
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

int pow8(int x, int n, int r){
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
int power8(int x, int n){
    return pow8(x,n,1);
}

int pow9(int x, int n, int *r){
    if (n != 0)
    {
        if (n%2 != 0)
        {
            *r *= x;
        }
        pow9(x*x,n/2,r);
    }
}
int power9(int x, int n){
    int r = 1;
    pow9(x,n,&r);
    return r;
}

int power10(int x, int n){
    int r = 1;
    while (n != 0)
    {
        if (n % 2 != 0)
        {
            r *= x;
        }
        //n = n/2;
        n *= 0.5;
        x *= x;
    }
    return r;
}

////////////////////////////////////////////////


int main(int argc, char const *argv[]){
        //printf("res = %f\n", sommeInf());
        //suite();
        printf("res1 = %d\n", power1(2,6));
        printf("res2 = %f\n", power2(2,6));
        printf("res3 = %d\n", power3(2,6));
        printf("res4 = %d\n", power4(2,6));
        printf("res5 = %d\n", power5(2,6));
        printf("res6 = %d\n", power6(2,6));
        printf("res7 = %d\n", power7(2,6));
        printf("res8 = %d\n", power8(2,6));
        printf("res9 = %d\n", power9(2,6));
        printf("res10 = %d\n", power10(2,6));

        printf("res-2 = %f\n", power2(2,-6));
        //printf("res2 = %d\n", power2(2,6));
    
    return 0;
}
