 /*
 * Author: binyxia
 * Usage: Template Method note
 * Note: Simple mechanism, Polymorphism of Virtual Functions
 *       Provides flexible extension. Virtual func is based on func pointer
 */
 
 // Lib developer
class Library{
public:
    //Stable template method
    void Run(){ // I think Run process is generally stable, but some of the details are changing.

    Step1();  //stable

    if (Step2())  // changing ==> Polymorphic invocation of virtual functions
    {
        Step3();  //stable
    }

    for (int i = 0; i < 4; i++)
    {
        Step4(); //changing ==> Polymorphic invocation of virtual functions
    }

    Step5();
    }

    virtual ~Library(){}   // Destructor function must be virtual, otherwise child can't call his own destructor func

protected: 
    //Set these funcs to protected because it makes no sense to call alone
    void Step1(){ //stable
        //...
    }

     void Step3(){ //stable
        //...
    }

     void Step5(){ //stable
        //...
    }

    virtual bool Step2()=0;//changing
    virtual bool Step4()=0;//changing
 };


 //Application developer
 class Application :public Library
 {
 protected:
    virtual bool Step2(){ //child Override Implementation

    }

    virtual bool Step4(){ //child Override Implementation

    }
 };
 
 int main(){
    Library *pLib=new Application(); //*pLib is a Polymorphic pointer
    pLib->Run();
    delete pLib;

 }
 