#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if( strcmp(argv[1], "test") )
  {
    printf("Compare inconsistent\n");
  }
  else
  {
    printf("Compare consistent\n");
  }
  return 0;
}