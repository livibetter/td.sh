/***********************************************************************************/
/* td: main.c - the C of td.sh                                                     */
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

#include <td.h>

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROGRAM "td"

int
main(int argc, char *argv[])
{
  int i;
  int opt;
  bool print_all_numbers = false;
  bool pad_units = false;
  char pad_char = '\0';
  long long t;

  while ((opt = getopt(argc, argv, "aPp::")) != -1) {
    switch (opt) {
    case 'a':
      print_all_numbers = true;
      break;
    case 'P':
      pad_units = true;
      break;
    case 'p':
      if (!optarg)
        pad_char = ' ';
      else
        pad_char = optarg[0];
      break;
    default:
      fprintf(stderr, "Usage %s [-P]", PROGRAM);
      exit(EXIT_FAILURE);
    }
  }

  for (i = optind; i < argc; i++) {
    t = atoll(argv[i]);
    print_td(t, print_all_numbers, pad_units, pad_char);
  }
  return 0;
}
