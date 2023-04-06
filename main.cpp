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

bool IS_ASTAR = false;
bool IS_B_FIRST = false;
Node *INIT_NODE;
Node *END_NODE;

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
    if (IS_ASTAR) {
        archivo << "A*:" << std::endl;
    } else if (IS_B_FIRST) {
        archivo << "BF:" << std::endl;
    }
    archivo << "Inicio: [" << INIT_NODE->getX() << "," << INIT_NODE->getY() << "]" << "\n";
    archivo << "Fin: [" << END_NODE->getX() << "," << END_NODE->getY() << "]" << "\n";

    int rows = (int) map.size();
    int cols = (int) map[0].size();

    archivo << "COLS: " << rows << "\n";
    archivo << "ROWS: " << cols << "\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            archivo << map[i][j];
        }
        archivo << std::endl;
    }
}

std::vector<std::vector<std::string>>
setNodeMap(std::vector<std::vector<Node>> net, const std::vector<Node *> &path) {
    int rows = (int) net.size();
    int cols = (int) net[0].size();
    std::vector<std::vector<std::string>> map(rows, std::vector<std::string>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((&net[i][j])->getDeleted()) {   // Nodo Borrado
                map[i][j] = " ";
            } else if (!(&net[i][j])->getDeleted() && (&net[i][j])->getObstacle()) {  // Nodo Obst.
                map[i][j] = "-";
            } else {    // Camino
                map[i][j] = "0";
            }
        }
    }
    for (auto &i: path) {
        map[i->getX()][i->getY()] = "+";
    }

    map[INIT_NODE->getX()][INIT_NODE->getY()] = "A";
    map[END_NODE->getX()][END_NODE->getY()] = "B";
    return map;
}

int main() {
    float pBorrado;
    float rPropagation;
    int rows;
    int cols;
    int cObstacles;
    bool algoritmoHeuris;

    std::cout << "Ingrese el porcentaje de borrado:";
    std::cin >> pBorrado;
    std::cout << "Ingrese el numero de obstaculos:";
    std::cin >> cObstacles;
    std::cout << "Ingrese el porcentaje de propagacion:";
    std::cin >> rPropagation;
    std::cout << "Ingrese el numero de filas:";
    std::cin >> rows;
    std::cout << "Ingrese el numero de columnas:";
    std::cin >> cols;
    std::cout << "Ingrese el algoritmo a utilizar:\n0: A*\n1: Best-First\n:";
    std::cin >> algoritmoHeuris;

    NetOfNodes test(rows, cols, rPropagation, pBorrado);

    std::cout << "buildMesh..." << std::endl;
    test.buildMesh(cObstacles);
    std::cout << "buildMesh [OK]" << std::endl;

    std::cout << "getInitNode..." << std::endl;
    INIT_NODE = test.getInitNode();
    std::cout << "getInitNode [OK]" << std::endl;

    std::cout << "getEndNode..." << std::endl;
    END_NODE = test.getEndNode();
    std::cout << "getEndNode [OK]" << std::endl;

    if (algoritmoHeuris) {
        IS_B_FIRST = true;

        std::cout << "bestFirst..." << std::endl;
        test.bestFirst();
        std::cout << "bestFirst [OK]" << std::endl;

        if (test.is_bestFirst_PathEmpty()) {
            std::cout << "No hay camino" << std::endl;
            return 0;
        } else {
            std::cout << "Hay camino" << std::endl;
            std::cout << "setNodeMap..." << std::endl;
            std::vector<std::vector<std::string>> map = setNodeMap(test.getNet(), test.get_bestFirst_Path());
            std::cout << "setNodeMap [OK]" << std::endl;
            std::cout << "saveNodeMapping..." << std::endl;
            saveNodeMapping(map);
            std::cout << "saveNodeMapping [OK]" << std::endl;
        }
    } else {
        IS_ASTAR = true;
        std::cout << "aStar..." << std::endl;
        test.aStar();
        std::cout << "aStar [OK]" << std::endl;

        if (test.is_aStar_PathEmpty()) {
            std::cout << "No hay camino" << std::endl;
            return 0;
        } else {
            std::cout << "Hay camino" << std::endl;
            std::cout << "setNodeMap..." << std::endl;
            std::vector<std::vector<std::string>> map = setNodeMap(test.getNet(), test.get_aStar_Path());
            std::cout << "setNodeMap [OK]" << std::endl;
            std::cout << "saveNodeMapping..." << std::endl;
            saveNodeMapping(map);
            std::cout << "saveNodeMapping [OK]" << std::endl;
        }
    }
    return 0;
}
