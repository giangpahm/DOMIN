#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

void printMap(vector<vector<char>> map)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void expand(vector<vector<char>>& map, int x, int y)
{
    if (x < 0 || y < 0 || x >= map.size() || y >= map[0].size()) {
        return;
    }

    if (map[x][y] != 'X') {
        return;
    }

    int mines = 0;
    for (int i = max(0, x - 1); i <= min((int)map.size() - 1, x + 1); i++) {
        for (int j = max(0, y - 1); j <= min((int)map[0].size() - 1, y + 1); j++) {
            if (map[i][j] == '*') {
                mines++;
            }
        }
    }

    if (mines == 0) {
        map[x][y] = ' ';
        for (int i = max(0, x - 1); i <= min((int)map.size() - 1, x + 1); i++) {
            for (int j = max(0, y - 1); j <= min((int)map[0].size() - 1, y + 1); j++) {
                expand(map, i, j);
            }
        }
    }
    else {
        map[x][y] = mines + '0';
    }
}

int main()
{
    srand(time(NULL));

    int m, n, k;
    cin >> m >> n >> k;

    vector<vector<char>> map(m, vector<char>(n, 'X'));

    while (k > 0) {
        int i = rand() % m;
        int j = rand() % n;
        if (map[i][j] != '*') {
            map[i][j] = '*';
            k--;
        }
    }

    bool win = false;
    while (!win) {
        printMap(map);

        int x, y;
        cin >> x >> y;

        if (map[x][y] == '*') {
            cout << "YOU'RE DEAD!" << endl;
            map[x][y] = '+';
            printMap(map);
            break;
        }
        else {
            expand(map, x, y);

            bool finished = true;
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[0].size(); j++) {
                    if (map[i][j] == 'X') {
                        finished = false;
                        break;
                    }
                }
            }

            if (finished) {
                win = true;
                cout << "YOU WIN!" << endl;
                printMap(map);
            }
        }
    }

    return 0;
}
