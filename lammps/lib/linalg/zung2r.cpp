#ifdef __cplusplus
extern "C" {
#endif
#include "lmp_f2c.h"
static integer c__1 = 1;
int zung2r_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau,
            doublecomplex *work, integer *info)
{
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublecomplex z__1;
    integer i__, j, l;
    extern int zscal_(integer *, doublecomplex *, doublecomplex *, integer *),
        zlarf_(char *, integer *, integer *, doublecomplex *, integer *, doublecomplex *,
               doublecomplex *, integer *, doublecomplex *, ftnlen),
        xerbla_(char *, integer *, ftnlen);
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;
    *info = 0;
    if (*m < 0) {
        *info = -1;
    } else if (*n < 0 || *n > *m) {
        *info = -2;
    } else if (*k < 0 || *k > *n) {
        *info = -3;
    } else if (*lda < max(1, *m)) {
        *info = -5;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_((char *)"ZUNG2R", &i__1, (ftnlen)6);
        return 0;
    }
    if (*n <= 0) {
        return 0;
    }
    i__1 = *n;
    for (j = *k + 1; j <= i__1; ++j) {
        i__2 = *m;
        for (l = 1; l <= i__2; ++l) {
            i__3 = l + j * a_dim1;
            a[i__3].r = 0., a[i__3].i = 0.;
        }
        i__2 = j + j * a_dim1;
        a[i__2].r = 1., a[i__2].i = 0.;
    }
    for (i__ = *k; i__ >= 1; --i__) {
        if (i__ < *n) {
            i__1 = i__ + i__ * a_dim1;
            a[i__1].r = 1., a[i__1].i = 0.;
            i__1 = *m - i__ + 1;
            i__2 = *n - i__;
            zlarf_((char *)"Left", &i__1, &i__2, &a[i__ + i__ * a_dim1], &c__1, &tau[i__],
                   &a[i__ + (i__ + 1) * a_dim1], lda, &work[1], (ftnlen)4);
        }
        if (i__ < *m) {
            i__1 = *m - i__;
            i__2 = i__;
            z__1.r = -tau[i__2].r, z__1.i = -tau[i__2].i;
            zscal_(&i__1, &z__1, &a[i__ + 1 + i__ * a_dim1], &c__1);
        }
        i__1 = i__ + i__ * a_dim1;
        i__2 = i__;
        z__1.r = 1. - tau[i__2].r, z__1.i = 0. - tau[i__2].i;
        a[i__1].r = z__1.r, a[i__1].i = z__1.i;
        i__1 = i__ - 1;
        for (l = 1; l <= i__1; ++l) {
            i__2 = l + i__ * a_dim1;
            a[i__2].r = 0., a[i__2].i = 0.;
        }
    }
    return 0;
}
#ifdef __cplusplus
}
#endif
