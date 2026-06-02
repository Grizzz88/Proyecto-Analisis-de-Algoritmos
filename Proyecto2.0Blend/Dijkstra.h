#pragma once

#include <vector>
#include "Grafo.h"

using namespace std;

enum TipoPeso
{
    DISTANCIA,
    TIEMPO
};

struct ResultadoDijkstra
{
    vector<double> costo;
    vector<int> padre;
};

class Dijkstra
{
public:

    ResultadoDijkstra calcular(
        const Grafo& grafo,
        int nodoOrigenReal,
        TipoPeso tipo
    );
};