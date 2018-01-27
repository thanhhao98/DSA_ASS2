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

void funRequest1(char* id1, char* id2, VM_Record saveTime, L1List<VM_Record> recordList){
    L1Item<VM_Record> *temp = recordList.getHead();
    AVLNode<VM_Record> *node1 = NULL;
    AVLNode<VM_Record> *node2 = NULL;
    while(temp){
        if(!strcmp(id1,temp->data.id)){
            node1 = temp->treeAVL.find(saveTime);
        }
        if(!strcmp(id2,temp->data.id)){
            node2 = temp->treeAVL.find(saveTime);
        }
        temp = temp->pNext;
    }
    if(node1&&node2)
    {
        if(node1->data.longitude >node2->data.longitude){
            cout << "E ";
        } else {
            cout << "W ";
        }
        if(node1->data.latitude > node2->data.latitude){
            cout << "N ";
        } else {
            cout << "S ";
        }
        cout << distanceEarth(node1->data.latitude, node1->data.longitude, node2->data.latitude, node2->data.longitude) << endl;
    }
    else {
        cout << -1 << endl;
    }

}

void funRequest2(int key , double Along, L1List<VM_Record> recordList){
    L1Item<VM_Record> *temp = recordList.getHead();
    int num = 0;
    if(key){
        while(temp){
            num = Along<temp->maxLongLa[0]? num:num+1;
            temp = temp->pNext;
        }
    } else {
        while(temp){
            num = Along>temp->minLongLa[0]? num:num+1;
            temp = temp->pNext;
        }
    }
    cout << num << endl;
}

void funRequest3(int key , double Ala, L1List<VM_Record> recordList){
    L1Item<VM_Record> *temp = recordList.getHead();
    int num = 0;
    if(key){
        while(temp){
            num = Ala<temp->maxLongLa[1]? num:num+1;
            temp = temp->pNext;
        }
    } else {
        while(temp){
            num = Ala>temp->minLongLa[1]? num:num+1;
            temp = temp->pNext;
        }
    }
    cout << num << endl;
}

void funRequest4(double* coordinateLongLati, double r, VM_Record *timeRecord, L1List<VM_Record> recordList){
    int countVM = 0;
    L1Item<VM_Record> *temp = recordList.getHead();
    while(temp){
        L1List<VM_Record> newList;
        makeListInSize(temp->treeAVL,newList,timeRecord[0],timeRecord[1]);
        if(newList.getSize()){
            L1Item<VM_Record> *subTemp = newList.getHead();
            while(subTemp){
                if(distanceEarth(coordinateLongLati[1],coordinateLongLati[0],subTemp->data.latitude,subTemp->data.longitude)<r){
                    countVM++;
                    break;
                }
                subTemp = subTemp->pNext;
            }
        }
        temp = temp->pNext;
    }
    cout << countVM << endl;
}

void funRequest5(double r, VM_Record dataRecord, L1List<VM_Record> recordList){
    // not exist VM with id ?
    L1Item<VM_Record> *temp = recordList.getHead();
    while(temp){
        if(!strcmp(dataRecord.id,temp->data.id)){
            L1List<VM_Record> newList;
            makeList(temp->treeAVL,newList);
            L1Item<VM_Record> *subTemp = newList.getHead();
            while(subTemp){
                // how to count time move into and go out ??
                // TODO


                subTemp = subTemp->pNext;
            }

            break;
        }
        temp = temp->pNext;
    }


}

bool processRequest(VM_Request &request, L1List<VM_Record> &recordList, void *pGData) {
    int checkCase = checkRequest(request);
    if(!checkCase) return false;
    switch(checkCase){
        case 1:{
            char id1[ID_MAX_LENGTH];
            char id2[ID_MAX_LENGTH];
            VM_Record saveTime;
            // Here code to get id1 id2 and saveTime
            string temp;
            stringstream scin(request.code);
            getline(scin,temp,'_');
            getline(scin,temp,'_');
            strncpy(id1, temp.data(), ID_MAX_LENGTH - 1);
            getline(scin,temp,'_');
            strncpy(id2, temp.data(), ID_MAX_LENGTH - 1);
            getline(scin,temp);
            if(temp.length()==6){
                char getTime[30] = "12/05/2016 ";
                getTime[11] = temp.data()[0];
                getTime[12] = temp.data()[1];
                getTime[13] = ':';
                getTime[14] = temp.data()[2];
                getTime[15] = temp.data()[3];
                getTime[16] = ':';
                getTime[17] = temp.data()[4];
                getTime[18] = temp.data()[5];
                getTime[19] = '\0';

                struct tm tm;
                strptime(getTime, "%m/%d/%Y %H:%M:%S" , &tm);
                saveTime.timestamp = timegm(&tm);
                cout << request.code << ": ";
                funRequest1(id1,id2,saveTime, recordList); 

                return true;
            } else {
                // sure ??
                return false;
            }
        }
        case 2:{
            double Along;
            string temp;
            stringstream scin(request.code);
            getline(scin,temp,'_');
            getline(scin,temp,'_');
            Along = stod(temp);
            getline(scin,temp);
            if(temp.length()==1){
                int key = temp.data()[0]=='W'? 1:-1;
                if(temp.data()[0]=='W'){
                    key = 1;
                } else if(temp.data()[0]=='E') {
                    key = 0;
                } else {
                    return false;
                }
                cout << request.code << ": ";
                funRequest2( key ,Along, recordList);
                return true;
            } else return false;
        }
        case 3:{
            double Ala;
            string temp;
            stringstream scin(request.code);
            getline(scin,temp,'_');
            getline(scin,temp,'_');
            Ala = stod(temp);
            getline(scin,temp);
            if(temp.length()==1){
                int key = temp.data()[0]=='E'? 1:-1;
                if(temp.data()[0]=='S'){
                    key = 1;
                } else if(temp.data()[0]=='N') {
                    key = 0;
                } else {
                    return false;
                }
                cout << request.code << ": ";
                funRequest3( key ,Ala, recordList);
                return true;
            } else return false;

        }
        case 4:{
            // TOTO
            // seprate the parameter

        }
        case 5:{

        }
        case 6:{

        }
        case 7:{

        }
        case 8:{

        }
        case 9:{

        }
    }
    return true;
}


