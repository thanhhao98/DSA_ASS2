/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#define __PI 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = gmtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadVMDB(char* fName, L1List<VM_Record> &db) {
    ifstream dbFile(fName);
    if(dbFile.fail()){
        cout << "The file i not fount!";
        return;
    }
    string tempString;
    getline(dbFile, tempString);
    while(getline(dbFile, tempString,',')){
        if(!tempString.empty()){
            VM_Record newNode;
            // read time
            getline(dbFile, tempString,',');
            struct tm tm;
            strptime(tempString.data(), "%m/%d/%Y %H:%M:%S" , &tm);
            newNode.timestamp = timegm(&tm);
            //read id
            getline(dbFile, tempString,',');
            strncpy(newNode.id, tempString.data(), ID_MAX_LENGTH - 1);            
            //read longitude
            getline(dbFile, tempString,',');
            newNode.longitude = stod(tempString);            
            //read latitude
            getline(dbFile, tempString,',');
            newNode.latitude = stod(tempString);
            
            L1Item<VM_Record> *temp = db.getHead();
            while(temp){
                if(!strcmp(temp->data.id,newNode.id)){
                    temp->treeAVL.insert(newNode);
                    temp->maxLongLa[0] = (temp->maxLongLa[0]<newNode.longitude)? newNode.longitude:temp->maxLongLa[0];
                    temp->minLongLa[0] = (temp->minLongLa[0]>newNode.longitude)? newNode.longitude:temp->minLongLa[0];
                    temp->maxLongLa[1] = (temp->maxLongLa[1]<newNode.latitude)? newNode.latitude:temp->maxLongLa[1];
                    temp->minLongLa[1] = (temp->minLongLa[1]>newNode.latitude)? newNode.latitude:temp->minLongLa[1];
                    break;
                }
                temp=temp->pNext;
            }
            if(!temp){
                db.insertHead(newNode);
                db.getHead()->treeAVL.insert(newNode);
                db.getHead()->maxLongLa[0] = db.getTail()->minLongLa[0] = newNode.longitude;
                db.getHead()->maxLongLa[1] = db.getTail()->minLongLa[1] = newNode.latitude;
            }       
        }
        getline(dbFile,tempString);
    }
    dbFile.close();
}

bool parseVMRecord(char *pBuf, VM_Record &bInfo) {
    // TODO: write code to parse a record from given line
}

void process(L1List<VM_Request>& requestList, L1List<VM_Record>& rList) {
    void*   pGData = NULL;
    initVMGlobalData(&pGData);

    while (!requestList.isEmpty()) {
        if(!processRequest(requestList[0], rList, pGData))
            cout << requestList[0].code << " is an invalid event\n";
        requestList.removeHead();
    }

    releaseVMGlobalData(pGData);
}

void printVMRecord(VM_Record &b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
inline double deg2rad(double deg) {
    return (deg * __PI / 180);
}

///  This function converts radians to decimal degrees
inline double rad2deg(double rad) {
    return (rad * 180 / __PI);
}

///   This function return distance of 2 poin with longitude vs latitude
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}