//
//  main.cpp
//  CECS282_Program6
//
//  Created by Jasmin Agustin on 4/19/17.
//  Copyright © 2017 Jasmin Agustin. All rights reserved.
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // allow Microsoft Visual C++ to user strcpy insted of strcpy_s
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <iomanip>

#include "MemoryManager.hpp"

struct simpleDate{
    short date[3];
};

void printSimpleDate(simpleDate * sdPtr){
    std::cout << *(short *)((char *)sdPtr + 0);
    std::cout << '/';
    std::cout << *(short *)((char *)sdPtr + 2);
    std::cout << '/';
    std::cout << *(short *)((char *)sdPtr + 4);
}

void setSimpleDate(simpleDate * sdPtr, int m, int d, int y){
    short * month = (short *) ((char *) sdPtr + 0);
    short * day = (short *) ((char *) sdPtr + 2);
    short * year = (short *) ((char *) sdPtr + 4);
    * month = (short) m;
    * day = (short) d;
    * year = (short) y;
}

int main(void){
    using namespace MemoryManager;  // allow functions in Memory Manager to be used without prefix
    initializeMemoryManager();
    
    int start = freeMemory();
    
    std::cout << "\nMem before any allocations\n";
    std::cout << "Free Memory:\t"<<freeMemory()<<std::endl;
    std::cout << "InUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "Used Memory:\t"<<usedMemory()<<std::endl;
    //	memView(0, 60);
    //	std::cin.get();
    
    //allocate some memory
    
    simpleDate* birthDayPtr = (simpleDate *) allocate(sizeof(simpleDate));
    std::cout << "\nMem after allocation of birthDay\n";
    std::cout << "size(birthDayPtr) = "<<size(birthDayPtr)<<std::endl;
    std::cout << "Free Memory:\t"<<freeMemory()<<std::endl;
    std::cout << "InUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "Used Memory:\t"<<usedMemory()<<std::endl;
    //	memView(0, 60);
    //	std::cin.get();
    
    char* gradePtr = (char*)allocate(sizeof(char));
    std::cout << "\nMem after allocation of gradePtr:\n";
    std::cout << "size(gradePtr) = "<<size(gradePtr)<<std::endl;
    std::cout << "Free Memory:\t"<<freeMemory()<<std::endl;
    std::cout << "InUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "Used Memory:\t"<<usedMemory()<<std::endl;
    //	memView(0, 60);
    //	std::cin.get();
    
    int* IDPtr = (int*)allocate(sizeof(int));
    std::cout << "\nMem after allocation of IDPtr:\n";
    std::cout << "size(IDPtr) = "<<size(IDPtr)<<std::endl;
    std::cout << "Free Memory:\t"<<freeMemory()<<std::endl;
    std::cout << "InUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "Used Memory:\t"<<usedMemory()<<std::endl;
    //	memView(0, 60);
    //	std::cin.get();
    
    char* name = (char*)allocate(15);
    std::cout << "\nMem after allocation of name:\n";
    std::cout << "size(name) = "<<size(name)<<std::endl;
    std::cout << "Free Memory:\t"<<freeMemory()<<std::endl;
    std::cout << "InUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "Used Memory:\t"<<usedMemory()<<std::endl;
    //	memView(0, 60);
    //	std::cin.get();
    
    std::cout << "\nMem after all allocations, before assignments\n";
    
    //	memView(0, 60);
    //	std::cin.get();
    
    *gradePtr = 'A';
    setSimpleDate(birthDayPtr, 5, 11, 2017);
    *IDPtr = 123456789;
    strcpy(name, "Master Gold");
    
    //	std::cout << "\nMem after all allocations, after assignments\n";
    
    //	memView(0, 60);
    //	system("pause");
    
    std::cout << std::endl;
    
    std::cout << "gradePtr    :" << " Address:" << (unsigned long*)gradePtr << " Value:"<<*gradePtr<<std::endl;
    
    std::cout << "birthDayPtr :" << " Address:" << (unsigned long*)(short *)birthDayPtr << " Value:";
    printSimpleDate (birthDayPtr);
    std::cout << std::endl;
    
    std::cout << "IDPtr       :"<<" Address:" << (unsigned long*)IDPtr << " Value:"<< *IDPtr<<std::endl;
    std::cout << "name        :"<<" Address:" << (unsigned long*)name << " Value:"<< name<<std::endl;
    
    std::cout << "\nDeallocating IDptr:"<<std::endl;
    deallocate(IDPtr);
    
    std::cout << "\nDeallocating gradePtr:"<<std::endl;
    deallocate(gradePtr);
    //	memView(0, 60);
    //	std::cout << "Press any key to continue:";
    //	std::cin.get();
    
    
    std::cout << "\nLeaking some Memory...\n";
    for(int i=0; i<5000; i++)
        int *memLeak = (int *) allocate(4);
    
    //	std::cout << "\nMem after Deallocations\n"<<std::endl;
    //	memView(0, 60);
    
    std::cout << "\n\nFree memory at start = " << start << std::endl;
    std::cout << "\n\nFree memory now = " << freeMemory() << std::endl;
    std::cout << "\n\nTotal Memory used = " << start - freeMemory() << std::endl;
    std::cout << "inUse Memory:\t"<<inUseMemory()<<std::endl;
    std::cout << "used Memory:\t"<<usedMemory()<<std::endl;
    std::cout << "Total Memory:\t"<<inUseMemory()+freeMemory()+usedMemory()<<std::endl;
    
    std::cout << std::endl;
    printSimpleDate(birthDayPtr);
    std::cout << "...Happy Birthday "<<name<<"!!!\n\n"<<std::endl;
    
    // force the screen to pause
    std::cout << "Press any key to continue:";
    std::cin.get();
    
    return 0;
}
