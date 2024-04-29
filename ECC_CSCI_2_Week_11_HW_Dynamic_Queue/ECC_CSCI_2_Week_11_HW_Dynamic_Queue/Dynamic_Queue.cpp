/*
 Program Name: Dynamic_Queue.cpp
 Programmer: Moris Gomez
 Date: Tuesday 04/25/2024
 Version Control: 13.0
 About: Week 11, CSCI 2, HW.
 Description:
 
 Modify the program you wrote for (last week) 
 which is as follows so it uses a queue instead of stack.
 Use the Dynamic Queue class with member functions.

 Last week’s homework:
 “Design an inventory class that stores the following
 members:
 
 - serialNumber: Integer that holds a part’s serial number.
 - manufactDate: Member holding date the part was manufactured.
 - LotNum: Integer that holds the part’s lot number.

 The class should have appropriate member functions for
 storing data into, and retrieving data from, these members.

 Next, design a stack class that can hold objects of the
 class described above. If you wish, you may use the
 template you designed in Lab programming lab#2.

 Last, design a program that uses the stack class described
 above. The program should have a loop that asks the user if
 he or she wishes to add a part to inventory, or take a part
 from inventory. The loop should repeat until the user is
 finished.

 If the user wishes to add a part to inventory, the program
 should ask for the serial number, date of manufacture, and
 lot number. The data should be stored in an inventory
 object, and pushed onto the stack.

 If the user wishes to take a part from inventory, the
 program should pop the top most part from the stack and
 display the contents of its member variables.

 When the user finishes the program, it should display the
 contents of the member values of all the objects that
 remain on the stack."
*/

#include <iostream>
#include <string>

using namespace std;

//reminder: Although this data structure does have a linked list, it is still a queue, so we should only be adding via rear and removing via front.
class DynamicQueue
{
private:
    struct Node //a Node data type can be created via a class too.
    //if using struct, it has to be inside private of of outer class.
    //if using class, it can be outside outer class(separate).
    {
        int lotNumber = 0; //1 place value for simplicity.
        int serialNumber = 000; //1 place value for simplicity.
        string manufactDate = "00/00/0000"; //string for simplicity.
        Node *next = NULL; //not a new Node. pointer to a potential Node.
        //how do we make a constructor for a Node in this case???????
    }; //end struct Node
    
    Node *rear; //pointer to potential last Node.
    Node *front; //pointer to potential first Node.
    int numItems; //tracks # of parts in dynamic queue.
    
public:
//constructor:
    DynamicQueue()
    {
        front = NULL;
        rear = NULL;
        numItems = 0;
    }
//destructor:
    ~DynamicQueue()
    {
        clear();
    }
//function 1: enqueue()
    void enqueue(int lot, int seria, string date)
    //enqueue adds another Node to rear.
    {
        Node *n = new Node; //new Node = n.
        n->lotNumber = lot; //initialization of new Node.
        n->serialNumber = seria; //initialization of new Node.
        n->manufactDate = date; //initialization of new Node.
        if(isEmpty()) //special case: queue is empty.
        {
            front = n; //front points to new Node.
            rear = n; //rear also points to new Node.
        }
        else //not empty, existing Nodes in queue.
        {
            rear->next = n; 
            //make last Node's next point to new Node.
            //connects last Node to n Node.
            rear = n; //makes rear point to last Node which is n.
        }
        numItems++; //always increase after enqueueing.
    } //end enqueue() function.
    
//function 2: dequeue()
    void dequeue(int &l, int &s, string d)
    //have to pass in variables to put details of Node we are dequeing and return it.
    //passing by reference bc any changes in here show in main function.
    {
        Node *temp; //holds the address of Node we want to dequeue (delete).
        if(isEmpty()) //if queue is empty..cant remove anything.
        {
            cout << "Queue is empty!" << endl;
        }
        else //else not empty.
        {
            if(numItems == 1) //special case: 1 element in queue.
            {
                l = front->lotNumber; //give l the Node's lotNumber.
                s = front->serialNumber; //give s the Node's serialNumber.
                d = front->manufactDate; //give d the Node's manufactDate.
                delete front; //delete the Node front is pointing to.
                rear = NULL; //rear points to nothing.
                //what about front? did that pointer get deleted with the Node it was pointing to.??????????????
                numItems--; //updated tracker.
            }
            else //else more than 1 element in queue.
            {
                l = front->lotNumber; //give l the Node's lotNumber.
                s = front->serialNumber; //give s the Node's serialNumber.
                d = front->manufactDate; //give d the Node's manufactDate.
                temp = front; //temp points to whatever front is pointing to.
                //need temp bc we will need to reassign front.
                front = front->next; //front points to second Node.
                delete temp; //delete 1st Node.
                //Node gets deleted, but temp can still point to address.
                //in fact, it is still pointing to the address but that address is not assigned. its like floating?
                //can make temp point to another node if needed.
                //can even assign temp to NULL for better coding.
                numItems--; //update tracker.
            } //close inner else.
        } //close outer else.
    } //end dequeue() function.
//function 3: display()
    void display()
    {
        int tracker = 1;
        Node *current = front; //current holds the address program is on. assigned front which points to the 1st Node.
        if(isEmpty())
        {
            cout << "Queue is empty!" << endl;
        }
        else
        {
            while(current != NULL) //if so, we are at end of queue.
            {
                cout << "Node #: " << tracker << endl;
                cout << "Node Address: " << current << endl;
                cout << "Serial #: " << current->serialNumber << endl;
                cout << "Manufactured Date: " << current->manufactDate << endl;
                cout << "Lot #: " << current->lotNumber<< endl;
                cout << "Next Address: " << current->next << endl << endl;
                tracker++;
                current = current->next; //go to next Node.
            } //close while loop.
        } //close else.
    } //end display() function.
//function 4: isEmpty()
    bool isEmpty() //straight forward.
    {
        if(numItems > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    } //end isEmpty() function.
    
//function 5: clear()
    void clear()
    {
        int l;
        int s;
        string d;
        while(!isEmpty())
        {
            dequeue(l, s, d); //calling dequeue within clear until queue is empty.
        } //close while loop.
    } //end clear() function.
    
//function 6: front()
    void viewFront()
    {
        if(isEmpty()) //if queue is empty..cant view anything.
        {
            cout << "Queue is empty!" << endl;
        }
        else
        {
            cout << "Node Address: " << front << endl;
            cout << "Lot #: " << front->lotNumber<< endl;
            cout << "Serial #: " << front->serialNumber << endl;
            cout << "Manufactured Date: " << front->manufactDate << endl;
            
            cout << "Next Address: " << front->next << endl << endl;
        }
    } //end viewFront() function.
    
//function 6: rear()
    void viewRear()
    {
        if(isEmpty()) //if queue is empty..cant view anything.
        {
            cout << "Queue is empty!" << endl;
        }
        else
        {
            cout << "Node Address: " << rear << endl;
            cout << "Lot #: " << rear->lotNumber<< endl;
            cout << "Serial #: " << rear->serialNumber << endl;
            cout << "Manufactured Date: " << rear->manufactDate << endl;
            cout << "Next Address: " << rear->next << endl << endl;
        }
    } //end viewRear() function.
    
    
}; //end class Dynamic Queue.


int main()
{
/*
    //1. create an object of DynamicQueue class:
    DynamicQueue qOne; //creates empty dynamic queue.
    
    //2. enqueue some Nodes to qOne:
    qOne.enqueue(1, 679, "07/25/2000");
    qOne.enqueue(6, 780, "05/05/2006");
    qOne.enqueue(4, 193, "01/10/2022");
    qOne.enqueue(3, 774, "12/21/2023");

    //3. display Nodes in qOne:
    qOne.display();

     Node #: 1
     Node Address: 0x600000b88000
     Serial #: 679
     Manufactured Date: 07/25/2000
     Lot #: 1
     Next Address: 0x600000b88030

     Node #: 2
     Node Address: 0x600000b88030
     Serial #: 780
     Manufactured Date: 05/05/2006
     Lot #: 6
     Next Address: 0x600000b88060

     Node #: 3
     Node Address: 0x600000b88060
     Serial #: 193
     Manufactured Date: 01/10/2022
     Lot #: 4
     Next Address: 0x600000b88090

     Node #: 4
     Node Address: 0x600000b88090
     Serial #: 774
     Manufactured Date: 12/21/2023
     Lot #: 3
     Next Address: 0x0
     
    
    //4. use dequeue function:
    int x; //stores lot# of dequeued Node.
    int y; //stores serial# of dequeued Node.
    string z; //stores manuDate of dequeued Node.
    
    qOne.dequeue(x, y, z);
    //any changes to variables in dequeue function shown here in
    //main function bc passed as reference.
    
    //5. display Nodes in qOne to make sure the first one was dequeued:
    qOne.display();
    
     Node #: 1
     Node Address: 0x6000016843c0
     Serial #: 780
     Manufactured Date: 05/05/2006
     Lot #: 6
     Next Address: 0x6000016843f0

     Node #: 2
     Node Address: 0x6000016843f0
     Serial #: 193
     Manufactured Date: 01/10/2022
     Lot #: 4
     Next Address: 0x600001684420

     Node #: 3
     Node Address: 0x600001684420
     Serial #: 774
     Manufactured Date: 12/21/2023
     Lot #: 3
     Next Address: 0x0
     
    //6. use clear function:
    qOne.clear(); //passed.
    
    //7. call display function to make sure Dynamic Queue is empty:
    cout << "================" << endl;
    qOne.display(); //passed.
*/

    //create same program with user inputs:
    DynamicQueue qTwo;
 
    //1. get user option input:
    int x = 0; //holds option of user.
    int a; //lot num.
    int b; //serial num.
    string c; //manu date.
    while (x != 8) //bc 5 means quit.
    {
        //display menu:
        cout << "1. Enqueue a machine." << endl;
        cout << "2. Dequeue a machine." << endl;
        cout << "3. Display all machines." << endl;
        cout << "4. View front of the queue." << endl;
        cout << "5. View rear of the queue." << endl;
        cout << "6. Check if queue is empty." << endl;
        cout << "7. Clear all machines." << endl;
        cout << "8. Quit." << endl;
        cout << "=======================" << endl;
        cout << "=======================" << endl;
        
        //prompt & store user option in x as built-in int type:
        cout << "Enter option: ";
        cin >> x;
        
        //2. logic paths for user options:
        if(x == 1) //to enqueue
        {
            //stores car part input in y:
            cout << "Enter Lot Number (1 digit): ";
            cin >> a;
            
            cout << "Enter Lot # (3 digits): ";
            cin >> b;
            
            cout << "Enter Manufactured Date (00/00/0000): ";
            cin >> c;
    
            //adds part to queue:
            qTwo.enqueue(a, b, c);
        }
        else if(x == 2) //to dequeue:
        {
            qTwo.dequeue(a, b, c);
        }
        else if(x == 3) //to display:
        {
            qTwo.display();
        }
        else if(x == 4) //view front:
        {
            qTwo.viewFront();
        }
        else if(x == 5) //view rear:
        {
            qTwo.viewRear();
        }
        else if(x == 6) //check if empty:
        {
            bool tF= qTwo.isEmpty();
            if (tF)
            {
                cout << "yes, queue is empty." << endl;
            }
            else
            {
                cout << "no, queue is not empty" << endl;
            }
        }
        else if(x == 7) //to clear:
        {
            qTwo.clear();
        }
        else if(x == 8) //to quit:
        {
            break;
        }
        else
        {
            cout << "ERROR: Invalid Option Selected. Try Again." << endl;
        }
    } //end while loop:
    cout << "PROGRAM HAS QUIT. RUN IT AGAIN FOR A NEW QUEUE." << endl;
} //end main function driver.
