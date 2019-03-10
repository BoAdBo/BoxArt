// didn't pass, TLE
class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    return isValidSudoku(board, 0, 0);
  }

  bool isValidSudoku(std::vector<std::vector<char>>& board, int i, int j) {
    if (i == 9 && j == 9) {
      for (int k = 0; k < 9; ++ k) {
        int row = k / 3;
        int col = k % 3;
        std::fill(std::begin(mask), std::end(mask), false);

        for (int n = 0; n < 9; ++ n) {
          int r = n / 3;
          int c = n % 3;
          mask[intBoard[row * 3 + r][col * 3 + c] - 1] = true;
        }
        for (int m = 0; m < 9; ++ m) {
          if (!mask[m]) return false;
        }
      }
      return true;
    } else if (i == 9) {

      // std::cout << "damned" << '\n';
      // check for column consistency
      std::fill(std::begin(mask), std::end(mask), false);

      for (int m = 0; m < 9; ++ m)
        mask[intBoard[m][j] - 1] = true;

      for (int m = 0; m < 9; ++ m)
        if (!mask[m]) return false;

      return isValidSudoku(board, 0, j+1);
    } else if (j == 9) {
      assert(false);
      // check for row consistency
      std::fill(std::begin(mask), std::end(mask), false);

      for (int m = 0; m < 9; ++ m)
        mask[intBoard[i][m] - 1] = true;

      for (int m = 0; m < 9; ++ m)
        if (!mask[m]) return false;

      return false;
      // return isValidSudoku(board, )
    } else {
      // fill in the blanks
      if (board[i][j] == '.') {
        for (int n = 1; n <= 9; ++ n) {
          intBoard[i][j] = n;
          if (isValidSudoku(board, i+1, j)) return true;
        }
        return false;
      } else {
        intBoard[i][j] = board[i][j] - '0';
        return isValidSudoku(board, i+1, j);
      }
    }
  }

  bool mask[9];
  int intBoard[9][9];
};
