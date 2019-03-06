class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        if(m == 0) return 0;
        n = matrix[0].size();
        if(n == 0) return 0;

        len = 0;
        paths = vector(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                len = max(len, dfs(matrix, i, j));
            }
        }
        return len;
    }

private:
    int dfs(vector<vector<int>>& board, int i, int j) {
        if(paths[i][j] == 0) {
            for(auto d : directions) {
                int x = i + d.first;
                int y = j + d.second;
                if(x >= 0 && x < m && y >= 0 && y < n && board[x][y] < board[i][j]) {
                    paths[i][j] = max(paths[i][j], dfs(board, x, y));
                }
            }
            paths[i][j]++;
        }
        return paths[i][j];
    }

    const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<int>> paths;
    int m;
    int n;
    int len;
};
