#include "DiametroVial.h"
#include <queue>
#include <limits>
#include <iostream>

struct Estado
{
    int nodo;
    double distancia;
};

struct CompararEstado
{
    bool operator()(const Estado& a, const Estado& b)
    {
        return a.distancia > b.distancia;
    }
};

ResultadoDiametro DiametroVial::calcularDiametro(
    const Grafo& grafo,
    const vector<int>& nodosComponenteGigante
)
{
    ResultadoDiametro resultado;
    resultado.distanciaMaxima = 0.0;

    const vector<vector<Arista>>& dirigido = grafo.obtenerDirigido();

    // Convertir IDs reales a índices internos
    vector<int> indices;
    for (int idReal : nodosComponenteGigante)
        indices.push_back(grafo.buscarIndice(idReal));

    // Para cada nodo de la componente gigante
    for (int origenIndice : indices)
    {
        vector<double> distancia(grafo.cantidadNodos(),
            numeric_limits<double>::max());

        priority_queue<Estado, vector<Estado>, CompararEstado> cola;

        distancia[origenIndice] = 0.0;
        cola.push({ origenIndice, 0.0 });

        while (!cola.empty())
        {
            Estado actual = cola.top();
            cola.pop();

            if (actual.distancia > distancia[actual.nodo])
                continue;

            for (const Arista& arista : dirigido[actual.nodo])
            {
                double nuevaDist = actual.distancia + arista.distancia;
                if (nuevaDist < distancia[arista.destino])
                {
                    distancia[arista.destino] = nuevaDist;
                    cola.push({ arista.destino, nuevaDist });
                }
            }
        }

        // Buscar distancia máxima desde este nodo
        for (int i = 0; i < grafo.cantidadNodos(); i++)
        {
            if (distancia[i] < numeric_limits<double>::max() &&
                distancia[i] > resultado.distanciaMaxima)
            {
                resultado.distanciaMaxima = distancia[i];
                resultado.nodoOrigenReal = grafo.obtenerIdReal(origenIndice);
                resultado.nodoDestinoReal = grafo.obtenerIdReal(i);
            }
        }
    }

    return resultado;
}