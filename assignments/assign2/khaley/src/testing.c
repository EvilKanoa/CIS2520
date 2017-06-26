/**
 * @file testing.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing tests for vault application
 */

 #include <stdio.h>
 #include "VaultUtilities.h"

int main()
{
    int i;
    int size;
    int hash;
    int numValues = 59;
    char *testValues[59];

    testValues[0] = "Google";
    testValues[1] = "YouTube";
    testValues[2] = "Facebook";
    testValues[3] = "Wikipedia";
    testValues[4] = "Yahoo!";
    testValues[5] = "Reddit";
    testValues[6] = "Google India";
    testValues[7] = "Amazon";
    testValues[8] = "Tmall";
    testValues[9] = "Twitter";
    testValues[10] = "Google Japan";
    testValues[11] = "Windows Live";
    testValues[12] = "Instagram";
    testValues[13] = "Sina Corp";
    testValues[14] = "Google Germany";
    testValues[15] = "Jingdong Mall";
    testValues[16] = "Google UK";
    testValues[17] = "LinkedIn";
    testValues[18] = "Google France";
    testValues[19] = "Google Russia";
    testValues[20] = "Google Brazil";
    testValues[21] = "Yahoo! Japan";
    testValues[22] = "Netflix";
    testValues[23] = "t.co";
    testValues[24] = "Google Hong Kong";
    testValues[25] = "Imgur";
    testValues[26] = "Google Italy";
    testValues[27] = "eBay";
    testValues[28] = "Google Spain";
    testValues[29] = "WordPress.com";
    testValues[30] = "MSN";
    testValues[31] = "AliExpress";
    testValues[32] = "Bing";
    testValues[33] = "Tumblr";
    testValues[34] = "Google Canada";
    testValues[35] = "Microsoft";
    testValues[36] = "Stack Overflow";
    testValues[37] = "Twitch";
    testValues[38] = "Blogspot";
    testValues[39] = "Amazon Japan";
    testValues[40] = "Google Mexico";
    testValues[41] = "Apple Inc.";
    testValues[42] = "Mail.ru";
    testValues[43] = "IMDb";
    testValues[44] = "Microsoft Office";
    testValues[45] = "Google Korea";
    testValues[46] = "GitHub";
    testValues[47] = "Pinterest";
    testValues[48] = "PayPal";
    testValues[49] = "Diply";
    testValues[50] = "Google Taiwan";
    testValues[51] = "Google Turkey";
    testValues[52] = "Google Australia";
    testValues[53] = "Amazon Germany";
    testValues[54] = "Google Indonesia";
    testValues[55] = "Microsoft Online Services";
    testValues[56] = "Amazon UK";
    testValues[57] = "Adobe Systems";
    testValues[58] = "Wikia";

    printf("Format: Value for hash, Hash\n");
    for (size = 20; size <= 120; size += 20) {
        printf("\nWith table size: %d\n", size);
        for (i = 0; i < numValues; i++) {
            hash = hashDescriptor(size, testValues[i]);
            printf("%s, %d\n", testValues[i], hash);
        }
    }

    return 0;
}
