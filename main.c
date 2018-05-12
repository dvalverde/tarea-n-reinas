#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int g_n;
int col[15]={0};
int con[100]={0};
int promising_children[100]={0};
int prom_fin=0;
int nodos_solucion=0;
int nodos_promising=0;
int nodos_total=0;

double MC=0;

void N_Queen(int n);
void MC_Queen(int n);
int abs(int n);

int main()
{
    srand(time(NULL));
    N_Queen(4);
    MC_Queen(4);
    printf("totales=%d, promising=%d, solucion=%d, MC=%f",nodos_total,nodos_promising,nodos_solucion,MC);
    return 0;
}

void restart_child(){
    for(int i =0;i<100;i++)
        promising_children[i]=-1;
    prom_fin=0;
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

int mc_nqueens(int n){
    int i,j;
    int m,mprod,numnode;
    i=0;
    numnode=mprod=m= 1;
    while(m!=0&& i!=n){
        mprod=mprod*m;
        numnode=numnode+mprod*n;
        i++;
        restart_child();
        for(j=1;j<=n;j++){
            con[i]=j;
            if(promising(j)){
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
    while(i<60){
        MC+=mc_nqueens(n);
        i++;
    }
    MC=MC/60;
}

