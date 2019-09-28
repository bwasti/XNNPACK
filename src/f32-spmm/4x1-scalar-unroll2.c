// Auto-generated file. Do not edit!
//   Template: src/f32-spmm/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/math.h>
#include <xnnpack/spmm.h>


void xnn_f32_spmm_ukernel_4x1__scalar_unroll2(
    uint32_t m,
    uint32_t n,
    const float*restrict a,
    const float*restrict weights,
    const int32_t*restrict widx_dmap,
    const uint32_t*restrict nidx_nnzmap,
    float*restrict c,
    const union xnn_f32_output_params params[restrict static 1])
{
  assert(m != 0);

  const float vmin = params->scalar.min;
  const float vmax = params->scalar.max;
  size_t i = m;
  while (i >= 4) {
    const float*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    size_t j = n;
    do {
      uint32_t nnz = *nnzmap++;
      float vacc0x0 = *w++;
      float vacc0x1 = 0.0f;
      float vacc1x0 = vacc0x0;
      float vacc1x1 = 0.0f;
      float vacc2x0 = vacc0x0;
      float vacc2x1 = 0.0f;
      float vacc3x0 = vacc0x0;
      float vacc3x1 = 0.0f;
      for (; nnz >= 2; nnz -= 2) {
        const intptr_t diff0 = dmap[0];
        const intptr_t diff1 = dmap[1];
        dmap += 2;
        const float va0x0 = a[0];
        const float va1x0 = a[1];
        const float va2x0 = a[2];
        const float va3x0 = a[3];
        a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff0);
        const float vb0 = *w++;
        vacc0x0 += va0x0 * vb0;
        vacc1x0 += va1x0 * vb0;
        vacc2x0 += va2x0 * vb0;
        vacc3x0 += va3x0 * vb0;
        const float va0x1 = a[0];
        const float va1x1 = a[1];
        const float va2x1 = a[2];
        const float va3x1 = a[3];
        a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff1);
        const float vb1 = *w++;
        vacc0x1 += va0x1 * vb1;
        vacc1x1 += va1x1 * vb1;
        vacc2x1 += va2x1 * vb1;
        vacc3x1 += va3x1 * vb1;
      }
      float vacc0 = vacc0x0;
      float vacc1 = vacc1x0;
      float vacc2 = vacc2x0;
      float vacc3 = vacc3x0;
      vacc0 += vacc0x1;
      vacc1 += vacc1x1;
      vacc2 += vacc2x1;
      vacc3 += vacc3x1;
      if XNN_LIKELY(nnz != 0) {
        do {
          const intptr_t diff = *dmap++;
          const float va0 = a[0];
          const float va1 = a[1];
          const float va2 = a[2];
          const float va3 = a[3];
          a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff);
          const float vb = *w++;
          vacc0 += va0 * vb;
          vacc1 += va1 * vb;
          vacc2 += va2 * vb;
          vacc3 += va3 * vb;
        } while (--nnz != 0);
      }
      float vout0 = math_min_f32(vacc0, vmax);
      float vout1 = math_min_f32(vacc1, vmax);
      float vout2 = math_min_f32(vacc2, vmax);
      float vout3 = math_min_f32(vacc3, vmax);
      vout0 = math_max_f32(vout0, vmin);
      vout1 = math_max_f32(vout1, vmin);
      vout2 = math_max_f32(vout2, vmin);
      vout3 = math_max_f32(vout3, vmin);
      c[0] = vout0;
      c[1] = vout1;
      c[2] = vout2;
      c[3] = vout3;
      c += m;
    } while (--j != 0);
    c -= m * n;
    c += 4;
    a += 4;
    i -= 4;
  }
  if XNN_UNLIKELY(i != 0) {
    if (i & 2) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t j = n;
      do {
        uint32_t nnz = *nnzmap++;
        float vacc0x0 = *w++;
        float vacc0x1 = 0.0f;
        float vacc1x0 = vacc0x0;
        float vacc1x1 = 0.0f;
        for (; nnz >= 2; nnz -= 2) {
          const intptr_t diff0 = dmap[0];
          const intptr_t diff1 = dmap[1];
          dmap += 2;
          const float va0x0 = a[0];
          const float va1x0 = a[1];
          a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff0);
          const float vb0 = *w++;
          vacc0x0 += va0x0 * vb0;
          vacc1x0 += va1x0 * vb0;
          const float va0x1 = a[0];
          const float va1x1 = a[1];
          a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff1);
          const float vb1 = *w++;
          vacc0x1 += va0x1 * vb1;
          vacc1x1 += va1x1 * vb1;
        }
        float vacc0 = vacc0x0;
        float vacc1 = vacc1x0;
        vacc0 += vacc0x1;
        vacc1 += vacc1x1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float va0 = a[0];
            const float va1 = a[1];
            a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff);
            const float vb = *w++;
            vacc0 += va0 * vb;
            vacc1 += va1 * vb;
          } while (--nnz != 0);
        }
        float vout0 = math_min_f32(vacc0, vmax);
        float vout1 = math_min_f32(vacc1, vmax);
        vout0 = math_max_f32(vout0, vmin);
        vout1 = math_max_f32(vout1, vmin);
        c[0] = vout0;
        c[1] = vout1;
        c += m;
      } while (--j != 0);
      c -= m * n;
      c += 2;
      a += 2;
    }
    if (i & 1) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t j = n;
      do {
        uint32_t nnz = *nnzmap++;
        float vacc0x0 = *w++;
        float vacc0x1 = 0.0f;
        for (; nnz >= 2; nnz -= 2) {
          const intptr_t diff0 = dmap[0];
          const intptr_t diff1 = dmap[1];
          dmap += 2;
          const float va0x0 = a[0];
          a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff0);
          const float vb0 = *w++;
          vacc0x0 += va0x0 * vb0;
          const float va0x1 = a[0];
          a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff1);
          const float vb1 = *w++;
          vacc0x1 += va0x1 * vb1;
        }
        float vacc0 = vacc0x0;
        vacc0 += vacc0x1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float va0 = a[0];
            a = (const float*restrict) ((uintptr_t) a + (uintptr_t) diff);
            const float vb = *w++;
            vacc0 += va0 * vb;
          } while (--nnz != 0);
        }
        float vout0 = math_min_f32(vacc0, vmax);
        vout0 = math_max_f32(vout0, vmin);
        c[0] = vout0;
        c += m;
      } while (--j != 0);
      c -= m * n;
      c += 1;
      a += 1;
    }
  }
}