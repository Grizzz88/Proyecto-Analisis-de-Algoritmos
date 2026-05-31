#pragma once

#include <vector>
#include <unordered_map>

#include "Arista.h"

using namespace std;

class Grafo
{
private:

    // Conversión:
    // id real -> índice interno

    unordered_map<int, int> idAIndice;

    // índice interno -> id real

    vector<int> indiceAId;

    vector<vector<Arista>> dirigido;

    vector<vector<Arista>> noDirigido;

public:

    int obtenerIndice(int idReal);

    void agregarArista(
        int origenReal,
        int destinoReal,
        double distancia,
        int velocidad,
        bool oneway,
        const string& tipoVia
    );

    int cantidadNodos() const;

    int cantidadAristasDirigidas() const;

    int cantidadAristasNoDirigidas() const;
};