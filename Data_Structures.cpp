/*

This is an on-going project where I am trying to implement various Data Structures in C++ so that I can
sharpen my alorithimic thinking and develop an good understanding of data structures. So far, I have implemented
Singly and Doubly Linked Lists, Stacks and Queues (Although some of those still need improvements).

Author: Andreas Mastronikolis.

*/

#include <iostream>

template <class Entry_Type> struct DL_Node
/* In this struct, we model a single block of the doubly linked list
we wish to instantiate. The block contains a variable about the information
it contains and two pointers to the next and previous blocks */
{
	Entry_Type Data; /* This entry contains the data of the node*/
	DL_Node* Next; /* This struct variable contains a pointer of the next node*/
	DL_Node* Previous; /* This struct variable contains a pointer of the previous node*/
};
template <class Entry_Type> struct SL_Node
/* In this struct, we model a single block of the singly linked list
we wish to instantiate. The block contains a variable about the information
it contains and one pointer to the next block */
{
	Entry_Type Data; /* This entry contains the data of the node*/
	SL_Node* Next; /* This struct variable contains a pointer of the next node*/
};

template <class Entry_Type> class SL_List

/* An instance of this class is representing a single singly linked
list. It contains the private functions and public variables and
functions illustrated below: */

{
private:

	void Insert_At_Start(Entry_Type Value)
		/* This private function inserts a single block in the beginning
		of the list (Pointer Head) with the data Value, indicated above */
	{
		SL_Node<Entry_Type>* New_SL_Node = new SL_Node<Entry_Type>; /* We dynamically allocate the instantiated pointer */
		(*New_SL_Node).Data = Value; /* We store it in the data Value */
		(*New_SL_Node).Next = Head; /* We assign that the next block should be the current head */
		Head = New_SL_Node; /* We make this block the new Head */
	}
	void Delete_Tail()
		/* This private function deletes the last block of the list (Pointer Tail) */
	{
		SL_Node<Entry_Type>* current, previous = NULL;
		current = Head;

		/* Here, we wish to obtain a pointer that points to the block 
		right before the Tail block. */

		while ((*current).Next != NULL) 
		/* The while condition becomes false when current = Tail
		with the previous variable pointing to the block before the 
		Tail pointer. */
		{
			previous = current; /* We assign current to previous*/
			current = (*current).Next; /* Change to the current pointer to its next */
		}
		Tail = previous; /* In the end, we change Tail to previous */
		(*previous).Next = NULL; /* We make previous pointing to NULL, as this is the new Tail. */
		delete current; /* We are deleting the data stored in the memory location of the current. */
	}
	void Delete_Head()
		/* This private function deletets the block Head of the list (Pointer Head) */
	{
		SL_Node<Entry_Type>* Old_Head; /* We instantiate a pointer which will point to the old Head */
		Old_Head = Head; /* We assign the Old_Head the pointer of the current Head */
		Head = (*Head).Next; /* We change the current Head to the block right next to it */
		delete Old_Head; /* We delete the information stored in the old Head */
	}
public:
	SL_Node<Entry_Type>* Head, * Tail; 
	/* We create two pointer variables that point to the first (Head) and Last (Tail) blocks of the list. */
	unsigned long int Size = 0;
	/* We instantiate the variable Size, that will count the Size of the List. */
	
	SL_List()
		/* We call a constructor that assigns
		the values NULL to the Nodes Head and Tail since
		the list, when it is instantiated doesn't have any elements */
	{
		Head = NULL; /* Assignment of NULL to Head */
		Tail = NULL; /* Assignment of NULL to Tail */
		Size = 0;  /* Assignment of 0 to Size (the List has no elements) */
	}
	SL_List(Entry_Type array_list[], int Size)
		/* This constructor attempts to initialize the list
		via a predefined array. The list will contain the elements
		of the array array_list[] (of size Size) in increasing order. */
	{
		Head = NULL; /* Standard assignments of NULL to Head and Tail */
		Tail = NULL;
		for (int i = 0; i < Size; i++) /* For elements in the array */
		{
			(*this).Insert_At_Start(array_list[i]); /* We insert the i-th element of the array */
		}
	}
	void Insert(Entry_Type value, char Ins_Mode = 'T')
	{
		SL_Node<Entry_Type>* New_SL_Node = new SL_Node<Entry_Type>; /* We dynamically allocate the New_SL_Node, which is the node we wish to add */
		(*New_SL_Node).Data = value;

		if (Ins_Mode == 'T')
			/* The Mode T stands for Tail_Insertion. Given this command, the block
			with data Value will be added to as a Tail to the List */
		{
			(*New_SL_Node).Next = NULL; /* We set the next Node of New_SL_Node to be NULL as we want it to be at the Tail */
			if (Head == NULL)
			{
				Head = New_SL_Node;
				Tail = New_SL_Node;
			}
			else
			{
				(*Tail).Next = New_SL_Node;
				Tail = New_SL_Node;
			}
		}
		else if (Ins_Mode == 'H')
		{
			(*this).Insert_At_Start(value); /* We use the private function Insert_At_Start (see above) */
		}
		else
		{
			std::cout << "The command '" << Ins_Mode << "' could not be identified." << '\n';
		}
		Size++;
	}
	void Insert(Entry_Type value, int position)
		/* This public functions aims to insert an element with data value at a
		pre-specified position by the user (indicated by the variable position). */
	{
		SL_Node<Entry_Type>* Iterator;
		SL_Node<Entry_Type>* dummy;
		SL_Node<Entry_Type>* temp;
		Iterator = Head;

		if (position == 0) Insert_At_Start(value);
		else
		{
			for (int i = 0; i < position; i++)
			{
				dummy = Iterator;
				Iterator = (*Iterator).Next;
			}
			(*dummy).Next = temp;
			(*temp).Data = value;
			(*temp).Next = Iterator;
		}
	}
	void Delete(int position)
		/* This public function aims to delete an element at a
		pre-specified position by the user (indicated by the variable position). */
	{
		SL_Node<Entry_Type>* Iterator, previous;
		int size = (*this).Get_Size();
		Iterator = Head;
		if (position < size - 1 && position > 0)
		{
			for (int i = 0; i < position; i++)
			{
				previous = Iterator;
				Iterator = (*Iterator).Next;
			}
			(*previous).Next = (*Iterator).Next;
			delete Iterator;
		}
		else if (position == 0) (*this).Delete_Head();
		else if (position == size - 1) (*this).Delete_Tail();
		else std::cout << "Warning: Index is out of bounds" << std::endl;
		Size--;
	}
	void Print(char Mode = 'F')
		/* This public function aims to print the entire list. The are several modes
		associated with the function. The F Mode stands for Full_Print, and the output
		is a presentation of the list as an ordered set of blocks with data at an allocated
		memory in RAM. The V Mode stands for Values_Only and omitts the memory locations. The
		L mode stands for Locations, and prints only the locations of the nodes in RAM. */
	{
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		if (Head == NULL && Tail == NULL) std::cout << "[Empty List]" << '\n';
		else if (Mode == 'F')
		{
			while (Iterator != NULL)
			{
				if ((*Iterator).Next == NULL)
				{
					std::cout << "[" << (*Iterator).Data << ", NULL]";
					Iterator = (*Iterator).Next;
				}
				else
				{
					std::cout << "[" << (*Iterator).Data << ", " << (*Iterator).Next << "] -- ";
					Iterator = (*Iterator).Next;
				}
			}
		}
		else if (Mode == 'V')
		{
			while (Iterator != NULL)
			{
				if (Iterator == Head && (*Iterator).Next != NULL)
				{
					std::cout << "[" << (*Iterator).Data << ", ";
					Iterator = (*Iterator).Next;
				}
				else if (Iterator == Head && (*Iterator).Next == NULL)
				{
					std::cout << "[" << (*Iterator).Data << "]";
					Iterator = (*Iterator).Next;
				}
				else if ((*Iterator).Next == NULL && Iterator != Head)
				{
					std::cout << (*Iterator).Data << "]";
					Iterator = (*Iterator).Next;
				}
				else
				{
					std::cout << (*Iterator).Data << ", ";
					Iterator = (*Iterator).Next;
				}
			}
		}
		else if (Mode == 'L')
		{
			while (Iterator != NULL)
			{
				if (Iterator == Head && (*Iterator).Next != NULL)
				{
					std::cout << "[" << Iterator << ", ";
					Iterator = (*Iterator).Next;
				}
				else if (Iterator == Head && (*Iterator).Next == NULL)
				{
					std::cout << "[" << Iterator << "]";
					Iterator = (*Iterator).Next;
				}
				else if ((*Iterator).Next == NULL && Iterator != Head)
				{
					std::cout << Iterator << "]";
					Iterator = (*Iterator).Next;
				}
				else
				{
					std::cout << Iterator << ", ";
					Iterator = (*Iterator).Next;
				}
			}
		}
		std::cout << '\n';
	}
	void Reverse()
		/* This public function aims to reverse the order of the entire singly linked
		list. */
	{
		SL_Node<Entry_Type>* Back = NULL;
		SL_Node<Entry_Type>* Middle = NULL;
		SL_Node<Entry_Type>* Front;
		Front = Head;
		SL_Node<Entry_Type>* Tail_Temp = Tail;
		Tail = Head;
		Head = Tail_Temp;
		while (Front != NULL)
		{
			Back = Middle;
			Middle = Front;
			Front = (*Front).Next;
			(*Middle).Next = Back;
		}
	}
	void Swap(int position_1, int position_2)
		/* This public function aims to swap two nodes in the list, found at positions
		position_1 and position_2, respectively. */
	{
		SL_Node<Entry_Type>* SL_Node_1;
		SL_Node<Entry_Type>* SL_Node_2;
		Entry_Type BkpData;
		SL_Node_1 = SL_Node_2 = Head;
		for (int i = 0; i < position_1; i++) SL_Node_1 = (*SL_Node_1).Next;
		for (int i = 0; i < position_2; i++) SL_Node_2 = (*SL_Node_2).Next;
		BkpData = (*SL_Node_2).Data;
		(*SL_Node_2).Data = (*SL_Node_1).Data;
		(*SL_Node_1).Data = BkpData;
	}
	void Remove(Entry_Type value)
		/* This public function aims to remove an element with data value. I implement
		a simple sequential search algorithm to find the node with data value. */
	{
		SL_List<Entry_Type> temp = (*this).Linear_Search(value);
		int size = temp.Get_Size();
		SL_Node<Entry_Type>* Iterator;
		Iterator = temp.Head;
		int counter = 0;
		while (Iterator != NULL)
		{
			(*this).Delete((*Iterator).Data - counter);
			counter++;
			Iterator = (*Iterator).Next;
		}
	}
	SL_List Linear_Search(Entry_Type value)
		/* This public function aims to find the position of an element with data value. It is
		essentially a sequently search algorithm with a time-complexity of O(n); the symbols here have
		their ususal meanings. */
	{
		SL_List<Entry_Type> Index_List;
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		int position = 0;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data == value)
			{
				Index_List.Insert(position);
			}
			Iterator = (*Iterator).Next;
			++position;
		}
		return Index_List;
	}
	int Get_Interval(int lower_limit, int upper_limit)
		/* This public function returns the number of elements that are in the closed interval
		[lower_limit, upper_limit].  */
	{
		int counter = 0;
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data <= upper_limit && (*Iterator).Data >= lower_limit) ++counter;
			Iterator = (*Iterator).Next;
		}
		return counter;
	}
	int Get_Size()
		/* This public function returns the Size of the list. */
	{
		return Size;
	}
	bool is_Empty()
		/* This public function returns whether the list is empty or not. */
	{
		if (Head == NULL && Tail == NULL) return true;
		else return false;
	}
	bool Does_Contain(Entry_Type value)
		/* This public function returns true/false on if the list contains an element with the specified value */
	{
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		int position = 0;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data == value)
				break;
			Iterator = (*Iterator).Next;
			++position;
		}
		if (position < (*this).Get_Size()) return true;
		else return false;
	}
	Entry_Type Get_Max()
		/* This public function returns the maximum value of the list. */
	{
		int Maximum_Int;
		Maximum_Int = INT32_MIN;
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data > Maximum_Int) Maximum_Int = (*Iterator).Data;
			Iterator = (*Iterator).Next;
		}
		return Maximum_Int;
	}
	Entry_Type Get_Min()
		/* This public function minimum value of the list */
	{
		int Maximum_Int;
		Maximum_Int = INT32_MAX;
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data < Maximum_Int) Maximum_Int = (*Iterator).Data;
			Iterator = (*Iterator).Next;
		}
		return Maximum_Int;
	}
	bool is_Sorted()
		/* This public function returns true/false on if the list is sorted or not. */
	{
		int x = INT32_MIN;
		SL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data < x)
				return false;
			x = (*Iterator).Data;
			Iterator = (*Iterator).Next;
		}
		return true;
	}
};
template <class Entry_Type> class DL_List
{
private:
	DL_Node<Entry_Type>* Get_Pointer(int Index)
	{
		DL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		if (Index < Size && Index >= 0)
		{
			for (int i = 0; i < Index; i++)
			{
				Iterator = (*Iterator).Next;
			}
		}
		else
		{
			std::cout << "Warning: Index is out of bounds" << std::endl;
		}
		return Iterator;
	}
	int Node_to_Index(DL_Node<Entry_Type>* Node)
	{
		if (Node == Head) return 0;
		else if (Node == Tail) return (Size - 1);
		else
		{
			int counter = 0;
			DL_Node<Entry_Type>* Iterator = Head;
			while (Iterator != Node) counter++;
			return counter;
		}
	}
	DL_Node<Entry_Type>* Index_to_Node(int Index)
	{
		if (Index == 0) return Head;
		else if (Index == Size - 1) return Tail;
		else if (Index < Size - 1 && Index > 0)
		{
			DL_Node<Entry_Type>* Iterator;
			Iterator = Head;
			for (int i = 0; i < Index; i++) Iterator = (*Iterator).Next;
			return Iterator;
		}
	}
public:
	unsigned long int Size = 0;
	DL_Node<Entry_Type>* Head, * Tail;
	DL_List() { Head = NULL; Tail = NULL; }
	DL_List(Entry_Type Value)
	{
		Head = NULL; Tail = NULL;
		(*this).Insert(Value);
	}
	Entry_Type Get_Value(int position)
	{
		DL_Node<Entry_Type>* Iterator = Get_Pointer(position);
		return (*Iterator).Data;
	}
	void Insert(Entry_Type Value, char Ins_Mode = 'T')
	{
		DL_Node<Entry_Type>* New_Node = new DL_Node<Entry_Type>;
		(*New_Node).Data = Value;
		if (Ins_Mode == 'T')
		{
			if (Head == NULL && Tail == NULL)
			{
				(*New_Node).Next = NULL;
				(*New_Node).Previous = NULL;
				Head = New_Node;
				Tail = New_Node;
			}
			else
			{
				(*Tail).Next = New_Node;
				(*New_Node).Previous = Tail;
				(*New_Node).Next = NULL;
				Tail = New_Node;
			}
		}
		else if (Ins_Mode == 'H')
		{
			if (Head == NULL)
			{
				(*New_Node).Next = NULL;
				(*New_Node).Previous = NULL;
				Head = New_Node;
				Tail = New_Node;
			}
			else
			{
				DL_Node<Entry_Type>* Tail_Node = Head;
				(*Tail_Node).Previous = New_Node;
				(*New_Node).Next = Head;
				(*New_Node).Previous = NULL;
				Head = New_Node;
			}
		}
		Size++;
	}
	void Insert(Entry_Type Value, int Index)
	{
		if (Index == Size - 1)
		{
			(*this).Insert(Value, 'T');
		}
		else if (Index == 0)
		{
			(*this).Insert(Value, 'H');
		}
		else if (Index > 0 && Index < Size - 1)
		{
			DL_Node<Entry_Type>* Position = (*this).Get_Pointer(Index);
			DL_Node<Entry_Type>* Previous = (*this).Get_Pointer(Index - 1);
			DL_Node<Entry_Type>* New_Node;
			(*New_Node).Data = Value;
			(*Position).Previous = New_Node;
			(*New_Node).Next = Position;
			(*Previous).Next = New_Node;
		}
		else
		{
			std::cout << "Warning! Index is out of bounds." << std::endl;
		}
	}
	void Delete(Entry_Type Index, char Del_Mode = 'E')
	{
		DL_Node<Entry_Type>* Iterator;
		DL_Node<Entry_Type>* Previous = new DL_Node<Entry_Type>;
		Iterator = Head;
		if (Del_Mode == 'E')
		{
			if (Index < Size && Index > 0)
			{
				for (int i = 0; i < Index; i++)
				{
					Previous = Iterator;
					Iterator = (*Iterator).Next;
				}
				(*Previous).Next = (*Iterator).Next;
				delete Iterator;
			}
			else if (Index == 0 && Size == 1)
			{
				delete Iterator;
				Head, Tail = NULL;
			}
			else if (Index == 0 && Size != 1)
			{
				Head = (*Iterator).Next;
				(*Head).Previous = NULL;
				delete Iterator;
			}
			else if (Index == Size - 1 && Size != 1)
			{
				for (int i = 0; i < Size; i++)
				{
					Previous = Iterator;
					Iterator = (*Iterator).Next;
				}
				(*Previous).Next = NULL;
				Tail = Previous;
				delete Iterator;
			}
			else std::cout << "Warning: Index is out of bounds" << std::endl;
		}
		else if (Del_Mode == 'A')
		{
			if (Index < Size && Index >= 0)
			{
				for (int i = 0; i < Index; i++)
				{
					Iterator = (*Iterator).Next;
				}
				DL_Node<Entry_Type>* Next_Pointer = (*Iterator).Next;
				Tail = Iterator;
				(*Tail).Next = NULL;
				delete Next_Pointer;
			}
		}
		else if (Del_Mode == 'B')
		{
			if (Index < Size && Index >= 0)
			{
				for (int i = 0; i < Index; i++)
				{
					Iterator = (*Iterator).Next;
				}
				Head = Iterator;
				(*Head).Previous = NULL;
			}
		}
		else if (Del_Mode != 'B' || Del_Mode != 'A' || Del_Mode != 'E')
		{
			std::cout << "Error in DL_List.Delete(). The parameter " << Del_Mode << " cannot be interpeted as a command." << std::endl;
		}
	}
	void Print(char Mode = 'F')
	{
		DL_Node<Entry_Type>* Iterator = Head;
		if (Head == NULL && Tail == NULL) std::cout << "[Empty List]";
		else if (Mode == 'F')
		{
			while (Iterator != NULL)
			{
				if ((*Iterator).Next == NULL && (*Iterator).Previous == NULL)
				{
					std::cout << "[" << "NULL" << ", " << (*Iterator).Data << ", NULL]";
				}
				else if ((*Iterator).Previous == NULL && (*Iterator).Next != NULL)
				{
					std::cout << "[" << "NULL" << ", " << (*Iterator).Data << ", " << (*Iterator).Next << "] -- ";
				}
				else if ((*Iterator).Next != NULL && (*Iterator).Previous != NULL)
				{
					std::cout << "[" << (*Iterator).Previous << ", " << (*Iterator).Data << ", " << (*Iterator).Next << "]" << " -- ";
				}
				else if ((*Iterator).Next == NULL && (*Iterator).Previous != NULL)
				{
					std::cout << "[" << (*Iterator).Previous << ", " << (*Iterator).Data << "," << " NULL]";
				}
				Iterator = (*Iterator).Next;
			}
			std::cout << '\n';
		}
		else if (Mode == 'V')
		{
			while (Iterator != NULL)
			{
				if ((*Iterator).Next == NULL && (*Iterator).Previous == NULL)
				{
					std::cout << "[" << (*Iterator).Data << "]";
				}
				else if ((*Iterator).Previous == NULL && (*Iterator).Next != NULL)
				{
					std::cout << "[" << (*Iterator).Data << ",";
				}
				else if ((*Iterator).Previous != NULL && (*Iterator).Next == NULL)
				{
					std::cout << (*Iterator).Data << "]";
				}
				else if ((*Iterator).Previous != NULL && (*Iterator).Next != NULL)
				{
					std::cout << (*Iterator).Data << ",";
				}
				Iterator = (*Iterator).Next;
			}
			std::cout << '\n';
		}
		else if (Mode == 'L')
		{
			while (Iterator != NULL)
			{
				if ((*Iterator).Next == NULL && (*Iterator).Previous == NULL)
				{
					std::cout << "[" << Iterator << "]";
				}
				else if ((*Iterator).Previous == NULL && (*Iterator).Next != NULL)
				{
					std::cout << "[" << Iterator << ",";
				}
				else if ((*Iterator).Previous != NULL && (*Iterator).Next == NULL)
				{
					std::cout << Iterator << "]";
				}
				else if ((*Iterator).Previous != NULL && (*Iterator).Next != NULL)
				{
					std::cout << Iterator << ",";
				}
				Iterator = (*Iterator).Next;
			}
		}
		else
		{
			std::cout << "The command '" << Mode << "' was not understood";
		}
		std::cout << '\n';
	}
	bool is_Sorted()
	{
		int x = INT32_MIN;
		DL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		while (Iterator != NULL)
		{
			if ((*Iterator).Data < x)
				return false;
			x = (*Iterator).Data;
			Iterator = (*Iterator).Next;
		}
		return true;
	}
	bool is_Empty()
	{
		if (Head == NULL && Tail == NULL) return true;
		else return false;
	}
	bool Does_Contain(Entry_Type value)
	{
		DL_Node<Entry_Type>* Iterator;
		Iterator = Head;
		int position = 0;
		while ((*Iterator).Data != value) Iterator = (*Iterator).Next; ++position;
		if (position < Size) return true;
		else return false;
	}
	void Reverse()
	{
		DL_Node<Entry_Type>* Back = NULL;
		DL_Node<Entry_Type>* Middle = NULL;
		DL_Node<Entry_Type>* Front;
		Front = Head;
		DL_Node<Entry_Type>* Tail_Temp = Tail;
		Tail = Head;
		Head = Tail_Temp;
		while (Front != NULL)
		{
			Back = Middle;
			Middle = Front;
			Front = (*Front).Next;
			(*Middle).Next = Back;
		}
	}
	void Swap(int position_1, int position_2)
	{
		DL_Node<Entry_Type>* SL_Node_1;
		DL_Node<Entry_Type>* SL_Node_2;
		DL_Node<Entry_Type>* Saver;
		SL_Node_1 = SL_Node_2 = Head;
		for (int i = 0; i < position_1; i++) SL_Node_1 = (*SL_Node_1).Next;
		for (int i = 0; i < position_2; i++) SL_Node_2 = (*SL_Node_2).Next;
		(*Saver).Data = (*SL_Node_2).Data;
		(*SL_Node_2).Data = (*SL_Node_1).Data;
		(*SL_Node_1).Data = (*Saver).Data;
		delete Saver;
	}
	void Clear()
	{
		for (int i = 0; i < Size; i++)
		{
			(*this).Delete(0);
		}
	}
	// Various Algorithms
	void BubbleSort()
	{
		for (int i = 0; i < Size - 1; i++)
		{
			for (int j = 0; j < Size - 1 - i; j++)
			{
				if ((*this).Get_Value(j) > (*this).Get_Value(j + 1)) (*this).Swap(j, j + 1);
			}
		}
	}
	void InsertionSort()
	{
		for (int i = 1; i < Size; i++)
		{
			int j = i;
			while (j > 0 && (*this).Get_Value(j - 1) > (*this).Get_Value(j))
			{
				(*this).Swap(j, j - 1);
				j = j - 1;
			}

		}
	}
	void SelectionSort()
	{
		int j, k;
		j = k = 0;
		for (int i = 0; i < Size; i++)
		{
			for (j = k = i; j < Size; j++)
			{
				if ((*this).Get_Value(j) < (*this).Get_Value(k)) k = j;
			}
			(*this).Swap(i, k);
		}
	}
};
template <class Entry_Type> class Stack
/* This class is an implementation of a Stack via Linked Lists. */
{
	DL_List<Entry_Type> List;
public:
	void Push(Entry_Type Value)
	{
		List.Insert(Value, 'H');
	}
	void Pop()
	{
		List.Delete(0, 'E');
	}
	void Print()
	{
		List.Print('V');
	}
	void Clear()
	{

	}
	bool Is_Empty()
	{
		return List.is_Empty();
	}
	void Get_Value(int Index)
	{
		List.Get_Value(Index);
	}
};
template <class Entry_Type> class Queue
/* This public function is an implementation of a Queque via Linked Lists. */
{
private:
	DL_List<Entry_Type> List;
public:
	void Enqueue(Entry_Type Value)
	{
		List.Insert(Value, 'H');
	}
	void Dequeue()
	{
		std::cout << List.Size << std::endl;
		List.Delete(List.Size - 1, 'E');
	}
	void Print()
	{
		List.Print('V');
	}
};

template <class Entry_Type> SL_List<Entry_Type> Copy(SL_List<Entry_Type> List)
{
	SL_List<Entry_Type> Output;
	SL_Node<Entry_Type>* New_Head, New_Tail, Old_Iterator;
	New_Head = NULL;
	New_Tail = NULL;
	Output.Head = New_Head;
	Output.Tail = New_Tail;
	Old_Iterator = List.Head;

	while (Old_Iterator != NULL)
	{
		Output.Insert((*Old_Iterator).Data);
		Old_Iterator = (*Old_Iterator).Next;
	}
	return Output;
}
template <class Entry_Type> SL_List<Entry_Type> Concatenate(SL_List<Entry_Type> List_1, SL_List<Entry_Type> List_2)
{
	SL_List<Entry_Type> Concatenated_List;
	(*(List_1.Tail)).Next = List_2.Head;
	Concatenated_List.Head = List_1.Head;
	Concatenated_List.Tail = List_2.Tail;
	SL_Node<Entry_Type>* Random_Position = new SL_Node<Entry_Type>;
	List_2.Head = Random_Position;
	delete(List_2.Head);
	return Concatenated_List;
}
template <class Entry_Type> SL_List<Entry_Type> Concatenate(SL_List<Entry_Type> List_1, SL_List<Entry_Type> List_2, int position, char Command)
{
	SL_List<Entry_Type> Result;
	int Command_Int = 0;
	if (Command == 'A') Command_Int = 0;
	if (Command == 'B') Command_Int = 1;

	if (position < 0 || position > List_1.Get_Size())
	{
		std::cout << "Warning: The position parameter on Concatenate is out of bounds. The Concatenate instruction was scrapped." << std::endl;
		return Result;
	}
	else
	{
		Result.Head = List_1.Head;
		Result.Tail = List_1.Tail;
		SL_Node<Entry_Type>* Iterator;
		Iterator = List_1.Head;
		switch (Command_Int)
		{
		case 0:
			if (position == List_1.Get_Size() - 1) return Concatenate(List_1, List_2);
			else
			{
				for (int i = 0; i < position; ++i) Iterator = (*Iterator).Next;
				(*(List_2.Tail)).Next = (*Iterator).Next;
				(*Iterator).Next = List_2.Head;
				return Result;
			}
		case 1:
			if (position == 0) return Concatenate(List_2, List_1);
			else
			{
				for (int i = 0; i < position - 1; ++i) Iterator = (*Iterator).Next;
				(*(List_2.Tail)).Next = (*Iterator).Next;
				(*Iterator).Next = List_2.Head;
				return Result;
			}
		}
	}
}
template <class Entry_Type> SL_List<Entry_Type> New_Concatenate(SL_List<Entry_Type> List_1, SL_List<Entry_Type> List_2)
{
	SL_List<Entry_Type> New_Concatenate = Copy(Concatenate(List_1, List_2));
	return New_Concatenate;
}
template <class Entry_Type> SL_List<Entry_Type> New_Concatenate(SL_List<Entry_Type> List_1, SL_List<Entry_Type> List_2, int position, char Command)
{
	SL_List New_Concatenate = Copy(Concatenate(List_1, List_2, position, Command));
	return New_Concatenate;
}
template <class Entry_Type> SL_List<Entry_Type> Convert(int array_list[], int size)
{
	SL_List<Entry_Type> Output;
	for (int i = 0; i < size; ++i) Output.Insert(array_list[i]);
	return Output;
}
template <class Entry_Type> bool Are_Equal(SL_List<Entry_Type> List_1, SL_List<Entry_Type> List_2)
{
	SL_Node<Entry_Type>* Iterator_1;
	SL_Node<Entry_Type>* Iterator_2;
	Iterator_1 = List_1.Head;
	Iterator_2 = List_2.Head;
	if (List_1.Get_Size() != List_2.Get_Size()) return false;
	else
	{
		while (Iterator_1 != NULL && Iterator_2 != NULL)
		{
			if ((*Iterator_1).Data != (*Iterator_2).Data) return false;
			else
			{
				Iterator_1 = (*Iterator_1).Next;
				Iterator_2 = (*Iterator_2).Next;
			}
		}
	}
	return true;
}

template<class Entry_Type> int Linear_Search(DL_List<Entry_Type> List, Entry_Type Element)
{
	DL_Node<Entry_Type>* Iterator;
	Iterator = List.Head;
	unsigned long int Index = 0;
	while (Iterator != (*(List.Tail)).Next && (*Iterator).Data != Element)
	{
		Iterator = (*Iterator).Next;
		Index += 1;
	}
	if (Index == List.Size)
	{
		return -1;
	}
	else
	{
		return Index;
	}
}
template<class Entry_Type> DL_List<int> A_Linear_Search(DL_List<Entry_Type> List, Entry_Type Element)
{
	DL_Node<Entry_Type>* Iterator;
	DL_List<Entry_Type> Output;
	Iterator = List.Head;
	int Index = 0;
	while (Iterator != NULL)
	{
		if ((*Iterator).Data == Element)
		{
			Output.Insert(Index);
			Iterator = (*Iterator).Next;
			Index++;
		}
		else
		{
			Iterator = (*Iterator).Next;
			Index += 1;
		}
	}
	return Output;
}
template<class Entry_Type> DL_List<Entry_Type> Copy(DL_List<Entry_Type> List)
{
	DL_List<Entry_Type> Output;
	DL_Node<Entry_Type>* New_Head, New_Tail, Old_Iterator;
	New_Head = NULL;
	New_Tail = NULL;
	Output.Head = New_Head;
	Output.Tail = New_Tail;
	Old_Iterator = List.Head;
	while (Old_Iterator != NULL)
	{
		Output.Insert((*Old_Iterator).Data);
		Old_Iterator = (*Old_Iterator).Next;
	}
	return Output;
}
