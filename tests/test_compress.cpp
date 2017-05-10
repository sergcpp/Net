#include "test_common.h"

#include <cstdio>

#include "../Compress.h"

void test_compress() {
    net::Packet test_buf(1024);
    for (int i = 0; i < 256; i++) {
        test_buf[i] = (uint8_t)(i % 255);
    }

    for (int i = 256; i < 768; i++) {
        test_buf[i] = 0;
    }

    for (int i = 768; i < test_buf.size(); i++) {
        test_buf[i] = (uint8_t)(i % 255);
    }

    net::Packet compr = net::CompressLZO(test_buf);

    printf("size before %i, size after %i\n", int(test_buf.size()), int(compr.size()));

    net::Packet decompr = net::DecompressLZO(compr);

    assert(decompr.size() == test_buf.size());
    assert(test_buf == decompr);
}