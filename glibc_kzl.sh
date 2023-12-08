diff -uprN final_package/memcmp.S gtw_final_package/memcmp.S
--- final_package/memcmp.S	2020-11-10 11:13:48.672929610 +0800
+++ gtw_final_package/memcmp.S	2020-11-07 11:57:26.000000000 +0800
@@ -18,7 +18,7 @@
    License along with the GNU C Library.  If not, see
    <http://www.gnu.org/licenses/>.  */
 
-#include <port_aarch64.h>
+#include "port_aarch64.h"
 
 /* Assumptions:
  *
@@ -39,8 +39,11 @@
 #define data2w		w5
 #define data2h		x6
 #define tmp1		x7
+#define tmp2		x8
 
-ENTRY_ALIGN (memcmp, 6)
+#define	MEMCMP memcmp
+
+ENTRY_ALIGN (MEMCMP, 6)
 	DELOUSE (0)
 	DELOUSE (1)
 	DELOUSE (2)
@@ -106,7 +109,7 @@ L(loop16):
 	b.ne	L(return64)
 	
 	subs    limit, limit, 16
-	b.hi    L(loop16)
+	b.pl    L(loop16)
 	/* Compare last 1-16 bytes using unaligned access.  */
 L(last_bytes):
 	add	src1, src1, limit
@@ -157,7 +160,7 @@ L(less8):
 	ldr     data1w,	[src1, limit]
 	ldr     data2w,	[src2, limit]
 	b	L(return)
-	.p2align 4	
+
 L(less4):
 	adds	limit, limit, 4
 	beq	L(ret_0)
@@ -174,7 +177,6 @@ L(ret_0):
     	mov     result, 0
     	ret
 
-END (memcmp)
-#undef bcmp
-weak_alias (memcmp, bcmp)
-libc_hidden_builtin_def (memcmp)
+END (MEMCMP)
+libc_hidden_builtin_def (MEMCMP)
+
diff -uprN final_package/memcpy.S gtw_final_package/memcpy.S
--- final_package/memcpy.S	2020-11-10 11:22:27.842929610 +0800
+++ gtw_final_package/memcpy.S	2020-11-07 13:30:18.000000000 +0800
@@ -1,5 +1,5 @@
-/* Optimized memcpy for Qualcomm Falkor processor.
-   Copyright (C) 2017-2020 Free Software Foundation, Inc.
+/* Optimized memcpy for Huawei kunpeng processor.
+   Copyright (C) 2017-2019 Free Software Foundation, Inc.
 
    This file is part of the GNU C Library.
 
@@ -14,14 +14,16 @@
    Lesser General Public License for more details.
 
    You should have received a copy of the GNU Lesser General Public
-   License along with the GNU C Library.  If not, see
-   <https://www.gnu.org/licenses/>.  */
+   License along with the GNU C Library; if not, see
+   <http://www.gnu.org/licenses/>.  */
 
-#include <sysdep.h>
+#include "port_aarch64.h"
 
 /* Assumptions:
-
-   ARMv8-a, AArch64, falkor, unaligned accesses.  */
+ *
+ * ARMv8-a, AArch64, unaligned accesses.
+ *
+ */
 
 #define dstin	x0
 #define src	x1
@@ -46,32 +48,21 @@
 #define Q_q	q6
 #define S_q	q22
 
-/* Copies are split into 3 main cases:
-
-   1. Small copies of up to 32 bytes
-   2. Medium copies of 33..128 bytes which are fully unrolled
-   3. Large copies of more than 128 bytes.
-
-   Large copies align the source to a quad word and use an unrolled loop
-   processing 64 bytes per iteration.
 
-   FALKOR-SPECIFIC DESIGN:
 
-   The smallest copies (32 bytes or less) focus on optimal pipeline usage,
-   which is why the redundant copies of 0-3 bytes have been replaced with
-   conditionals, since the former would unnecessarily break across multiple
-   issue groups.  The medium copy group has been enlarged to 128 bytes since
-   bumping up the small copies up to 32 bytes allows us to do that without
-   cost and also allows us to reduce the size of the prep code before loop64.
-
-   The copy loop uses only one register q0.  This is to ensure that all loads
-   hit a single hardware prefetcher which can get correctly trained to prefetch
-   a single stream.
+#ifndef MEMMOVE
+# define MEMMOVE memmove
+#endif
+#ifndef MEMCPY
+# define MEMCPY memcpy
+#endif
 
-   The non-temporal stores help optimize cache utilization.  */
+/* Overlapping large forward memmoves use a loop that copies backwards.
+   Otherwise memcpy is used. Small moves branch to memcopy16 directly.
+   The longer memcpy cases fall through to the memcpy head.
+*/
 
-#if IS_IN (libc)
-ENTRY_ALIGN (__memcpy_falkor, 6)
+ENTRY_ALIGN (MEMMOVE, 6)
 
 	DELOUSE (0)
 	DELOUSE (1)
@@ -196,27 +187,25 @@ L(loop64):
 	ldr	B_q, [srcend, -16]
 	str	B_q, [dstend, -16]
 	ret
+	
 
-END (__memcpy_falkor)
-libc_hidden_builtin_def (__memcpy_falkor)
+END (MEMMOVE)
+libc_hidden_builtin_def (MEMMOVE)
 
 
-/* RATIONALE:
+/* Copies are split into 3 main cases: small copies of up to 16 bytes,
+   medium copies of 17..96 bytes which are fully unrolled. Large copies
+   of more than 96 bytes align the destination and use load-and-merge
+   approach in the case src and dst addresses are unaligned not evenly,
+   so that, actual loads and stores are always aligned.
+   Large copies use the loops processing 64 bytes per iteration for
+   unaligned case and 128 bytes per iteration for aligned ones.
+*/
 
-   The move has 4 distinct parts:
-   * Small moves of 32 bytes and under.
-   * Medium sized moves of 33-128 bytes (fully unrolled).
-   * Large moves where the source address is higher than the destination
-     (forward copies)
-   * Large moves where the destination address is higher than the source
-     (copy backward, or move).
+#define MEMCPY_PREFETCH_LDR 640
 
-   We use only two registers q6 and q22 for the moves and move 32 bytes at a
-   time to correctly train the hardware prefetcher for better throughput.
-
-   For small and medium cases memcpy is used.  */
-
-ENTRY_ALIGN (__memmove_falkor, 6)
+	.p2align 4
+ENTRY (MEMCPY)
 
 	DELOUSE (0)
 	DELOUSE (1)
@@ -310,6 +299,7 @@ L(move_long):
 	str	C_q, [dstin]
 3:	ret
 
-END (__memmove_falkor)
-libc_hidden_builtin_def (__memmove_falkor)
-#endif
+
+END (MEMCPY)
+
+libc_hidden_builtin_def (MEMCPY)
diff -uprN final_package/memset.S gtw_final_package/memset.S
--- final_package/memset.S	2020-11-10 11:16:49.032929610 +0800
+++ gtw_final_package/memset.S	2020-11-07 13:16:38.000000000 +0800
@@ -16,20 +16,9 @@
    License along with the GNU C Library.  If not, see
    <http://www.gnu.org/licenses/>.  */
 
-#include <port_aarch64.h>
+#include "port_aarch64.h"
+#include "memset-reg.h"
 
-#define dstin	x0
-#define val	x1
-#define valw	w1
-#define count	x2
-#define dst	x3
-#define dstend	x4
-#define tmp1	x5
-#define tmp1w	w5
-#define tmp2	x6
-#define tmp2w	w6
-#define zva_len x7
-#define zva_lenw w7
 
 #ifndef MEMSET
 # define MEMSET memset
diff -uprN final_package/port_aarch64.h gtw_final_package/port_aarch64.h
--- final_package/port_aarch64.h	2020-11-10 11:13:05.112929610 +0800
+++ gtw_final_package/port_aarch64.h	2020-11-07 11:34:44.000000000 +0800
@@ -19,7 +19,7 @@
 #ifndef _AARCH64_SYSDEP_H
 #define _AARCH64_SYSDEP_H
 
-#include <sysdeps/generic/sysdep.h>
+#include "sysdep_generic.h"
 
 #define port_ret                mov     pc, r14
 
diff -uprN final_package/sysdep_generic.h gtw_final_package/sysdep_generic.h
--- final_package/sysdep_generic.h	2020-11-10 10:44:25.392929610 +0800
+++ gtw_final_package/sysdep_generic.h	2020-11-07 11:46:14.000000000 +0800
@@ -36,6 +36,18 @@
 #endif
 
 /* Makros to generate eh_frame unwind information.  */
+#  define cfi_startproc			.cfi_startproc
+#  define cfi_endproc			.cfi_endproc
+
+#ifndef C_SYMBOL_NAME
+# define C_SYMBOL_NAME(name) name
+#endif
+
+# define hidden_def(name)
+# define libc_hidden_def(name) hidden_def (name)
+# define libc_hidden_builtin_def(name) libc_hidden_def (name)
+
+#ifdef HAVE_ASM_CFI_DIRECTIVES
 #ifdef __ASSEMBLER__
 # define cfi_startproc			.cfi_startproc
 # define cfi_endproc			.cfi_endproc
@@ -94,4 +106,24 @@
    ".cfi_lsda " CFI_STRINGIFY(enc) "," CFI_STRINGIFY(exp)
 #endif
 
+#else
+
+# define CFI_STARTPROC
+# define CFI_ENDPROC
+# define CFI_DEF_CFA(reg, off)
+# define CFI_DEF_CFA_REGISTER(reg)
+# define CFI_DEF_CFA_OFFSET(off)
+# define CFI_ADJUST_CFA_OFFSET(off)
+# define CFI_OFFSET(reg, off)
+# define CFI_REL_OFFSET(reg, off)
+# define CFI_REGISTER(r1, r2)
+# define CFI_RETURN_COLUMN(reg)
+# define CFI_RESTORE(reg)
+# define CFI_UNDEFINED(reg)
+# define CFI_REMEMBER_STATE
+# define CFI_RESTORE_STATE
+# define CFI_WINDOW_SAVE
+# define CFI_PERSONALITY(enc, exp)
+# define CFI_LSDA(enc, exp)
+#endif
 #include "dwarf2.h"
