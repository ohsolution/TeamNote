using cpx = complex<double>;
const double PI = acos(-1);

void fft(vector<cpx>& poly, cpx w)
{
    int n = poly.size();
    if(n == 1) return;

    vector<cpx> even(n >> 1), odd(n >> 1);
    for(int i = 0; i < n; i++) {
        if(i & 1) odd[i >> 1] = poly[i];
        else even[i >> 1] = poly[i];
    }
    fft(even, w * w);
    fft(odd, w * w);
    cpx wp(1, 0);
    for(int i = 0; i < (n >> 1); i++) {
        poly[i] = even[i] + wp * odd[i];
        poly[i + n / 2] = even[i] - wp * odd[i];
        wp = wp * w;
    }
}

void mul(vector<int>& a, vector<int>& b, vector<int>& c)
{
    vector<cpx> ca(a.begin(), a.end());
    vector<cpx> cb(b.begin(), b.end());
    vector<cpx> cc;
    int n = 1;
    while(n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;
    ca.resize(n);
    cb.resize(n);
    cc.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    fft(ca, w);
    fft(cb, w);

    for(int i = 0; i < n; i++) {
        cc[i] = ca[i] * cb[i];
    }

    fft(cc, cpx(w.real(), -w.imag()));
    c.resize(n);
    for(int i = 0; i < n; i++) {
        c[i] = round(cc[i].real() / n);
    }
}
