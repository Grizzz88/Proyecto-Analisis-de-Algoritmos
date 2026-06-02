#include "DiametroVial.h"
#include "Dijkstra.h"

#include <limits>

using namespace std;

ResultadoDiametro DiametroVial::calcularDiametro(
    const Grafo& grafo,
    const vector<int>& nodosComponenteGigante
)
{
    ResultadoDiametro resultado;

    resultado.distanciaMaxima = 0.0;

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