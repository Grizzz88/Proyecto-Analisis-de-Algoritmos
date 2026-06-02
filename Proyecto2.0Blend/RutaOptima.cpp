#include "RutaOptima.h"
#include "Dijkstra.h"

#include <algorithm>

using namespace std;

static vector<int> reconstruirRuta(
    const Grafo& grafo,
    int destinoIndice,
    const vector<int>& padre
)
{
    vector<int> ruta;

    int actual = destinoIndice;

    while (actual != -1)
    {
        ruta.push_back(
            grafo.obtenerIdReal(actual)
        );

        actual = padre[actual];
    }

    reverse(
        ruta.begin(),
        ruta.end()
    );

    return ruta;
}

static void calcularMetricasRuta(
    const Grafo& grafo,
    ResultadoRuta& ruta
)
{
    ruta.distanciaTotal = 0.0;
    ruta.tiempoTotal = 0.0;

    const vector<vector<Arista>>& dirigido =
        grafo.obtenerDirigido();

    for (size_t i = 0; i + 1 < ruta.ruta.size(); i++)
    {
        int origen =
            grafo.buscarIndice(ruta.ruta[i]);

        int destino =
            grafo.buscarIndice(ruta.ruta[i + 1]);

        for (const Arista& arista : dirigido[origen])
        {
            if (arista.destino == destino)
            {
                ruta.distanciaTotal +=
                    arista.distancia;

                ruta.tiempoTotal +=
                    arista.tiempo;

                break;
            }
        }
    }
}

ResultadoRuta RutaOptima::rutaPorDistancia(
    const Grafo& grafo,
    int origenReal,
    int destinoReal
)
{
    Dijkstra dijkstra;

    ResultadoDijkstra resultado =
        dijkstra.calcular(
            grafo,
            origenReal,
            DISTANCIA
        );

    ResultadoRuta ruta;

    int destinoIndice =
        grafo.buscarIndice(destinoReal);

    ruta.ruta =
        reconstruirRuta(
            grafo,
            destinoIndice,
            resultado.padre
        );

    calcularMetricasRuta(
        grafo,
        ruta
    );

    return ruta;
}

ResultadoRuta RutaOptima::rutaPorTiempo(
    const Grafo& grafo,
    int origenReal,
    int destinoReal
)
{
    Dijkstra dijkstra;

    ResultadoDijkstra resultado =
        dijkstra.calcular(
            grafo,
            origenReal,
            TIEMPO
        );

    ResultadoRuta ruta;

    int destinoIndice =
        grafo.buscarIndice(destinoReal);

    ruta.ruta =
        reconstruirRuta(
            grafo,
            destinoIndice,
            resultado.padre
        );

    calcularMetricasRuta(
        grafo,
        ruta
    );

    return ruta;
}