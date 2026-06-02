#pragma once

#include <vector>

#include "Grafo.h"

using namespace std;

struct ResultadoDiametro
{
    int nodoOrigenReal;
    int nodoDestinoReal;
    double distanciaMaxima;
};

class DiametroVial
{
public:

    ResultadoDiametro calcularDiametro(
        const Grafo& grafo,
        const vector<int>& nodosComponenteGigante
    );

    ResultadoDiametro calcularDiametroSampling(
        const Grafo& grafo,
        const vector<int>& nodosComponenteGigante,
        int cantidadMuestras
    );
};