/**********************************
* File:     Type.h
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/2/2
***********************************/

#ifndef UCCPP_TYPE_H
#define UCCPP_TYPE_H

enum {
    CHAR, UCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG, LONGLONG, ULONGLONG, ENUM,
    FLOAT, DOUBLE, LONGDOUBLE, POINTER, VOID, UNION, STRUCT, ARRAY, FUNCTION
};

// type qualifier
enum {
    CONST = 0x1,
    VOLATILE = 0x2
};

/// B: memory block
enum {
    I1, U1, I2, U2, I4, U4, F4, F8, V, B
};

#endif//UCCPP_TYPE_H
