/*
 *  sha1.cpp
 *
 *  Copyright (C) 1998, 2009
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *****************************************************************************
 *  $Id: sha1.cpp 12 2009-06-22 19:34:25Z paulej $
 *****************************************************************************
 *
 *  Description:
 *      This class implements the Secure Hashing Standard as defined
 *      in FIPS PUB 180-1 published April 17, 1995.
 *
 *      The Secure Hashing Standard, which uses the Secure Hashing
 *      Algorithm (SHA), produces a 160-bit message digest for a
 *      given data stream.  In theory, it is highly improbable that
 *      two messages will produce the same message digest.  Therefore,
 *      this algorithm can serve as a means of providing a "fingerprint"
 *      for a message.
 *
 *  Portability Issues:
 *      SHA-1 is defined in terms of 32-bit "words".  This code was
 *      written with the expectation that the processor has at least
 *      a 32-bit machine word size.  If the machine word size is larger,
 *      the code should still function properly.  One caveat to that
 *      is that the input functions taking characters and character arrays
 *      assume that only 8 bits of information are stored in each character.
 *
 *  Caveats:
 *      SHA-1 is designed to work with messages less than 2^64 bits long.
 *      Although SHA-1 allows a message digest to be generated for
 *      messages of any number of bits less than 2^64, this implementation
 *      only works with messages with a length that is a multiple of 8
 *      bits.
 *
 */


#include <sha1/sha1.h>

SHA1::SHA1() {
    Reset();
}

void SHA1::reset() {
    lengthLow         = 0;
    lengthHigh        = 0;
    messageBlockIndex = 0;

    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;

    computed  = false;
    corrupted = false;
}

bool SHA1::result(unsigned *messageDigestArray) {
    if ( corrupted )
        return false;

    if ( !computed ) {
        padMsg();
        computed = true;
    }

    for( int i = 0; i < 5; i++ )
        messageDigestArray[i] = H[i];

    return true;
}

void SHA1::input(const unsigned char *messageArray, unsigned length) {
    if ( !length )
        return;

    if ( computed || corrupted )
    {
        corrupted = true;
        return;
    }

    while( length-- && !corrupted )
    {
        messageBlock[messageBlockIndex++] = *messageArray & 0xFF;

        lengthLow += 8;
        lengthLow &= 0xFFFFFFFF;
        if (lengthLow == 0)
        {
            lengthHigh++;
            lengthHigh &= 0xFFFFFFFF;
            if (lengthHigh == 0)
                corrupted = true;
        }

        if (messageBlockIndex == 64)
            processBlock();

        messageArray++;
    }
}

void SHA1::input(const char *messageArray, unsigned length)
{
    input((unsigned char *) messageArray, length);
}

void SHA1::Input(unsigned char message_element)
{
    Input(&message_element, 1);
}

void SHA1::Input(char message_element)
{
    Input((unsigned char *) &message_element, 1);
}

SHA1& SHA1::operator<<(const char *messageArray)
{
    const char *p = messageArray;

    while(*p)
    {
        Input(*p);
        p++;
    }

    return *this;
}

SHA1& SHA1::operator<<(const unsigned char *messageArray)
{
    const unsigned char *p = messageArray;

    while(*p)
    {
        Input(*p);
        p++;
    }

    return *this;
}

SHA1& SHA1::operator<<(const char message_element)
{
    Input((unsigned char *) &message_element, 1);

    return *this;
}

SHA1& SHA1::operator<<(const unsigned char message_element)
{
    Input(&message_element, 1);

    return *this;
}

void SHA1::processBlock()
{
    const unsigned K[] =    {               // Constants defined for SHA-1
                                0x5A827999,
                                0x6ED9EBA1,
                                0x8F1BBCDC,
                                0xCA62C1D6
                            };
    int         t;                          // Loop counter
    unsigned    temp;                       // Temporary word value
    unsigned    W[80];                      // Word sequence
    unsigned    A, B, C, D, E;              // Word buffers

    /*
     *  Initialize the first 16 words in the array W
     */
    for(t = 0; t < 16; t++)
    {
        W[t] = ((unsigned) messageBlock[t * 4]) << 24;
        W[t] |= ((unsigned) messageBlock[t * 4 + 1]) << 16;
        W[t] |= ((unsigned) messageBlock[t * 4 + 2]) << 8;
        W[t] |= ((unsigned) messageBlock[t * 4 + 3]);
    }

    for(t = 16; t < 80; t++)
    {
       W[t] = CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
    }

    A = H[0];
    B = H[1];
    C = H[2];
    D = H[3];
    E = H[4];

    for(t = 0; t < 20; t++)
    {
        temp = CircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 20; t < 40; t++)
    {
        temp = CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 40; t < 60; t++)
    {
        temp = CircularShift(5,A) +
               ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = CircularShift(30,B);
        B = A;
        A = temp;
    }

    for(t = 60; t < 80; t++)
    {
        temp = CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = CircularShift(30,B);
        B = A;
        A = temp;
    }

    H[0] = (H[0] + A) & 0xFFFFFFFF;
    H[1] = (H[1] + B) & 0xFFFFFFFF;
    H[2] = (H[2] + C) & 0xFFFFFFFF;
    H[3] = (H[3] + D) & 0xFFFFFFFF;
    H[4] = (H[4] + E) & 0xFFFFFFFF;

    messageBlockIndex = 0;
}

void SHA1::padMsg()
{
    /*
     *  Check to see if the current message block is too small to hold
     *  the initial padding bits and length.  If so, we will pad the
     *  block, process it, and then continue padding into a second block.
     */
    if (messageBlockIndex > 55)
    {
        messageBlock[messageBlockIndex++] = 0x80;
        while(messageBlockIndex < 64)
        {
            messageBlock[messageBlockIndex++] = 0;
        }

        processBlock();

        while(messageBlockIndex < 56)
        {
            messageBlock[messageBlockIndex++] = 0;
        }
    }
    else
    {
        messageBlock[messageBlockIndex++] = 0x80;
        while(messageBlockIndex < 56)
        {
            messageBlock[messageBlockIndex++] = 0;
        }

    }

    /*
     *  Store the message length as the last 8 octets
     */
    messageBlock[56] = (lengthHigh >> 24) & 0xFF;
    messageBlock[57] = (lengthHigh >> 16) & 0xFF;
    messageBlock[58] = (lengthHigh >> 8) & 0xFF;
    messageBlock[59] = (lengthHigh) & 0xFF;
    messageBlock[60] = (lengthLow >> 24) & 0xFF;
    messageBlock[61] = (lengthLow >> 16) & 0xFF;
    messageBlock[62] = (lengthLow >> 8) & 0xFF;
    messageBlock[63] = (lengthLow) & 0xFF;

    processBlock();
}

unsigned SHA1::CircularShift(int bits, unsigned word)
{
    return ((word << bits) & 0xFFFFFFFF) | ((word & 0xFFFFFFFF) >> (32-bits));
}
