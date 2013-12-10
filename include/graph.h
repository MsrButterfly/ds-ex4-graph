#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

#define max(x, y) (x > y)? x : y

template <typename _IdType, typename _DataType>
class UDG {
public:
    UDG() {}
    ~UDG() {}
    bool addVertex(const _IdType &id, const _DataType &data) {
        for (const Vertex &vertex : vertexes) {
            if (vertex.id == id) {
                return false;
            }
        }
        vertexes.push_back(Vertex(id, data));
        return true;
    }
    bool eraseVertex(const _IdType &id) {
        int pos = positionWithId(id);
        if (pos == -1) {
            return false;
        }
        for (const Vertex &vertex : vertexes) {
            if (vertex.id != id) {
                while (eraseEdge(vertex.id, id));
            }
        }
        typename std::vector<Vertex>::iterator p = vertexes.begin();
        for (int i = 0; i < pos; i++, p++);
        vertexes.erase(p);
        return true;
    }
    bool addEdge(const _IdType &start, const _IdType &end, const int &weight = 1) {
        if (start == end) {
            return false;
        }
        int startPos = positionWithId(start), endPos = positionWithId(end);
        if (startPos == -1 || endPos == -1) {
            return false;
        }
        vertexes[startPos].edges.push_back(Edge(end, weight));
        vertexes[endPos].edges.push_back(Edge(start, weight));
        return true;
    }
    bool eraseEdge(const _IdType &start, const _IdType &end) {
        int startPos = positionWithId(start);
        int endPos = positionWithId(end);
        bool found = false;
        typename std::list<Edge>::iterator p;
        for (p = vertexes[startPos].edges.begin(); p != vertexes[startPos].edges.end(); p++) {
            if (p -> to == end) {
                vertexes[startPos].edges.erase(p);
                found = true;
                break;
            }
        }
        for (p = vertexes[endPos].edges.begin(); p != vertexes[endPos].edges.end(); p++) {
            if (p -> to == start) {
                vertexes[endPos].edges.erase(p);
                break;
            }
        }
        return found;
    }
    std::vector<std::stack<_IdType>> pathsBetween(_IdType v1, _IdType v2, int length) {
        while (!path.empty()) {
            path.pop();
        }
        paths.clear();
        visited.clear();
        for (int i = 0; i < vertexes.size(); i++) {
            visited.push_back(false);
        }
        _pathsBetween(v1, v2, length);
        return paths;
    }
private:
    void _pathsBetween(_IdType v1, _IdType v2, int length) {
        if (length < 0) {
            return;
        }
        if (length == 0 && v1 == v2) {
            path.push(v1);
            paths.push_back(path);
            path.pop();
            return;
        }
        path.push(v2);
        int pos = positionWithId(v2);
        visited[pos] = true;
        for (const Edge &edge : vertexes[pos].edges) {
            int toPos = positionWithId(edge.to);
            if (!visited[toPos]) {
                _pathsBetween(v1, edge.to, length - edge.weight);
            }
        }
        visited[pos] = false;
        path.pop();
    }
public:
    void bfs(void visit(const _IdType &, _DataType &)) {
        visited.clear();
        if (vertexes.size() == 0) {
            return;
        }
        std::queue<_IdType> idQueue;
        for (int i = 0; i < vertexes.size(); i++) {
            visited.push_back(false);
        }
        for (int i = 0; i < vertexes.size(); i++) {
            if (!visited[i]) {
                idQueue.push(vertexes[i].id);
                visited[positionWithId(vertexes[i].id)] = true;
            }
            while (!idQueue.empty()) {
                int pos = positionWithId(idQueue.front());
                idQueue.pop();
                visit(vertexes[pos].id, vertexes[pos].data);
                for (const Edge &edge : vertexes[pos].edges) {
                    int toPos = positionWithId(edge.to);
                    if (!visited[toPos]) {
                        idQueue.push(edge.to);
                        visited[toPos] = true;
                    }
                }
            }
        }
    }
    void dfs(void visit(const _IdType &, _DataType &)) {
        visited.clear();
        if (vertexes.size() == 0) {
            return;
        }
        for (int i = 0; i < vertexes.size(); i++) {
            visited.push_back(false);
        }
        for (int i = 0; i < vertexes.size(); i++) {
            dfs(visit, i);
        }
    }
private:
    void dfs(void visit(const _IdType &, _DataType &), int pos) {
        if (visited[pos]) {
            return;
        }
        visit(vertexes[pos].id, vertexes[pos].data);
        visited[pos] = true;
        for (const Edge &edge : vertexes[pos].edges) {
            dfs(visit, positionWithId(edge.to));
        }
    }
public:
    void showAdjList() {
        for (const Vertex &vertex : vertexes) {
            std::cout << vertex.id << '(' << vertex.data << ')' << ":";
            for (const Edge &edge : vertex.edges) {
                std::cout << ' ' << vertexes[positionWithId(edge.to)].id << '(' << edge.weight << ')';
            }
            std::cout << std::endl;
        }
    }
private:
    class Edge {
    public:
        Edge(const _IdType &to, const int &weight = 1) : to(to), weight(weight) {}
        _IdType to;
        int weight;
    };
    class Vertex {
    public:
        Vertex(const _IdType &id, const _DataType &data) : id(id), data(data) {}
        _IdType id;
        _DataType data;
        std::list<Edge> edges;
    };
    int positionWithId(const _IdType &id) const {
        typename std::vector<Vertex>::const_iterator p = vertexes.begin();
        for (int i = 0; i < vertexes.size(); i++, p++) {
            if (p -> id == id) {
                return i;
            }
        }
        return -1;
    }
    std::stack<_IdType> path;
    std::vector<std::stack<_IdType>> paths;
    std::stack<_IdType> idStack;
    std::vector<Vertex> vertexes;
    std::vector<bool> visited;
};
