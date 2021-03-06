/* Runtime ABI for the ARM Cortex-M
 * uldivmod.S: unsigned 64 bit division
 *
 * Copyright (c) 2012 Jörg Mische <bobbl@gmx.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

.extern kernel_panic

	.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb
	.text
	.code 16
@ {unsigned long long quotient, unsigned long long remainder}
@ __aeabi_uldivmod(unsigned long long numerator, unsigned long long denominator)
@
@ Divide r1:r0 by r3:r2 and return the quotient in r1:r0 and the remainder
@ in r3:r2 (all unsigned)
@
	.thumb_func
	.section .text.__aeabi_uldivmod,"ax",%progbits
        .global __aeabi_uldivmod
__aeabi_uldivmod:
	cmp	r3, #0
	bne	L_large_denom
	cmp	r2, #0
	beq	L_divison_by_0
	cmp	r1, #0
	beq	L_fallback_32bits
	@ case 1: num >= 2^32 and denom < 2^32
	@ Result might be > 2^32, therefore we first calculate the upper 32
	@ bits of the result. It is done similar to the calculation of the
	@ lower 32 bits, but with a denominator that is shifted by 32.
	@ Hence the lower 32 bits of the denominator are always 0 and the
	@ costly 64 bit shift and sub operations can be replaced by cheap 32
	@ bit operations.
	push	{r4, r5, r6, r7, lr}
	@ shift left the denominator until it is greater than the numerator
	@ denom(r7:r6) = r3:r2 << 32
	@ TODO(crosbug.com/p/36128): Loops like this (which occur in several
	@ places in this file) are inefficent in ARMv6-m.
	movs	r5, #1		@ bitmask
	adds	r7, r2, #0	@ dont shift if denominator would overflow
	bmi	L_upper_result
	cmp	r1, r7
	blo	L_upper_result
L_denom_shift_loop1:
	lsls	r5, #1
	lsls	r7, #1
	bmi	L_upper_result	@ dont shift if overflow
	cmp	r1, r7
	bhs	L_denom_shift_loop1
L_upper_result:
	mov	r3, r1
	mov	r2, r0
	movs	r1, #0		@ upper result = 0
L_sub_loop1:
	cmp	r3, r7
	bcc	L_dont_sub1	@ if (num>denom)
	subs	r3, r7		@ num -= denom
	orrs	r1, r5		@ result(r7:r6) |= bitmask(r5)
L_dont_sub1:
	lsrs	r7, #1		@ denom(r7:r6) >>= 1
	lsrs	r5, #1		@ bitmask(r5) >>= 1
	bne	L_sub_loop1
	movs	r5, #1
	lsls	r5, #31
	movs	r6, #0
	b	L_lower_result
	@ case 2: division by 0
	@ call __aeabi_ldiv0
L_divison_by_0:
	b	__aeabi_ldiv0
	@ case 3: num < 2^32 and denom < 2^32
	@ fallback to 32 bit division
L_fallback_32bits:
	mov	r1, r0
	udiv	r0, r2		@ r0 = quotient
	mul	r3, r0, r2	@ r3 = quotient * divisor
	subs	r2, r3, r2	@ r2 = remainder
	movs	r1, #0
	movs	r3, #0
	bx	lr
	@ case 4: denom >= 2^32
	@ result is smaller than 2^32
L_large_denom:
	push	{r4, r5, r6, r7, lr}
	mov	r7, r3
	mov	r6, r2
	mov	r3, r1
	mov	r2, r0
	@ Shift left the denominator until it is greater than the numerator
	movs	r1, #0		@ high word of result is 0
	movs	r5, #1		@ bitmask
	adds	r7, #0		@ dont shift if denominator would overflow
	bmi	L_lower_result
	cmp	r3, r7
	blo	L_lower_result
L_denom_shift_loop4:
	lsls	r5, #1
	lsls	r7, #1
	lsls	r6, #1
	adcs	r7, r1		@ r1=0
	bmi	L_lower_result	@ dont shift if overflow
	cmp	r3, r7
	bhs	L_denom_shift_loop4
L_lower_result:
	movs	r0, #0
L_sub_loop4:
	mov	r4, r3
	cmp	r2, r6
	sbcs	r4, r7
	bcc	L_dont_sub4	@ if (num>denom)
	subs	r2, r6		@ numerator -= denom
	sbcs	r3, r7
	orrs	r0, r5		@ result(r1:r0) |= bitmask(r5)
L_dont_sub4:
	lsls	r4, r7, #31	@ denom(r7:r6) >>= 1
	lsrs	r6, #1
	lsrs	r7, #1
	orrs	r6, r4
	lsrs	r5, #1		@ bitmask(r5) >>= 1
	bne	L_sub_loop4
	pop	{r4, r5, r6, r7, pc}
__aeabi_ldiv0:
        movs    r0, 5
	bl	kernel_panic

@ {long long quotient, long long remainder}
@ __aeabi_ldivmod(long long numerator, long long denominator)
@
@ Divide r1:r0 by r3:r2 and return the quotient in r1:r0 and the remainder in
@ r3:r2 (all signed)
@
	.thumb_func
	.section .text.__aeabi_ldivmod
        .global __aeabi_ldivmod
__aeabi_ldivmod:
	cmp	r1, #0
	bge	L_num_pos
	push	{r4, lr}
	movs	r4, #0			@ num = -num
	rsbs	r0, r0, #0
	sbcs	r4, r1
	mov	r1, r4
	cmp	r3, #0
	bge	L_neg_both
	movs	r4, #0			@ den = -den
	rsbs	r2, r2, #0
	sbcs	r4, r3
	mov	r3, r4
	bl	__aeabi_uldivmod
	movs	r4, #0			@ rem = -rem
	rsbs	r2, r2, #0
	sbcs	r4, r3
	mov	r3, r4
	pop	{r4, pc}
L_neg_both:
	bl	__aeabi_uldivmod
	movs	r4, #0			@ quot = -quot
	rsbs	r0, r0, #0
	sbcs	r4, r1
	mov	r1, r4
	movs	r4, #0			@ rem = -rem
	rsbs	r2, r2, #0
	sbcs	r4, r3
	mov	r3, r4
	pop	{r4, pc}
L_num_pos:
	cmp	r3, #0
	bge	__aeabi_uldivmod
	push	{r4, lr}
	movs	r4, #0			@ den = -den
	rsbs	r2, r2, #0
	sbcs	r4, r3
	mov	r3, r4
	bl	__aeabi_uldivmod
	movs	r4, #0			@ quot = -quot
	rsbs	r0, r0, #0
	sbcs	r4, r1
	mov	r1, r4
	pop	{r4, pc}