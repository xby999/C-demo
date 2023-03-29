/*
 * Author: binyxia
 * Usage: Strategy pattern note
 * 
 * Note: When you use conditional statements to select between different algorithms, 
 *       the code needs to evaluate the condition each time it runs, 
 *       which can add overhead and slow down the performance of the application. 
 *       On the other hand, when you use the strategy pattern, 
 *       the selection of the algorithm is made at compile-time, 
 *       and the actual execution of the algorithm can be done using polymorphism, 
 *       which is generally faster and more efficient.
 *       
 *       The advantages of using the strategy pattern over a conditional approach like if/else include:
 *       #1 Better modularity and flexibility
 *       #2 Easier maintenance
 *       #3 Improved code reusability
 *       #4 Better testability
 */

class TaxStrategy{ //Basic class
public:
    virtual double Calculate(const Context& context)=0;  //pure virtual 
    virtual ~TaxStrategy(){}
};

class CNTax : public TaxStrategy{
public:
    virtual double Calculate(const Context& context){
        //************************
    }
};

class USTax : public TaxStrategy{
public:
    virtual double Calculate(const Context& context){
        //************************
    }
};

class DETax : public TaxStrategy{
public:
    virtual double Calculate(const Context& context){
        //************************
    }
};


class SalesOrder
{
private:
    TaxStrategy* strategy; //Polymorphic pointer
public:
    SalesOrder(StrategyFactory* strategyFactory){
        this->strategy=strategyFactory->NewStrategy();
    }
    ~SalesOrder(){
        delete this->strategy;
    }

    public double CalculateTax(){
        //...
        Context context();

        double val= strategy->Calculate(context); //Polymorphic invocation, 
                                                  //Based on different return types strategyFactory->NewStrategy()
                                                  // will call different Tax type
        //....
    }
};
//In C programm, func pointer can replace a large number of if else
