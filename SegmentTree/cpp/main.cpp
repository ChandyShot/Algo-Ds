// Segment tree range sum with point update

#include <bits/stdc++.h>

using namespace std;

int get_segment_size(int n){
    int size = 1;
    for(; size < n; size <<= 1);
    return size<<1;
}

void make_tree(int *a, int &n, int *tree, int &seg_size, int idx, int lo, int hi){
    if(lo == hi){
        tree[idx] = a[lo];
        return;
    }

    int mid = (lo + hi)>>1;
    int left = 2*idx;
    int right = left+1;
    make_tree(a, n, tree, seg_size, left, lo, mid);
    make_tree(a, n, tree, seg_size, right, mid+1, hi);
    tree[idx] = tree[left] + tree[right];
}

void build_tree(int *a, int &n, int *tree, int &seg_size){
    make_tree(a, n, tree, seg_size, 1, 0, n-1);
}

int make_query(int *tree, int ts, int te, int idx, int &lo, int &hi){
    if(lo <= ts && hi >= te){
        return tree[idx];
    }

    if(hi < ts || lo > te){
        return 0;
    }

    int mid = (ts + te)>>1;
    int left = make_query(tree, ts, mid, 2*idx, lo, hi);
    int right = make_query(tree, mid+1, te, 2*idx+1, lo, hi);

    return left + right;
}

int query(int *tree, int &n, int lo, int hi){
    if(lo > hi || lo < 0 || hi >= n){
        cout<<"Invalid Query"<<endl;
        return -1;
    }

    return make_query(tree, 0, n-1, 1, lo, hi);
}

void make_point_update(int *a, int ts, int te, int *tree, int idx, int i, int val){
    if(ts == te){
        a[i] = val;
        tree[idx] = val;
        return;
    }

    int mid = (ts + te) / 2;
    if(i >= ts && i <= mid){
        make_point_update(a, ts, mid, tree, 2*idx, i, val);
    }
    else{
        make_point_update(a, mid+1, te, tree, 2*idx+1, i, val);
    }

    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

void point_update(int *a, int n, int *tree, int seg_size, int i, int val){
    if(i < 0 || i >= n){
        cout<<"invalid point update operation"<<endl;
        return;
    }

    return make_point_update(a, 0, n-1, tree, 1, i, val);
}

int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    int seg_size = get_segment_size(n);
    int tree[seg_size];
    build_tree(a, n, tree, seg_size);

    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            int lo, hi;
            cin>>lo>>hi;
            cout<<query(tree, n, lo, hi)<<endl;
        }
        else if(type == 2){
            int i, val;
            cin>>i>>val;
            point_update(a, n, tree, seg_size, i, val);
        }
    }

    return 0;
}
