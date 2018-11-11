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
        '&', '+', '&', '&', '+', '+'
};
int book[Row][Col] {}, step = 0, range[4][2] {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool is_end = false;
Map_list<int, pair<int, int>> ml(0, pair<int, int>(0, 0));
auto it_head = ml.begin();
pair<int, pair<int, int>> pr;

int main() {
    int x, y;
    while(it_head != ml.end()) {
        pr = *it_head;
        for(int i = 0; i < 4; ++i) {
            x = pr.second.first + range[i][0], y = pr.second.second + range[i][1];
            if(x < 0 || x >= Row || y < 0 || y >= Col || book[x][y] || map[x][y] == '&')
                continue;
            ml.push_back(++step, pair<int, int>(x, y));
            if(map[x][y] == '0') {
                is_end = true;
                break;
            }
            book[x][y] = step;
        }
        if(is_end) break;
        ++it_head;
    }

    for_each(ml.begin(), ml.end(), [](const pair<int, pair<int, int>>& pr){
        cout << pr.first << ":(" << pr.second.first << "," << pr.second.second << "); ";
    }), NHR;

    for (int j = 0; j < Row; ++j) {
        for (int i = 0; i < Col; ++i)
            //cout << (book[j][i] ? '@' : map[j][i]) << " ";
            if(book[j][i])
                cout << book[j][i] << " ";
            else
                cout << map[j][i] << " ";
        cout << endl;
    }

    return 0;
}