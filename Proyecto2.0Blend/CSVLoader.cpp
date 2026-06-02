#include "CSVLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool CSVLoader::cargarEdges(const string& archivo,Grafo& grafo)
{
    ifstream file(archivo);
    if (!file.is_open())
    {
        cout << "Error al abrir: "
            << archivo
            << endl;

        return false;
    }
    string linea;
    getline(file, linea);
    while (getline(file, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        stringstream ss(linea);
        string osm_id_str;
        string from_str;
        string to_str;
        string distance_str;
        string fclass_str;
        string oneway_str;
        string maxspeed_str;

        getline(ss, osm_id_str, ',');
        getline(ss, from_str, ',');
        getline(ss, to_str, ',');
        getline(ss, distance_str, ',');
        getline(ss, fclass_str, ',');
        getline(ss, oneway_str, ',');
        getline(ss, maxspeed_str, ',');

        EdgeCSV e;

        e.from = stoi(from_str);

        e.to = stoi(to_str);

        e.distancia = stod(distance_str);

        e.fclass = fclass_str;

        e.oneway = (oneway_str == "1");

        if (maxspeed_str.empty())
        {
            e.maxspeed = 0;
        }
        else
        {
            e.maxspeed = stoi(maxspeed_str);
        }

        if (e.maxspeed > 0)
        {
            velocidadesPorClase[e.fclass].push_back(e.maxspeed);
        }

        edges.push_back(e);
    }

    file.close();

    calcularMedianas();

    corregirVelocidades();

    for (const auto& e : edges)
    {
        grafo.agregarArista(e.from,e.to,e.distancia,e.maxspeed,e.oneway,e.fclass);
    }

    return true;
}

void CSVLoader::calcularMedianas()
{
    for (auto& par : velocidadesPorClase)
    {
        string clase = par.first;
        vector<int>& velocidades = par.second;

        sort(velocidades.begin(), velocidades.end());

        int n = static_cast<int>(velocidades.size());
        int mediana;

        if (n % 2 == 0)
        {
            mediana = (velocidades[n / 2 - 1] + velocidades[n / 2]) / 2;
        }
        else
        {
            mediana = velocidades[n / 2];
        }

        medianaPorClase[clase] = mediana;
    }
}

void CSVLoader::corregirVelocidades()
{
    for (auto& e : edges)
    {
        if (e.maxspeed != 0)
        {
            continue;
        }

        auto it =
            medianaPorClase.find(
                e.fclass
            );

        if (it != medianaPorClase.end())
        {
            e.maxspeed =
                it->second;
        }
        else
        {
            e.maxspeed = 30;
        }
    }
}