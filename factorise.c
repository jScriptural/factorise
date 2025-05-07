/* FACTORISE
 *
 * Author: Jscriptural
 * email: isongjohn014@gmail.com
 *
 * Factorise a positive integer into its prime factors.
 * CAVEAT:  WHEN GIVEN A NEGATIVE NUMBER IT IGNORES THE SIGN
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

uint64_t fac[1024]={0};
int ind = 0;
typedef char* string;


void factors(uint64_t num);
int compar(const void *a, const void *b);
static int factorise(uint64_t num,uint64_t *x, uint64_t *y);



int main(int argc, string argv[])
{
  int64_t orig_num;

  for(int i =1; i < argc; ++i)
  {
    orig_num = strtol(argv[i], NULL, 10);
    
    //if number is negative
    //make it positive
    if(orig_num < 0)
      orig_num *= -1;

    uint64_t num = orig_num; 
    while(num != 0 && (num % 2) == 0)
    {
      fac[ind++] = 2;
      num /= 2;
    }

    if(num != 1)
      factors(num);


    //sort factors in ascending order
    if(ind > 1)
      qsort(fac,(size_t)ind, sizeof(uint64_t),&compar);

    printf("%ld: ",orig_num);
    for(int i=0; i < ind; ++i)
      printf("%ld ",fac[i]);

    printf("\n");
    ind = 0;
  }
  return 0;

}

void factors(uint64_t num)
{
  uint64_t x,y;
  if(factorise(num,&x,&y) == 0)
  {
    fac[ind++] = num;
    return;
  }

  factors(x);
  factors(y);
}

int factorise(uint64_t num,uint64_t *x, uint64_t *y)
{
  //This function uses fermat method
  //to factorise a number.
  //The general idea is that to
  //factorise a number say b, 
  //we look for a number n such that 
  //(n*n - b) = k*k, a perfect square.
  //implies that b = (n+k)(n-k);
  uint64_t j,int_k;
  double frac_k;

  j = (uint32_t) ceil(sqrt(num));

  frac_k = sqrt(j*j - num);
  int_k = (uint64_t) frac_k;

  while(frac_k != int_k)
  {
    ++j;
    frac_k = sqrt(j*j - num);
    int_k = (uint64_t) frac_k;
  }
  *x = j + int_k;
  *y = j - int_k;

  if(j < ((num+1)/2))
    return 1;
  else
    return 0;
}

int compar(const void *a, const void *b)
{
  int i, j;
  i = *(int *) a;
  j = *(int *)  b;

  return i - j;
}
