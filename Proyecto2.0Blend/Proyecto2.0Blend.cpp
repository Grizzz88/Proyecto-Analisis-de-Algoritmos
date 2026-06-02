#include <iostream>
#include <vector>

#include "CSVLoader.h"
#include "Grafo.h"
#include "AlcanceVehicular.h"
#include "IslasViales.h"
#include "DiametroVial.h"
#include "RedEmergenciaMinima.h"


using namespace std;

int main()
{
    Grafo grafo;

    CSVLoader loader;

    // Cargar edges limpios
    if (!loader.cargarEdges("edges_limpio.csv", grafo))
    {
        return 1;
    }

    cout << "Nodos: " << grafo.cantidadNodos() << endl;
    cout << "Aristas dirigidas: " << grafo.cantidadAristasDirigidas() << endl;
    cout << "Aristas no dirigidas: " << grafo.cantidadAristasNoDirigidas() << endl;

    cout << "\n===== OBJETIVO 1: ALCANCE VEHICULAR =====" << endl;

    int nodoOrigen;
    cout << "Ingrese el ID real del nodo origen: ";
    cin >> nodoOrigen;

    AlcanceVehicular alcance;
    vector<int> nodosAlcanzables = alcance.calcularAlcance(
        grafo,
        nodoOrigen,
        5000.0 // 5 km
    );

    cout << "Nodos alcanzables en 5 km: " << nodosAlcanzables.size() << endl;

    cout << "\n===== OBJETIVO 2: ISLAS VIALES =====" << endl;

    IslasViales islas;
    ResultadoIslas resultadoIslas = islas.analizar(grafo);

    cout << "Cantidad total de islas viales: " << resultadoIslas.cantidadComponentes << endl;
    cout << "Tamaño de la componente gigante: " << resultadoIslas.tamanioComponenteGigante << " nodos" << endl;

    cout << "Primeros nodos de la componente gigante:" << endl;
    int limite = 20;
    if ((int)resultadoIslas.nodosComponenteGigante.size() < limite)
        limite = (int)resultadoIslas.nodosComponenteGigante.size();

    for (int i = 0; i < limite; i++)
        cout << resultadoIslas.nodosComponenteGigante[i] << endl;

    
    cout << "\n===== OBJETIVO 4: RED DE EMERGENCIA MINIMA =====" << endl;

    RedEmergenciaMinima redEmergencia;
    ResultadoMST resultadoMST =
        redEmergencia.calcularMST(
            grafo,
            resultadoIslas.nodosComponenteGigante
        );

    cout << "Aristas usadas en el MST: " << resultadoMST.cantidadAristasUsadas << endl;
    cout << "Distancia total cubierta: " << resultadoMST.distanciaTotalMetros << " metros" << endl;
    cout << "Distancia total cubierta: " << resultadoMST.distanciaTotalKm << " km" << endl;

    cout << "Primeras aristas del MST:" << endl;
    int limiteMST = 20;
    if ((int)resultadoMST.aristas.size() < limiteMST)
        limiteMST = (int)resultadoMST.aristas.size();

    for (int i = 0; i < limiteMST; i++)
    {
        cout << grafo.obtenerIdReal(resultadoMST.aristas[i].origen)
            << " -> "
            << grafo.obtenerIdReal(resultadoMST.aristas[i].destino)
            << " | distancia: "
            << resultadoMST.aristas[i].distancia
            << " m" << endl;
    }


    return 0;
}