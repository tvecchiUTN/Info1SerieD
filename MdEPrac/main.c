#include <stdio.h>
#include "salidas.h"
#include "entradas.h"
#include "tiempo.h"

#define ON 1
#define OFF 0

#define DESCARGA 0
#define CARGA 1
#define CALEFACCION 2

int main(void)
{
    int estadoMaq = CARGA;

    MotorLlenado(OFF);
    Indicador(OFF);
    Calefa(OFF);
    Servicio(OFF);

    setTime(1);
    while(1)
    {
        switch(estadoMaq)
        {
            case DESCARGA:

                if(!getTime())
                {
                    if(BotonServicio())
                    {
                        Servicio(ON);
                        Indicador(OFF);
                        setTimer(30000);
                    }

                    if(!TanqueLleno)
                    {
                        Servicio(OFF);
                        estadoMaq = CARGA;
                    }

                }
                break;
            case CARGA:

                if(TanqueVacio)
                {
                    MotorLlenado(ON);
                    Calefa(OFF);
                }else if(!TanqueVacio && !TanqueLleno)
                {
                    MotorLlenado(ON);
                }else if(TanqueLleno)
                {
                    MotorLlenado(OFF);
                    estadoMaq = CALEFACCION;
                }

                break;
            case CALEFACCION:
                if(!TempOK)
                {
                    Calefa(ON);
                    Indicador(OFF);
                }
                else if(TempOK)
                {
                    Indicador(ON);
                    estadoMaq = DESCARGA;
                }
                break;

        }


    }

}
