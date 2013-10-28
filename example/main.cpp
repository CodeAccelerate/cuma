#include "IO/JpegIO.h"
#include <cstdio>

int main(int argc, char **argv) {
  int status = read_JPEG_file("/Users/ypzhang/Downloads/espresso.jpg");
  printf("status = %d.\n", status);
  return 0;
}
