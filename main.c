#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Defino los semáforos
sem_t mutex_comandante;
sem_t naves_en_posicion;
sem_t orden_ataque;
sem_t ciudades_caidas;
sem_t sincronizacion_batalla;

void hablarConComandanteExtraterrestre()
{
        printf("Presidente: Bienvenido comandante alien \n");
}

void presentarseALideresMundiales()
{
        printf("Hola, soy el comandante alien \n");
}

void tomarPosicionEnMegaCiudad()
{
        printf("Una nave ha tomado la posición de una ciudad \n");
}

void atacarMegaciudad()
{
        printf("La nave comienza el ataque a la ciudad \n");
}

void iniciarProtocoloDefensivo()
{
        printf("La ciudad inicia el protocolo de defensa contra las naves \n");
}

void contraatacarNaves()
{
        printf("La ciudad contrataca a las naves. Parece resultar ineficaz.... "
               "\n");
}

void perderBatalla()
{
        printf("Los humanos han perdido la batalla \n");
}

void descenderATierra()
{
        printf("Al haber ganado las batallas, la nave nodriza desciende a la "
               "tierra \n");
}

void abrirCompuertas()
{
        printf("Se abren las compuertas de la nave nodriza \n");
}

void abandonarTierra()
{
        printf("Luego de abrirse las compuertas, un polen extraño comienza a "
               "aniquilar a los extraterrestres. El comandante ordena el "
               "retiro del planeta \n");
}

void *presidentes(void *arg)
{
        sem_wait(&mutex_comandante);
        hablarConComandanteExtraterrestre();
        presentarseALideresMundiales();
        sem_post(&mutex_comandante);
}

void *naves_destructoras(void *arg)
{
        // Fase 1: Tomar posición
        tomarPosicionEnMegaCiudad();
        sem_post(&naves_en_posicion); // aviso que estoy lista

        // Fase 2: Esperar orden de ataque y atacar
        sem_wait(&orden_ataque);
        atacarMegaciudad();
        sem_post(&sincronizacion_batalla); // Aviso que terminé de atacar

        return NULL;
}

void *ciudades(void *arg)
{
        // Esperar a que la nave correspondiente ataque primero
        sem_wait(&sincronizacion_batalla);

        // Ahora la ciudad se defiende
        iniciarProtocoloDefensivo();
        contraatacarNaves();
        sem_post(&ciudades_caidas); // aviso que ya caí

        return NULL;
}

void *comandante(void *arg)
{
        // Espero a las 33 naves
        for (int i = 0; i < 33; i++) {
                sem_wait(&naves_en_posicion);
        }
        // Orden de ataque → desbloquea a todas las ciudades
        for (int i = 0; i < 33; i++) {
                sem_post(&orden_ataque);
        }

        // Espero a que caigan todas las ciudades
        for (int i = 0; i < 33; i++) {
                sem_wait(&ciudades_caidas);
        }

        // Luego el comandante baja y ocurre el final
        perderBatalla();
        descenderATierra();
        abrirCompuertas();
        abandonarTierra();
}

int main(void)
{
        // Inicializo los semáforos
        sem_init(&mutex_comandante, 0, 1);
        sem_init(&naves_en_posicion, 0, 0);
        sem_init(&orden_ataque, 0, 0);
        sem_init(&ciudades_caidas, 0, 0);
        sem_init(&sincronizacion_batalla, 0, 0);
        // Defino el arreglo de threads
        pthread_t presidentes_threads[15];
        pthread_t naves_destructoras_threads[33];
        pthread_t ciudades_threads[33];
        pthread_t comandante_thread;

        // Creo los hilos
        for (int i = 0; i < 15; i++) {
                pthread_create(&presidentes_threads[i], NULL, presidentes,
                               NULL);
        }
        for (int i = 0; i < 33; i++) {
                pthread_create(&naves_destructoras_threads[i], NULL,
                               naves_destructoras, NULL);
        }
        for (int i = 0; i < 33; i++) {

                pthread_create(&ciudades_threads[i], NULL, ciudades, NULL);
        }
        pthread_create(&comandante_thread, NULL, comandante, NULL);

        // Finalizo los hilos
        for (int i = 0; i < 15; i++) {
                pthread_join(presidentes_threads[i], NULL);
        }
        for (int i = 0; i < 33; i++) {
                pthread_join(naves_destructoras_threads[i], NULL);
        }
        for (int i = 0; i < 33; i++) {
                pthread_join(ciudades_threads[i], NULL);
        }
        pthread_join(comandante_thread, NULL);

        // Destruyo los semáforos
        sem_destroy(&mutex_comandante);
        sem_destroy(&naves_en_posicion);
        sem_destroy(&orden_ataque);
        sem_destroy(&ciudades_caidas);
        sem_destroy(&sincronizacion_batalla);

        return 0;
}
