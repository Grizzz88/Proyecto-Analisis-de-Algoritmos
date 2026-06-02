#include "IslasViales.h"

#include <queue>
#include <iostream>

using namespace std;

ResultadoIslas IslasViales::analizar(const Grafo& grafo)
{
    ResultadoIslas resultado;

    resultado.cantidadComponentes = 0;
    resultado.tamanioComponenteGigante = 0;

    int cantidadNodos = grafo.cantidadNodos();

    vector<bool> visitado(cantidadNodos, false);

    const vector<vector<Arista>>& noDirigido =
        grafo.obtenerNoDirigido();

    for (int i = 0; i < cantidadNodos; i++)
    {
        if (visitado[i])
        {
            continue;
        }

        resultado.cantidadComponentes++;

        vector<int> componenteActual;

        queue<int> cola;

        visitado[i] = true;

        cola.push(i);

        while (!cola.empty())
        {
            int actual = cola.front();
            cola.pop();

            componenteActual.push_back(actual);

            for (const Arista& arista : noDirigido[actual])
            {
                int vecino = arista.destino;

                if (!visitado[vecino])
                {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }

        int tamanioActual =
            static_cast<int>(componenteActual.size());

        resultado.tamaniosComponentes.push_back(tamanioActual);

        if (tamanioActual > resultado.tamanioComponenteGigante)
        {
            resultado.tamanioComponenteGigante = tamanioActual;

            resultado.nodosComponenteGigante.clear();

            for (int indiceInterno : componenteActual)
            {
                resultado.nodosComponenteGigante.push_back(
                    grafo.obtenerIdReal(indiceInterno)
                );
            }
        }
    }

    return resultado;
}