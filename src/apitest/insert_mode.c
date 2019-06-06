#include "libvim.h"
#include "minunit.h"

void test_setup(void) {
  vimInput("<Esc>");
  vimInput("<Esc>");
  vimExecute("e!");
}

void test_teardown(void) {

}

/* TODO: Get this test green */
/* MU_TEST(insert_count) { */
/*   vimInput("5"); */
/*   vimInput("i"); */
/*   vimInput("a"); */
/*   vimInput("\033"); */

/*   char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine()); */
/*   printf("LINE: %s\n", line); */
/*   mu_check(strcmp(line, "aaaaaThis is the first line of a test file") == 0); */
/* } */

MU_TEST(insert_beginning) {
  vimInput("I");
  vimInput("a");
  vimInput("b");
  vimInput("c");

  char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine());
  mu_check(strcmp(line, "abcThis is the first line of a test file") == 0);
}

MU_TEST(insert_cr) {
  vimInput("I");
  vimInput("a");
  vimInput("b");
  vimInput("c");
  vimInput("<CR>");

  char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine());
  mu_check(strcmp(line, "abc") == 0);
}

MU_TEST(insert_prev_line) {
  vimInput("O");
  vimInput("a");
  vimInput("b");
  vimInput("c");
  mu_check(vimWindowGetCursorLine() == 1);

  char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine());

  printf("LINE: %s\n", line);

  mu_check(strcmp(line, "abc") == 0);
}

MU_TEST(insert_next_line) {
  vimInput("o");
  vimInput("a");
  vimInput("b");
  vimInput("c");

  mu_check(vimWindowGetCursorLine() == 2);

  char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine());

  printf("LINE: %s\n", line);

  mu_check(strcmp(line, "abc") == 0);
}
MU_TEST(insert_end) {
  vimInput("A");
  vimInput("a");
  vimInput("b");
  vimInput("c");
  char_u *line = vimBufferGetLine(curbuf, vimWindowGetCursorLine());

  printf("LINE: %s\n", line);

  mu_check(strcmp(line, "This is the first line of a test fileabc") == 0);
}

MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    /* MU_RUN_TEST(insert_count); */
    MU_RUN_TEST(insert_prev_line);
    MU_RUN_TEST(insert_next_line);
    MU_RUN_TEST(insert_beginning);
    MU_RUN_TEST(insert_cr);
    MU_RUN_TEST(insert_end);
}

int main(int argc, char **argv) {
  vimInit(argc, argv);

  win_setwidth(5);
  win_setheight(100);

  buf_T *buf = vimBufferOpen("testfile.txt", 1, 0);

  MU_RUN_SUITE(test_suite);
  MU_REPORT();

  return minunit_status;
}