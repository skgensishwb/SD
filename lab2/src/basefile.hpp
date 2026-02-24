#pragma once

class BaseFile {
    protected:
        FILE* m_file;
        MyString m_path;

    public:
        bool isOpen();
        bool canRead();
        bool canWrite();
        size_t writeRaw(const void *buf, size_t nBytes);
        size_t readRaw(void *buf, size_t maxBytes);
        long tell();
        bool seek(long offset);
        size_t read(void *buf, size_t maxBytes);
        size_t write(const void *buf, size_t nBytes);

        BaseFile();
        BaseFile(const char* filePath, const char* mode);
        BaseFile(FILE* filePtr);

        ~BaseFile();
};

class Base32File : public BaseFile {
    protected:
        char m_table[33];

    protected:
        int encoded32Size(int rawSize);
        int decoded32Size(int encodeSize);
        int encode32(const char *rawData, int rawSize, MyString* dst);
        int decode32(const char *encodedData, int encodedSize, MyString* dst);

    public:
        size_t write(const void *buf, size_t nBytes);
        size_t read(void *buf, size_t maxBytes);

        Base32File();
        Base32File(const char* filePath, const char* mode);
        Base32File(const char* filePath, const char* mode, const char* table);

        ~Base32File();
};

class RleFile : public BaseFile {
    protected:
        unsigned char m_pendingCount; // сколько байт осталось от текущей серии
        char m_pendingByte;           // какой байт повторяется
    
    protected:
        int encodeRLE(const char *rawData, int rawSize, char** dst, int* dstSize);
        int decodeRLE(const char *encodedData, int encodedSize, char** dst, int* dstSize);

    public:
        size_t read(void *buf, size_t maxBytes);
        size_t write(const void *buf, size_t nBytes);

        RleFile();
        RleFile(const char* filePath, const char* mode);

        ~RleFile();
};