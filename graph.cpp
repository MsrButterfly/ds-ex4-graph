#include <iostream>
#include <string>
#include "include/ipv4-address.h"
#include "include/graph.h"

void printIP(const char &vertex, IPv4Address &ip) {
    std::cout << vertex << ": " << ip << std::endl;
}

int main(int argc, char const *argv[]) {
    UDG<char, IPv4Address> graph;

    graph.addVertex('A', IPv4Address(192, 168, 0, 1));
    graph.addVertex('B', IPv4Address(10, 16, 45, 124));
    graph.addVertex('C', IPv4Address(211, 123, 23, 12));
    graph.addVertex('D', IPv4Address(43, 32, 180, 197));
    graph.addVertex('E', IPv4Address(234, 222, 123, 1));
    graph.addVertex('F', IPv4Address(32, 23, 65, 233));
    graph.addVertex('G', IPv4Address(12, 168, 173, 90));
    graph.addVertex('H', IPv4Address(233, 168, 0, 55));
    graph.addVertex('I', IPv4Address(128, 168, 164, 64));
    graph.addVertex('J', IPv4Address(164, 168, 7, 6));
    graph.addVertex('K', IPv4Address(3, 168, 11, 56));
    graph.addVertex('L', IPv4Address(40, 168, 0, 43));
    graph.addVertex('M', IPv4Address(45, 168, 23, 136));
    graph.addVertex('N', IPv4Address(8, 8, 8, 8));
    graph.addVertex('O', IPv4Address(12, 168, 45, 23));
    graph.addVertex('P', IPv4Address(76, 45, 239, 234));

    // graph.eraseVertex('D');

    graph.addEdge('C', 'B', 2);
    graph.addEdge('K', 'J', 3);
    graph.addEdge('O', 'K', 7);
    graph.addEdge('J', 'D', 3);
    graph.addEdge('H', 'I', 5);
    graph.addEdge('P', 'A', 8);
    graph.addEdge('L', 'O', 1);
    graph.addEdge('G', 'E', 4);
    graph.addEdge('G', 'H', 2);
    graph.addEdge('O', 'M', 9);
    graph.addEdge('D', 'E', 9);
    graph.addEdge('C', 'A', 4);
    graph.addEdge('B', 'P', 2);
    graph.addEdge('D', 'F', 8);
    graph.addEdge('L', 'N', 5);

    std::cout << "DFS Result:" << std::endl;
    graph.dfs(printIP);
    std::cout << std::endl;
    std::cout << "BFS Result:" << std::endl;
    graph.bfs(printIP);

    std::vector<std::stack<char>> paths = graph.pathsBetween('I', 'M', 42);
	std::cout << std::endl;
	std::cout << "Path from I to M (length = 42): " << std::endl;
    for (std::stack<char> path : paths) {
    	if (!path.empty()) {
    		std::cout << path.top();
    		path.pop();
    	}
    	while (!path.empty()) {
    		std::cout << " -> " << path.top();
    		path.pop();
    	}
    	std::cout << std::endl;
    }

    paths = graph.pathsBetween('A', 'P', 8);
	std::cout << std::endl;
	std::cout << "Path from A to P (length = 8): " << std::endl;
    for (std::stack<char> path : paths) {
    	if (!path.empty()) {
    		std::cout << path.top();
    		path.pop();
    	}
    	while (!path.empty()) {
    		std::cout << " -> " << path.top();
    		path.pop();
    	}
    	std::cout << std::endl;
    }

    return 0;
}