/*
 * Author: binyxia
 * Note :The Observer pattern typically involves two main components:
 *       a subject (also called an observable or publisher) and
 *       one or more observers (also called subscribers or listeners).
 *       The subject is the object that's being observed,
 *       while the observers are the objects that need to be notified
 *       when the state of the subject changes.
 */

class IProgress
{
public:
    virtual void DoProgress(float value) = 0;
    virtual ~IProgress() {}
};

class FileSplitter
{
    string m_filepath;
    int m_fileNumber;

    List<IProgress*> m_iprogressList; // abstract notification mechanism
public:
    FileSplitter(const string &filePath, int fileNumber) : m_fileNumber(fileNumber), m_filepath(filePath)
    {
    }

    void addIProgress(IProgress *iprogress){
        m_iprogressList.push_back(iprogress);
    }

    void removeIProgress(IProgress *iprogress){
        m_iprogressList.remove(iprogress);
    }
    void split()
    {
        // 1. Read big file

        // 2. Write to small files in batches
        for (int i = 0; i < m_fileNumber; i++)
        {
            //...

            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            opProgress(progressValue);
        }
    }

protected:
    virtual void
    onProgress(float value)
    {
        List<IProgress*>::Iterator itor = m_iprogressList.begin();

        while(itor != m_iprogressList.end()){
            (*itor)->DoProgress(value);
            itor++;
        }
    }
};
