/*
 * common_macros.h
 *
 *  Created on: Dec 27, 2019
 *      Author: Noha Gamal
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit of a port */
#define SET_BIT(REG , BIT) ( REG |= (1<<(BIT)) )

/* Clear a certain bit of a port */
#define CLEAR_BIT(REG,BIT) (REG&=( ~(1<<(BIT)) ))

/* SET a port */
#define SET_PORT(REG) (REG=0xff)

/* Clear a port */
#define CLEAR_PORT(REG) (REG=0x00)
/* Toggle a certain bit of a port */
#define TOGGLE_BIT(REG , BIT) ( REG ^= (1<<(BIT)) )

/* Rotate left a port number of times */
#define ROL_BIT(REG , NUM) (REG = (REG<<(NUM)) |(REG >>(8-(NUM))) )

/* Rotate left a port number of times */
#define ROR_BIT(REG , NUM) (REG = (REG<<(NUM)) |(REG >>(8-(NUM))) )

/* check if the bit is set */
#define BIT_IS_SET(REG , BIT) (REG &(1<<BIT))

/* check if the bit is clear */
#define BIT_IS_CLEAR(REG , BIT) (!(REG &(1<<BIT)) )

#endif /* COMMON_MACROS_H_ */

