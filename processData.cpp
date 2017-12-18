/*
 * ==========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 2 - Data structures and Algorithms - Fall 2017
 * ==========================================================================================
 */
#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include "requestLib.h"
#include "dbLib.h"

using namespace std;

#define GPS_DISTANCE_ERROR 0.005


bool initVMGlobalData(void** pGData) {
    // TODO: allocate and initialize global data
    // return false if failed
    return true;
}

void releaseVMGlobalData(void* pGData) {
    // TODO: do your cleanup, left this empty if you don't have any dynamically allocated data

}

int checkRequest(VM_Request &request){
    switch(request.code[0]){
        case '1':{
            return 1;
        }
        case '2':{
            return 2;
        }
        case '3':{
            return 3;
        }
        case '4':{
            return 4;
        }
        case '5':{
            return 5;
        }
        case '6':{
            return 6;
        }
        case '7':{
            return 7;
        }
        case '8':{
            return 8;
        }
        case '9':{
            return 9;
        }
        default: return 0;
    }
}



bool processRequest(VM_Request &request, L1List<VM_Record> &recordList, void *pGData) {
    // int checkCase = checkRequest(request);
    // if(!checkCase) return false;
    // cout << request << ":";
    // switch(checkCase){
    //     case 1:{

    //     }
    //     case 2:{

    //     }
    //     case 3:{

    //     }
    //     case 4:{

    //     }
    //     case 5:{

    //     }
    //     case 6:{

    //     }
    //     case 7:{

    //     }
    //     case 8:{

    //     }
    //     case 9:{

    //     }
    // }
    // cout << endl;
    return true;
}


