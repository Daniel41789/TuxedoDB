#include <stdio.h>
#include <string.h>
#include <atmi.h>
#include <fml32.h>
#include "biblioBD.fml.h"

typedef struct hospital{
    int id;
    char nombre[20];
    char apellido[20];
    char telefono[10];
}hospital;

int main(int argc, char **argv)
{
    int ivL_resLlamd;
    long ivL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;
    FBFR32 *recv;
    FLDLEN32 flen;
    char msgbuf[64];

    hospital hos;
}


