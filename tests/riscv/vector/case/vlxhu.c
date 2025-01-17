/*
 * Copyright (c) 2021 T-Head Semiconductor Co., Ltd. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "testsuite.h"
#include "rvv_insn.h"

struct rvv_reg src0[] = {
    {
        .fixu16 = {
            {0xffa5, 0x0034, 0xff8c, 0x0074, 0xffcd, 0x0075, 0xff92, 0x007a, },
            {0x0060, 0x0019, 0x003c, 0xff91, 0xfffd, 0xffab, 0x0023, 0x0021, },
        },
    },
};

struct rvv_reg src1[] = {
    {
        .fixu16 = {
            {0x0000, 0x0002, 0x0004, 0x0006, 0x0008, 0x000a, 0x000c, 0x000e},
            {0x0010, 0x0012, 0x0014, 0x0016, 0x0018, 0x001a, 0x001c, 0x001e},
        },
        .fixu32 = {
            {0x00000000, 0x00000002, 0x00000004, 0x00000006, },
            {0x00000008, 0x0000000a, 0x0000000c, 0x0000000e, },
        },
        .fixu64 = {
            {0x0000000000000000, 0x0000000000000002, },
            {0x0000000000000004, 0x0000000000000006, }
        },

    },
};


struct rvv_reg dst0[] = {
    {
        .fixu16 = {
            {0xffa5, 0x0034, 0xff8c, 0x0074, 0xffcd, 0x0075, 0xff92, 0x007a, },
            {0x0060, 0x0019, 0x003c, 0xff91, 0xfffd, 0xffab, 0x0023, 0x0000, },
        },
        .fixu32 = {
            {0x0000ffa5, 0x00000034, 0x0000ff8c, 0x00000074, },
            {0x0000ffcd, 0x00000075, 0x0000ff92, 0x00000000, },
        },
        .fixu64 = {
            {0x000000000000ffa5, 0x0000000000000034, },
            {0x000000000000ff8c, 0x0000000000000000, },
        },
    },
    {
        .fixu16 = {
            {0xffa5, 0x1111, 0xff8c, 0x1111, 0xffcd, 0x1111, 0xff92, 0x1111, },
            {0x0060, 0x1111, 0x003c, 0x1111, 0xfffd, 0x1111, 0x0023, 0x1111, },
        },
        .fixu32 = {
            {0x0000ffa5, 0x11111111, 0x0000ff8c, 0x11111111, },
            {0x0000ffcd, 0x11111111, 0x0000ff92, 0x11111111, },
        },
        .fixu64 = {
            {0x000000000000ffa5, 0x1111111111111111, },
            {0x000000000000ff8c, 0x1111111111111111, },
        },
    },
    {
        .fixu16 = {
            {0x1111, 0x0034, 0x1111, 0x0074, 0x1111, 0x0075, 0x1111, 0x007a, },
            {0x1111, 0x0019, 0x1111, 0xff91, 0x1111, 0xffab, 0x1111, 0x0021, },
        },
        .fixu32 = {
            {0x11111111, 0x00000034, 0x11111111, 0x00000074, },
            {0x11111111, 0x00000075, 0x11111111, 0x0000007a, },
        },
        .fixu64 = {
            {0x1111111111111111, 0x0000000000000034, },
            {0x1111111111111111, 0x0000000000000074, },
        },
    },
};


struct rvv_reg res0;

int main(void)
{
    init_testsuite("Testing insn vlxhu\n");

    /* sew 16 */
    test_vlxhu_16(vlmax_16 - 1, &pad.fixu16[0], src0[0].fixu16[0], src1[0].fixu16[0], res0.fixu16[0]);
    result_compare_s16_lmul(res0.fixu16[0], dst0[0].fixu16[0]);

    test_vlxhu_16_vm(&vme.fixu16, &pad.fixu16[0], src0[0].fixu16[0], src1[0].fixu16[0], res0.fixu16[0]);
    result_compare_s16_lmul(res0.fixu16[0], dst0[1].fixu16[0]);

    test_vlxhu_16_vm(&vmo.fixu16, &pad.fixu16[0], src0[0].fixu16[0], src1[0].fixu16[0], res0.fixu16[0]);
    result_compare_s16_lmul(res0.fixu16[0], dst0[2].fixu16[0]);

    /* sew 32 */
    test_vlxhu_32(vlmax_32 - 1, &pad.fixu32[0], src0[0].fixu16[0], src1[0].fixu32[0], res0.fixu32[0]);
    result_compare_s32_lmul(res0.fixu32[0], dst0[0].fixu32[0]);

    test_vlxhu_32_vm(&vme.fixu32, &pad.fixu32[0], src0[0].fixu16[0], src1[0].fixu32[0], res0.fixu32[0]);
    result_compare_s32_lmul(res0.fixu32[0], dst0[1].fixu32[0]);

    test_vlxhu_32_vm(&vmo.fixu32, &pad.fixu32[0], src0[0].fixu16[0], src1[0].fixu32[0], res0.fixu32[0]);
    result_compare_s32_lmul(res0.fixu32[0], dst0[2].fixu32[0]);

    /* sew 64 */
    test_vlxhu_64(vlmax_64 - 1, &pad.fixu64[0], src0[0].fixu16[0], src1[0].fixu64[0], res0.fixu64[0]);
    result_compare_s64_lmul(res0.fixu64[0], dst0[0].fixu64[0]);

    test_vlxhu_64_vm(&vme.fixu64, &pad.fixu64[0], src0[0].fixu16[0], src1[0].fixu64[0], res0.fixu64[0]);
    result_compare_s64_lmul(res0.fixu64[0], dst0[1].fixu64[0]);

    test_vlxhu_64_vm(&vmo.fixu64, &pad.fixu64[0], src0[0].fixu16[0], src1[0].fixu64[0], res0.fixu64[0]);
    result_compare_s64_lmul(res0.fixu64[0], dst0[2].fixu64[0]);

    return done_testing();
}
