//
//  MemoryManager.cpp
//  CECS282_Program6
//
//  Created by Jasmin Agustin on 4/20/17.
//  Copyright © 2017 Jasmin Agustin. All rights reserved.
//

#include "MemoryManager.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

namespace MemoryManager{
    
    // IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
    //
    // This is the only static memory that you may use, no other global variables
    // may be created, if you need to save data make it fit in MM_pool
    //
    // IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
    
    const int MM_POOL_SIZE = 65536;
    char MM_pool[MM_POOL_SIZE];
    
    void memView(int start, int end){
        const unsigned int SHIFT = 8;
        const unsigned int MASK = 1 << (SHIFT - 1);
        
        unsigned int value;	// used to facilitate bit shifting and masking
        
        cout << "         Pool                     Unsignd  Unsigned " << endl;
        cout << "Mem Add  indx   bits   chr ASCII#  short      int    " << endl;
        cout << "-------- ---- -------- --- ------ ------- ------------" << endl;
        
        for(int i = start; i <= end; i++){
            cout << (long*)(MM_pool + i) << ':';// the actual address in hexadecimal
            cout << '[' << setw(2) << i << ']';	// the index into MM_pool
            
            value = MM_pool[i];
            cout << " ";
            for(int j = 1; j <= SHIFT; j++){// the bit sequence for this byte (8 bits)
                cout << ((value & MASK) ? '1' : '0');
                value <<= 1;
            }
            cout << " ";
            
            cout << '|' << *(char*)(MM_pool + i) << "| (";// the ASCII character of the 8 bits (1 byte)
            cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";// the ASCII number of the character
            
            cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";// the unsigned short value of 16 bits (2 bytes)
            cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";// the unsigned int value of 32 bits (4 bytes)
            
            cout << endl;
        }
    }
    
    void initializeMemoryManager(void){
        *(unsigned short*) MM_pool = 6;
        *(unsigned short*)(MM_pool + 2) = 0;
        *(unsigned short*)(MM_pool + 4) = 0;
    }
    
    void* allocate(int aSize){
        unsigned short NAM = *(unsigned short*) MM_pool;
        if(NAM + aSize > MM_POOL_SIZE)
            onOutOfMemory();
        *(unsigned short*)(MM_pool + NAM) = aSize;
        unsigned short *current = (unsigned short*)(MM_pool + NAM);
        unsigned short *inUsePtr = (unsigned short*)(MM_pool + *(unsigned short*)(MM_pool + 2));
        if(*(unsigned short*)(MM_pool + 2) == 0){
            *(current + 1) = 0;
            *(current + 2) = 0;
        }
        else{
            *(current + 1) = *(unsigned short*)(MM_pool + 2);
            *(current + 2) = 0;
            *(inUsePtr + 2) = NAM;
        }
        *(unsigned short*)(MM_pool + 2) = NAM;
        *(unsigned short*) MM_pool = *(unsigned short*) MM_pool + 6 + aSize;
        return (void*)(MM_pool + NAM + 6);
    }
    
    void deallocate(void* aPointer){
        unsigned short *usedPtr = (unsigned short*)(MM_pool + *(unsigned short*)(MM_pool + 4));
        unsigned short *current = (unsigned short*) aPointer - 3;
        unsigned short *next = (unsigned short*)(MM_pool + *(current + 1));
        unsigned short *previous = (unsigned short*)(MM_pool + *(current + 2));
        if(*(unsigned short*)(MM_pool + 4) == 0){
            *(unsigned short*)(MM_pool + 4) = *(previous + 1);
            *(previous + 1) = *(current + 1);
            *(next + 2) = *(current + 2);
            *(current + 1) = 0;
            *(current + 2) = 0;
        }
        else{
            *(usedPtr + 2) = *(previous + 1);
            *(previous + 1) = *(current + 1);
            *(next + 2) = *(current + 2);
            *(current + 1) = *(unsigned short*)(MM_pool + 4);
            *(unsigned short*)(MM_pool + 4) = *(usedPtr + 2);
            *(current + 2) = 0;
        }
    }
    
    int freeMemory(void){
        return MM_POOL_SIZE - inUseMemory() - usedMemory() - 6;
    }
    
    int usedMemory(void){
        int usedMemory = 0;
        unsigned short *current = (unsigned short*)(MM_pool + *(unsigned short*)(MM_pool + 4));
        if(*(unsigned short*)(MM_pool + 4) == 0)
            return usedMemory;
        else{
            while(*(current + 1) != 0){
                usedMemory = usedMemory + 6 + *current;
                current = (unsigned short*)(MM_pool + *(current + 1));
            }
            usedMemory = usedMemory + 6 + *current;
        }
        return usedMemory;
    }
    
    int inUseMemory(void){
        int inUseMemory = 0;
        unsigned short *current = (unsigned short*)(MM_pool + *(unsigned short*)(MM_pool + 2));
        if(*(unsigned short*)(MM_pool + 2) == 0)
            return inUseMemory;
        else{
            while(*(current + 1) != 0){
                inUseMemory = inUseMemory + 6 + *current;
                current = (unsigned short*)(MM_pool + *(current + 1));
            }
            inUseMemory = inUseMemory + 6 + *current;
        }
        return inUseMemory;
    }
    
    int size(void * aPointer){
        return *(unsigned short*)(void*)((char*)aPointer - 6);
    }
    
    void onOutOfMemory(void){
        std::cerr << "/nMemory pool out of memory" << std::endl;
        cin.get( );
        exit(1);
    }
}
