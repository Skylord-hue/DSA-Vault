#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// =====================================================
//                      SOLUTION
// =====================================================
class Solution {
public:
    int orangesRotting(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();

        queue<pair<int, int>> q;
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));
        int freshCount = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (matrix[r][c] == 2) {
                    q.push({r, c});
                    visit[r][c] = true;
                } else if (matrix[r][c] == 1) {
                    freshCount++;
                }
            }
        }

        if (freshCount == 0) return 0;

        int minutes = 0;
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty() && freshCount > 0) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                    if (matrix[nr][nc] != 1 || visit[nr][nc]) continue;

                    visit[nr][nc] = true;
                    matrix[nr][nc] = 2; // Make it rotten
                    freshCount--;
                    q.push({nr, nc});
                }
            }
            minutes++;
        }

        return (freshCount == 0) ? minutes : -1;
    }
};

// =====================================================
//                     TEST CASES
// =====================================================
struct TestCase {
    string name;
    vector<vector<int>> grid;
    int expected;
};

vector<TestCase> tests() {
    return {
        {"Standard Case (4 min)", {{2,1,1},{1,1,0},{0,1,1}}, 4},
        {"Isolated Fresh Orange", {{2,1,1},{0,1,1},{1,0,1}}, -1},
        {"No Fresh Oranges",      {{0,2}},                   0},
        {"No Rotten Oranges",     {{1,1},{1,1}},            -1},
        {"Empty Grid",            {},                        0}
    };
}

// =====================================================
//                       DRIVER
// =====================================================
int main() {
    vector<TestCase> ts = tests();
    Solution sol;
    int passed = 0;

    cout << "=== ROTTING ORANGES ===\n";
    for (size_t i = 0; i < ts.size(); i++) {
        // Deep copy grid so original test case isn't mutated
        vector<vector<int>> matrix = ts[i].grid;
        int got = sol.orangesRotting(matrix);
        bool ok = (got == ts[i].expected);
        passed += ok;

        cout << (ok ? "PASS" : "FAIL") << "  #" << i + 1 << " " << ts[i].name;
        if (!ok) {
            cout << "  (expected " << ts[i].expected << ", got " << got << ")";
        }
        cout << "\n";
    }
    cout << passed << "/" << ts.size() << " passed\n";
    return 0;
}
