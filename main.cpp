#include <iostream>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <unordered_set>
#include <stack>
#include <fstream>
#include <algorithm>
#include <queue>
#include "src/Node.h"
#include "src/NetOfNodes.h"

/*
 * Christian W. Aranibar Solaligue.
 * El algoritmo A* y BestFirst en ocasiones falla, esto se debe al borrado y los obstaculos.
 * No se encuentra el camino o se queda a la espera.
 * El algoritmo empieza realizando las conexiones entre nodos, luego se borran nodos y se crean obstaculos.
 * Para el borado de nodos se pasa un porcentaje que asegura el borrado de nodos.
 * Los obstaculos tinen un porcentaje de propagacion, es decir, si un nodo tiene un obstaculo, los nodos adyacentes
 * tienen un porcentaje de probabilidad de ser obstaculos.
 * Ambos algoritmos de busqueda se generan en la misma malla de nodos.
 * Todo se ejecuta en consola, el resultado del camino se encuentra en el archivo data.txt dentro de la carpeta src.
 */

void saveNodeMapping(std::vector<std::vector<std::string>> map) {
    std::ofstream archivo("../src/data.txt", std::ios::out);
    int rows = (int) map.size();
    int cols = (int) map[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            archivo << map[i][j] << " ";
        }
        archivo << std::endl;
    }
}

std::vector<std::vector<std::string>>
setNodeMap(std::vector<std::vector<Node>> net, const std::vector<Node *> &path, Node *initNode, Node *endNode) {
    int rows = (int) net.size();
    int cols = (int) net[0].size();
    std::vector<std::vector<std::string>> map(rows, std::vector<std::string>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((&net[i][j])->getDeleted()) {   // Nodo Borrado
                map[i][j] = "  ";
            } else if (!(&net[i][j])->getDeleted() && (&net[i][j])->getObstacle()) {  // Nodo Obst.
                map[i][j] = "[]";
            } else {    // Camino
                map[i][j] = "--";
            }
        }
    }
    for (auto &i: path) {
        map[i->getX()][i->getY()] = "++";
    }

    map[initNode->getX()][initNode->getY()] = "AA";
    map[endNode->getX()][endNode->getY()] = "BB";
    return map;
}

int main() {
    float pBorrado = 0.10;
    float rPropagation = 0.30;
    int rows = 20;
    int cols = 20;
    bool algoritmoHeuris;

    std::cout << "Ingrese el porcentaje de borrado:";
    std::cin >> pBorrado;
    std::cout << "Ingrese el porcentaje de propagacion:";
    std::cin >> rPropagation;
    std::cout << "Ingrese el numero de filas:";
    std::cin >> rows;
    std::cout << "Ingrese el numero de columnas:";
    std::cin >> cols;
    std::cout << "Ingrese el algoritmo a utilizar (0: A*, 1: Best-First):";
    std::cin >> algoritmoHeuris;

    if (algoritmoHeuris) {
        NetOfNodes test(rows, cols, rPropagation, pBorrado);
        test.buildMesh();
        test.bestFirst();
        if (test.is_bestFirst_PathEmpty()) {
            std::cout << "No hay camino" << std::endl;
            return 0;
        } else {
            std::cout << "Hay camino" << std::endl;
            std::vector<std::vector<std::string>> map = setNodeMap(test.getNet(), test.get_bestFirst_Path(),
                                                                   test.getInitNode(), test.getEndNode());
            saveNodeMapping(map);
        }
    } else {
        NetOfNodes test(rows, cols, rPropagation, pBorrado);
        test.buildMesh();
        test.aStar();
        if (test.is_aStar_PathEmpty()) {
            std::cout << "No hay camino" << std::endl;
            return 0;
        } else {
            std::cout << "Hay camino" << std::endl;
            std::vector<std::vector<std::string>> map = setNodeMap(test.getNet(), test.get_aStar_Path(),
                                                                   test.getInitNode(), test.getEndNode());
            saveNodeMapping(map);
        }
    }
    return 0;
}
