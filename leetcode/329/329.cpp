// first version
// row major storage two dimension array
template <typename T>
class MultiDim{
private:
  std::size_t row;
  std::size_t col;
  std::vector<T> storage;

public:
  explicit MultiDim() : row(0), col(0)
    { }

  explicit MultiDim(std::size_t row, std::size_t col)
    : row(row), col(col), storage(row * col)
    { }

  explicit MultiDim(std::size_t row, std::size_t col, const T&& val)
    : row(row), col(col), storage(row * col, val)
    { }

  T& operator() (std::size_t row_index, std::size_t col_index) {
    return storage[row_index * this->col + col_index];
  }

  const T& operator() (std::size_t row_index, std::size_t col_index) const {
    return storage[row_index * this->col + col_index];
  }
};

class Solution {
public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    // assume matrix[0].size == matrix[k].size for all k
    if (matrix.size() == 0 || matrix.front().size() == 0) return 0;
    MultiDim<int> dist(matrix.size(), matrix.front().size(), 0);
    int max = 0;
    for (int i = 0; i < matrix.size(); ++ i) {
      for (int j = 0; j < matrix[i].size(); ++ j) {
        if (dist(i, j) == 0) {
          int length = dfs(i, j, matrix, dist);
          if (max < length)
            max = length;
        }
      }
    }
    return max;
  }

  int dfs(int row, int col, const std::vector<std::vector<int>>& matrix,
          MultiDim<int>& dist) {
    int max = 0;
    const int bound_bottom = matrix.size();
    const int bound_right = matrix[0].size();
    const std::vector<std::pair<int, int>> dirs =
      {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // for all neighbours
    for (const auto& dir : dirs) {
      int next_row = row + dir.first;
      int next_col = col + dir.second;

      if (next_row < bound_bottom && next_row >= 0 &&
          next_col < bound_right && next_col >= 0 &&
          matrix[row][col] < matrix[next_row][next_col]) {
        // dist == 0 means that it's not visited yet,
        // or it doesn't have any neighbour with smaller value
        int length;
        if (dist(next_row, next_col) == 0)
          length = dfs(next_row, next_col, matrix, dist);
        else
          length = dist(next_row, next_col) + 1;

        if (max < length)
          max = length;
      }
    }
    // memorize the longest increasing path to this node
    dist(row, col) = max;
    return max + 1;
  }
};
