#ifndef NODEMESH_NODE_H
#define NODEMESH_NODE_H

class Node {
private:
    int x, y, fCost, gCost, hCost;
    double weight;
    bool obstacle, deleted, visited;
    Node *up, *down, *right, *left, *upLeft, *upRight, *downLeft, *downRight, *parent;
public:
    Node();

    // Setters
    void setX(int value);

    void setY(int value);

    void set_fCost(int value);

    void set_gCost(int value);

    void set_hCost(int value);

    void setWeight(double value);

    void setObstacle(bool value);

    void setDeleted(bool value);

    void setVisited(bool value);

    void setUp(Node *node);

    void setDown(Node *node);

    void setRight(Node *node);

    void setLeft(Node *node);

    void setUpLeft(Node *node);

    void setUpRight(Node *node);

    void setDownLeft(Node *node);

    void setDownRight(Node *node);

    void setParent(Node *node);

    // Getters
    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    [[nodiscard]] int get_fCost() const;

    [[nodiscard]] int get_gCost() const;

    [[nodiscard]] int get_hCost() const;

    [[nodiscard]] double getWeight() const;

    [[nodiscard]] bool getObstacle() const;

    [[nodiscard]] bool getDeleted() const;

    [[nodiscard]] bool getVisited() const;

    Node *getUp();

    Node *getDown();

    Node *getRight();

    Node *getLeft();

    Node *getUpLeft();

    Node *getUpRight();

    Node *getDownLeft();

    Node *getDownRight();

    Node *getParent();

    // Operators
    bool operator==(const Node &rhs) const;
};

Node::Node() : up(nullptr), down(nullptr), right(nullptr), left(nullptr),
               upLeft(nullptr), upRight(nullptr), downLeft(nullptr), downRight(nullptr), parent(nullptr),
               x(0), y(0), weight(0.0), obstacle(false), deleted(false), visited(false), fCost(0), gCost(0),
               hCost(0) {}

void Node::setX(int value) {
    x = value;
}

void Node::setY(int value) {
    y = value;
}

void Node::setWeight(double value) {
    weight = value;
}

void Node::setObstacle(bool value) {
    obstacle = value;
}

void Node::setDeleted(bool value) {
    deleted = value;
}

void Node::setUp(Node *node) {
    up = node;
}

void Node::setDown(Node *node) {
    down = node;
}

void Node::setRight(Node *node) {
    right = node;
}

void Node::setLeft(Node *node) {
    left = node;
}

void Node::setUpLeft(Node *node) {
    upLeft = node;
}

void Node::setUpRight(Node *node) {
    upRight = node;
}

void Node::setDownLeft(Node *node) {
    downLeft = node;
}

void Node::setDownRight(Node *node) {
    downRight = node;
}

[[nodiscard]] int Node::getX() const {
    return x;
}

[[nodiscard]] int Node::getY() const {
    return y;
}

double Node::getWeight() const {
    return weight;
}

bool Node::getObstacle() const {
    return obstacle;
}

bool Node::getDeleted() const {
    return deleted;
}

Node *Node::getUp() {
    return up;
}

Node *Node::getDown() {
    return down;
}

Node *Node::getRight() {
    return right;
}

Node *Node::getLeft() {
    return left;
}

Node *Node::getUpLeft() {
    return upLeft;
}

Node *Node::getUpRight() {
    return upRight;
}

Node *Node::getDownLeft() {
    return downLeft;
}

Node *Node::getDownRight() {
    return downRight;
}

void Node::set_fCost(int value) {
    fCost = value;

}

void Node::set_gCost(int value) {
    gCost = value;
}

void Node::set_hCost(int value) {
    hCost = value;
}

void Node::setVisited(bool value) {
    visited = value;
}

void Node::setParent(Node *node) {
    parent = node;
}

int Node::get_fCost() const {
    return fCost;
}

int Node::get_gCost() const {
    return gCost;
}

int Node::get_hCost() const {
    return hCost;
}

bool Node::operator==(const Node &rhs) const {
    return x == rhs.x && y == rhs.y;
}

Node *Node::getParent() {
    return parent;
}

bool Node::getVisited() const {
    return visited;
}

#endif //NODEMESH_NODE_H
