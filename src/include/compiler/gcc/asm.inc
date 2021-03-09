/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: asm.inc
 * Description		: This file consists of gcc standard asm macros
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

.macro vectors name
.section .\name, "ax", "progbits"
\name:
.org 0x00
.endm

.macro function name
.global \name
.section .text.\name
.type \name, "function"
\name:
.endm

.macro object name
.global \name
.section .\name
.type \name, "object"
\name:
.endm
