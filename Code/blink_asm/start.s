.section .init
.global _start /* Main is our entry point and must be global */

.equ VIR_LEG, 0x7e2000e8
.equ PHY_LEG, 0xC02000e8
.equ THI_LEG, 0xFE2000e8
/*.equ VIR, 0x47e2000e8
.equ PHY, 0x4C02000e8
*/
_start:
	/*mov r0, #0xFFF  /* Put a value inside the register r0 */
	/*LDR r1, =VIR_LEG*/
	/* LDR r0, [r1] */
	/* bx lr /* Return from main */
	LDR R1, =THI_LEG   /* Load the address of GPIO_PUP_PDN_CNTRL_REG1 into R0*/
	LDR R0, [R1]

