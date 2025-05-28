#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, char> PIC;

int main() {
    int numAristas;
    cout << "¿Cuántas aristas tiene el grafo? ";
    cin >> numAristas;

    map<char, vector<PIC>> grafo;
    set<char> vertices;

    cout << "Ingresa las aristas en formato: A 5 L" << endl;
    for (int i = 0; i < numAristas; ++i) {
        char u, v;
        int w;
        cin >> u >> w >> v;
        grafo[u].push_back({w, v});
        grafo[v].push_back({w, u});
        vertices.insert(u);
        vertices.insert(v);}

    set<char> visitados;
    priority_queue< pair<int, pair<char, char>>, vector<pair<int, pair<char, char>>>, greater<>> pq;

    char inicio = *vertices.begin(); // primer vértice
    visitados.insert(inicio);
    for (auto [peso, vecino] : grafo[inicio])
        pq.push({peso, {inicio, vecino}});

    cout << "\nÁrbol de Expansión Mínima (Prim):\n";
    while (!pq.empty() && visitados.size() < vertices.size()) {
        auto [peso, arista] = pq.top(); pq.pop();
        char u = arista.first, v = arista.second;
        if (visitados.count(v)) continue;
        visitados.insert(v);
        cout << u << " " << peso << " " << v << endl;

        for (auto [p, vecino] : grafo[v])
            if (!visitados.count(vecino))
                pq.push({p, {v, vecino}});}
    return 0;}
