//
//  main.cpp
//  ds-ex4-graph
//
//  Created by Darren Liu on 13-12-11.
//  Copyright (c) 2013年 mashiroLab. All rights reserved.
//

#include <iostream>
#include <string>
#include "include/ipv4-address.h"
#include "include/graph.h"

void print(const char &vertex, IPv4Address &ip) {
    std::cout << vertex << ": " << ip << std::endl;
}

int main(int argc, char const *argv[]) {
    UDG<char, IPv4Address> graph;
    
    graph['A'] = IPv4Address(192, 168, 0, 1);
    graph['B'] = IPv4Address(10, 16, 45, 124);
    graph['C'] = IPv4Address(211, 123, 23, 12);
    graph['D'] = IPv4Address(43, 32, 180, 197);
    graph['E'] = IPv4Address(234, 222, 123, 1);
    graph['F'] = IPv4Address(32, 23, 65, 233);
    graph['G'] = IPv4Address(12, 168, 173, 90);
    graph['H'] = IPv4Address(233, 168, 0, 55);
    graph['I'] = IPv4Address(128, 168, 164, 64);
    graph['J'] = IPv4Address(164, 168, 7, 6);
    graph['K'] = IPv4Address(3, 168, 11, 56);
    graph['L'] = IPv4Address(40, 168, 0, 43);
    graph['M'] = IPv4Address(45, 168, 23, 136);
    graph['N'] = IPv4Address(8, 8, 8, 8);
    graph['O'] = IPv4Address(12, 168, 45, 23);
    graph['P'] = IPv4Address(76, 45, 239, 234);
    
    graph.link('C', 'B', 2);
    graph.link('K', 'J', 3);
    graph.link('O', 'K', 7);
    graph.link('J', 'D', 3);
    graph.link('H', 'I', 5);
    graph.link('P', 'A', 8);
    graph.link('L', 'O', 1);
    graph.link('G', 'E', 4);
    graph.link('G', 'H', 2);
    graph.link('O', 'M', 9);
    graph.link('D', 'E', 9);
    graph.link('C', 'A', 4);
    graph.link('B', 'P', 2);
    graph.link('D', 'F', 8);
    graph.link('L', 'N', 5);
    
    graph.showAdjList();
    
    std::cout << std::endl;
    
    std::cout << "DFS Result:" << std::endl;
    graph.dfs(print);
    std::cout << std::endl;
    std::cout << "BFS Result:" << std::endl;
    graph.bfs(print);
    
    std::vector<std::stack<char>> paths = graph.paths('I', 'M', 42);
    std::cout << std::endl;
    std::cout << "Paths from I to M (length = 42): " << std::endl;
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
    
    paths = graph.paths('A', 'P', 8);
    std::cout << std::endl;
    std::cout << "Paths from A to P (length = 8): " << std::endl;
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

    std::cout << std::endl;

    graph.erase('D');
    graph.unlink('A', 'P');
    graph.showAdjList();
    
    return 0;
}
