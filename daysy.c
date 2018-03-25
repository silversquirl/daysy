#include "daysy.h"

// n starts at 1
void x_of_the_month(unsigned int n, int wday, struct tm *t) {
  time_t tt; // Temporary time_t
  struct tm *ttm; // Temporary tm

  // First day of month
  struct tm m1 = *t;
  m1.tm_mday = 1;
  m1.tm_isdst = -1; // Calculate DST
  tt = mktime(&m1);
  ttm = localtime(&tt);

  // First <wday> of month
  struct tm first = *ttm;
  first.tm_mday = (wday - ttm->tm_wday) % 7 + 1;
  first.tm_isdst = -1;
  tt = mktime(&first);
  ttm = localtime(&tt);

  // <n>th <wday> of month
  struct tm nth = *ttm;
  nth.tm_mday += 7 * (n - 1);
  nth.tm_isdst = -1;
  tt = mktime(&nth);
  *t = *localtime(&tt);
}
