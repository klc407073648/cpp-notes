int shared = 1;

void swap(int*a,int *b)
{
    *a ^= *b ^= *a ^= *b;
}