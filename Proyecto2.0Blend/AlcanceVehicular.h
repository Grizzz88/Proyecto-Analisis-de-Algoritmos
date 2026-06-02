#pragma once
#include "Dijkstra.h"
#include <vector>

#include "Grafo.h"

using namespace std;

class AlcanceVehicular
{
public:
    vector<int> calcularAlcance(
        const Grafo& grafo,
        int nodoOrigenReal,
        double distanciaMaxima
    );
};