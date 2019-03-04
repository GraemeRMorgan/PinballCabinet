/**
 * @file	hal_memreg.c
 * @author  
 * @version 
 *
 * @brief Memory Regions part of the Hardware Abstraction Layer. 
 *
 */
#include "hal.h"

//(NOTE: These must match memory layout in linker script)
#define MEM_REGION_APP_BASEPTR		(uint8_t*)0x20014000		//App mem region ptr to start address
#define MEM_REGION_SYS_BASEPTR		(uint8_t*)0x20000000		//System mem region ptr to start address
#define MEM_REGION_APP_SIZE			0x00014000					//80 KB
#define MEM_REGION_SYS_SIZE			0x00014000					//80 KB

/**
*	HAL Memory Regions Init
*
*	Initializes Memory. This function must be called after
*	HAL CPU Init. That is: hal_cpu_init(); hal_mem_init();...
*
*/
void hal_memreg_init(void){
	//nothing to initialize...
	//for consistency...
	//and compatibility if future versions require initialization
}

/**
*	HAL Memory Region Read
*
*	Reads information related to the specified memory region.
*
*	@param memid	the specified memory region
*	@param memreg	a pointer to the tMemRegion variable to be populated
*/
void hal_memreg_read( tMemRegionId memid, tMemRegion* memreg ){
	if( memreg == 0 ) return; //Error (null ptr)
	
	memreg->id = memid;
	
	switch( memid ){
		case MemRegSystem:
			memreg->base = MEM_REGION_SYS_BASEPTR;
			memreg->size  = MEM_REGION_SYS_SIZE;
			break;
		case MemRegApp:
			memreg->base = MEM_REGION_APP_BASEPTR;
			memreg->size  = MEM_REGION_APP_SIZE;
			break;
		default:	
			//Error		  
			break;
	}
	
	return 0;
}
