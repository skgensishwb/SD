#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "basefile.hpp"
#include "../../lab1/src/mystring.hpp"

bool BaseFile::isOpen() {
    return (m_file != nullptr);
}

bool BaseFile::canRead() {
    return (m_file != nullptr) && (access(m_path.cStr(), R_OK) == 0); //
}

bool BaseFile::canWrite() {
    return (m_file != nullptr) && (access(m_path.cStr(), W_OK) == 0); //
}

size_t BaseFile::writeRaw(const void *buf, size_t nBytes) {
    return fwrite(buf, 1, nBytes, m_file);
}

size_t BaseFile::readRaw(void *buf, size_t maxBytes) {
    return fread(buf, 1, maxBytes, m_file);
}
long BaseFile::tell() {
    return ftell(m_file);
}

bool BaseFile::seek(long offset) { //
    return (fseek(m_file, offset, SEEK_SET) == 0);
}

size_t BaseFile::read(void *buf, size_t maxBytes) {
    return readRaw(buf, maxBytes);
}

size_t BaseFile::write(const void *buf, size_t nBytes) {
    return writeRaw(buf, nBytes);
}

BaseFile::BaseFile() : m_file(nullptr) {
    m_path.copyString("");
    std::cout << "Default constructor" << std::endl;
}

BaseFile::BaseFile(const char* filePath, const char* mode) : m_file(nullptr) {
    m_path.copyString(filePath);
    m_file = fopen(filePath, mode);
    std::cout << "Constructor with parameters" << std::endl;
}

BaseFile::BaseFile(FILE* filePtr) : m_file(filePtr) {
    m_path.copyString("<external>");
    std::cout << "Constructor with FILE" << std::endl;
}

BaseFile::~BaseFile() {
    if (m_file != nullptr) {
        fclose(m_file);
        m_file = nullptr;
    }
}

// -------------------------------------------------------------------------------------- //

int Base32File::encoded32Size(int rawSize) {
    return ((rawSize*8+4)/5);
}

int Base32File::decoded32Size(int encodeSize) {
    return (encodeSize*5/8);
}

int Base32File::encode32(const char *rawData, int rawSize, MyString* dst) {
    if (dst == nullptr || rawData == nullptr) {
        return 1;
    }
    if (rawSize < 0) {
        return 1;
    }
    if (rawSize == 0) {
        return 0;
    }

    int encodedLen = encoded32Size(rawSize);
    char* tmpBuf = new char[encodedLen + 1];
    
    unsigned int buffer = 0;
    int bitsInBuffer = 0;
    int dstIndex = 0;

    for (int i = 0; i < rawSize; i++) {
        unsigned int current_byte = static_cast<unsigned char>(rawData[i]);
        buffer = (buffer << 8) | current_byte;
        bitsInBuffer += 8;

        while (bitsInBuffer >= 5) {
            unsigned int result = (buffer >> (bitsInBuffer - 5)) & 0x1F;
            tmpBuf[dstIndex] = m_table[result];

            bitsInBuffer -= 5;
            dstIndex++;

            buffer &= (1U << bitsInBuffer) - 1;
        }
    }

    if (bitsInBuffer > 0) {
        unsigned int result = (buffer << (5 - bitsInBuffer)) & 0x1F;
        tmpBuf[dstIndex] = m_table[result];
        dstIndex++;
    }

    tmpBuf[dstIndex] = '\0';
    dst->copyString(tmpBuf);
    delete[] tmpBuf;

    return 0;
}

int Base32File::decode32(const char *encodedData, int encodedSize, MyString* dst) { // записывает в dst
    if (encodedData == nullptr || encodedData == nullptr) {
        return 1;
    }
    if (encodedSize < 0) {
        return 1;
    }
    if (encodedSize == 0) {
        return 0;
    }

    int decodingTable[256];
    for (int i = 0; i < 256; i++) {
        decodingTable[i] = -1;
    }

    for (int i = 0; i < 32; i++) {
        decodingTable[(unsigned char)m_table[i]] = i;
    }

    int decodedLen = decoded32Size(encodedSize);
    char* tmpBuf = new char[decodedLen + 1];

    unsigned int buffer = 0;
    int bitsInBuffer = 0;
    int dstIndex = 0;  

    for (int i = 0; i < encodedSize; ++i) {
        unsigned char currentChar = static_cast<unsigned char>(encodedData[i]);
        
        int five_bits = decodingTable[currentChar];
        if (five_bits == -1) {
            delete[] tmpBuf;
            return 2;
        }

        buffer = (buffer << 5) | five_bits;
        bitsInBuffer += 5;

        while (bitsInBuffer >= 8) {
            unsigned char byte = (buffer >> (bitsInBuffer - 8)) & 0xFF;
            tmpBuf[dstIndex] = (char)byte;
            dstIndex++;

            bitsInBuffer -= 8;
            buffer &= (1U << bitsInBuffer) - 1;
        }
    }

    tmpBuf[dstIndex] = '\0';
    dst->copyString(tmpBuf);
    delete[] tmpBuf;

    return 0;
}

size_t Base32File::write(const void *buf, size_t nBytes) {
    if (!canWrite() || nBytes == 0) {
        return 0;
    }

    MyString encoded;
    int result = encode32((const char*)buf, (int)nBytes, &encoded);
    if (result != 0) {
        return 0;
    }

    int encodedLen = encoded32Size((int)nBytes);
    size_t written = writeRaw(encoded.getString(), encodedLen);

    if ((int)written == encodedLen) {
        return nBytes;
    }

    return 0;
}

size_t Base32File::read(void *buf, size_t maxBytes) {
    if (!canRead() || maxBytes == 0) {
        return 0;
    }

    int encodedLen = encoded32Size((int)maxBytes);

    char* encodedBuf = new char[encodedLen + 1];
    size_t actualRead = readRaw(encodedBuf, encodedLen);

    if (actualRead == 0) {
        delete[] encodedBuf;
        return 0;
    }
    encodedBuf[actualRead] = '\0';

    MyString decoded;
    int result = decode32(encodedBuf, (int)actualRead, &decoded);
    delete[] encodedBuf;

    if (result != 0) {
        return 0;
    }

    char* decodedStr = decoded.getString();
    int decodedLen = decoded.len(decodedStr);
    size_t toCopy = (size_t)decodedLen < maxBytes ? (size_t)decodedLen : maxBytes;
    for (size_t i = 0; i < toCopy; i++) {
        ((char*)buf)[i] = decodedStr[i];
    }

    return toCopy;
}

static void setDefaultTable(char* table) {
    const char* def = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    for (int i = 0; i < 32; i++) {
        table[i] = def[i];
    }
    table[32] = '\0';
}

Base32File::Base32File() : BaseFile() {
    setDefaultTable(m_table);
    std::cout << "Base32File: Default constructor" << std::endl;
}

Base32File::Base32File(const char* filePath, const char* mode) : BaseFile(filePath, mode) {
    setDefaultTable(m_table);
    std::cout << "Base32File: Constructor with parameters" << std::endl;
}

Base32File::Base32File(const char* filePath, const char* mode, const char* table)
    : BaseFile(filePath, mode)
{
    for (int i = 0; i < 32; i++) {
        m_table[i] = table[i];
    }
    m_table[32] = '\0';
    std::cout << "Base32File: Constructor with custom table" << std::endl;
}

Base32File::~Base32File() {
    std::cout << "Base32File: Destructor" << std::endl;
}