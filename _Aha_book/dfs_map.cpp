#include "../common.h"
#include <vector>
#include <algorithm>
#include "../Map_list.h"

const int Col = 6, Row = 7;
char map[Row][Col] = {
        '+', '+', '+', '+', '+', '+',
        '&', '+', '&', '&', '&', '+',
        '+', '+', '&', '+', '&', '+',
        '+', '&', '&', '+', '+', '0',
        '+', '+', '+', '+', '+', '&',
        '&', '+', '+', '&', '+', '&',
        '&', '+', '&', '&', '+', '&'
};
int book[Row][Col] {}, total = 0;
Map_list<int, int*> ml;

void show_map(const char arr[][Col], const int row, const int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) cout << arr[i][j] << " ";
        cout << endl;
    }
}

int* book_arr(const int book[Row][Col]) {
    int* tmp = new int[Row * Col];
    for(int i = 0; i < Row; ++i)
        for(int j = 0; j < Col; ++j) {
            tmp[i * Col + j] = book[i][j];
        }
    return tmp;
}

void dfs(int x, int y, int depth) {
    if(x < 0 || x == Row || y < 0 || y == Col) return;
    if(map[x][y] == '0') {
        ml.push_back(depth, book_arr(book));
        ++total;
        return;
    }
    if(book[x][y] == 0 && map[x][y] != '&') {
        book[x][y] = 1;
        dfs(x, y + 1, depth + 1);
        dfs(x + 1, y, depth + 1);
        dfs(x, y - 1, depth + 1);
        dfs(x - 1, y, depth + 1);
        book[x][y] = 0;
    }
}

int main() {
    show_map(map, Row, Col);
    HR;
    dfs(0, 0, 0);
    ml.sort(false), ml.reverse();
    for_each(ml.begin(), ml.end(), [](const pair<int, int*>& pr){
        cout << "step:" << pr.first << endl;
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j)
                cout << (pr.second[i * Col + j] ? '@' : map[i][j]) << " ";
            cout << endl;
        }
        delete [] pr.second;
        HR;
    });
    cout << total << " kinds of ways to get destination, the minimal is " << ml.back().first;
    return 0;
}

