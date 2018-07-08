/*
 * CodeWarrior V1 and V2 Compiler
 * Purpose: Lowest level routines for all ColdFire processors.
 *
 * Notes:
 *
 * ulPortSetIPL() and mcf5xxx_wr_cacr() copied with permission from Freescale
 * supplied source files.
 */
    .global ulPortSetIPL
    .global _ulPortSetIPL
    .global mcf5xxx_wr_cacrx
    .global _mcf5xxx_wr_cacrx
    .global vPortYieldISR
    .global _vPortYieldISR
    .global vPortStartFirstTask
    .global _vPortStartFirstTask
    .extern _pxCurrentTCB
    .extern _vPortYieldHandler

    .text

.macro portSAVE_CONTEXT
  lea.l                (-60, sp), sp
  movem.l              d0-a6, (sp)
  move.l               _pxCurrentTCB, a0
  move.l               sp, (a0)
  .endm

.macro portRESTORE_CONTEXT
  move.l               _pxCurrentTCB, a0
  move.l               (a0), sp
  movem.l              (sp), d0-a6
  lea.l                (60, sp), sp
  rte
  .endm
/********************************************************************/
/*
 * This routines changes the IPL to the value passed into the routine.
 * It also returns the old IPL value back.
 * Calling convention from C:
 *   old_ipl = asm_set_ipl(new_ipl);
 */
ulPortSetIPL:
_ulPortSetIPL:
  link    A6,#-8
  movem.l D6-D7,(SP)

  move.w  SR,D7           /* current sr    */

  move.l  D7,D6           /* prepare return value  */
  andi.l  #0x0700,D6      /* mask out IPL  */
  lsr.l   #8,D6           /* IPL   */

  andi.l  #0x07,D0        /* least significant three bits  */
  lsl.l   #8,D0           /* move over to make mask    */

  andi.l  #0x0000F8FF,D7  /* zero out current IPL  */
  or.l    D0,D7           /* place new IPL in sr   */
  move.w  D7,SR

  move.l  D6, D0          /* Return value in D0 */
  movem.l (SP),D6-D7
  lea     8(SP),SP
  unlk    A6
  rts
/********************************************************************/
mcf5xxx_wr_cacrx:
_mcf5xxx_wr_cacrx:
  move.l  4(sp),d0
  .long   0x4e7b0002  /* movec d0,cacr   */
  nop
  rts
/********************************************************************/
/* Yield interrupt. */
_vPortYieldISR:
vPortYieldISR:
  portSAVE_CONTEXT
  jsr _vPortYieldHandler
  portRESTORE_CONTEXT
/********************************************************************/
vPortStartFirstTask:
_vPortStartFirstTask:
  portRESTORE_CONTEXT
  .end

