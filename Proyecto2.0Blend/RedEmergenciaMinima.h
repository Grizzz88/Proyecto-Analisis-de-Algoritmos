#pragma once

#include <vector>
#include "Grafo.h"

using namespace std;

struct AristaMST
{
    int origen;
    int destino;
    double distancia;
};

struct ResultadoMST
{
    double distanciaTotalMetros;
    double distanciaTotalKm;
    int cantidadAristasUsadas;

    vector<AristaMST> aristas;
};

class RedEmergenciaMinima
{
public:
    ResultadoMST calcularMST(
        const Grafo& grafo,
        const vector<int>& nodosComponenteGigante
    );
};