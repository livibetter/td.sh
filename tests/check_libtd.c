/*
 * libtd uniti test
 * Copyright (c) 2014 Yu-Jie Lin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>
#include <stdlib.h>

#include <check.h>

#include "../lib/td.h"

#define \
TEST_SPRINT_TD(str, t, all, pad, ch, expect) \
  do {                                       \
    str[0] = '\0';                           \
    sprint_td(str, t, all, pad, ch);         \
    ck_assert_str_eq(str, expect);           \
  } while (false);

START_TEST (test_libtd)
{
  char str[64] = "";

  TEST_SPRINT_TD(str,     0, false, false, '\0', "0 seconds");
  TEST_SPRINT_TD(str,     1, false, false, '\0', "1 second");
  TEST_SPRINT_TD(str,    -1, false, false, '\0', "1 second");
  TEST_SPRINT_TD(str,     2, false, false, '\0', "2 seconds");
  TEST_SPRINT_TD(str,    60, false, false, '\0', "1 minute");
  TEST_SPRINT_TD(str,    61, false, false, '\0', "1 minute 1 second");
  TEST_SPRINT_TD(str,  3599, false, false, '\0', "59 minutes 59 seconds");
  TEST_SPRINT_TD(str,  3600, false, false, '\0', "1 hour");
  TEST_SPRINT_TD(str,  3601, false, false, '\0', "1 hour 1 second");
  TEST_SPRINT_TD(str,  3660, false, false, '\0', "1 hour 1 minute");
  TEST_SPRINT_TD(str,  3661, false, false, '\0', "1 hour 1 minute 1 second");
  TEST_SPRINT_TD(str, 86400, false, false, '\0', "1 day");

  TEST_SPRINT_TD(str,       86400 + 86400 - 1, false, false, '\0', "1 day 23 hours 59 minutes 59 seconds");
  TEST_SPRINT_TD(str,   2 * 86400 + 86400 - 1, false, false, '\0', "2 days 23 hours 59 minutes 59 seconds");
  TEST_SPRINT_TD(str, 366 * 86400         + 1, false, false, '\0', "366 days 1 second");

  TEST_SPRINT_TD(str,     1, false,  true, '\0', "1 second ");
  TEST_SPRINT_TD(str,    60, false,  true, '\0', "1 minute ");
  TEST_SPRINT_TD(str,    60, false,  true,  ' ', " 1 minute ");
  TEST_SPRINT_TD(str,    60, false,  true,  '0', "01 minute ");

  TEST_SPRINT_TD(str,     0,  true, false, '\0', "0 days 0 hours 0 minutes 0 seconds");

  TEST_SPRINT_TD(str,    60,  true, false,  ' ', " 0 days  0 hours  1 minute  0 seconds");
  TEST_SPRINT_TD(str,    60,  true,  true, '\0', "0 days 0 hours 1 minute  0 seconds");
  TEST_SPRINT_TD(str,    60,  true,  true,  ' ', " 0 days  0 hours  1 minute   0 seconds");
}
END_TEST

Suite *
libtd_suite (void)
{
  Suite *suite = suite_create("libtd");

  TCase *tc_libtd = tcase_create("libtd");
  tcase_add_test(tc_libtd, test_libtd);
  suite_add_tcase(suite, tc_libtd);

  return suite;
}

int
main (void)
{
  int number_failed;

  Suite *s = libtd_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

