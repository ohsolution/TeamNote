constexpr int NINF = -2147483648;

int lis_num(int* d, int dNum)
{
    vector<int> res;
    res.push_back(NINF);

    for(int i = 0; i < dNum; i++) {
        if(res.back() < d[i]) res.push_back(d[i]);
        else {
            auto it = lower_bound(res.begin(), res.end(), d[i]);
            *it = d[i];
        }
    }

    return res.size();
}
