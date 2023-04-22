class MainForm : public Form, public IPorgrss
{
    TextBox* txtFilePath;
    TextBox* txtFileNumber;
    ProgressBar* progressBar;

public:
    void Button1_Click(){
        string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        ConsoleNotifier cn;

        FileSplitter splitter(filePath,number,this);

        splitter.addIProgress(this);
        splitter.addIProgress(&cn);

        splitter.split();
        splitter.removeIProgress(this);
        splitter.removeIProgress(&cn);
    }

    virtual void DoProgress(float value){
        progressBar->setValue(value);
    }
};

class ConsoleNotifier:public IProgress{ //second observer
    public:
    virtual void DoProgress(float value){
        cout<<".";
    }
}