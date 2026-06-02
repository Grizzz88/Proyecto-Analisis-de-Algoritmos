#pragma once

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