/***********************************************************************
* File:
*    stack.h
* Authors:
*    John Wood and Etienne Beaulac (Group 3)
* Description:
*    Our implementation of the stack class
************************************************************************/

#ifndef STACK_H
#define STACK_H
// #define DEBUG
#include <assert.h>
// #include <cstddef>
#include <iostream>


namespace custom
{

	template <class T>
	class stack
	{
	private:
		T *array;
		int numElements;
		int numCapacity;
		void resize(int numCapacity) 					       throw (const char *);

	public:
		stack() : numElements(0), numCapacity(0), array(NULL)    {            }
		stack(int numCapacity)							        throw (const char *);
		stack(const stack <T> & rhs)					        throw (const char *);
		~stack();

		stack & operator = (const stack & rhs)			     throw (const char *);

		int size()					const			        { return numElements;     }
		int capacity()				const			        { return numCapacity;     }
		inline bool empty()	   const			        { return numElements < 1; }
		void clear()								        { this->numElements = 0;  }
		void push(const T & t)					              throw (const char *);
		void pop()										           throw (const char *);
		T top()						const				           throw (const char *);
	};

	/*******************************************
	* STACK :: Assignment
	*******************************************/
	template <class T>
	stack <T> & stack <T> :: operator = (const stack <T> & rhs)
		throw (const char *)
	{
		try
		{
			if (array == rhs.array)
				return *this;
			if (numCapacity != rhs.numCapacity)
			{
				array = NULL;
				numCapacity = rhs.capacity();
				numElements = rhs.size();
				resize(rhs.size());
			}

			assert(numElements <= numCapacity);
			for (int i = 0; i < rhs.size(); i++)
				array[i] = rhs.array[i];
			return *this;
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}
	}

	/*******************************************
	* STACK :: NON-DEFAULT CONSTRUCTOR
	*******************************************/
	template <class T>
	stack <T> ::stack(int numCapacity)             throw (const char *)
	{
		// If capacity asked for is 0, get out, we don't need.
		if (numCapacity == 0)
			return;

		this->array = NULL;
		this->numCapacity = 0;
		this->numElements = 0;

		// attempt to allocate
		try
		{
			resize(numCapacity);
			this->numCapacity = numCapacity;
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}
	}

	/*******************************************
	* STACK :: COPY CONSTRUCTOR
	*******************************************/
	template <class T>
	stack <T> ::stack(const stack <T> & rhs)		throw (const char *)
	{
		*this = rhs;
	}

	/*******************************************
	* STACK :: DESTRUCTOR
	*******************************************/
	template <class T>
	stack <T> :: ~stack()
	{
		if (numElements > 0)
			delete[] array;
	}

	/*******************************************
	* STACK :: PUSH
	*******************************************/
	template <class T>
	inline void stack <T> ::push(const T & t)		throw (const char *)
	{
		try
		{
			if (numCapacity == 0)
			{
				assert(array == NULL);
				this->numCapacity = 1;
				resize(1);
			}
			// double the capacity if there is no more room in the vector
			else if (size() >= capacity())
			{
				this->numCapacity *= 2;
				resize(this->numCapacity);
			}

			// add the element to the last position in the array
			assert(numElements <= numCapacity);
			this->array[numElements] = t;
			this->numElements++;
			assert(numElements <= numCapacity);
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}
	}

	/*******************************************
	* STACK :: POP
	*******************************************/
	template <class T>
	void stack<T> ::pop()							throw (const char *)
	{
		if (numElements > 0)
			numElements--;
	}

	/*******************************************
	* STACK :: RESIZE
	*******************************************/
	template <class T>
	void stack<T> ::resize(int numCapacity = 0)			throw (const char *)
	{
		try
		{
         if (numCapacity < 0)
            numCapacity = 0;
			assert(numCapacity >= 0);
			if (numCapacity == 0)
				return;

			if (array != NULL)
			{
				assert(numElements > 0);
				T * temp = new T[numCapacity];
				for (int i = 0; i < numElements; i++)
					temp[i] = array[i];
				delete[] array;
				array = temp;
			}
			else
				array = new T[numCapacity];

			this->numCapacity = numCapacity;
			assert(numElements <= numCapacity);
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}
	}

	/*******************************************
	* STACK :: TOP
	*******************************************/
	template <class T>
	T stack<T> ::top()	const						throw (const char *)
	{
		try
		{
         if (!empty())
			   return array[numElements - 1];
		}
		catch (...)
		{
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
	}

}; // namespace custom
#endif
