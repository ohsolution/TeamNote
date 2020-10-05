constexpr int MAXN = 5000000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }
}
void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}
