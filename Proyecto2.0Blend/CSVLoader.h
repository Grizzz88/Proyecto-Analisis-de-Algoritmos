#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Grafo.h"

using namespace std;

struct EdgeCSV
{
    int from;

    int to;

    double distancia;

    string fclass;

    bool oneway;

    int maxspeed;
};

class CSVLoader
{
private:
    vector<EdgeCSV> edges;
    unordered_map<string, vector<int>> velocidadesPorClase;
    unordered_map<string, int> medianaPorClase;
public:
    bool cargarEdges(const string& archivo,Grafo& grafo);
private:
    void calcularMedianas();
    void corregirVelocidades();
};