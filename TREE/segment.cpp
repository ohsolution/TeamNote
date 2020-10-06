//Segment Tree
#define ll long long
#define SEG_SIZE 4000000
struct Data{ll val, flag;} seg[SEG_SIZE];
int x, y;
ll update_val;
ll make_seg(int e,int s=1, int pos=1){
    if(s == e){
        ll tmp; cin >> tmp;
        return seg[pos].val = tmp;
    }
    ll a = make_seg(s, (s + e) / 2, pos * 2);
    ll b = make_seg((s + e) / 2 + 1, e, pos * 2 + 1);
    return seg[pos].val = a + b;
}
void lazy(int s, int e, int pos){
    if (!seg[pos].flag) return;
    seg[pos].val += seg[pos].flag * (e - s + 1);
    if (s != e){seg[pos * 2].flag += seg[pos].flag; seg[pos * 2 + 1].flag += seg[pos].flag;}
    seg[pos].flag = 0;
}
ll sum(int s, int e, int pos){
    lazy(s, e, pos);
    if (e < x || y < s) return 0;
    if (x <= s && e <= y) return seg[pos].val;
    return sum(s, (s + e) / 2, pos * 2) + sum((s + e) / 2 + 1, e, pos * 2 + 1);
}
ll update(int s, int e, int pos){
    lazy(s, e, pos);
    if (e < x || y < s) return seg[pos].val;
    if (x <= s && e <= y){
        seg[pos].flag += update_val;
        lazy(s, e, pos);
        return seg[pos].val;
    }
    return seg[pos].val = update(s, (s + e) / 2, pos * 2) + update((s + e) / 2 + 1, e, pos * 2 + 1);
}
