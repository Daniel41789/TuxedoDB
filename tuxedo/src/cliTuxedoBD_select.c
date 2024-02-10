#include <stdio.h>
#include <string.h>
#include <atmi.h>
#include <fml32.h>
#include "biblioBD.fml.h"

typedef struct hospital{
    int idDoctor;
    char nombre[20];
    char apellido[20];
    char especialidad[20];
}hospital;

int main(int argc, char **argv)
{
    int ivL_resLlamd;
    int ivL_numOcurr;
    int ivL_iterador;
    long ivL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];
    char zaL_hosNombre[20];
    hospital *spL_hosRegis;

    hospital hos;

    printf("*************************************************\n");
    printf("Doctor : "); scanf("%s", zaL_hosNombre);
    printf("*************************************************\n");

    printf("Conectamos con la aplicación");
    if(tpinit((TPINIT *) NULL) == -1){
        printf("Error en la conexión, tperrno = %d \n", tperrno);
        return(1);
    }

    //Reservamos espacio para el buffer FML
    printf("Reservamos espacio para los buffers FML\n");
    if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
        printf("Error reservando espacio para Buffer fbfrn");
        tpterm();
        return(1);
    }

    if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
        printf("Error Reservando espacio para Buffer recv\n");
        tpterm();
        return(1);
    }

    /*Manejo del Buffer FML*/
    printf ("\nInsertamos datos en buffer FML.");
    if(Fadd32 (fbfr, NOMBRE, zaL_hosNombre, 0) < 0){
        printf ("\n\tError insertando campo FML (NOMBRE)");
        tpfree((char*)fbfr);
        tpterm();
        return (0);
    }

    printf("Nombre del doctor insertado en el buffer FML: %s\n", zaL_hosNombre);


    //Invocamos al servicio    
    printf("Llamada al servicio 'select_Negocio_FML'\n");
    if(tpcall("select_Negocio_FML", (char *)fbfr, 0, (char **)&recv, &ivL_tamLongt, 0L) == -1){
        printf("\n Error en la llamada al servicio: tperrno = %d\n", tperrno);
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return (1);
    }

    if((ivL_numOcurr = Foccur32(recv, NOMBRE)) < 0)
    {
        printf("Error en Foccur32\n");
        tpfree((char *)fbfr);
        tpfree((char *)recv);
        tpterm();
        return (1); 
    }

    printf("Numero de ocurrencias: %d\n", ivL_numOcurr);
    spL_hosRegis = (hospital *) malloc(sizeof(hospital) * ivL_numOcurr);

    flen = sizeof(msgbuf);
    printf("Respuesta del servidor para el doctor: %s\n", zaL_hosNombre);
    for(ivL_iterador = 0;ivL_iterador < ivL_numOcurr; ivL_iterador++)
    {
        printf("Numero de registro: %d\n", (ivL_iterador + 1));
        Fget32(recv, IDDOCTOR, ivL_iterador, (char *)&spL_hosRegis[ivL_iterador].idDoctor,0);
        printf("Id del doctor : %d\n", spL_hosRegis[ivL_iterador].idDoctor);
        
        Fget32(recv, NOMBRE, ivL_iterador, (char *)spL_hosRegis[ivL_iterador].nombre,0);
        printf("Apellido del Doctor: %s\n", spL_hosRegis[ivL_iterador].nombre);
        
        Fget32(recv, ESPECIALIDAD, ivL_iterador, (char *)spL_hosRegis[ivL_iterador].especialidad,0);
        printf("Especialidad: %s\n", spL_hosRegis[ivL_iterador].especialidad);
        
    }

    // Liberamos el buffer y desconectamos de la aplicacion
    printf("Liberamos Buffer y desconectamos de la aplicacion\n");
    tpfree((char *)fbfr);
    tpfree((char *)recv);
    tpterm();
    return 0;
}


// SELECT
