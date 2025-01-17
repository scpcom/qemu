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
        .fixs16 = {
            {0xffa5, 0x0034, 0xff8c, 0x0074, 0xffcd, 0x0075, 0xff92, 0x007a, },
            {0x0060, 0x0019, 0x003c, 0xff91, 0xfffd, 0xffab, 0x0023, 0x0021, },
        },
        .fixs32 = {
            {0xffffffa5, 0x00000034, 0xffffff8c, 0x00000074, },
            {0xffffffcd, 0x00000075, 0xffffff92, 0x0000007a, },
        },
        .fixs64 = {
            {0xffffffffffffffa5, 0x0000000000000034, },
            {0xffffffffffffff8c, 0x0000000000000074, },
        }
    },
};

struct rvv_reg src1[] = {
    {
        .fixs16 = {
            {0x0000, 0x0004, 0x0008, 0x000c, 0x0010, 0x0014, 0x0018, 0x001c, },
            {0x0000, 0x0004, 0x0008, 0x000c, 0x0010, 0x0014, 0x0018, 0x001c, },
        },
        .fixs32 = {
            {0x00000000, 0x00000004, 0x00000008, 0x0000000c, },
            {0x00000000, 0x00000004, 0x00000008, 0x0000000c, },
        },
        .fixs64 = {
            {0x0000000000000000, 0x0000000000000004, },
            {0x0000000000000000, 0x0000000000000004, },
        },

    },
};

struct rvv_reg dst0[] = {
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x0034, 0x1111, 0xff8c, 0x1111, 0x0074, 0x1111, },
            {0xffcd, 0x1111, 0x0075, 0x1111, 0xff92, 0x1111, 0x007a, 0x1111, },
        },
    },
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x1111, 0x1111, 0xff8c, 0x1111, 0x1111, 0x1111, },
            {0xffcd, 0x1111, 0x1111, 0x1111, 0xff92, 0x1111, 0x1111, 0x1111, },
        },
    },
    {
        .fixs16 =
        {
            {0x1111, 0x1111, 0x0034, 0x1111, 0x1111, 0x1111, 0x0074, 0x1111, },
            {0x1111, 0x1111, 0x0075, 0x1111, 0x1111, 0x1111, 0x007a, 0x1111, },
        },
    },
};

struct rvv_reg dst1[] = {
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x0034, 0x1111, 0xff8c, 0x1111, 0x0074, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x1111, 0x1111, 0xff8c, 0x1111, 0x1111, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
    {
        .fixs16 = {
            {0x1111, 0x1111, 0x0034, 0x1111, 0x1111, 0x1111, 0x0074, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
};
struct rvv_reg dst2[] = {
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x0034, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
    {
        .fixs16 = {
            {0xffa5, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
    {
        .fixs16 = {
            {0x1111, 0x1111, 0x0034, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
            {0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, },
        },
    },
};


struct rvv_reg res0;

int main(void)
{
    init_testsuite("Testing insn vsxh\n");

    /* sew 16 */
    test_vsxh_16(vlmax_16 / 2, &pad.fixs16[0], src0[0].fixs16[0], src1[0].fixs16[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst0[0].fixs16[0]);

    test_vsxh_16_vm(vlmax_16 / 2, &vme.fixs16, &pad.fixs16[0], src0[0].fixs16[0], src1[0].fixs16[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst0[1].fixs16[0]);

    test_vsxh_16_vm(vlmax_16 / 2, &vmo.fixs16, &pad.fixs16[0], src0[0].fixs16[0], src1[0].fixs16[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst0[2].fixs16[0]);

    /* sew 32 */
    test_vsxh_32(vlmax_32 / 2, &pad.fixs16[0], src0[0].fixs32[0], src1[0].fixs32[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst1[0].fixs16[0]);

    test_vsxh_32_vm(vlmax_32 / 2, &vme.fixs32, &pad.fixs16[0], src0[0].fixs32[0], src1[0].fixs32[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst1[1].fixs16[0]);

    test_vsxh_32_vm(vlmax_32 / 2, &vmo.fixs32, &pad.fixs16[0], src0[0].fixs32[0], src1[0].fixs32[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst1[2].fixs16[0]);

    /* sew 64 */
    test_vsxh_64(vlmax_64 / 2, &pad.fixs16[0], src0[0].fixs64[0], src1[0].fixs64[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst2[0].fixs16[0]);

    test_vsxh_64_vm(vlmax_64 / 2, &vme.fixs64, &pad.fixs16[0], src0[0].fixs64[0], src1[0].fixs64[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst2[1].fixs16[0]);

    test_vsxh_64_vm(vlmax_64 / 2, &vmo.fixs64, &pad.fixs16[0], src0[0].fixs64[0], src1[0].fixs64[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst2[2].fixs16[0]);

    return done_testing();
}
