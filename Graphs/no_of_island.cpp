#include <iostream>
using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
public:
    // ---------- DFS ----------
    void islandDFS(vector<vector<int>>& matrix, vector<vector<bool>>& visit, int row, int col) {
        if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size()) return;
        if (matrix[row][col] == 0 || visit[row][col]) return;

        visit[row][col] = true;

        islandDFS(matrix, visit, row + 1, col);
        islandDFS(matrix, visit, row - 1, col);
        islandDFS(matrix, visit, row, col + 1);
        islandDFS(matrix, visit, row, col - 1);
    }

    int numIslandsDFS(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int R = matrix.size(), C = matrix[0].size();
        vector<vector<bool>> visit(R, vector<bool>(C, false));

        int count = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (matrix[i][j] == 1 && !visit[i][j]) {
                    count++;
                    islandDFS(matrix, visit, i, j);
                }
        return count;
    }

    // ---------- BFS ----------
    void islandBFS(vector<vector<int>>& matrix, vector<vector<bool>>& visit, int sr, int sc) {
        int R = matrix.size(), C = matrix[0].size();
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        queue<pair<int, int>> q;
        visit[sr][sc] = true;  // mark on push, not on pop
        q.push({sr, sc});

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (matrix[nr][nc] == 0 || visit[nr][nc]) continue;

                visit[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    int numIslandsBFS(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int R = matrix.size(), C = matrix[0].size();
        vector<vector<bool>> visit(R, vector<bool>(C, false));

        int count = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (matrix[i][j] == 1 && !visit[i][j]) {
                    count++;
                    islandBFS(matrix, visit, i, j);
                }
        return count;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<string> grid;
    int expected;
};

vector<TestCase> tests() {
    return {
        {"empty grid",              {},                                   0},
        {"single land",             {"1"},                                1},
        {"single water",            {"0"},                                0},
        {"all land",                {"111", "111", "111"},                1},
        {"all water",               {"000", "000", "000"},                0},
        {"LeetCode ex 1",           {"11110", "11010", "11000", "00000"}, 1},
        {"LeetCode ex 2",           {"11000", "11000", "00100", "00011"}, 3},
        {"diagonal not connected",  {"10", "01"},                         2},
        {"checkerboard",            {"101", "010", "101"},                5},
        {"C shape (needs left)",    {"111", "001", "111"},                1},
        {"U shape (needs up)",      {"101", "101", "111"},                1},
        {"island with a lake",      {"111", "101", "111"},                1},
        {"single row",              {"10101"},                            3},
        {"single column",           {"1", "0", "1", "1", "0"},            2},
    };
}

// =====================================================
//                       DRIVER
// =====================================================
vector<vector<int>> toMatrix(const vector<string>& rows) {
    vector<vector<int>> m;
    for (const string& row : rows) {
        vector<int> line;
        for (char ch : row) line.push_back(ch - '0');
        m.push_back(line);
    }
    return m;
}

int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== NUMBER OF ISLANDS ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        const TestCase& t = ts[i];

        vector<vector<int>> matrix = toMatrix(t.grid);
        int gotDFS = sol.numIslandsDFS(matrix);
        int gotBFS = sol.numIslandsBFS(matrix);
        bool ok = (gotDFS == t.expected && gotBFS == t.expected);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << t.name;
        if (!ok) {
            cout << "  (expected " << t.expected
                 << ", dfs " << gotDFS << ", bfs " << gotBFS << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << ts.size() << " passed\n";
    return 0;
}