// implemented by Naoya Maeda 2011/10/25 //
#ifndef KVS_EXCEPTION_H_INCLUDE
#define KVS_EXCEPTION_H_INCLUDE

#include <exception>
#include <string>
#include <kvs/Message>


#if KVS_ENABLE_DEBUG
#define KVS_THROW(EXCEPTION, message) \
    (kvsMessageError(message), 
     kvs::detail::Throw<EXCEPTION>(message, KVS_MACRO_FILE, KVS_MACRO_LINE, KVS_MACRO_FUNC))
#else
#define KVS_THROW(EXCEPTION, message) throw EXCEPTION(message);
#endif

namespace kvs
{

namespace detail
{
    inline std::string MakeSourceInfo(const char* file, int line, const char* func)
    {
        std::stringstream ss;
        ss << "At file : " << file << "\n";
        ss << "At line : " << line << "\n";
        ss << "At func : " << func << "\n";
        return ss.str();
    }

    template <typename ExceptionType>
    inline void Throw(const std::string& message, const char* file, int line, const char* func)
    {
        throw ExceptionType(message + MakeSourceInfo(file, line, func));
    }
}

class Exception : public std::exception
{
protected:
    explicit Exception(const std::string& message)
        : m_message(message)
    {}

public:
    const char* what() const throw()
    {
        return m_message.c_str();
    }

    void addMessage(const std::string& str)
    {
        m_message += str;
    }

private:
    std::string m_message;
}; // Exception


#define KVS_DEFINE_EXCEPTION(NAME) \
class NAME: public kvs::Exception \
{ \
public: \
    explicit NAME(const std::string& message = "") \
        : kvs::Exception(message) {} \
}

KVS_DEFINE_EXCEPTION(TempException);
KVS_DEFINE_EXCEPTION(NullPointingException);
KVS_DEFINE_EXCEPTION(NotImplementedException);
KVS_DEFINE_EXCEPTION(NotSupportedException);
KVS_DEFINE_EXCEPTION(FileReadFaultException);
KVS_DEFINE_EXCEPTION(FileWriteFaultException);
KVS_DEFINE_EXCEPTION(InvalidDataException);
KVS_DEFINE_EXCEPTION(InvalidTypeException);
KVS_DEFINE_EXCEPTION(OpenGLException);

#undef KVS_DEFINE_EXCEPTION


//class TempException : public kvs::Exception
//{
//public:
//    explicit TempException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit TempException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class NullPointingException : public kvs::Exception
//{
//public:
//    explicit NullPointingException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit NullPointingException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class NotImplementedException : public kvs::Exception
//{
//public:
//    explicit NotImplementedException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit NotImplementedException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class NotSupportedException : public kvs::Exception
//{
//public:
//    explicit NotSupportedException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit NotSupportedException(const char* message)
//        : kvs::Exception(message) {}
//};
//
////class FileNotFoundException : public kvs::Exception
////{
////public:
////    explicit FileNotFoundException(const std::string& message)
////        : kvs::Exception(message) {}
////    explicit FileNotFoundException(const char* message)
////        : kvs::Exception(message) {}
////};
//
////class FileCannotOpenException : public kvs::Exception
////{
////public:
////    explicit FileCannotOpenException(const std::string& message)
////        : kvs::Exception(message) {}
////    explicit FileCannotOpenException(const char* message)
////        : kvs::Exception(message) {}
////};
//
//class FileReadFaultException : public kvs::Exception
//{
//public:
//    explicit FileReadFaultException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit FileReadFaultException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class FileWriteFaultException : public kvs::Exception
//{
//public:
//    explicit FileWriteFaultException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit FileWriteFaultException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class InvalidDataException : public kvs::Exception
//{
//public:
//    explicit InvalidDataException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit InvalidDataException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class InvalidTypeException : public kvs::Exception
//{
//public:
//    explicit InvalidTypeException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit InvalidTypeException(const char* message)
//        : kvs::Exception(message) {}
//};
//
//class OpenGLException : public kvs::Exception
//{
//public:
//    explicit OpenGLException(const std::string& message)
//        : kvs::Exception(message) {}
//    explicit OpenGLException(const char* message = "")
//        : kvs::Exception(message) {}
//};

} // kvs

#endif
