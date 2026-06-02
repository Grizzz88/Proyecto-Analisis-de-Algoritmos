#include "AlcanceVehicular.h"

#include <queue>
#include <limits>
#include <iostream>

using namespace std;

struct EstadoAlcance
{
    int nodo;
    double distancia;
};

struct CompararEstadoAlcance
{
    bool operator()(const EstadoAlcance& a, const EstadoAlcance& b)
    {
        return a.distancia > b.distancia;
    }
};

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

    int cantidadNodos = grafo.cantidadNodos();

    vector<double> distancia(
        cantidadNodos,
        numeric_limits<double>::max()
    );

    priority_queue<
        EstadoAlcance,
        vector<EstadoAlcance>,
        CompararEstadoAlcance
    > cola;

    int origen = grafo.buscarIndice(nodoOrigenReal);

    distancia[origen] = 0.0;

    cola.push({ origen, 0.0 });

    const vector<vector<Arista>>& dirigido = grafo.obtenerDirigido();

    while (!cola.empty())
    {
        EstadoAlcance actual = cola.top();
        cola.pop();

        if (actual.distancia > distancia[actual.nodo])
        {
            continue;
        }

        if (actual.distancia > distanciaMaxima)
        {
            continue;
        }

        for (const Arista& arista : dirigido[actual.nodo])
        {
            double nuevaDistancia =
                actual.distancia + arista.distancia;

            if (nuevaDistancia <= distanciaMaxima &&
                nuevaDistancia < distancia[arista.destino])
            {
                distancia[arista.destino] = nuevaDistancia;

                cola.push({
                    arista.destino,
                    nuevaDistancia
                    });
            }
        }
    }

    for (int i = 0; i < cantidadNodos; i++)
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