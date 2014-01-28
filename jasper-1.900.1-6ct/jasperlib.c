// This is an amalgamation of the jasper library modified by bcb
// this amalgamation was done by mvh 20100117
// mvh 20100119: simplified and works with unchanged jasper-1.900.1-6ct

#include <stddef.h>   // first inclusion avoids compile error later

#include "base/jas_cm.c"
#include "base/jas_debug.c"
#include "base/jas_getopt.c"
#include "base/jas_icc.c"
#include "base/jas_iccdata.c"
#include "base/jas_image.c"
#include "base/jas_init.c"
#include "base/jas_malloc.c"
#include "base/jas_seq.c"
#include "base/jas_stream.c"
#include "base/jas_string.c"
#include "base/jas_tmr.c"
#include "base/jas_tvp.c"
#include "base/jas_version.c"

#include "bmp/bmp_cod.c"
#include "bmp/bmp_dec.c"
#include "bmp/bmp_enc.c"

#include "jp2/jp2_cod.c"
#include "jp2/jp2_dec.c"
#include "jp2/jp2_enc.c"

#include "jpc/jpc_bs.c"
#include "jpc/jpc_cs.c"
#define OPT_DEBUG OPTx_DEBUG  // symbol is double
#include "jpc/jpc_dec.c"
#undef OPT_DEBUG
#include "jpc/jpc_enc.c"
#include "jpc/jpc_math.c"
#include "jpc/jpc_mct.c"
#include "jpc/jpc_mqcod.c"
#include "jpc/jpc_mqdec.c"
#include "jpc/jpc_mqenc.c"
#include "jpc/jpc_qmfb.c"
#include "jpc/jpc_t1cod.c"
#include "jpc/jpc_t1dec.c"
#include "jpc/jpc_t1enc.c"
#include "jpc/jpc_t2cod.c"
#include "jpc/jpc_t2dec.c"
#include "jpc/jpc_t2enc.c"
#include "jpc/jpc_tagtree.c"
#include "jpc/jpc_tsfb.c"
#include "jpc/jpc_util.c"

#include "jpg/jpg_val.c"
#ifdef HAVE_LIBJPEG
#  include "jpg/jpg_dec.c"
#  include "jpg/jpg_enc.c"
#else
#  include "jpg/jpg_dummy.c"
#endif

#include "mif/mif_cod.c"

#include "pgx/pgx_cod.c"
#include "pgx/pgx_dec.c"
#include "pgx/pgx_enc.c"

#include "pnm/pnm_cod.c"
#include "pnm/pnm_dec.c"
#include "pnm/pnm_enc.c"

#include "ras/ras_cod.c"
#include "ras/ras_dec.c"
#include "ras/ras_enc.c"
