#include <stdio.h>

#ifndef _DEBUG_PRINT_H_
#define _DEBUG_PRINT_H_

#define DEBUG_PRINT_OFF 

#ifdef DEBUG_PRINT_ON /*    DEBUG_PRINT_OFF    */
#define DEBUG_PRINT printf
#else 
#define DEBUG_PRINT      
#endif

#endif