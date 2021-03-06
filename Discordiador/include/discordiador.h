#ifndef DISCORDIADOR_H
#define DISCORDIADOR_H

#include "shared_utils.h"
#include <commons/memory.h>
// /home/utnso/TPCUATRI/tp-2021-1c-Pascusa/Discordiador/tareas.txt

//flag para liberar puerto 

uint32_t cicloCPU;
int tiempoSabotaje;
uint32_t proximoPID = 0; 
char * posicionBase;
t_config * config;
int cantidadBloqueados;
char * tipoAlgoritmo;

typedef struct tcb_discordiador{
    uint32_t tid;
    char estado;
    uint32_t posicionX;
    uint32_t posicionY;
    sem_t semaforoTrabajo;
    sem_t termineIO;
    sem_t empeceIO;
    uint32_t pid;
    char * descripcionTarea;
    int parametros;
    int tiempo;
    bool fueExpulsado;
} TCB_DISCORDIADOR;

bool planificacionPausada = false;

int proximoTID = 0;
sem_t semaforoTripulantes; 
sem_t consultarSiHayVacios;
sem_t esperarAlgunTripulante; 
sem_t consultarSiHayVacios2;
sem_t IO;
sem_t gestionarIO;
sem_t cambiarAReady;
sem_t cambiarANuevo;
sem_t cambiarATrabajando;
sem_t cambiarAFinalizado;
sem_t cambiarABloqueado;
sem_t cambiarABloqueadosEmergencia;
sem_t semaforoSabotaje;
sem_t semaforoSabotajeBloqueados;
sem_t mutexPID; 
sem_t semaforoPlanificacionPausada;
sem_t contadorBloqueados;
sem_t estoyListo;
 

t_log * loggerDiscordiador; 
t_list * listaTripulantes;
t_list * listaReady;
t_list * listaBloqueados;
t_list * listaTrabajando;
t_list * listaNuevos;
t_list * listaTerminados;
t_list * tareasDeIO;
t_list * listaTCBsNuevos;
t_list * listaBloqueadosEmergencia;
t_list * listaBloqueadosSabotaje;


uint32_t iniciarPCB(char*, int);
void servidorPrincipal();
void atenderImongo();
int conectarImongo();
int conectarMiRAM();
void cambiarEstadoTripulantesA(char);
void iniciarPatota(char **);
void listarTripulantes();
void consola();
void mandarPaqueteSerializado(t_buffer*,int, int);
void serializarYMandarPCB(char*,int,uint32_t, int, t_list *);
void serializarYMandarInicioTareaIO(int, int, uint32_t);
void serializarYMandarInicioTareaNormal(uint32_t, char*);
void serializarYMandarPedidoDeTarea(int, uint32_t, uint32_t);
void gestionarTarea(char*,int , uint32_t);
void serializarYMandarElegidoDelSabotaje(uint32_t);
int gradoMultitarea;
bool esTareaDeIO(char*);
bool coincideID(TCB_DISCORDIADOR*);
bool haySabotaje = false;
int cantidadDeSabotajes;
void serializarYMandarPosicion(TCB_DISCORDIADOR *);
void ponerATrabajar();
void trasladarseA(uint32_t,uint32_t,TCB_DISCORDIADOR*);
void trasladarseADuranteSabotaje(uint32_t,uint32_t,TCB_DISCORDIADOR*);
void cambiarDeEstado(TCB_DISCORDIADOR *, char);
void pasarTripulante(TCB_DISCORDIADOR *);
void salirDeListaEstado(TCB_DISCORDIADOR *);
void subModuloTripulante(TCB_DISCORDIADOR *);
void gestionadorIO();
void cambiarEstadosABloqueados();
void volverAEstadosPostSabotaje();
bool tripulanteConIDMasChico(TCB_DISCORDIADOR *, TCB_DISCORDIADOR*);
void serializarYMandarNuevoEstado(TCB_DISCORDIADOR*);
void serializaYMandarExpulsado(uint32_t, uint32_t);
TCB_DISCORDIADOR * crearTCB(char *, uint32_t); // chequear lo de la lista
TCB_DISCORDIADOR * tripulanteMasCercano(uint32_t, uint32_t);
void mostrarLista(t_list *); 
void ponerReadyNuevosTripulantes();
char * leerTareas(char *);
void serializarYMandarPedidoDeBitacora(uint32_t);
int socketParaSabotajes;
void expulsarTripulate(TCB_DISCORDIADOR *);
char idMapa(uint32_t);

#endif
