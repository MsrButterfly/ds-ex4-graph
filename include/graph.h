#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

template <typename Key, typename Value>
class UDG {
private:
    class E {
    public:
        E() {}
        E(const Key &k, const unsigned int &w = 1) : k(k), w(w) {}
        Key k;
        int w;
    };
    class V {
    public:
        V() {}
        V(const Value &value) : value(value) {}
        Value value;
        std::list<E> es;
        bool visited;
    };
    std::map<Key, V> vs;
public:
    UDG() {}
    ~UDG() {}
    Value &operator[](Key &&k) {
        return vs[k].value;
    }
    std::size_t erase(const Key &k) {
        for (const auto &e : vs[k].es) {
            vs[e.k].es.remove_if([k](const E & e) {
                return e.k == k;
            });
        }
        return vs.erase(k);
    }
    bool link(const Key &k1, const Key &k2, const unsigned int &w) {
        if (w == 0) {
            return false;
        }
        typename std::map<Key, V>::iterator v1 = vs.find(k1);
        typename std::map<Key, V>::iterator v2 = vs.find(k2);
        if (v1 == vs.end() || v2 == vs.end()) {
            return false;
        }
        typename std::list<E>::iterator e1 =
            find_if(v1 -> second.es.begin(),
                    v1 -> second.es.end(),
        [k2](const E & e) {
            return e.k == k2;
        });
        typename std::list<E>::iterator e2 =
            find_if(v2 -> second.es.begin(),
                    v2 -> second.es.end(),
        [k1](const E & e) {
            return e.k == k1;
        });
        if (e1 != v1 -> second.es.end() && e2 != v2 -> second.es.end()) {
            e1 -> w = w;
            e2 -> w = w;
        } else {
            v1 -> second.es.push_back(E(k2, w));
            v2 -> second.es.push_back(E(k1, w));
        }
        return true;
    }
    bool unlink(const Key &k1, const Key &k2) {
        typename std::map<Key, V>::iterator v1 = vs.find(k1);
        typename std::map<Key, V>::iterator v2 = vs.find(k2);
        if (v1 == vs.end() || v2 == vs.end()) {
            return false;
        }
        v1 -> second.es.remove_if([k2](const E & e) {
            return e.k == k2;
        });
        v2 -> second.es.remove_if([k1](const E & e) {
            return e.k == k1;
        });
        return true;
    }
private:
    std::stack<Key> _path;
    std::vector<std::stack<Key>> __paths;
public:
    std::vector<std::stack<Key>> paths(const Key &k1, const Key &k2, int l) {
        while (!_path.empty()) {
            _path.pop();
        }
        __paths.clear();
        for (auto &v : vs) {
            v.second.visited = false;
        }
        _paths(k1, k2, l);
        return __paths;
    }
private:
    void _paths(const Key &k1, const Key &k2, int l) {
        if (l < 0) {
            return;
        }
        if (l == 0 && k1 == k2) {
            _path.push(k1);
            __paths.push_back(_path);
            _path.pop();
            return;
        }
        _path.push(k2);
        vs[k2].visited = true;
        for (const auto &e : vs[k2].es) {
            if (!vs[e.k].visited) {
                _paths(k1, e.k, l - e.w);
            }
        }
        vs[k2].visited = false;
        _path.pop();
    }
public:
    void bfs(void visit(const Key &, Value &)) {
        if (vs.size() == 0) {
            return;
        }
        std::queue<Key> ks;
        for (auto &v : vs) {
            v.second.visited = false;
        }
        for (auto &v : vs) {
            if (!v.second.visited) {
                ks.push(v.first);
                v.second.visited = true;
            }
            while (!ks.empty()) {
                Key k = ks.front();
                ks.pop();
                visit(k, vs[k].value);
                for (const auto &e : vs[k].es) {
                    if (!vs[e.k].visited) {
                        ks.push(e.k);
                        vs[e.k].visited = true;
                    }
                }
            }
        }
    }
public:
    void dfs(void visit(const Key &, Value &)) {
        for (auto &v : vs) {
            v.second.visited = false;
        }
        for (const auto &v : vs) {
            dfs(visit, v.first);
        }
    }
private:
    void dfs(void visit(const Key &, Value &), Key k) {
        if (vs[k].visited) {
            return;
        }
        vs[k].visited = true;
        visit(k, vs[k].value);
        for (const auto &e : vs[k].es) {
            dfs(visit, e.k);
        }
    }
public:
    void showAdjList() {
        for (const auto &v : vs) {
            std::cout << v.first << '(' << v.second.value << ')' << ":";
            for (const auto &e : v.second.es) {
                std::cout << ' ' << e.k << '(' << e.w << ')';
            }
            std::cout << std::endl;
        }
    }
};
