#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m)), vis(n, vector<int>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> g[i][j];
        }
    }

    queue<array<int, 3>> q;
    for(int i = 0; i < n - 1; ++i){
        for(int j = 0; j < m - 1; ++j){
            if(g[i][j]==g[i][j+1]&&g[i][j]==g[i+1][j]&&g[i][j]==g[i+1][j+1]){
                q.push({i, j, g[i][j]}); vis[i][j] = 1;
            }
        }
    }


    function<void (int, int)> fill = [&](int r, int c){
        g[r][c] = g[r+1][c] = g[r][c+1] = g[r+1][c+1] = -1;
    };

    function<int (int, int)> chk = [&](int r, int c){
        if(r < 0 || c < 0 || r + 1 >= n || c + 1 >= m || vis[r][c]) return 0;
        int first_num = 0;
        if(g[r][c] ^ -1){
            if(first_num == 0){
                first_num = g[r][c];
            } else if(first_num ^ g[r][c]){
                return 0;
            }
        }

        if(g[r+1][c] ^ -1){
            if(first_num == 0){
                first_num = g[r+1][c];
            } else if(first_num ^ g[r+1][c]){
                return 0;
            }
        }

        if(g[r][c+1] ^ -1){
            if(first_num == 0){
                first_num = g[r][c+1];
            } else if(first_num ^ g[r][c+1]){
                return 0;
            }
        }

        if(g[r+1][c+1] ^ -1){
            if(first_num == 0){
                first_num = g[r+1][c+1];
            } else if(first_num ^ g[r+1][c+1]){
                return 0;
            }
        }
        return first_num;
    };

    // function<void(void)> print = [&](){
    //     for(int i = 0; i < n; ++i){
    //         for(int j = 0; j < m; ++j){
    //             cout << g[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // };

    vector<array<int, 2>> dir = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    vector<array<int, 3>> ops;

    // 8 squares at most created
    while(q.size()){
        array<int, 3> pos = q.front(); q.pop();
        int r = pos[0], c = pos[1], color = pos[2];
        fill(r, c);
        // print();
        ops.push_back({r + 1, c + 1, color});
        // cout << "debugging: " << r + 1 << " " << c + 1 << " " << color << endl;
        for(array<int, 2>& d : dir){
            int nr = r+d[0], nc = c+d[1], val_q = chk(nr, nc);
            if(val_q){
                vis[nr][nc] = 1;
                q.push({nr, nc, val_q});
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(g[i][j]^-1){
                cout << -1 << '\n'; return 0;
            }
        }
    }

    reverse(ops.begin(), ops.end());
    cout << ops.size() << '\n';
    for(array<int, 3>& e : ops){
        cout << e[0] << " " << e[1] << " " << e[2] << '\n';
    }

    return 0;
}
