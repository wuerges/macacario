#include <bits/stdc++.h>
using namespace std;


inline int left(int x) {
    return x*2+1;
}

inline int right(int x) {
    return x*2+2;
}

template<typename Func, typename T>
struct Segtree {

    const int N;
    vector<T> data;
    vector<T> lazy;

    const T neutral;
    const Func *f;

    Segtree(int n, T neut, Func f): N(n), data(4*n, 0), lazy(4*n, 0), neutral(neut), f(f) {

    }
    void update(int a, int b, int v) {
        return update(a, b, v, 0, N-1, 0);
    }

    void push(int x, int l, int r) {
        data[x] += lazy[x];
        if(l != r) {
            lazy[right(x)] += lazy[x];
            lazy[left(x)] += lazy[x];
        }
        lazy[x] = 0;
    }

    void update(int a, int b, int v, int l, int r, int x) {
        push(x, l, r);
        if(l> b || r < a) {
            return;
        }
        if(a <= l && r <= b) {
            lazy[x] += v;
            push(x, l, r);
        }
        else {
            int mid = (l+r)/2;
            update(a, b, v, l, mid, left(x));
            update(a, b, v, mid+1, r, right(x));
            data[x] = f(data[left(x)], data[right(x)]);
        }

    }

    int query(int a, int b) {
        return query(a, b, 0, 0, N-1);
    }

    int query(int a, int b, int x, int l, int r) {
        if(l> b || r < a) {
            return neutral;
        }
        if(a <= l && r <= b) {
            return data[x];
        }
        else {
            int mid = (l+r)/2;
            int lr = query(a, b, left(x), l, mid);
            int rr = query(a, b, right(x), mid+1, r);
            return f(lr, rr);
        }
    }

    void print(int x, int l, int r,int ident) {
        int mid = (l+r) / 2;
        if(l!=r) {
            print(right(x), mid+1, r, ident+1);
        }
        for(int i = 0; i < ident; ++i) {
            cout << "  ";
        }
        printf("(%d,%d) = %d\n", l, r, data[x]);
        if(l!=r) {
            print(left(x), l, mid, ident+1);
        }
        
    }

};


constexpr int INF = 1e9;

int main() {

    
    // for(int i = 0; i < 10; ++i) {
    //     seg_min.update(i, 10-1, i+1);
    //     printf("updated %d %d\n", i, i+1);
    //     for(int i = 0; i < 10*4; ++i)  {
    //         printf("(%d, %d) ", i, seg_min.data[i]);
    //     }
    //     cout << '\n';
    // }

    // seg_min.print(0, 0, 10-1, 0);
    
    // for(int i = 0; i < 10; ++i) {
    //     printf("query %d %d %d\n", i, i, seg_min.query(i, 10-1));

    // }    


    int N;
    cin >> N;
    
    Segtree<int(int,int), int> seg_min(N, INF, [](int a, int b) {return min(a, b);});
    Segtree<int(int,int), int> seg_max(N, -INF, [](int a, int b) {return max(a, b);});
    Segtree<int(int,int), int> seg_sum(N, 0, [](int a, int b) {return a + b;});


    string line(N, ' ');
    
    string commands;
    cin >> commands;

    int P = 0;

    int max_p = 0;
    for(int i = 0; i < N; ++i) {
        char c = commands[i];

        char & o = line[P];
        if(c=='R') {
            P = min(N-1, P+1);
        }
        else if (c=='L') {
            P = max(0, P-1);
        }
        else {
            if(o==')') {
                seg_min.update(P, N-1, 1);
                seg_max.update(P, N-1, 1);
                seg_sum.update(P, P, 1);
            }
            else if(o=='(') {
                seg_min.update(P, N-1, -1);
                seg_max.update(P, N-1, -1);
                seg_sum.update(P, P, -1);
            }

            if(c=='(') {
                seg_min.update(P, N-1, 1);
                seg_max.update(P, N-1, 1);
                seg_sum.update(P, P, 1);            
            }
            else if(c==')') {
                seg_min.update(P, N-1, -1);
                seg_max.update(P, N-1, -1);
                seg_sum.update(P, P, -1);
            }

            o = c;
        }

        max_p = max(max_p, seg_max.query(0, N-1));

        bool min_ok = seg_min.query(0, N-1) >= 0;
        bool sum_ok = seg_sum.query(0, N-1) == 0;

        if(i>0) cout << ' ';
        if(min_ok && sum_ok) {
            cout << seg_max.query(0, N-1);
        }
        else {
            cout << -1;
        }
    }
    cout <<'\n';
}