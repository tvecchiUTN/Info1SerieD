#include <stdio.h>
#include "salidas.h"
#include "entradas.h"
#include "tiempo.h"

#define ON 1
#define OFF 0

#define LLENANDOSE 0
#define LLENO 1
#define EVAL_CRITICO 2
#define CRITICO 3

#define AGUA_FRIA 0
#define AGUA_CALIENTE 1
#define VACIO 2

#define NO_SERVIR 0
#define SIRVIENDO 1


void MdEbomba(int *flag_vacio);
void MdECalefaccion(int flag_vacio, int *flag_servir);
void MdEServir(int flag_servir);

int main(void)
{
    MotorLlenado(OFF);
    Indicador(OFF);
    Calefa(OFF);
    Servicio(OFF);

    int flag_bomba = 0;
    int flag_calef = 0;

    while(1)
    {
        MdEbomba(&flag_bomba);
        MdECalefaccion(flag_bomba, &flag_calef);
        MdEServir(flag_calef);

    }
}

void MdEbomba(int *flag_vacio)
{
    static int stBomba = LLENANDOSE;
    static int critic = ON;

    setTime(0);
    switch(stBomba)
    {
        case LLENANDOSE:
            if(!TanqueLleno())
            {
                MotorLlenado(ON);
            }
            else if(TanqueLleno())
            {
                MotorLlenado(OFF);
                stBomba = LLENO;
            }
            if(TanqueVacio())
            {
                MotorLlenado(ON);
                setTime(120);
                *flag_vacio = ON;
                stBomba = EVAL_CRITICO;
            }

            break;

        case LLENO:
            if(!TanqueLleno())
            {
                MotorLlenado(ON);
                stBomba = LLENANDOSE;
            }
            break;

        case EVAL_CRITICO:
            if(!getTime())
            {
                stBomba = CRITICO;
            }else if(!TanqueVacio())
            {
                *flag_vacio = OFF;
                setTime(0);
                stBomba = LLENANDOSE;
            }
            break;

        case CRITICO:
            if(!TanqueVacio())
            {
                *flag_vacio = OFF;
                stBomba = LLENANDOSE;
            }


            if(!getTime())
            {
                if(critic == ON)
                {
                    setTime(1);
                    Indicador(ON);
                    critic = OFF;
                }
                else
                {
                    setTime(1);
                    Indicador(OFF);
                    critic = ON;
                }
            }

            break;
    }
}

void MdECalefaccion(int flag_vacio, int *flag_servir)
{
    static int stCalefa = AGUA_FRIA;

    switch(stCalefa)
    {
        case AGUA_FRIA:
            if(!TempOK() && (flag_vacio == OFF))
            {
                Calefa(ON);
                *flag_servir = OFF;
            }
            else  if(TempOK() && (flag_vacio == OFF))
            {
                Calefa(OFF);
                *flag_servir = ON;
                stCalefa = AGUA_CALIENTE;
            }

            if(flag_vacio == ON)
            {
                Calefa(OFF);
                stCalefa = VACIO;
            }
            break;

        case AGUA_CALIENTE:
            if(!TempOK())
            {
                Calefa(ON);
                flag_servir = OFF;
                stCalefa = AGUA_FRIA;
            }
            break;

        case VACIO:
            if(flag_vacio == OFF)
            {
                Calefa(ON);
                stCalefa = AGUA_FRIA;
            }
            break;
    }

}

void MdEServir(int flag_servir)
{
    static int stServir = NO_SERVIR;

    switch(stServir)
    {
        case NO_SERVIR:
            if(flag_servir == ON)
            {
                if(BotonServicio())
                {
                    setTime(30);
                    Servicio(ON);
                    stServir = SIRVIENDO;
                }
            }
            break;

        case SIRVIENDO:
            if(!getTime())
            {
                Servicio(OFF);
                stServir = NO_SERVIR;
            }

    }
}
