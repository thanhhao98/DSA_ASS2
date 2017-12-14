/*
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for database management
 * =========================================================================================
 */

#ifndef DSA171A2_DBLIB_H
#define DSA171A2_DBLIB_H

#include <string>
#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <functional>

#include "dsaLib.h"
#include "requestLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define ID_MAX_LENGTH   16

typedef struct VM_Record {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  longitude, latitude;
    VM_Record() {
        id[0] = 0;
    }
    VM_Record(const char* busID) {
        strcpy(id, busID);
    }
    VM_Record(VM_Record& bus) : timestamp(bus.timestamp), longitude(bus.longitude), latitude(bus.latitude) {
        strcpy(id, bus.id);
    }
    inline bool operator==(VM_Record a){
        return (int)this->timestamp == (int)a.timestamp;
    }
    inline bool operator<(VM_Record a){
        return (int)this->timestamp < (int)a.timestamp;
    }
    inline bool operator>(VM_Record a){
        return (int)this->timestamp > (int)a.timestamp;
    }
    inline bool operator<=(VM_Record a){
        return *this==a||*this<a;
    }
    inline bool operator>=(VM_Record a){
        return *this==a||*this>a;
    }
}VM_Record_t;

void    printVMRecord(VM_Record &);
void    strPrintTime(char* des, time_t& t);
bool    parseVMRecord(char*, VM_Record &);
void    loadVMDB(char*, L1List<VM_Record> &);
double  distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

bool processRequest(VM_Request &, L1List<VM_Record> &, void *);

bool initVMGlobalData(void** pGData);
void releaseVMGlobalData(void* pGData);

void process(L1List<VM_Request>& requestList, L1List<VM_Record>& recordList);

#endif //DSA171A2_DBLIB_H
