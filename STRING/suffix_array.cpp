constexpr int MAXN = 500005;
struct SANode
{
    int idx;
    int rank[2];
};
SANode sa[MAXN];
SANode saTmp[MAXN];
int rev[MAXN];
int cnt[MAXN];
int lcp[MAXN];

bool operator<(const SANode& l, const SANode& r)
{
    if(l.rank[0] == r.rank[0]) {
        return l.rank[1] < r.rank[1];
    }
    return l.rank[0] < r.rank[0];
}

void get_sa(const char* str, int sNum)
{
    for(int i = 0; i < sNum; i++) {
        sa[i].idx = i;
        sa[i].rank[0] = str[i];
        if(i + 1 < sNum) sa[i].rank[1] = str[i + 1];
        else sa[i].rank[1] = -1;
    }
    sort(sa, sa + sNum);

    for(int k = 4; k < 2 * sNum; k *= 2) {
        int rank0 = sa[0].rank[0];
        int rank1 = sa[0].rank[1];
        int cRank = 0;
        sa[0].rank[0] = 0;
        rev[sa[0].idx] = 0;

        for(int i = 1; i < sNum; i++) {
            if(sa[i].rank[0] == rank0 && sa[i].rank[1] == rank1) {
                rank0 = sa[i].rank[0];
                rank1 = sa[i].rank[1];
                sa[i].rank[0] = cRank;
            } else {
                rank0 = sa[i].rank[0];
                rank1 = sa[i].rank[1];
                sa[i].rank[0] = ++cRank;
            }
            rev[sa[i].idx] = i;
        }

        // ----- Counting sort버전, nextRank 기준으로 정렬(nextrank 구하면서 정렬) -----
        int maxRank = cRank + 1;
        memset(cnt, 0, sizeof(int) * (maxRank + 1));
        for(int i = 0; i < sNum; i++) {
            int nextI = sa[i].idx + k / 2;
            sa[i].rank[1] = (nextI < sNum) ? sa[rev[nextI]].rank[0] : -1;
            cnt[sa[i].rank[1] + 1]++;
        }
        for(int i = 1; i < maxRank + 1; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = sNum - 1; i >= 0; i--) {
            saTmp[--cnt[sa[i].rank[1] + 1]] = sa[i];
        }
        // rank 기준으로 정렬
        memset(cnt, 0, sizeof(int) * (maxRank + 1));
        for(int i = 0; i < sNum; i++) {
            cnt[sa[i].rank[0] + 1]++;
        }
        for(int i = 1; i < maxRank + 1; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = sNum - 1; i >= 0; i--) {
            sa[--cnt[saTmp[i].rank[0] + 1]] = saTmp[i];
        }
        // ----- 복잡하면 그냥 Sort버전 -----
        for(int i = 0; i < sNum; i++) {
            int nextI = sa[i].idx + k / 2;
            sa[i].rank[1] = (nextI < sNum) ? sa[rev[nextI]].rank[0] : -1;
        }
        sort(sa, sa + sNum);
        // -------------------------------
    }
}

void get_lcp(const char* str, int sNum)
{
    for(int i = 0; i < sNum; i++) {
        rev[sa[i].idx] = i;
    }

    int len = 0;
    for(int i = 0; i < sNum; i++) {
        int c1 = rev[i];
        if(c1 == sNum - 1) continue;
        int c2 = sa[c1 + 1].idx;
        while(str[i + len] == str[c2 + len]) {
            len++;
        }
        lcp[c1] = len;
        len = max(len - 1, 0);
    }
}
