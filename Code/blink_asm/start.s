/* This is a comment */
.global main /* Main is our entry point and must be global */

main:
	mov r0, #3  /* Put a 2 inside the register r0 */
	bx lr /* Return from main */
