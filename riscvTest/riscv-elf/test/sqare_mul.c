
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

int pow(unsigned int x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;

  int tmp = pow(x, p>>1);
  if (p%2 == 0) return mul(tmp, tmp);
  else return  mul(x , mul(tmp, tmp));
}

int main()
{
    unsigned int a = 3;
    unsigned int b = 18;
    unsigned int c = pow(a,b);
    return c;
}