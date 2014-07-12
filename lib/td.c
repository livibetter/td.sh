/***********************************************************************************/
/* td.c Converting seconds to human readable time duration.                        */
/* Copyright (c) 2014 Yu-Jie Lin                                                   */
/*                                                                                 */
/* Permission is hereby granted, free of charge, to any person obtaining a copy of */
/* this software and associated documentation files (the "Software"), to deal in   */
/* the Software without restriction, including without limitation the rights to    */
/* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies   */
/* of the Software, and to permit persons to whom the Software is furnished to do  */
/* so, subject to the following conditions:                                        */
/*                                                                                 */
/* The above copyright notice and this permission notice shall be included in all  */
/* copies or substantial portions of the Software.                                 */
/*                                                                                 */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   */
/* SOFTWARE.                                                                       */
/***********************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *units[] = {"second", "minute", "hour", "day"};
int n_units = sizeof(units) / sizeof(char *);

void
print_td(long long t, bool print_all_numbers, bool pad_units, char pad_char)
{
  int i;
  long long n[] = {
    abs(t) % 60,
    abs(t) / 60 % 60,
    abs(t) / 3600 % 24,
    abs(t) / 86400
  };
  /* space between two components */
  bool need_space = false;

  if (t == 0) {
    printf("0 seconds");
    return;
  }

  for (i = n_units - 1; i >= 0; i--) {
    if (n[i] || print_all_numbers) {
      if (need_space) {
        printf(" ");
        need_space = false;
      }
      if (n[i] < 10)
        printf("%c", pad_char);
      if (n[i] == 1) {
        if (pad_units)
          printf("%lld %s ", n[i], units[i]);
        else
          printf("%lld %s", n[i], units[i]);
      } else
        printf("%lld %ss", n[i], units[i]);
      need_space = true;
    }
  }
  printf("\n");
}
