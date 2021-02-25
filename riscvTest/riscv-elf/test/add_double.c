
unsigned int mul(unsigned int x, unsigned int y) {
    if(y==0){return 0;}
    if(y==1){return x;}
    
    if(y&0x01) {
        // add and double
        return x + mul( x+x, (y-1)>>1);
    } else {
        // double
        return mul( x+x, (y)>>1);
    }
}

int main()
{
    int a = 55;
    int b = 49;
    int c = mul(a,b);
    return c;
}