/*
 * operations.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Mohamed AbdelAzeem
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define TOGGLE_BIT(REG, BIT_NUM) (REG = REG ^ (1<<BIT_NUM))
#define SET_BIT(REG, BIT_NUM) (REG=REG|(1<<BIT_NUM))
#define CLEAR_BIT(REG, BIT_NUM) (REG=REG &(~(1<<BIT_NUM)))

#endif /* OPERATIONS_H_ */
