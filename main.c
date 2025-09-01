#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// TODO: implementar

void hablarConComandanteExtraterrestre();
void presentarseALideresMundiales();
void tomarPosicionEnMegaCiudad();
void atacarMegaciudad();
void iniciarPotocoloDefensivo();
void contraatacarNaves();
void perderBatalla();
void descenderATierra();
void abrirCompuertas();
void abandonarTierra();

void* presidentes(void* arg){
        //Implementar
}
void* naves_destructoras(void* arg){
        //Implementar
}
void* ciudades(void* arg){
        //Implementar
}
void* comandante(void* arg){
        //Implementar
}
int main(void){
        printf("Hello there!\n");
        pthread_t presidentes[5];
        pthread_t naves_destructoras[33];
        pthread_t ciudades[33];
        pthread_t comandante;

        for(int i=0;i<5;i++){
                pthread_create(&presidentes[i],NULL,presidentes,NULL);
        }
        for(int i=0;i<33;i++){
                pthread_create(&naves_destructoras[i],NULL,naves_destructoras,NULL);
        }
        for(int i=0;i<33;i++){
                pthread_create(&ciudades[i],NULL,ciudades,NULL);
        }
        pthread_create(comandante,NULL,comandante,NULL);

        return 0;
}