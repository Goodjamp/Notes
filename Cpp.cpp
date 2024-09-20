// dictionary:
// атрибуты - данные элементы - свойства
// варианты поведения - операции - функции элементы - методы
// клиенты класса - части ВНЕШНЕГО относительно класса кода который использует класс
// Фундаментальні ознаки ООП: інкапсуляція, наслідування, поліморфізм
// Інкапсуляція - поєднання властивостей і можливих операцій над в єдиному адстрактному типі даних (наприклад класі). !!!!!

//------------------------------------------------------------------------------------------
//---------------------------------using references &-----------------------------------
//------------------------------------------------------------------------------------------

int &getRef(int inVal)
{
    static int val;
    val = inVal;
    return val; // Don't use & to take an address. We return REFERENCE, not address !!
}

//------------------------------------------------------------------------------------------
//---------------------------------Simple class declaration-----------------------------------
//------------------------------------------------------------------------------------------

class Class1 {
    # private
    # By the default the access type label is: private
    void f1();
    # By the default the access type label is: private
    # "f1()" it is a private class function-member
}

class Class2 {
public:    
    void f1();
    # Redefine access type label to public
    # "f1()" it is a public class function-member
}

//------------------------------------------------------------------------------------------
//---------------------------------Constructor by default-----------------------------------
//------------------------------------------------------------------------------------------

class Class3 {
public:  // <----------- it is important set *public* access type for the user defined construct, becous default is *private*
    Class3(int inVar1 = 11, int inVar2 = 12); // This is constructor by the default. Set default value only for the prototype. 
               //      /\
private:       //      ||
    int var1;  //      ---------------------------------------------------------------------------------------------------------------+
    int var2;  //                                                                                                                     |
};             //                                                                                                                     |
               //                                                                                                                     |
Class3::Class3(int inVar1, int inVar2)  // Default constructor implementation. Default value set on the class declaration ----+
{
    var1 = inVar1;
    var2 = inVar2;
}

int main(int argCnt, char **argVal)
{    
    // The next 3 methods of creating class object is the same..
    Class3 className3;
    Class3 className4();
    Class3 className5 = Class3();

    // The next 3 methods of creating class object is the same.
    Class3 className6(2);
    Class3 className7(2, 5);
    Class3 className8 = Class3(4, 5);

    return 0;
}


//------------------------------------------------------------------------------------------
//---------------------------------Cons (read only)-----------------------------------------
//------------------------------------------------------------------------------------------
/*
The const qualifier could be used for the following:
(1)- class object: const Class Item class Object;
(2) - class item property: const int;
 */
 
 /*
   --------------------------------------------(1)-----------------------------------------------------------
   If the class object is const all class properties are const with default value. To take access (ONLY READ)
   to const properties we need to add methods with *const* specifier.
  */
#include <iostream>

using namespace std;
 
class Class4 {
public:
    Class4(int inVar = 0)
    {
        var = inVar;
    }

    int getVarValInt()  // read *var* value for the no const class object
    {
        cout << "Invoke not const";
        return var;
    }

    int getVarValInt() const // <-   Overload the getVarValInt to take a access to the class properties in case of const class objeck !! 
    {
        cout << "Invoke const";
        return var;
    }

    int getVarValExt() const; // <-   Use const to take a access to the class properties in case of const class objeck !! 

private: // or public. It does not have any matter
    int var;
};

int Class4::getVarValExt() const // <-   Use const to take a access to the class properties in case of const class objeck !! 
{
    return var;
}

int main(int argCnt, char **argVal)
{
    const Class4 classItemConst(10);
    Class4 classItemNoConst(10);
    
    cout << "Const var: " << classItemConst.getVarValInt() << "\n";
    cout << "No const var: " << classItemNoConst.getVarValInt() << "\n";
    
    return 0;
}

 /*
   --------------------------------------------(2)-----------------------------------------------------------
   The class includes const methods. All const methods must be initialized at the moment of class creation.
   A special constructor description must be used to initialize the const method.
  */
  
#include <iostream>

using namespace std;
 
class Class5 {
public:
    Class5(int inVar = 10, int intVarConst = 11)
    : varConst(intVarConst) // <------------------------Init const item.
    {
		// varConst = intVarConst; // <---------------wrong syntax !!!!!!!!!!!
        var = inVar;
    }

    int getVarConst()
    {
        return varConst;
    }
    
private:
    int var;
    const int varConst;
};

int main(int argCnt, char **argVal)
{
    Class5 classItem(5, 6);
    
    cout << "varConst = " << classItem.getVarConst();

    return 0;
}

//------------------------------------------------------------------------------------------
//---------------------------------Class as properties of other class-----------------------
//------------------------------------------------------------------------------------------

/*
  If the properties of the class are a class, we need to invoke a constructor of these properties together with the constructor of the main class. 
 */

#include <iostream>

using namespace std;

class Class6 {
public:      // <---------It is important to set access level as *public* (in the context of the task) because the default access level is *private* !!!!!!!!!!!!
    Class6(int inVar = 6)
    {
        var = inVar;
        cout << "Init Class6 var = " << var << "\n";
    }
    
private:
    int var;
};

class Class7 {
public:      // <---------It is important to set access level as *public* (in the context of the task) because the default access level is *private* !!!!!!!!!!!!
    Class7(int inVar = 7)
    {
        var = inVar;
        cout << "Init Class7 var = " << var << "\n";
    }
    
private:
    int var;
};

class Class8 {
public:      // <---------It is important to set access level as *public* (in the context of the task) because the default access level is *private* !!!!!!!!!!!!
    Class8(int inVar8 = 7, int inVar7 = 7, int inVar6 = 7)
    : class6(inVar6), class7(inVar7)        // <----- The order of invoking of the constructor is the order of declaration or properties
    {                                                                                                                               //  |  
        var = inVar8;                                                                                                               //  |
        cout << "Init Class8 var = " << var << "\n";                                                                                //  | 
    }                                                                                                                               //  | 
                                                                                                                                    //  | 
public:                                                                                                                             //  |
    int var;                                                                                                                        //  |
    Class7 class7; // <-----------------------------------------------------------------------------------------------------------------+ first !!
    Class6 class6; // <-----------------------------------------------------------------------------------------------------------------+ second  !!
	               //                                                                                                                   +---------> constructor of the  Class8!!!!
};

int main(int argCnt, char **argVal)
{
    Class8 class8(1,2,3);
    
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------
//---------------------------------Inheritance: overriding method (перевизначення методів при наслідуванні)-------------------
//----------------------------------------------------------------------------------------------------------------------------

#include <iostream>

using namespace std;

class Class9 {
public:
    Class9(int inVar = 10)
	{
		var = inVar;
	}
	void printVar()
	{
		cout << "Class 9 var = " << var << "\n";
	}
	
private:
    int var;
};

class Class10 : Class9 {
    Class10(int varBase = 11, int varDerivative = 12)
	: Class9(varDerivative)
	{
		var = varBase;
	}
public:
	void printVar()   // overriding method printVar of the base class
	{
		Class9::printVar(); // But we still can invoke *printVar* method with using operator *::*
		cout << "Class 10 var = " << var << "\n";
	}
private:
    int var;	
};

int main(int argCnt, char **argVal)
{
	Class10 class10(13, 14);
	
	class10.printVar();
	
	return 0;
}