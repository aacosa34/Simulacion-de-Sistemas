#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

long long int gen_aritmetica_entera(long long int x, int m){
    return (1013*x)%m;
}

int gen_aritmetica_real(float x, int m){
    x = 1013*x/m;
    x = (x-(int)x)*m;
    return x;
}

int gen_aritmetica_real_corregida(float x, int m){
    x = 1013*x/m;
    x = (x-(int)x)*m;
    x = (int) (x+0.5);
    return x;
}

double gen_aritmetica_real_fmod(double x, int m){
    x = fmod(1013*x,m);
    return x;
}

int main(){
    // TODO main como se pide en el enunciado
}