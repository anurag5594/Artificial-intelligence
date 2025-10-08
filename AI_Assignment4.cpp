#include <bits/stdc++.h>
using namespace std;

struct Node {
    pair<int, int> position;
    Node* parent;
    int g, h, f;

    Node(pair<int, int> pos, Node* p = nullptr) {
        position = pos;
        parent = p;
        g = h = f = 0;
    }
};

int heuristic(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

vector<pair<int, int>> astar(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int n = grid.size();
    int m = grid[0].size();

    priority_queue<Node*, vector<Node*>, Compare> open_list;
    set<pair<int, int>> closed_list;

    Node* start_node = new Node(start);
    Node* goal_node = new Node(goal);
    open_list.push(start_node);

    while (!open_list.empty()) {
        Node* current = open_list.top();
        open_list.pop();
        closed_list.insert(current->position);

        // Goal found
        if (current->position == goal_node->position) {
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.push_back(current->position);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Possible 4-direction moves
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nx = current->position.first + dx[i];
            int ny = current->position.second + dy[i];

            // Check boundaries
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            // Skip obstacles
            if (grid[nx][ny] == 1) continue;
            // Skip visited
            if (closed_list.count({nx, ny})) continue;

            Node* neighbor = new Node({nx, ny}, current);
            neighbor->g = current->g + 1;
            neighbor->h = heuristic(neighbor->position, goal_node->position);
            neighbor->f = neighbor->g + neighbor->h;

            // Check if already in open_list with better g
            bool skip = false;
            // (priority_queue doesn't allow direct search, so approximate)
            // For simplicity, we allow duplicates — the one with lower f will be processed earlier
            // To avoid memory leak, this should be improved with a map of best g-scores

            if (!skip) {
                open_list.push(neighbor);
            }
        }
    }
    return {}; // No path found
}

int main() {
    // 0 = free cell, 1 = obstacle
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    vector<pair<int, int>> path = astar(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found: \n";
        for (auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }
    return 0;
}
