// https://jutge.org/problems/P57511_es/submissions
// Submitted on 2022-02-28. Was part of a technical interview and had to programmed in under an hour

#include <bits/stdc++.h>
using namespace std;

pair<int, int> id_to_coords(const string &a) {
   return make_pair(a[0] - 'a', a[1] - '1');
}

struct piece {
   int x, y;
   char type=0;
};

vector<pair<int, int>> threatened_squares(piece p, const vector<vector<char>> &board) {
   vector<pair<int, int>> moves;
   int i = p.x;
   int j = p.y;
   if (p.type == 'T' or p.type == 'D') {
      for (int k = 1; k < 8; ++k) {
         int x = i + k;
         int y = j;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i - k;
         int y = j;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i;
         int y = j + k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i;
         int y = j - k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
   }
   if (p.type == 'A' or p.type == 'D') {
      for (int k = 1; k < 8; ++k) {
         int x = i + k;
         int y = j + k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i - k;
         int y = j + k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i + k;
         int y = j - k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }
      for (int k = 1; k < 8; ++k) {
         int x = i - k;
         int y = j - k;
         if (0 <= x and x < 8 and 0 <= y and y < 8) {
            moves.emplace_back(x, y);
            if (board[x][y]) break;
         }
         else {
            break;
         }
      }      
   }

   if (p.type == 'C') {
      vector<pair<int, int>> v = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
      for (auto [x, y]: v) {
         moves.emplace_back(i + x, y + j);
      }
   }
   if (p.type == 'R') {
      vector<pair<int, int>> v = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
      for (auto [x, y]: v) {
         moves.emplace_back(i + x, y + j);
      }
   }

   return moves;
}

bool is_mate(pair<int, int> king, const vector<vector<char>> &board) {
   map<pair<int, int>, bool> threatened;
   vector<pair<int, int>> v({{0, 0}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}});
   for (auto [x, y]: v) {
      int i = x + king.first;
      int j = y + king.second;
      if (0 <= i and i < 8 and 0 <= j and j < 8)
         threatened[{i, j}] = false;
   }
   for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
         if (board[i][j] and board[i][j] != 'N') {
            piece p;
            p.x = i;
            p.y = j;
            p.type = board[i][j];
            for (auto [x, y]: threatened_squares(p, board)) {
               threatened[{x, y}] = true;
            }
         }
      }
   }
   for (auto [c, b]: threatened) {
      if (!b)
         return false;
   }
   return true;
}

int main() {
   string king;
   while (cin >> king) {
      int n;
      cin >> n;
      pair<int, int> k = id_to_coords(king.substr(1, 2));
      vector<vector<char>> board(8, vector<char>(8, 0));
      for (int i = 0; i < n; ++i) {
         string piece;
         cin >> piece;
         pair<int, int> c = id_to_coords(piece.substr(1, 2));
         board[c.first][c.second] = piece[0];
      }
      pair<int, int> mate_coords;
      char mate_piece;
      int mates = 0;
      board[k.first][k.second] = 'N';
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            if (board[i][j] and board[i][j] != 'N') {
               piece p;
               p.x = i;
               p.y = j;
               p.type = board[i][j];
               for (auto m: threatened_squares(p, board)) {
                  if (0 <= m.first and m.first < 8 and 0 <= m.second and m.second < 8 and board[m.first][m.second] == 0) {
                     if (board[i][j] == 'R' and max(abs(m.first - k.first), abs(m.second - k.second)) == 1)
                        continue;
                     vector<vector<char>> board2 = board;
                     board2[i][j] = 0;
                     board2[m.first][m.second] = board[i][j];
                     board2[k.first][k.second] = 0;
                     if (is_mate(k, board2)) {
                        ++mates;
                        mate_coords = {m.first, m.second};
                        mate_piece = board[i][j];
                     }
                  }
               }
            }
      if (mates == 0) {
         cout << "NO\n";
      }
      else if (mates == 1) {
         cout << mate_piece << (char)('a' + mate_coords.first) << 1 + mate_coords.second << '\n';
      }
      else {
         cout << ">1\n";
      }
   }
}
