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

    const T neutral;
    const Func *f;

    Segtree(int n, T neut, Func f): N(n),data(4*n, neut), neutral(neut), f(f) {

    }
    void update(int p, int v) {
        return update(p, v, 0, N-1, 0);
    }

    void update(int p, int v, int l, int r, int x) {
        if (p > r || p < l) {
            return;
        }
        if(l == r) {
            data[x] = v;
        }
        else {
            int mid = (l+r)/2;
            update(p, v, l, mid, left(x));
            update(p, v, mid+1, r, right(x));
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


constexpr int INF = 100;

int main() {

    Segtree<int(int,int), int> seg_min(10, INF, [](int a, int b) {return min(a, b);});

    for(int i = 0; i < 10; ++i) {
        seg_min.update(i, i+1);
        printf("updated %d %d\n", i, i+1);
        for(int i = 0; i < 10*4; ++i)  {
            printf("(%d, %d) ", i, seg_min.data[i]);
        }
        cout << '\n';
    }

    seg_min.print(0, 0, 10-1, 0);
    
    for(int i = 0; i < 10; ++i) {
        printf("query %d %d %d\n", i, 10-1, seg_min.query(i, 10-1));

    }    
}
