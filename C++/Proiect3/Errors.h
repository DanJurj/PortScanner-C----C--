#pragma once
#define ERR_BASE 1024
#define ERR_ALOC (ERR_BASE +1)
#define ERR_OPEN (ERR_BASE +2)
#define ERR_SOCKET (ERR_BASE +3)
#define ERR_TECHNIQUE_UNKNOWN (ERR_BASE +4)
#define ERR_INCORECT_SYNTAX (ERR_BASE +5)
#define ERR_INCORECT_GROUPING_CHOICE (ERR_BASE + 6)
#define ERR_WRONG_SCAN (ERR_BASE +7)
#define ERR_CONNECT (ERR_BASE +8)
#define ERR_SEND    (ERR_BASE +9)
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define CHECK_ALOC(ptr)\
	if(ptr==NULL)\
		throw new Exception(ERR_ALOC,"eroare alocare");
#define CHECK_OPEN(ptr)\
	if(ptr==NULL)\
		throw new Exception(ERR_OPEN,"eroare deschidere fisier");
enum Grupare
{
	Group_IP, Group_Port
};

