/*
 *  sha1.h
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *****************************************************************************
 *  $Id: sha1.h 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This class implements the Secure Hashing Standard as defined
 *      in FIPS PUB 180-1 published April 17, 1995.
 *
 *      Many of the variable names in this class, especially the single
 *      character names, were used because those were the names used
 *      in the publication.
 *
 *      Please read the file sha1.cpp for more information.
 *
 */

#ifndef WOLF_SHA1_H
#define WOLF_SHA1_H

class SHA1 {
public:
    SHA1();
    void Reset();
    bool Result(unsigned * message_digest_array);
    void Input(const unsigned char * message_array, unsigned length);
    void Input(const char * message_array, unsigned length);
    void Input(unsigned char message_element);
    void Input(char message_element);
    SHA1& operator << (const char *message_array);
    SHA1& operator << (const unsigned char *message_array);
    SHA1& operator << (const char message_element);
    SHA1& operator << (const unsigned char message_element);
private:
    void ProcessMessageBlock();
    void PadMessage();
    inline unsigned CircularShift(int bits, unsigned word);
    unsigned H[5];
    unsigned Length_Low;
    unsigned Length_High;
    unsigned char Message_Block[64];
    int Message_Block_Index;
    bool Computed;
    bool Corrupted;
};

#endif /* WOLF_SHA1_H */
