.global main /* Main is our entry point and must be global */

.equ VIR_LEG, 0x7e2000e8
.equ VIR, 0x47e2000e8
.equ PHY, 0x4C02000e8

main:
	mov r0, #0x10000000  /* Put a value inside the register r0 */
	bx lr /* Return from main */
