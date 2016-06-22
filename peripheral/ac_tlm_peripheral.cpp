/**
 * @file      ac_tlm_mem.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ac_tlm_peripheral.h"
#include <byteswap.h>
#include <math.h>
#include <time.h>

#include "ac_debug_model.H"
#define DEBUG_MODEL

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate peripheral from ArchC
using user::ac_tlm_peripheral;

/// Constructor
ac_tlm_peripheral::ac_tlm_peripheral( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the peripheral
    target_export( *this );
    srand(STARTING_SEED);
}

/// Destructor
ac_tlm_peripheral::~ac_tlm_peripheral() {
}

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d id the data being write
  * @returns A TLM response packet with SUCCESS
*/
ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d )
{
  switch(a) {
    case Z1_R_P1_ADDR:
        *DOUBLE_PART1(&(z1.r)) = d;
        break;
    case Z1_R_P2_ADDR:
        *DOUBLE_PART2(&(z1.r)) = d;
        break;
    case Z1_I_P1_ADDR:
        *DOUBLE_PART1(&(z1.i)) = d;
        break;
    case Z1_I_P2_ADDR:
        *DOUBLE_PART2(&(z1.i)) = d;
        break;
    case Z2_R_P1_ADDR:
        *DOUBLE_PART1(&(z2.r)) = d;
        break;
    case Z2_R_P2_ADDR:
        *DOUBLE_PART2(&(z2.r)) = d;
        break;
    case Z2_I_P1_ADDR:
        *DOUBLE_PART1(&(z2.i)) = d;
        break;
    case Z2_I_P2_ADDR:
        *DOUBLE_PART2(&(z2.i)) = d;
        break;
  }
  return SUCCESS;
}

/** Internal Read
  * Note: Always read 32 bits
  * @param a is the address to read
  * @param d id the data that will be read
  * @returns A TLM response packet with SUCCESS and a modified d
*/
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  double aux;
  switch(a){
	case ADD_R_P1_ADDR:
		 aux = z1.r + z2.r;
		 d = *DOUBLE_PART1(&aux);
		 break;
	case ADD_R_P2_ADDR:
		 aux = z1.r + z2.r;
		 d = *DOUBLE_PART2(&aux);
		 break;
	case ADD_I_P1_ADDR:
		 aux = z1.i + z2.i;
		 d = *DOUBLE_PART1(&aux);
		 break;
	case ADD_I_P2_ADDR:
		 aux = z1.i + z2.i;
		 d = *DOUBLE_PART2(&aux);
		 break;
		 /*
	case ADD_I_ADDR:
		 d = z1.i + z2.i;
		 break;
	case SUB_R_ADDR:
		  d = z1.r - z2.r;
		  break;
	case SUB_I_ADDR:
		  d = z1.i - z2.i;
		  break;
	case MULT_R_ADDR:
		  d = (z1.r*z2.r - z1.i*z2.i);
		  break;
	case MULT_I_ADDR:
		  d = (z1.r*z2.i + z1.i*z2.r);
		  break;
	case MOD_ADDR:
		  d = (z1.r*z1.r + z1.i*z1.i);
		  break;
	case SCALAR_R_ADDR:
		  d = (z1.r*z2.r); 
		  break;
	case SCALAR_I_ADDR:
		  d = (z1.i*z2.i);
		  break;
	case LOG_ADDR:
		  d = log(z1.r);
		  break;
	case FRAC_ADDR:
		  d = (z1.r - (int)z1.r);
		  break;
	case FLOOR_ADDR:
		  d = (double)((int) z1.r);
		  break;
	case RANDOM_ADDR:
		  d = ((double) rand() / (RAND_MAX)) + 1;
		  break;
*/
  }
  return SUCCESS;
}







