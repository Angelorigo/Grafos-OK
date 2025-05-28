#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

// ARISTAS (peso, nodo1, nodo2)
typedef tuple<int, char, char> Arista;

// GRAFO 
vector<Arista> aristas = {
    {75, 'A', 'D'}, {14, 'A', 'S'}, {27, 'A', 'B'}, {87, 'A', 'E'},
    {16, 'B', 'S'}, {21, 'B', 'C'}, {86, 'B', 'F'}, {13, 'C', 'S'},
    {29, 'C', 'D'}, {100, 'C', 'G'}, {12, 'D', 'S'}, {75, 'D', 'H'},
    {24, 'E', 'F'}, {81, 'E', 'I'}, {22, 'F', 'G'}, {97, 'F', 'J'},
    {23, 'G', 'H'}, {83, 'G', 'K'}, {91, 'H', 'L'}, {12, 'I', 'J'},
    {131, 'J', 'K'}, {16, 'K', 'L'}};

// ALGORITMO DE KRUSKAL
map<char, char> parent;

char find(char x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];}

void unionSets(char x, char y) {
    parent[find(x)] = find(y);}

void kruskal() {
    for (auto [peso, u, v] : aristas) {
        parent[u] = u;
        parent[v] = v;}

    sort(aristas.begin(), aristas.end());

    cout << "\nMST usando Kruskal:\n";
    int total = 0;
    for (auto [peso, u, v] : aristas) {
        if (find(u) != find(v)) {
            unionSets(u, v);
            cout << u << " " << peso << " " << v << endl;
            total += peso;}}
    cout << "Peso total: " << total << endl;}

// ALGORITMO DE PRIM
map<char, vector<pair<char, int>>> grafo;

void construirGrafo() {
    grafo.clear();
    for (auto [peso, u, v] : aristas) {
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});}}

void prim(char inicio) {
    set<char> visitado;
    vector<tuple<int, char, char>> mst;
    int total = 0;

    visitado.insert(inicio);
    while (visitado.size() < grafo.size()) {
        int minPeso = 1e9;
        char nodoU, nodoV;
        for (char u : visitado) {
            for (auto [v, peso] : grafo[u]) {
                if (visitado.find(v) == visitado.end() && peso < minPeso) {
                    minPeso = peso;
                    nodoU = u;
                    nodoV = v;}}}

        visitado.insert(nodoV);
        mst.push_back({minPeso, nodoU, nodoV});
        total += minPeso;}

    cout << "\nMST usando Prim desde nodo 'S':\n";
    for (auto [peso, u, v] : mst)
        cout << u << " " << peso << " " << v << endl;
    cout << "Peso total: " << total << endl;}

// MENÚ PRINCIPAL
int main() {
    int opcion;
    construirGrafo();
    do {
        cout << "\nMENU:\n";
        cout << "1. Ejecutar Kruskal\n";
        cout << "2. Ejecutar Prim desde S\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                kruskal();
                break;
            case 2:
                prim('S');
                break;
            case 3:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida.\n";}}
    while(opcion != 3);
    return 0;}
