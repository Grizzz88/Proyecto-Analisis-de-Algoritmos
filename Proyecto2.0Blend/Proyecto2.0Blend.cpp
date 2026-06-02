#include <iostream>
#include <vector>

#include "CSVLoader.h"
#include "Grafo.h"
#include "AlcanceVehicular.h"
#include "IslasViales.h"
#include "DiametroVial.h"
#include "RedEmergenciaMinima.h"
#include "RutaOptima.h"

using namespace std;

int main()
{
    Grafo grafo;
    CSVLoader loader;

    if (!loader.cargarEdges("edges_limpio.csv", grafo))
    {
        cout << "Error cargando archivo CSV." << endl;
        return 1;
    }

    cout << "Nodos: "
        << grafo.cantidadNodos()
        << endl;

    cout << "Aristas dirigidas: "
        << grafo.cantidadAristasDirigidas()
        << endl;

    cout << "Aristas no dirigidas: "
        << grafo.cantidadAristasNoDirigidas()
        << endl;

    // =====================================================
    // OBJETIVO 1
    // =====================================================

    cout << "\n===== OBJETIVO 1: ALCANCE VEHICULAR ====="
        << endl;

    int nodoOrigen;

    cout << "Ingrese el ID real del nodo origen: ";
    cin >> nodoOrigen;

    cout << "Existe nodo? "
        << grafo.existeNodo(nodoOrigen)
        << endl;

    AlcanceVehicular alcance;

    vector<int> nodosAlcanzables =
        alcance.calcularAlcance(
            grafo,
            nodoOrigen,
            5000.0
        );

    cout << "Nodos alcanzables en 5 km: "
        << nodosAlcanzables.size()
        << endl;

    // =====================================================
    // OBJETIVO 2
    // =====================================================

    cout << "\n===== OBJETIVO 2: ISLAS VIALES ====="
        << endl;

    IslasViales islas;

    ResultadoIslas resultadoIslas =
        islas.analizar(grafo);

    cout << "Cantidad total de islas viales: "
        << resultadoIslas.cantidadComponentes
        << endl;

    cout << "Tamaño de la componente gigante: "
        << resultadoIslas.tamanioComponenteGigante
        << " nodos"
        << endl;

    cout << "\nPrimeros nodos de la componente gigante:"
        << endl;

    int limite = min(
        20,
        (int)resultadoIslas.nodosComponenteGigante.size()
    );

    for (int i = 0; i < limite; i++)
    {
        cout
            << resultadoIslas.nodosComponenteGigante[i]
            << endl;
    }

    // =====================================================
    // OBJETIVO 3
    // =====================================================
    cout << "\n===== OBJETIVO 3: DIAMETRO VIAL =====" << endl;

    int tamanioGigante =
        resultadoIslas.tamanioComponenteGigante;

    if (tamanioGigante <= 1000)
    {
        cout << "Modo exacto." << endl;

        DiametroVial diametro;

        ResultadoDiametro resultadoDiametro =
            diametro.calcularDiametro(
                grafo,
                resultadoIslas.nodosComponenteGigante
            );

        cout << "Nodo origen: "
            << resultadoDiametro.nodoOrigenReal
            << endl;

        cout << "Nodo destino: "
            << resultadoDiametro.nodoDestinoReal
            << endl;

        cout << "Distancia minima mas larga: "
            << resultadoDiametro.distanciaMaxima
            << " metros"
            << endl;
    }
    else
    {
        cout << "Componente gigante demasiado grande ("
            << tamanioGigante
            << " nodos)." << endl;

        cout << "Se omite el calculo exacto del diametro."
            << endl;

        cout << "Para datasets grandes se recomienda "
            << "usar una aproximacion."
            << endl;
    }
    // =====================================================
    // OBJETIVO 4
    // =====================================================

    cout << "\n===== OBJETIVO 4: RED DE EMERGENCIA MINIMA ====="
        << endl;

    RedEmergenciaMinima redEmergencia;

    ResultadoMST resultadoMST =
        redEmergencia.calcularMST(
            grafo,
            resultadoIslas.nodosComponenteGigante
        );

    cout << "Aristas usadas en el MST: "
        << resultadoMST.cantidadAristasUsadas
        << endl;

    cout << "Distancia total cubierta: "
        << resultadoMST.distanciaTotalMetros
        << " metros"
        << endl;

    cout << "Distancia total cubierta: "
        << resultadoMST.distanciaTotalKm
        << " km"
        << endl;

    cout << "\nPrimeras aristas del MST:"
        << endl;

    int limiteMST =
        min(
            20,
            (int)resultadoMST.aristas.size()
        );

    for (int i = 0; i < limiteMST; i++)
    {
        cout
            << grafo.obtenerIdReal(
                resultadoMST.aristas[i].origen
            )
            << " -> "
            << grafo.obtenerIdReal(
                resultadoMST.aristas[i].destino
            )
            << " | distancia: "
            << resultadoMST.aristas[i].distancia
            << " m"
            << endl;
    }

    cout << "\n===== BONUS: RUTA OPTIMA =====" << endl;

    int origen;
    int destino;

    cout << "Nodo origen: ";
    cin >> origen;

    cout << "Nodo destino: ";
    cin >> destino;

    RutaOptima rutas;

    ResultadoRuta rutaDistancia =
        rutas.rutaPorDistancia(
            grafo,
            origen,
            destino
        );

    ResultadoRuta rutaTiempo =
        rutas.rutaPorTiempo(
            grafo,
            origen,
            destino
        );
    cout << "\n===== COMPARACION =====" << endl;

    cout << "\nRuta por distancia" << endl;

    cout << "\nDistancia: "
        << rutaDistancia.distanciaTotal / 1000.0
        << " km" << endl;

    cout << "Tiempo: "
        << rutaDistancia.tiempoTotal / 60.0
        << " h" << endl;

    cout << "\nRuta por tiempo" << endl;

    cout << "\nDistancia: "
        << rutaTiempo.distanciaTotal / 1000.0
        << " km" << endl;

    cout << "Tiempo: "
        << rutaTiempo.tiempoTotal / 60.0
        << " h" << endl;

    double diferenciaKm =
        (rutaTiempo.distanciaTotal -
            rutaDistancia.distanciaTotal) / 1000.0;

    double diferenciaHoras =
        (rutaTiempo.tiempoTotal -
            rutaDistancia.tiempoTotal) / 60.0;

    cout << "\nDiferencia:" << endl;

    cout << (diferenciaKm >= 0 ? "+" : "")
        << diferenciaKm
        << " km" << endl;

    cout << (diferenciaHoras >= 0 ? "+" : "")
        << diferenciaHoras
        << " h" << endl;
    return 0;
}