#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void HOOKSHA() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

#define all(a) a.begin(), a.end()

class Game {
public:
    vector<vector<char>> state;
    Game* parent = nullptr;
    int level = 0, hueris = 0;

    Game() {
        state.resize(3, vector<char>(3));
    }

    void setInitialState() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> state[i][j];
    }

    void getState() {
        cout << "=================" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << state[i][j] << " ";
            }
            cout << endl;
        }
        cout << "=================" << endl;
    }

    bool isGoalState() {
        vector<vector<char>> Goal = {{'1', '2', '3'},
                                     {'4', '5', '6'},
                                     {'7', '8', '*'}};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                if (state[i][j] != Goal[i][j]) return false;
        }
        return true;
    }

    void printPath() {
        cout << "the solution is found by * Greedy search * after :" << level << " operation " << endl;
        deque<vector<vector<char>>> solution;
        Game* path = this;
        while (true) {
            vector<vector<char>> now(3, vector<char>(3));
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    now[i][j] = path->state[i][j];
                }
            }
            solution.push_front(now);
            if (path->parent == nullptr) break;
            path = path->parent;
        }
        cout << "=================" << endl;
        for (int i = 0; i < (int)solution.size(); i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cout << solution[i][j][k] << " ";
                }
                cout << endl;
            }
            cout << "=================" << endl;
        }
    }

    bool move(int i, int j) {
        return i >= 0 && i < 3 && j >= 0 && j < 3;
    }

    vector<Game*> validActions() {
        vector<Game*> actions;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->state[i][j] == '*') {
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (move(nx, ny)) {
                            Game* new_state = new Game(*this);
                            swap(new_state->state[i][j], new_state->state[nx][ny]);
                            actions.push_back(new_state);
                        }
                    }
                }
            }
        }
        return actions;
    }

    // Manhattan Distance Heuristic
    int heuristic() {
        vector<vector<char>> Goal = {{'1', '2', '3'},
                                     {'4', '5', '6'},
                                     {'7', '8', '*'}};
        int tiles = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
               if (state[i][j] != Goal[i][j]) tiles++;
            }
        }
        return tiles  ;
    }
};

bool ok = false;

void Greedy_8_solver(Game* initial) {
    priority_queue<pair<int, Game*>, vector<pair<int, Game*>>, greater<pair<int, Game*>>> pq;
    map<vector<vector<char>>, int> visited;
    pq.push({initial->heuristic(), initial});
    visited[initial->state] = initial->heuristic();
    while (!pq.empty()) {
        Game* node = pq.top().second;
        pq.pop();
        if (node->isGoalState()) {
            node->printPath();
            ok = true;
            cout << "DONE" << endl;
            return;
        }
        vector<Game*> actions = node->validActions();
        for (auto i : actions) {
            int h = i->heuristic();
            if (!visited.count(i->state)) {
                visited[i->state] = 1;
                // f(N) = H(N) only
                pq.push({h , i});
                i->parent = node;
                i->level = node->level + 1;
            }
        }
    }
}

int main() {
    HOOKSHA();
    int t = 1;
    // cin >> t;
    while (t--) {
        cout << "Enter the 8 puzzle and make the empty cell * " << endl;
        Game* initial = new Game();
        initial->setInitialState();
        Greedy_8_solver(initial);
        if (!ok)
            cout << "the puzzle is not solvable" << endl;
        delete initial;
    }
    return 0;
}
