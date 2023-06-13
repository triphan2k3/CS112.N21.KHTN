#include "testlib.h"

using namespace std;

void swap_str(char **str1_ptr, char **str2_ptr) {
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

int n = 0;

int main(int argc, char* argv[]) {
    swap_str(&argv[2], &argv[3]);
    registerTestlibCmd(argc, argv);

    int n = 0;
    while (!ans.seekEof()) {
        ++n;
        if (n > 1)
        if (!ouf.seekEoln()) quitf(_wa, "WA");

        if (ouf.seekEoln()) quitf(_wa, "WA");
        if (ouf.seekEof()) quitf(_wa, "WA");

        double uans = ouf.readDouble();
        double jans = ans.readDouble(0, 1);

        if (!doubleCompare(jans, uans, 1E-10)) quitf(_wa, "WA");
    }

    if (!ouf.seekEof()) quitf(_wa, "WA");

    quitf(_ok, "AC");

    return 0;
}
