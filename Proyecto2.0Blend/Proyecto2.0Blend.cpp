#include <iostream>

#include "CSVLoader.h"
#include "Grafo.h"

using namespace std;

int main()
{
    Grafo grafo;

    CSVLoader loader;

    if (!loader.cargarEdges(
        "edges_prueba.csv",
        grafo
    ))
    {
        return 1;
    }

    cout
        << "Nodos: "
        << grafo.cantidadNodos()
        << endl;

    cout
        << "Aristas dirigidas: "
        << grafo.cantidadAristasDirigidas()
        << endl;

    cout
        << "Aristas no dirigidas: "
        << grafo.cantidadAristasNoDirigidas()
        << endl;

    return 0;
}