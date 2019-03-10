class Solution {
public:
  inline int toLocal(int row, int col) {
    return (row / 3) * 3 + col / 3;
  }

  bool isValidSudoku(vector<vector<char>>& board) {
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
          intBoard[i][j] = num + 1;
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

    return true;
  }

  // there are each of them 9 regions
  // for restriction
  bool takeRow[9][9];
  bool takeCol[9][9];
  bool takeLoc[9][9];
  int intBoard[9][9];
};
