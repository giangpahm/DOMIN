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
            int mines = 0;
            for (int i = max(0, x - 1); i <= min(m - 1, x + 1); i++) {
                for (int j = max(0, y - 1); j <= min(n - 1, y + 1); j++) {
                    if (map[i][j] == '*') {
                        mines++;
                    }
                }
            }

            map[x][y] = mines + '0';

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
