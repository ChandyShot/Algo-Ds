// Basic implementation of range sum query

#include <bits/stdc++.h>

using namespace std;

// https://kartikkukreja.wordpress.com/2014/11/09/a-simple-approach-to-segment-trees/
// http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/

int getSegmentTreeSize(int n){
    // size if power of two immediately greater than n;
    int size = 1;
    for(; size < n; size<<=1);
    return size<<1;
}

void make_tree(int *a, int n, int *tree, int seg_size, int idx, int lo, int hi){
    if(lo == hi){
        tree[idx] = a[lo];
        return;
    }

    int left =  2*idx;
    int right = left + 1;
    int mid = (lo + hi)/2;
    make_tree(a, n, tree, seg_size, left, lo, mid);
    make_tree(a, n, tree, seg_size, right, mid+1, hi);
    tree[idx] = tree[left] + tree[right];
}

void build_tree(int *a, int n, int *tree, int seg_size){
    make_tree(a, n, tree, seg_size, 1, 0, n-1);
}

int make_query(int *tree, int ts, int te, int qs, int qe, int ti){
    if(qs <= ts && qe >= te){
        return tree[ti];
    }

    if(qs > te || qe < ts){
        return 0;
    }

    int mid = (ts + te)/2;
    int left = make_query(tree, ts, mid, qs, qe, 2*ti);
    int right = make_query(tree, mid+1, te, qs, qe, 2*ti + 1);
    return left + right;
}

int query(int *tree, int n, int qs, int qe){
   if(qs < 0 || qe >= n || qs > qe){
       cout<<"Invalid Input"<<endl;
       return -1;
   }
   return make_query(tree, 0, n-1, qs, qe, 1);
}


int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i=0; i<n; i++)
        cin>>a[i];
    int seg_size = getSegmentTreeSize(n);
    int tree[seg_size];
    build_tree(a, n, tree, seg_size);
    int q;
    cin>>q;
    while(q--){
        int lo, hi;
        cin>>lo>>hi;
        cout<<query(tree, n, lo, hi)<<endl;
    }
    return 0;
}
