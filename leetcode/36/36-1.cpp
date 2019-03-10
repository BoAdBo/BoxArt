class Solution {
public:
  inline int toLocal(int row, int col) {
    return (row / 3) * 3 + col / 3;
  }

  bool solveSudoku(vector<vector<char>>& board) {
    // std::fill(std::begin(takeRow), std::end(takeRow), false);
    // std::fill(std::begin(takeCol), std::end(takeCol), false);
    // std::fill(std::begin(takeLoc), std::end(takeLoc), false);
    assert(board.size() == 9 && board[0].size() == 9);
    std::fill(&takeRow[0][0], &takeRow[0][0] + sizeof(takeRow), false);
    std::fill(&takeCol[0][0], &takeCol[0][0] + sizeof(takeCol), false);
    std::fill(&takeLoc[0][0], &takeLoc[0][0] + sizeof(takeLoc), false);

    for (int i = 0; i < 9; ++ i) {
      for (int j = 0; j < 9; ++ j) {
        if (board[i][j] != '.') {
          int num = board[i][j] - '1';
          if (takeRow[i][num] ||
              takeCol[j][num] ||
              takeLoc[toLocal(i, j)][num]) {
            return false;
          }
          takeRow[i][num] = true;
          takeCol[j][num] = true;
          takeLoc[(i / 3) * 3 + j / 3][num] = true;
        }
      }
    }

    std::cout << std::boolalpha << solveSudoku(board, 0) << '\n';
    return true;
  }

  bool solveSudoku(std::vector<std::vector<char>>& board, int i) {
    // solution found
    if (i == 9 * 9) {
      return true;
    } else {
      int row = i / 9;
      int col = i % 9;
      if (board[row][col] == '.') {
        for (int n = 0; n < 9; ++ n) {
          // restriction violated
          if (takeRow[row][n] ||
              takeCol[col][n] ||
              takeLoc[toLocal(row, col)][n])  {
            continue;
          }
          char old = board[row][col];
          board[row][col] = n + '1';

          takeRow[row][n] = true;
          takeCol[col][n] = true;
          takeLoc[toLocal(row, col)][n] = true;
          // if this configuration make it through the end,
          // then we found a solution, propagate it
          if (solveSudoku(board, i + 1)) return true;
          // sadly doesn't work
          takeRow[row][n] = false;
          takeCol[col][n] = false;
          takeLoc[toLocal(row, col)][n] = false;
          board[row][col] = old;
        }
        // sadly, none of the number works
        return false;
      } else {
        // already fixed, next one
        return solveSudoku(board, i + 1);
      }
    }
  }

  // there are each of them 9 regions
  // for restriction
  bool takeRow[9][9];
  bool takeCol[9][9];
  bool takeLoc[9][9];
};
