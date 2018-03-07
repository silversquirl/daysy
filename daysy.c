#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const char *usage =
  "Usage: daysy [-f <format>] [-t <seconds>] <n> <weekday>\n"
  "\n"
  "Calculate the next <n>th <weekday> of the month\n"
  "\n"
  "Options:\n"
  "  -f <format>   Use <format> to format the resulting time [default: %x]\n"
  "  -t <seconds>  Use <seconds> as the input time rather than the current time\n"
  "  -h            This help page\n"
  "\n"
  "For more information, see daysy(1)\n";

const char *optstr = "f:t:h";

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

long parselong(char *s) {
  if (!*s) goto err;
  char *end;
  long res = strtol(s, &end, 10);
  if (*end) {
err:
    fprintf(stderr, "Invalid number for base 10: '%s'\n", optarg);
    exit(1);
  }
  return res;
}

int main(int argc, char *argv[]) {
  char *format = "%x";
  long seconds = -1;
  
  int c;
  while ((c = getopt(argc, argv, optstr)) > 0) {
    switch (c) {
    case '?': return 1;
    case 'f':
      format = optarg;
      break;
    case 't':
      seconds = parselong(optarg);
      break;
    case 'h':
      printf("%s", usage);
      return 0;
    }
  }

  if (optind + 2 != argc) {
    fprintf(stderr, "Incorrect number of arguments\n");
    return 1;
  }  

  int n = parselong(argv[optind]);
  int wday = parselong(argv[optind + 1]);

  time_t now = seconds < 0 ? time(NULL) : seconds;
  struct tm t = *localtime(&now);
  x_of_the_month(n, wday, &t);
  if (difftime(mktime(&t), now) < 0) {
    t.tm_mon += 1;
    x_of_the_month(n, wday, &t);
  }

  char buf[32];
  size_t chars = strftime(buf, sizeof buf, format, &t);
  printf("%*s\n", chars, buf);
}
