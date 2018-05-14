#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int g_n;
int col[15]={0};
int con[100]={0};
int promising_children[100]={0};
int prom_fin=0;
long double nodos_solucion=0;
long double nodos_promising=0;
long double nodos_total=0;

long double MC=0;

void N_Queen(int n);
void MC_Queen(int n);
int abs(int n);
long double exaustivo (int n);
long double factorial (int n);
void long_print(long double n);

int main()
{
    srand(time(NULL));
    N_Queen(14);//16= 7+ min, 15= 2- min, 14= 30+- s
    MC_Queen(14);
    long_print(MC);
    long_print(nodos_total);
    return 0;
}

void long_print(long double n){
    if(n>=1000000){
        int pot=6;
        n=n/1000000;
        while(n>10){
            n=n*0.1;
            pot++;
        }
        float s=n*1.0;
        printf("%1.3fe%02d",s,pot);
    }
    else{
        float s=((float) n);
        printf("%6.1f",s);
    }
}

void restart_child(){
    for(int i =0;i<100;i++)
        promising_children[i]=-1;
    prom_fin=0;
}

long double exaustivo (int n){
    return (pow(n,n+1)-1)/(n-1);
}

long double factorial (int n){
    long double resp=1;
    while(0<n){
        resp*=n;
        n--;
    }
    return resp;
}

int abs(int n){
    if (n<0)
        return 0-n;
    else
        return n;
}

int promising(int i){
    int k,segura;
    k=1;
    segura=1;
    while(segura&&k<i){
        if(col[k]==col[i]||abs(i-k)==abs(col[i]-col[k]))
            segura=0;
        k++;
    }
    return segura;
}

int promising_mc(int i){
    int k,segura;
    k=1;
    segura=1;
    while(segura&&k<i){
        if(con[k]==con[i]||abs(i-k)==abs(con[i]-con[k]))
            segura=0;
        k++;
    }
    return segura;
}

void Queens(int i){
    nodos_total++;
    int j;
    if(promising(i)){
        nodos_promising++;
        if(i==g_n){
            nodos_solucion++;
        }else{
            for(j=1;j<=g_n;j++){
                col[i+1]=j;
                Queens(i+1);
            }
        }
    }
}

void N_Queen(int n){
    g_n=n;
    col[0]=0;
    Queens(0);
}

long double mc_nqueens(int n){
    int i,j,m;
    long double mprod,numnode;
    i=0;
    numnode=mprod=m= 1;
    while(m!=0&& i!=n){
        mprod=mprod*m;
        numnode+=mprod*n;
        i++;
        restart_child();
        m=0;
        for(j=1;j<=n;j++){
            con[i]=j;
            if(promising_mc(i)){
                m++;
                promising_children[prom_fin]=j;
                prom_fin++;
            }
        }
        if(m!=0){
            j=-1;
            while(j==-1){
                j=promising_children[rand()%prom_fin];
            }
            con[i]=j;
        }
    }
    return numnode;
}

void MC_Queen(int n){
    int i=0;
    MC=0;
    while(i<100){
        MC+=mc_nqueens(n)*0.01;
        i++;
    }

}

