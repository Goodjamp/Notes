#include <QObject>
#include <stdint.h>

/* 
 * On the Qt we can tx CB function over the signal, to on the slot.
 * To do this we can use *function* metjhod of the std library, like next:
 * std::function<void(int a, bool b)>
 * 
 *
 * descri macrodefinition to isus pass CB function over the signal args
 */
#define CB_WRAP_2(CLASS,FUN)    std::bind(&CLASS::FUN, this, std::placeholders::_1, std::placeholders::_2)

/*
 * The next macros test to NULL the CB and call CB
 */
#define CALL_CB(x,...)        if (x != NULL) {x(__VA_ARGS__);}

/*
 * the *std::placeholders::_N* must be equal to the number of argmunts. The example above describe the
 * CB function with 2 input arguments 
 */

class A: public QObject {
    Q_OBJECT
public:
    explicit A(QObject *parent = nullptr);
    ~A(){};
	
private:
    int vara;
	bool varb;
public slots:
    /*
	 * Declare slot with one CB input argument
	 */
    sltA(std::function<void(int a, bool b)> cb);
	{
	    /*
		 * Call cb function
		 */
		CALL_CB(cb, vara, varb);
	}
}

class B: public QObject {
    Q_OBJECT
public:
    explicit B(QObject *parent = nullptr)
	{
	    varB = new B();
		connect(this, &A::sigA, varB, B::sltB);
	}
    ~B(){};
    
	/*
	 * On the next methot I show hav to emit signal with CB function
	 */
	void methodB(int a, bool b)
	{
	    emit sigB(CB_WRAP_2(B, cbB));
	}
	
signals:
    /*
	 * Declare signal with one CB input argument
	 */
    sigA(std::function<void(int a, bool b)> cb);
private
    B *varB;
	
	/*
	 * Describe CB function according signature from the signal-slot
	 */
	void cbB(int a, bool b)
	{
	   /*
	    * processing CB
	    */
	}
}

/*
 * Also we must declarate the CB function signature as new metatype !!!!!!!!!
 * We can do it on the main.cpp
 * take into acout that we must declare argument together type - name: signature is *int a*, we should declare *int a*, not only *int* !!
 */
qRegisterMetaType<std::function<void(int a, bool b)>>("std::function<void(int a, bool b)>");
 

