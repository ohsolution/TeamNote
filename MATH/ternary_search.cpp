#define LL long long

const int max_v = 1e5 + 7;
const LL INF = 1e18 + 7;

LL f(LL x)
{
    LL ret = 0;
    // do calculate
    return ret;
}

int main()
{
    LL l=LOWVALUE,r=HIGHVALUE; // range [l,r]
    while(r-l>=3) // reduce scope
    {
        LL lp = (l*2+r)/3; 
        LL rp = (l+r*2)/3;
        if(f(lp) <= f(rp)) r = rp; // get lowest value
        else l = lp;
    }

    LL ret = INF;
    fa(i,l,r+1) ret = min(f(i),ret); //find lowest value in last range 
}
