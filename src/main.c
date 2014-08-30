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

#include "../config.h"
#include <td.h>

#ifndef BASH_LOADABLE
#include <getopt.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef BASH_LOADABLE
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>
#endif

#ifndef BASH_LOADABLE
#define NAME    PACKAGE_NAME
#else
#define NAME    PACKAGE_NAME ".bash"
#endif
#define USAGE   PACKAGE_NAME " [OPTIONS] [--] [[duration] ...]"

#define PRINT_VERSION()  puts(NAME " " PACKAGE_VERSION)

#ifndef BASH_LOADABLE
#define GETOPT()  getopt(argc, argv, "hVaPp::")
#define OPTARG    optarg
#else
#define GETOPT()  internal_getopt(list, "hVaPp;")
#define OPTARG    list_optarg
#endif
#define URL_WEB   "https://github.com/livibetter/td.sh"
#define URL_BUG   "https://github.com/livibetter/td.sh/issues"


char *td_doc[] = {
  "Convert seconds to human readable time duration.",
  "",
  "Options:",
  "",
  "  -h         display this help message",
  "  -V         display version string",
  "  -a         print all numbers and units",
  "  -P         unit string padding",
  "  -p[X]      number padding using character X",
  (char *) NULL
};


void
print_help () {
  unsigned int i;

  puts("Usage: " USAGE);
  for (i = 0; i < sizeof(td_doc) / sizeof(char *); i++)
    if (td_doc[i])
      puts(td_doc[i]);

  printf("\n"\
         "Report bugs to <" URL_BUG ">\n"\
         "Home page: <" URL_WEB ">\n");
}


int
#ifndef BASH_LOADABLE
main(int argc, char *argv[])
#else
td_builtin (WORD_LIST *list)
#endif
{
  int i;
  int opt;
  bool print_all_numbers = false;
  bool pad_units = false;
  char pad_char = '\0';
  long long t;

#ifdef BASH_LOADABLE
  reset_internal_getopt();
#endif
  while ((opt = GETOPT()) != -1) {
    switch (opt) {
    case 'h':
      print_help();
      goto out;
    case 'V':
      PRINT_VERSION();
      goto out;
    case 'a':
      print_all_numbers = true;
      break;
    case 'P':
      pad_units = true;
      break;
    case 'p':
      if (!OPTARG)
        pad_char = ' ';
      else
        pad_char = OPTARG[0];
      break;
    default:
#ifndef BASH_LOADABLE
      fprintf(stderr, "Usage: " USAGE "\n");
      return EXIT_FAILURE;
#else
      return EX_USAGE;
#endif
    }
  }

#ifndef BASH_LOADABLE
  for (i = optind; i < argc; i++) {
    t = atoll(argv[i]);
#else
  for (list = loptend; list; list = list->next) {
    t = atoll(list->word->word);
#endif
    print_td(t, print_all_numbers, pad_units, pad_char);
  }

out:
#ifndef BASH_LOADABLE
  return EXIT_SUCCESS;
#else
  return EXECUTION_SUCCESS;
#endif
}


#ifdef BASH_LOADABLE
struct builtin td_struct = {
  "td",
  td_builtin,
  BUILTIN_ENABLED,
  td_doc,
  USAGE,
  0
};
#endif
