#include "../common.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../Map_list.h"

const int Col = 10, Row = 10, range[4][2] {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int map[Row][Col] = {
        1, 2, 1, 0, 0, 0, 0, 0, 2, 3,
        3, 0, 2, 0, 1, 2, 1, 0, 1, 2,
        4, 0, 1, 0, 1, 2, 3, 2, 0, 1,
        3, 2, 0, 0, 0, 1, 2, 4, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 1, 0, 1, 5, 4, 3, 0,
        0, 1, 2, 3, 1, 3, 6, 2, 1, 0,
        0, 0, 3, 7, 8, 6, 0, 1, 0, 2,
        0, 0, 0, 0, 0, 0, 0, 0, 3, 2
}, book[Row][Col] {}, num = 0;

Map_list<int, int> ml;
Map_list<int, int>::Iterator it_head;

void bfs() {
    int x, y;
    while(it_head != ml.end()) {
        for (int i = 0; i < 4; ++i) {
            x = (*it_head).first + range[i][0], y = (*it_head).second + range[i][1];
            if(x < 0 || x >= Row || y < 0 || y >= Col || book[x][y] || map[x][y] == 0)
                continue;
            book[x][y] = 1, map[x][y] = num;
            ml.push_back(x, y);
        }
        ++it_head;
    }
}

void reset(int x, int y) {
    ml.truncate();
    ml.push_back(x, y);
    it_head = ml.begin();
}

int main() {
    for (int j = 0; j < Row; ++j) {
        for (int i = 0; i < Col; ++i)
            if(map[j][i] > 0) --num, reset(j, i), bfs();
    }

    for (int j = 0; j < Row; ++j) {
        for (int i = 0; i < Col; ++i)
            cout << setw(3) << map[j][i];
        cout << endl;
    }

    return 0;
}
