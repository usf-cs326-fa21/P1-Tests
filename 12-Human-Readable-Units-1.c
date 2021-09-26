#if 0
    awk -F':' '{print $3}' /etc/passwd | sort -n > "${TEST_DIR}/inputs/all_uids"
    source "${TEST_DIR}/lib/crunner" -linspector
#endif

#include <limits.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"
#include "procfs.h"
#include "util.h"

test_start("Tests human_readable_size function.");

subtest("Comparing output against known values",
{
    char buf[128];
    human_readable_size(buf, 128, 0, 1);
    test_assert_str(buf, "==", "0.0 KiB", 500);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 1023, 1);
    test_assert_str(buf, "==", "1023.0 KiB", 500);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 1024, 8);
    test_assert_str(buf, "==", "1.00000000 MiB", 500);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 34359738367, 1);
    test_assert_str(buf, "==", "32.0 TiB", 500);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 2844524, 1);
    test_assert_str(buf, "==", "2.7 GiB", 500);
    test_printf("%s\n", buf);

    // disabling incorrect test case (fa '21): should be EiB here, not ZiB!
//    human_readable_size(buf, 128, 472877960873902080, 1);
//    test_assert_str(buf, "==", "420.0 ZiB", 500);
//    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 129049729231119, 2);
    test_assert_str(buf, "==", "117.37 PiB", 500);
    test_printf("%s\n", buf);
});

test_end
