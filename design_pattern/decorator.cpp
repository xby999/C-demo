/*
* AUthor: binyxia
* Note: Decorator patter lets you build flexible code that can be assembled at run time.
*       Avoid excessive use of inheritance to extend the functionality of objects.
*/


// Business Operation
class Stream
{
public:
    virtual char Read(int number) = 0;
    virtual void Seek(int position) = 0;
    virtual void Write(char data) = 0;

    virtual ~Stream(){};
};

// Principal class
class FileStream : public Stream
{
public:
    virtual char Read(int number)
    {
        // Read file stream
    }
    virtual void Seek(int position)
    {
        // Seek file stream
    }
    virtual void Write(char data)
    {
        // Write file stream
    }
};

class NetworkStream : public Stream
{
public:
    virtual char Read(int number)
    {
        // Read network stream
    }
    virtual void Seek(int position)
    {
        // Seek network stream
    }
    virtual void Write(char data)
    {
        // Write network stream
    }
};

class MemoryStream : public Stream
{
public:
    virtual char Read(int number)
    {
        // Read memory stream
    }
    virtual void Seek(int position)
    {
        // Seek memory stream
    }
    virtual void Write(char data)
    {
        // Write memory stream
    }
};

// Extension operation

class DecoratorStream :public Stream
{
protected:
    Stream* stream;
    DecoratorStream(Stream* stream):stream(stream){

    }
};

class CryptoStream : public DecoratorStream
{
    //Stream *stream; Unified integration into DecoratorStream classes

public:
    CryptoStream(Stream* stream):DecoratorStream(stream){//Calling the constructor of the base class

    }
    virtual char Read(int number)
    {
        
        stream->Read(number); //Crypto read stream operation
    }
    virtual void Seek(int position)
    {
        
        stream->Seek(position); //Crypto Seek stream operation
    }
    virtual void Write(char data)
    {
        
        stream->Write(data);//Crypto Write stream operation
    }
};

class BufferedStream : public DecoratorStream{
    //Stream *stream; Unified integration into DecoratorStream classes
    public:
    BufferedStream(Stream* stream):DecoratorStream(stream){ //Calling the constructor of the base class

    }
};

void Proccess()
{
    //assembled at run time
    FileStream* s1 = new FileStream();
    CryptoStream* s2 = new CryptoStream(s1);
}