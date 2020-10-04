// (a / b) % mod == (a * b^(mod-2)) % mod
LL divmod(LL a, LL b, LL mod)
{
    LL res = 1;
    LL ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}
