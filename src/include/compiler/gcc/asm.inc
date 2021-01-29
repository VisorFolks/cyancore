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
