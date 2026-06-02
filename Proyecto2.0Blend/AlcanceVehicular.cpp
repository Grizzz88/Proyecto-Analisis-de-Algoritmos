#include "AlcanceVehicular.h"
#include "Dijkstra.h"

#include <iostream>

using namespace std;

vector<int> AlcanceVehicular::calcularAlcance(
    const Grafo& grafo,
    int nodoOrigenReal,
    double distanciaMaxima
)
{
    vector<int> alcanzables;

    if (!grafo.existeNodo(nodoOrigenReal))
    {
        cout << "El nodo origen no existe en el grafo." << endl;
        return alcanzables;
    }

    Dijkstra dijkstra;

    ResultadoDijkstra resultado =
        dijkstra.calcular(
            grafo,
            nodoOrigenReal,
            DISTANCIA
        );

    const vector<double>& distancia =
        resultado.costo;

    for (int i = 0; i < grafo.cantidadNodos(); i++)
    {
        if (distancia[i] <= distanciaMaxima)
        {
            alcanzables.push_back(
                grafo.obtenerIdReal(i)
            );
        }
    }

    return alcanzables;
}