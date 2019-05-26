#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>


struct IGraph {
    virtual ~IGraph() {}
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

class CListGraph : public IGraph
{
private:
    std::vector<std::vector<std::pair<int, int>>> CList;
public:
    CListGraph() = delete;
    CListGraph(const IGraph &obj);
    CListGraph(int);
    void AddEdge(int from, int to, int weight) override;
    int VerticesCount() const override;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;
    ~CListGraph() override = default;
};

CListGraph::CListGraph(int numOfVertices) : IGraph () {
    for (int i = 0; i < numOfVertices; i++) {
        CList.push_back(std::vector<std::pair<int, int>>());
    }
}

void CListGraph::AddEdge(int from, int to, int weight) {
    assert(from < int(CList.size()) && to < int(CList.size()));
    CList[size_t(to)].push_back({ weight, from });
    CList[size_t(from)].push_back({ weight, to });
}

int CListGraph::VerticesCount() const {
    return int(CList.size());
}

std::vector<std::pair<int, int>> CListGraph::GetNextVertices(int vertex) const {
    return CList[size_t(vertex)];
}

std::vector<std::pair<int, int>> CListGraph::GetPrevVertices(int vertex) const {
    return  CList[size_t(vertex)];
}



std::vector<int> goroda(int begin, int n, IGraph &graph) {
    int counter = 0;
    std::vector<int> distances(size_t(n), INT32_MAX);
    distances[size_t(begin)] = 0;
    std::vector<bool> visited(size_t(n), false);
    std::set<std::pair<int, int>> _st;
    _st.insert(std::pair<int, int>(0 , begin));
    while (!_st.empty()) {
        auto cur_vertice = *_st.begin();
        _st.erase(_st.begin());
        auto vertices = graph.GetNextVertices(cur_vertice.second);
        visited[size_t(cur_vertice.second)] = true;
        for (auto &iter : vertices) {
            if (distances[size_t(iter.second)] > distances[size_t(cur_vertice.second)] + iter.first) {
                if(!visited[size_t(iter.second)]){
                    _st.erase(std::pair<int, int>(distances[size_t(iter.second)], iter.second ));
                    distances[size_t(iter.second)] = distances[size_t(cur_vertice.second)] + iter.first;
                    _st.insert(std::pair<int, int>( distances[size_t(iter.second)],iter.second));
                }
            }
        }
        counter++;
    }
    return distances;
}

int main()
{

    int n = 0, v = 0, begin = 0, end = 0;
    std::cin >> n >> v;
    CListGraph graph(n);
    for (int i = 0; i < v; ++i) {
        int from, to, w;
        std::cin >> from >> to >> w;
        graph.AddEdge(from, to, w);
    }
    std::cin >> begin >> end;
    std::vector<int> distances = goroda(begin, n, graph);
    std::cout << distances[size_t(end)] << std::endl;
    return 0;
}
