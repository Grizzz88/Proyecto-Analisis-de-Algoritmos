#include "Dijkstra.h"

#include "RutaOptima.h"
#include <queue>
#include <limits>

using namespace std;

struct EstadoDijkstra
{
    int nodo;
    double costo;
};

struct CompararEstadoDijkstra
{
    bool operator()(
        const EstadoDijkstra& a,
        const EstadoDijkstra& b
        )
    {
        return a.costo > b.costo;
    }
};

ResultadoDijkstra Dijkstra::calcular(
    const Grafo& grafo,
    int nodoOrigenReal,
    TipoPeso tipo
)
{
    ResultadoDijkstra resultado;

    int origen =
        grafo.buscarIndice(nodoOrigenReal);

    int n =
        grafo.cantidadNodos();

    resultado.costo.assign(
        n,
        numeric_limits<double>::max()
    );

    resultado.padre.assign(
        n,
        -1
    );

    priority_queue<
        EstadoDijkstra,
        vector<EstadoDijkstra>,
        CompararEstadoDijkstra
    > cola;

    resultado.costo[origen] = 0.0;

    cola.push({
        origen,
        0.0
        });

    const vector<vector<Arista>>& dirigido =
        grafo.obtenerDirigido();

    while (!cola.empty())
    {
        EstadoDijkstra actual =
            cola.top();

        cola.pop();

        if (actual.costo >
            resultado.costo[actual.nodo])
        {
            continue;
        }

        for (const Arista& arista :
            dirigido[actual.nodo])
        {
            double peso;

            if (tipo == DISTANCIA)
            {
                peso = arista.distancia;
            }
            else
            {
                peso = arista.tiempo;
            }

            double nuevoCosto =
                actual.costo + peso;

            if (nuevoCosto <
                resultado.costo[arista.destino])
            {
                resultado.costo[arista.destino] =
                    nuevoCosto;

                resultado.padre[arista.destino] =
                    actual.nodo;

                cola.push({
                    arista.destino,
                    nuevoCosto
                    });
            }
        }
    }

    return resultado;
}