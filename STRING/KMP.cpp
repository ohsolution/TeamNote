vector<int> fail;
vector<int> res;

void get_fail(const string& w)
{
    int wNum = w.size();
	fail.clear();
    fail.resize(wNum, 0);

    int j = 0;
    for(int i = 1; i < wNum; i++) {
        while(j > 0 && w[i] != w[j]) {
            j = fail[j - 1];
        }
        if(w[i] == w[j]) {
            fail[i] = j + 1;
            j++;
        }
    }
}

void kmp(const string& s, const string& w)
{
    get_fail(w);

    res.clear();

    int sNum = s.size();
    int wNum = w.size();

    int j = 0;
    for(int i = 0; i < sNum; i++) {

        while(j > 0 && s[i] != w[j]) {
            j = fail[j - 1];
        }

        if(s[i] == w[j]) {
            if(j == wNum - 1) {
                res.push_back(i - wNum + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
}
