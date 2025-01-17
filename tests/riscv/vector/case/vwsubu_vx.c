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
 * Lesser General Public License  *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "testsuite.h"
#include "rvv_insn.h"

struct rvv_reg src0[] = {
    {
        .fixu32 = {
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
        },
        .fixu16 = {
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        },
        .fixu8 = {
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
        },
    },
};

uint64_t src1 = 0x1122334455667788;
struct rvv_reg dst_vl[] = {
    {
        .fixu16 = {
            {0x001d, 0xffac, 0x0004, 0xffec, 0x0045, 0xffed, 0x000a, 0xfff2, },
            {0xffd8, 0xff91, 0xffb4, 0x0009, 0x0075, 0x0023, 0xff9b, 0xff99, },
            {0x001d, 0xffac, 0x0004, 0xffec, 0x0045, 0xffed, 0x000a, 0xfff2, },
            {0xffd8, 0xff91, 0xffb4, 0x0009, 0x0075, 0x0023, 0xff9b, 0x0000, },
        },
        .fixu32 = {
            {0x00005f4e, 0xffffda6a, 0xffff9967, 0xffff9719, },
            {0x00002bc1, 0xffffd5b7, 0xffffcfd5, 0x000029dc, },
            {0x00005f4e, 0xffffda6a, 0xffff9967, 0xffff9719, },
            {0x00002bc1, 0xffffd5b7, 0xffffcfd5, 0x00000000, },
        },
        .fixu64 = {
            {0x000000007a79eefe, 0x000000002cfc7ed9, },
            {0xffffffffc095da99, 0x000000008152fcd2, },
            {0x000000007a79eefe, 0x000000002cfc7ed9, },
            {0xffffffffc095da99, 0x0000000000000000, },
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .fixu16 = {
            {0x001d, 0x1111, 0x0004, 0x1111, 0x0045, 0x1111, 0x000a, 0x1111, },
            {0xffd8, 0x1111, 0xffb4, 0x1111, 0x0075, 0x1111, 0xff9b, 0x1111, },
            {0x001d, 0x1111, 0x0004, 0x1111, 0x0045, 0x1111, 0x000a, 0x1111, },
            {0xffd8, 0x1111, 0xffb4, 0x1111, 0x0075, 0x1111, 0xff9b, 0x1111, },
        },
        .fixu32 = {
            {0x00005f4e, 0x11111111, 0xffff9967, 0x11111111, },
            {0x00002bc1, 0x11111111, 0xffffcfd5, 0x11111111, },
            {0x00005f4e, 0x11111111, 0xffff9967, 0x11111111, },
            {0x00002bc1, 0x11111111, 0xffffcfd5, 0x11111111, },
        },
        .fixu64 = {
            {0x000000007a79eefe, 0x1111111111111111, },
            {0xffffffffc095da99, 0x1111111111111111, },
            {0x000000007a79eefe, 0x1111111111111111, },
            {0xffffffffc095da99, 0x1111111111111111, },
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .fixu16 = {
            {0x1111, 0xffac, 0x1111, 0xffec, 0x1111, 0xffed, 0x1111, 0xfff2, },
            {0x1111, 0xff91, 0x1111, 0x0009, 0x1111, 0x0023, 0x1111, 0xff99, },
            {0x1111, 0xffac, 0x1111, 0xffec, 0x1111, 0xffed, 0x1111, 0xfff2, },
            {0x1111, 0xff91, 0x1111, 0x0009, 0x1111, 0x0023, 0x1111, 0xff99, },
        },
        .fixu32 = {
            {0x11111111, 0xffffda6a, 0x11111111, 0xffff9719, },
            {0x11111111, 0xffffd5b7, 0x11111111, 0x000029dc, },
            {0x11111111, 0xffffda6a, 0x11111111, 0xffff9719, },
            {0x11111111, 0xffffd5b7, 0x11111111, 0x000029dc, },
        },
        .fixu64 = {
            {0x1111111111111111, 0x000000002cfc7ed9, },
            {0x1111111111111111, 0x000000008152fcd2, },
            {0x1111111111111111, 0x000000002cfc7ed9, },
            {0x1111111111111111, 0x000000008152fcd2, },
        },
    },
};


struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vwsubu.vx\n");

    /* uint8_t add */
    test_vwsubu_vx_8(vlmax_8 - 1, src0[i].fixu8[0], src1, res.fixu16[0], pad.fixu16[0]);
    result_compare_s16_lmulw(res.fixu16[0], dst_vl[i].fixu16[0]);

    test_vwsubu_vx_8_vm(src0[i].fixu8[0], src1, res.fixu16[0], vme.fixu8, pad.fixu16[0]);
    result_compare_s16_lmulw(res.fixu16[0], dst_even[i].fixu16[0]);

    test_vwsubu_vx_8_vm(src0[i].fixu8[0], src1, res.fixu16[0], vmo.fixu8, pad.fixu16[0]);
    result_compare_s16_lmulw(res.fixu16[0], dst_odd[i].fixu16[0]);

    /* uint16_t add */
    test_vwsubu_vx_16(vlmax_16 - 1, src0[i].fixu16[0], src1, res.fixu32[0], pad.fixu32[0]);
    result_compare_s32_lmulw(res.fixu32[0], dst_vl[i].fixu32[0]);

    test_vwsubu_vx_16_vm(src0[i].fixu16[0], src1, res.fixu32[0], vme.fixu16, pad.fixu32[0]);
    result_compare_s32_lmulw(res.fixu32[0], dst_even[i].fixu32[0]);

    test_vwsubu_vx_16_vm(src0[i].fixu16[0], src1, res.fixu32[0], vmo.fixu16, pad.fixu32[0]);
    result_compare_s32_lmulw(res.fixu32[0], dst_odd[i].fixu32[0]);

    /* uint32_t add */
    test_vwsubu_vx_32(vlmax_32 - 1, src0[i].fixu32[0], src1, res.fixu64[0], pad.fixu64[0]);
    result_compare_s64_lmulw(res.fixu64[0], dst_vl[i].fixu64[0]);

    test_vwsubu_vx_32_vm(src0[i].fixu32[0], src1, res.fixu64[0], vme.fixu32, pad.fixu64[0]);
    result_compare_s64_lmulw(res.fixu64[0], dst_even[i].fixu64[0]);

    test_vwsubu_vx_32_vm(src0[i].fixu32[0], src1, res.fixu64[0], vmo.fixu32, pad.fixu64[0]);
    result_compare_s64_lmulw(res.fixu64[0], dst_odd[i].fixu64[0]);

    return done_testing();
}
