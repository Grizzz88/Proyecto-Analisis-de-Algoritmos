#include "RedEmergenciaMinima.h"
#include <algorithm>
#include <unordered_set>

using namespace std;

class UnionFind
{
private:
    vector<int> padre;
    vector<int> rango;

public:
    UnionFind(int n)
    {
        padre.resize(n);
        rango.resize(n, 0);

        for (int i = 0; i < n; i++)
        {
            padre[i] = i;
        }
    }

    int encontrar(int x)
    {
        if (padre[x] != x)
            padre[x] = encontrar(padre[x]);
        return padre[x];
    }

    bool unir(int a, int b)
    {
        int raizA = encontrar(a);
        int raizB = encontrar(b);

        if (raizA == raizB)
            return false;

        if (rango[raizA] < rango[raizB])
            padre[raizA] = raizB;
        else if (rango[raizA] > rango[raizB])
            padre[raizB] = raizA;
        else
        {
            padre[raizB] = raizA;
            rango[raizA]++;
        }

        return true;
    }
};

ResultadoMST RedEmergenciaMinima::calcularMST(
    const Grafo& grafo,
    const vector<int>& nodosComponenteGigante
)
{
    ResultadoMST resultado;
    resultado.distanciaTotalMetros = 0.0;
    resultado.distanciaTotalKm = 0.0;
    resultado.cantidadAristasUsadas = 0;

    vector<int> indicesGigante;
    unordered_set<int> perteneceGigante;

    for (int idReal : nodosComponenteGigante)
    {
        int indice = grafo.buscarIndice(idReal);
        if (indice != -1)
        {
            indicesGigante.push_back(indice);
            perteneceGigante.insert(indice);
        }
    }

    vector<AristaMST> aristasCandidatas;
    const vector<vector<Arista>>& noDirigido = grafo.obtenerNoDirigido();

    // Construir lista de aristas candidatas
    for (int origen : indicesGigante)
    {
        for (const Arista& arista : noDirigido[origen])
        {
            int destino = arista.destino;
            if (perteneceGigante.find(destino) == perteneceGigante.end())
                continue;

            if (origen < destino) // evita duplicados
            {
                AristaMST nuevaArista;
                nuevaArista.origen = origen;
                nuevaArista.destino = destino;
                nuevaArista.distancia = arista.distancia;
                aristasCandidatas.push_back(nuevaArista);
            }
        }
    }

    sort(aristasCandidatas.begin(), aristasCandidatas.end(),
        [](const AristaMST& a, const AristaMST& b)
        { return a.distancia < b.distancia; });

    UnionFind unionFind(grafo.cantidadNodos());
    int nodosNecesarios = static_cast<int>(indicesGigante.size());

    for (const AristaMST& arista : aristasCandidatas)
    {
        if (unionFind.unir(arista.origen, arista.destino))
        {
            resultado.aristas.push_back(arista);
            resultado.distanciaTotalMetros += arista.distancia;
            resultado.cantidadAristasUsadas++;

            if (resultado.cantidadAristasUsadas == nodosNecesarios - 1)
                break;
        }
    }

    resultado.distanciaTotalKm = resultado.distanciaTotalMetros / 1000.0;
    return resultado;
}