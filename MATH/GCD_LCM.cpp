int gcd(int a, int b)
{
    if(a < b)
    {
        int t = a;
        a = b;
        b = t;
    }
    while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
