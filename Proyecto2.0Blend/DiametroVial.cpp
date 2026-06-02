#include "DiametroVial.h"
#include "Dijkstra.h"

#include <limits>
#include <random>
#include <algorithm>

using namespace std;

ResultadoDiametro DiametroVial::calcularDiametro(
    const Grafo& grafo,
    const vector<int>& nodosComponenteGigante
)
{
    ResultadoDiametro resultado;

    resultado.distanciaMaxima = 0.0;
    resultado.nodoOrigenReal = -1;
    resultado.nodoDestinoReal = -1;

    for (int origenReal : nodosComponenteGigante)
    {
        Dijkstra dijkstra;

        ResultadoDijkstra resultadoDijkstra =
            dijkstra.calcular(
                grafo,
                origenReal,
                DISTANCIA
            );

        const vector<double>& distancia =
            resultadoDijkstra.costo;

        for (int i = 0; i < grafo.cantidadNodos(); i++)
        {
            if (
                distancia[i] <
                numeric_limits<double>::max()
                &&
                distancia[i] >
                resultado.distanciaMaxima
                )
            {
                resultado.distanciaMaxima =
                    distancia[i];

                resultado.nodoOrigenReal =
                    origenReal;

                resultado.nodoDestinoReal =
                    grafo.obtenerIdReal(i);
            }
        }
    }

    return resultado;
}

ResultadoDiametro DiametroVial::calcularDiametroSampling(
    const Grafo& grafo,
    const vector<int>& nodosComponenteGigante,
    int cantidadMuestras
)
{
    ResultadoDiametro resultado;

    resultado.distanciaMaxima = 0.0;
    resultado.nodoOrigenReal = -1;
    resultado.nodoDestinoReal = -1;

    int totalNodos =
        (int)nodosComponenteGigante.size();

    if (totalNodos == 0)
    {
        return resultado;
    }

    cantidadMuestras =
        min(cantidadMuestras, totalNodos);

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<>
        distribucion(0, totalNodos - 1);

    for (int muestra = 0;
        muestra < cantidadMuestras;
        muestra++)
    {
        int indiceAleatorio =
            distribucion(gen);

        int origenReal =
            nodosComponenteGigante[indiceAleatorio];

        Dijkstra dijkstra;

        ResultadoDijkstra resultadoDijkstra =
            dijkstra.calcular(
                grafo,
                origenReal,
                DISTANCIA
            );

        const vector<double>& distancia =
            resultadoDijkstra.costo;

        for (int i = 0; i < grafo.cantidadNodos(); i++)
        {
            if (
                distancia[i] <
                numeric_limits<double>::max()
                &&
                distancia[i] >
                resultado.distanciaMaxima
                )
            {
                resultado.distanciaMaxima =
                    distancia[i];

                resultado.nodoOrigenReal =
                    origenReal;

                resultado.nodoDestinoReal =
                    grafo.obtenerIdReal(i);
            }
        }
    }

    return resultado;
}