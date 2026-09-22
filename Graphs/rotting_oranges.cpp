#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfsRotten(vector<vector<int>> &matrix) {
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
                matrix[nr][nc] = 2;
                freshCount--;
                q.push({nr, nc});
            }
        }
        minutes++;
    }

    return (freshCount == 0) ? minutes : -1;
}

int main() {
    // Test Case 1: Standard case where all oranges can rot
    // Expected output: 4
    vector<vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    cout << "Test 1: " << bfsRotten(grid1) << " (Expected: 4)\n";

    // Test Case 2: Fresh orange is isolated, impossible to rot all
    // Expected output: -1
    vector<vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << "Test 2: " << bfsRotten(grid2) << " (Expected: -1)\n";

    // Test Case 3: No fresh oranges at the start
    // Expected output: 0
    vector<vector<int>> grid3 = {
        {0, 2}
    };
    cout << "Test 3: " << bfsRotten(grid3) << " (Expected: 0)\n";

    // Test Case 4: Only fresh oranges, no rotten oranges to start the spread
    // Expected output: -1
    vector<vector<int>> grid4 = {
        {1, 1},
        {1, 1}
    };
    cout << "Test 4: " << bfsRotten(grid4) << " (Expected: -1)\n";

    return 0;
}
