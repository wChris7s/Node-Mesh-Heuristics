#ifndef NODEMESH_NETOFNODES_H
#define NODEMESH_NETOFNODES_H

class NetOfNodes {
private:
    Node *initNode, *endNode;
    float pBorrado, rPropagation;
    std::vector<std::vector<Node>> net;
    std::vector<Node *> aStar_Path;
    std::vector<Node *> bestFirst_Path;

    // Methods
    void buildConnections();

    void deleteRandomNodes();

    void genObstacles();

    static int manhattanDistance(Node *node1, Node *node2);

public:
    // Constructor
    NetOfNodes(int ROWS, int COLS, float rPropagation, float pBorrado);

    // Methods
    void buildMesh();

    int getRandom();

    static int getRandom(int min, int max);

    void aStar();

    void bestFirst();

    std::pair<int, int> setInitEnd();

    void setStartGoal();

    static bool compareNodes(Node *a, Node *b);

    // Getters
    int getROWS();

    int getCOLS();

    Node *getInitNode();

    Node *getEndNode();

    Node *getNode(int x, int y);

    std::vector<std::vector<Node>> getNet();

    std::vector<Node *> get_aStar_Path();

    std::vector<Node *> get_bestFirst_Path();

    bool is_aStar_PathEmpty();

    bool is_bestFirst_PathEmpty();
};

NetOfNodes::NetOfNodes(int ROWS, int COLS, float rPropagation, float pBorrado) : net(ROWS, std::vector<Node>(COLS)),
                                                                                 initNode(nullptr), endNode(nullptr),
                                                                                 rPropagation(rPropagation),
                                                                                 pBorrado(pBorrado) {}

void NetOfNodes::buildConnections() {
    for (int i = 0; i < getROWS(); i++) {
        for (int j = 0; j < getCOLS(); j++) {
            net[i][j].setX(i);  // Da la coordenada X al nodo.
            net[i][j].setY(j);  // Da la coordenada Y al nodo.
            if (i > 0) {
                // Conectar con el nodo de arriba
                net[i][j].setUp(&net[i - 1][j]);
                net[i][j].setWeight(getRandom());       // Le da peso al nodo.
                net[i - 1][j].setDown(&net[i][j]);      // Bidireccional.
                net[i - 1][j].setWeight(getRandom());   // Da otro peso.
            }
            if (i < getROWS() - 1) {
                // Conectar con el nodo de abajo
                net[i][j].setDown(&net[i + 1][j]);
                net[i][j].setWeight(getRandom());
                net[i + 1][j].setUp(&net[i][j]);
                net[i + 1][j].setWeight(getRandom());
            }
            if (j > 0) {
                // Conectar con el nodo de la izquierda
                net[i][j].setLeft(&net[i][j - 1]);
                net[i][j].setWeight(getRandom());
                net[i][j - 1].setRight(&net[i][j]);
                net[i][j - 1].setWeight(getRandom());
            }
            if (j < getCOLS() - 1) {
                // Conectar con el nodo de la derecha
                net[i][j].setRight(&net[i][j + 1]);
                net[i][j].setWeight(getRandom());
                net[i][j + 1].setLeft(&net[i][j]);
                net[i][j + 1].setWeight(getRandom());
            }
            if (i > 0 && j > 0) {
                // Conectar con el nodo diagonal de arriba a la izquierda
                net[i][j].setUpLeft(&net[i - 1][j - 1]);
                net[i][j].setWeight(getRandom());
                net[i - 1][j - 1].setDownRight(&net[i][j]);
                net[i - 1][j - 1].setWeight(getRandom());
            }
            if (i > 0 && j < getCOLS() - 1) {
                // Conectar con el nodo diagonal de arriba a la derecha
                net[i][j].setUpRight(&net[i - 1][j + 1]);
                net[i][j].setWeight(getRandom());
                net[i - 1][j + 1].setDownLeft(&net[i][j]);
                net[i - 1][j + 1].setWeight(getRandom());

            }
            if (i < getROWS() - 1 && j > 0) {
                // Conectar con el nodo diagonal de abajo a la izquierda
                net[i][j].setDownLeft(&net[i + 1][j - 1]);
                net[i][j].setWeight(getRandom());
                net[i + 1][j - 1].setUpRight(&net[i][j]);
                net[i + 1][j - 1].setWeight(getRandom());
            }
            if (i < getROWS() - 1 && j < getCOLS() - 1) {
                // Conectar con el nodo diagonal de abajo a la derecha
                net[i][j].setDownRight(&net[i + 1][j + 1]);
                net[i][j].setWeight(getRandom());
                net[i + 1][j + 1].setUpLeft(&net[i][j]);
                net[i + 1][j + 1].setWeight(getRandom());
            }
        }
    }
}

void NetOfNodes::deleteRandomNodes() {
    int numNodes = getROWS() * getCOLS();
    int numNodesToDelete = (int) ((float) numNodes * pBorrado);
    int nodesDeleted = 0;
    while (nodesDeleted < numNodesToDelete) {
        int i = getRandom(), j = getRandom();
        if (!net[i][j].getDeleted()) {
            if ((&net[i][j])->getUp() != nullptr) {
                (&net[i][j])->getUp()->setDown(nullptr);
                (&net[i][j])->setUp(nullptr);
            }
            if ((&net[i][j])->getDown() != nullptr) {
                (&net[i][j])->getDown()->setUp(nullptr);
                (&net[i][j])->setDown(nullptr);
            }
            if ((&net[i][j])->getLeft() != nullptr) {
                (&net[i][j])->getLeft()->setRight(nullptr);
                (&net[i][j])->setLeft(nullptr);
            }
            if ((&net[i][j])->getRight() != nullptr) {
                (&net[i][j])->getRight()->setLeft(nullptr);
                (&net[i][j])->setRight(nullptr);
            }
            if ((&net[i][j])->getUpLeft() != nullptr) {
                (&net[i][j])->getUpLeft()->setDownRight(nullptr);
                (&net[i][j])->setUpLeft(nullptr);
            }
            if ((&net[i][j])->getUpRight() != nullptr) {
                (&net[i][j])->getUpRight()->setDownLeft(nullptr);
                (&net[i][j])->setUpRight(nullptr);
            }
            if ((&net[i][j])->getDownLeft() != nullptr) {
                (&net[i][j])->getDownLeft()->setUpRight(nullptr);
                (&net[i][j])->setDownLeft(nullptr);
            }
            if ((&net[i][j])->getDownRight() != nullptr) {
                (&net[i][j])->getDownRight()->setUpLeft(nullptr);
                (&net[i][j])->setDownRight(nullptr);
            }
            (&net[i][j])->setDeleted(true);
            (&net[i][j])->setX(-1);
            (&net[i][j])->setY(-1);
            (&net[i][j])->setWeight(0.0);
            nodesDeleted++;
        }
    }
}

void NetOfNodes::genObstacles() {
    std::pair<int, int> XY = setInitEnd();
    net[XY.first][XY.second].setObstacle(true);
    int numObstacles = getROWS() * getCOLS() * rPropagation;
    int numObstaclesCreated = 1;
    std::queue<Node *> nodesToCheck;
    nodesToCheck.push(&net[XY.first][XY.second]);
    while (numObstaclesCreated < numObstacles && !nodesToCheck.empty()) {
        Node *current = nodesToCheck.front();
        nodesToCheck.pop();

        // Propagamos los obstáculos a los nodos vecinos
        if (current->getUp() != nullptr && !current->getUp()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getUp()->setObstacle(true);
            nodesToCheck.push(current->getUp());
            numObstaclesCreated++;
        }
        if (current->getDown() != nullptr && !current->getDown()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getDown()->setObstacle(true);
            nodesToCheck.push(current->getDown());
            numObstaclesCreated++;
        }
        if (current->getLeft() != nullptr && !current->getLeft()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getLeft()->setObstacle(true);
            nodesToCheck.push(current->getLeft());
            numObstaclesCreated++;
        }
        if (current->getRight() != nullptr && !current->getRight()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getRight()->setObstacle(true);
            nodesToCheck.push(current->getRight());
            numObstaclesCreated++;
        }

        if (current->getUpRight() != nullptr && !current->getUpRight()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getUpRight()->setObstacle(true);
            nodesToCheck.push(current->getUpRight());
            numObstaclesCreated++;
        }

        if (current->getUpLeft() != nullptr && !current->getUpLeft()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getUpLeft()->setObstacle(true);
            nodesToCheck.push(current->getUpLeft());
            numObstaclesCreated++;
        }

        if (current->getDownRight() != nullptr && !current->getDownRight()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getDownRight()->setObstacle(true);
            nodesToCheck.push(current->getDownRight());
            numObstaclesCreated++;
        }

        if (current->getDownLeft() != nullptr && !current->getDownLeft()->getObstacle() &&
            getRandom(0, 99) % 100 < rPropagation * 100) {
            current->getDownLeft()->setObstacle(true);
            nodesToCheck.push(current->getDownLeft());
            numObstaclesCreated++;
        }
    }
}

void NetOfNodes::buildMesh() {
    buildConnections();
    deleteRandomNodes();
    genObstacles();
    setStartGoal();
}

int NetOfNodes::getRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, getCOLS() - 1);
    return distribution(gen);
}

int NetOfNodes::getRandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}


int NetOfNodes::getROWS() {
    return (int) net.size();
}

int NetOfNodes::getCOLS() {
    return (int) net[0].size();
}

Node *NetOfNodes::getInitNode() {
    return initNode;
}

Node *NetOfNodes::getEndNode() {
    return endNode;
}

std::vector<std::vector<Node>> NetOfNodes::getNet() {
    return net;
}

std::pair<int, int> NetOfNodes::setInitEnd() {
    std::pair<int, int> startXY;
    bool sePuedeCrear = false;
    while (!sePuedeCrear) {
        int startX = getRandom();
        int startY = getRandom();
        if (net[startX][startY].getX() != -1 && net[startX][startY].getY() != -1 &&
            !net[startX][startY].getObstacle()) {
            startXY.first = startX;
            startXY.second = startY;
            sePuedeCrear = true;
        }
    }
    return startXY;
}

int NetOfNodes::manhattanDistance(Node *node1, Node *node2) {
    return abs(node1->getX() - node2->getX()) + abs(node1->getY() - node2->getY());
}

void NetOfNodes::setStartGoal() {
    std::pair<int, int> start = setInitEnd();
    std::pair<int, int> goal = setInitEnd();
    initNode = &net[start.first][start.second];
    endNode = &net[goal.first][goal.second];
}

Node *NetOfNodes::getNode(int x, int y) {
    return &net[x][y];
}

void NetOfNodes::aStar() {
    std::vector<Node *> openList;
    std::vector<Node *> closedList;

    initNode->set_gCost(0);
    initNode->set_hCost(manhattanDistance(initNode, endNode));
    initNode->set_fCost(initNode->get_gCost() + initNode->get_hCost());

    openList.push_back(initNode);

    while (!openList.empty()) {
        Node *current = openList[0];
        for (auto &node: openList) {
            if (node->get_fCost() < current->get_fCost()) {
                current = node;
            }
        }
        if (current == endNode) {
            Node *temp = current;
            while (temp != nullptr) {
                aStar_Path.push_back(temp);
                temp = temp->getParent();
            }
            break;
        }
        openList.erase(std::remove(openList.begin(), openList.end(), current), openList.end());
        closedList.push_back(current);
        std::vector<Node *> neighbors;

        int x = current->getX();
        int y = current->getY();

        if (x > 0 && (&net[x - 1][y]) != nullptr && !net[x - 1][y].getObstacle()) {
            neighbors.push_back(&net[x - 1][y]);
        }
        if (x < getROWS() - 1 && (&net[x + 1][y]) != nullptr && !net[x + 1][y].getObstacle()) {
            neighbors.push_back(&net[x + 1][y]);
        }
        if (y > 0 && (&net[x][y - 1]) != nullptr && !net[x][y - 1].getObstacle()) {
            neighbors.push_back(&net[x][y - 1]);
        }
        if (y < getCOLS() - 1 && (&net[x][y + 1]) != nullptr && !net[x][y + 1].getObstacle()) {
            neighbors.push_back(&net[x][y + 1]);
        }
        if (x > 0 && y > 0 && (&net[x - 1][y - 1]) != nullptr && !net[x - 1][y - 1].getObstacle()) {
            neighbors.push_back(&net[x - 1][y - 1]);
        }
        if (x > 0 && y < getCOLS() - 1 && (&net[x - 1][y + 1]) != nullptr && !net[x - 1][y + 1].getObstacle()) {
            neighbors.push_back(&net[x - 1][y + 1]);
        }
        if (x < getROWS() - 1 && y > 0 && (&net[x + 1][y - 1]) != nullptr && !net[x + 1][y - 1].getObstacle()) {
            neighbors.push_back(&net[x + 1][y - 1]);
        }
        if (x < getROWS() - 1 && y < getCOLS() - 1 && (&net[x + 1][y + 1]) != nullptr &&
            !net[x + 1][y + 1].getObstacle()) {
            neighbors.push_back(&net[x + 1][y + 1]);
        }
        for (auto &neighbor: neighbors) {
            bool skip = false;
            for (auto &closedNeighbor: closedList) {
                if (neighbor == closedNeighbor) {
                    skip = true;
                    break;
                }
            }
            if (skip) {
                continue;
            }
            int tentative_gCost = current->get_gCost() + manhattanDistance(current, neighbor);
            bool neighborIsBetter = false;
            for (auto &openNeighbor: openList) {
                if (neighbor == openNeighbor) {
                    neighborIsBetter = true;
                    break;
                }
            }
            if (!neighborIsBetter || tentative_gCost < neighbor->get_gCost()) {
                neighbor->setParent(current);
                neighbor->set_gCost(tentative_gCost);
                neighbor->set_hCost(manhattanDistance(neighbor, endNode));
                neighbor->set_fCost(neighbor->get_gCost() + neighbor->get_hCost());
                if (!neighborIsBetter) {
                    openList.push_back(neighbor);
                }
            }
        }
    }
}

std::vector<Node *> NetOfNodes::get_aStar_Path() {
    return aStar_Path;
}

bool NetOfNodes::is_aStar_PathEmpty() {
    return aStar_Path.empty();
}

std::vector<Node *> NetOfNodes::get_bestFirst_Path() {
    return bestFirst_Path;
}

bool NetOfNodes::is_bestFirst_PathEmpty() {
    return bestFirst_Path.empty();
}

void NetOfNodes::bestFirst() {
    std::priority_queue<Node *, std::vector<Node *>, decltype(&NetOfNodes::compareNodes)> openList(
            &NetOfNodes::compareNodes);
    std::vector<Node *> closedList;
    initNode->set_fCost(manhattanDistance(initNode, endNode));
    openList.push(initNode);
    while (!openList.empty()) {
        Node *current = openList.top();
        openList.pop();
        if (*current == *endNode) {
            Node *node = current;
            while (node != nullptr) {
                bestFirst_Path.insert(bestFirst_Path.begin(), node);
                node = node->getParent();
            }
            break;
        }
        current->setVisited(true);
        closedList.push_back(current);
        std::vector<Node *> neighbors;
        int x = current->getX();
        int y = current->getY();

        if (x > 0 && (&net[x - 1][y]) != nullptr && !net[x - 1][y].getObstacle()) {
            neighbors.push_back(&net[x - 1][y]);
        }
        if (x < getROWS() - 1 && (&net[x + 1][y]) != nullptr && !net[x + 1][y].getObstacle()) {
            neighbors.push_back(&net[x + 1][y]);
        }
        if (y > 0 && (&net[x][y - 1]) != nullptr && !net[x][y - 1].getObstacle()) {
            neighbors.push_back(&net[x][y - 1]);
        }
        if (y < getCOLS() - 1 && (&net[x][y + 1]) != nullptr && !net[x][y + 1].getObstacle()) {
            neighbors.push_back(&net[x][y + 1]);
        }
        if (x > 0 && y > 0 && (&net[x - 1][y - 1]) != nullptr && !net[x - 1][y - 1].getObstacle()) {
            neighbors.push_back(&net[x - 1][y - 1]);
        }
        if (x > 0 && y < getCOLS() - 1 && (&net[x - 1][y + 1]) != nullptr && !net[x - 1][y + 1].getObstacle()) {
            neighbors.push_back(&net[x - 1][y + 1]);
        }
        if (x < getROWS() - 1 && y > 0 && (&net[x + 1][y - 1]) != nullptr && !net[x + 1][y - 1].getObstacle()) {
            neighbors.push_back(&net[x + 1][y - 1]);
        }
        if (x < getROWS() - 1 && y < getCOLS() - 1 && (&net[x + 1][y + 1]) != nullptr &&
            !net[x + 1][y + 1].getObstacle()) {
            neighbors.push_back(&net[x + 1][y + 1]);
        }
        for (Node *neighbor: neighbors) {
            if (!neighbor->getVisited()) {
                neighbor->set_fCost(manhattanDistance(neighbor, endNode));
                neighbor->setParent(current);
                openList.push(neighbor);
                bool hasUnvisitedNeighbors = false;
                for (Node *n: neighbors) {
                    if (!n->getVisited()) {
                        hasUnvisitedNeighbors = true;
                        break;
                    }
                }
                if (!hasUnvisitedNeighbors) {
                    break;
                }
            }
        }
    }
}

bool NetOfNodes::compareNodes(Node *a, Node *b) {
    return a->get_fCost() > b->get_fCost();
}

#endif //NODEMESH_NETOFNODES_H
