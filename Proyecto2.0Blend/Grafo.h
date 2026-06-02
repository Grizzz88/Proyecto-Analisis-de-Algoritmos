#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Arista.h"

using namespace std;

class Grafo
{
private:
    unordered_map<int, int> idAIndice;
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

    bool existeNodo(int idReal) const;
    int buscarIndice(int idReal) const;
    int obtenerIdReal(int indice) const;

    const vector<vector<Arista>>& obtenerDirigido() const;
    const vector<vector<Arista>>& obtenerNoDirigido() const;
};