#include "Grafo.h"

int Grafo::obtenerIndice(int idReal)
{
    auto it = idAIndice.find(idReal);
    if (it != idAIndice.end())
    {
        return it->second;
    }
    int nuevoIndice = static_cast<int>(indiceAId.size());
    idAIndice[idReal] = nuevoIndice;
    indiceAId.push_back(idReal);
    dirigido.push_back(vector<Arista>());
    noDirigido.push_back(vector<Arista>());
    return nuevoIndice;
}

void Grafo::agregarArista(int origenReal,int destinoReal,double distancia,int velocidad,bool oneway,const string& tipoVia)
{
    int origen = obtenerIndice(origenReal);

    int destino = obtenerIndice(destinoReal);

    double tiempo = (distancia / 1000.0)/velocidad*60.0;
    Arista a;

    a.destino = destino;

    a.distancia = distancia;

    a.velocidad = velocidad;

    a.tiempo = tiempo;

    a.oneway = oneway;

    a.tipoVia = tipoVia;

    dirigido[origen].push_back(a);

    if (!oneway)
    {
        Arista inversa = a;

        inversa.destino = origen;

        dirigido[destino].push_back(inversa);
    }

    noDirigido[origen].push_back(a);

    Arista inversa = a;

    inversa.destino = origen;

    noDirigido[destino].push_back(inversa);
}

int Grafo::cantidadNodos() const
{
    return indiceAId.size();
}

int Grafo::cantidadAristasDirigidas() const
{
    int total = 0;

    for (const auto& lista : dirigido)
    {
        total += lista.size();
    }

    return total;
}

int Grafo::cantidadAristasNoDirigidas() const
{
    int total = 0;

    for (const auto& lista : noDirigido)
    {
        total += lista.size();
    }

    return total;
}
bool Grafo::existeNodo(int idReal) const
{
    return idAIndice.find(idReal) != idAIndice.end();
}

int Grafo::buscarIndice(int idReal) const
{
    auto it = idAIndice.find(idReal);

    if (it == idAIndice.end())
    {
        return -1;
    }

    return it->second;
}

int Grafo::obtenerIdReal(int indice) const
{
    return indiceAId[indice];
}

const vector<vector<Arista>>& Grafo::obtenerDirigido() const
{
    return dirigido;
}

const vector<vector<Arista>>& Grafo::obtenerNoDirigido() const
{
    return noDirigido;
}