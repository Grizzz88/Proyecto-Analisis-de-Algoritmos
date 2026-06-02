#pragma once

#include <vector>

#include "Grafo.h"

using namespace std;

struct ResultadoIslas
{
    int cantidadComponentes;

    int tamanioComponenteGigante;

    vector<int> nodosComponenteGigante;

    vector<int> tamaniosComponentes;
};

class IslasViales
{
public:
    ResultadoIslas analizar(const Grafo& grafo);
};