#pragma once

#include <vector>

#include "Grafo.h"

using namespace std;

struct ResultadoRuta
{
    double distanciaTotal;
    double tiempoTotal;

    vector<int> ruta;
};

class RutaOptima
{
public:

    ResultadoRuta rutaPorDistancia(
        const Grafo& grafo,
        int origenReal,
        int destinoReal
    );

    ResultadoRuta rutaPorTiempo(
        const Grafo& grafo,
        int origenReal,
        int destinoReal
    );
};