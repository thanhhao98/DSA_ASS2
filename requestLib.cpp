/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "requestLib.h"


void loadRequests(char* fName, L1List<VM_Request_t> &rList) {
    ifstream reqFile(fName);
    if(reqFile.fail()){
      cout << "The file i not fount!";
      return;
    }
    string tempString;
    while(getline(reqFile, tempString)){
      if(!tempString.empty()){
        string requestCode;
        stringstream streamLine(tempString);
        while(streamLine>>requestCode){
          if(!requestCode.empty()){
            VM_Request_t *newRequest = new VM_Request_t(requestCode);
            int i=0;
            while(newRequest->code[i]!='\0'){
              if(newRequest->code[i]==';' && newRequest->code[i+1]=='\0'){
                newRequest->code[i]='\0';
              }
              i++;
            }
            rList.push_back(*newRequest);
          }
        }
      }
    }
    reqFile.close();
}
