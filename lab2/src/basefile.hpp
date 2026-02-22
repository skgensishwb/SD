#pragma once

class BaseFile {
    public:
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