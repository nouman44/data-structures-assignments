#include <iostream>
using namespace std;

//class declaration
class Building
{

private:
	int *area; //1-D array to store areas
	int f, a, r; //required variables

public:
	//constructor function that initialzies the 1-D array and the variables
	//the area of a room can be from 1 to 9
	Building(int floors,int apartments,int rooms)
	{
		f = floors;
		a = apartments;
		r = rooms;

		area = new int[f*a*r];

		int i, j, k, index, value = 1;
		for (i = 0; i < f; i++) //triple loop to access all the dimensions of the building
		{
			for (j = 0; j < a; j++)
			{
				for (k = 0; k < r; k++)
				{
					index = (k*f*a) + (j*f) + i; //formula to calculate index in which floor is fastest changing

					if (value == 10) //increment values for area that doesnot exceed 9
						value = 1;

					area[index] = value;
					value++;
				}
			}
		}
	}

	//this function adds a new floor to the building by increasing the dimension f
	void AddFloor(int** newFloor)
	{
		int i, j, k, index, oldIndex, dimension = f*a*r;
		int *tempArray = new int[dimension]; //temp array to store the existing areas

		for (i = 0; i < dimension; i++)
		{
			tempArray[i] = area[i];
		}

		delete[] area;
		
		area = new int[(f + 1)*a*r]; //reallocation of the array by increased floor

		for (i = 0; i < f+1; i++) //triple loop to access all the dimensions of the building
		{
			for (j = 0; j < a; j++)
			{
				for (k = 0; k < r; k++)
				{
					index = (k*(f+1)*a) + (j*(f+1)) + i; //calculation of new index in which floor is fastest changing

					if (i == f) //condition to fill the new top floor
					{
						area[index] = newFloor[j][k];
					}
					else
					{
						oldIndex = (k*f*a) + (j*f) + i; //formula to calculate old index in which floor is fastest changing
						area[index] = tempArray[oldIndex];
					}
				}
			}
		}

		delete[] tempArray;
		f++; //increase floor by 1
	}


	//this function removes the top floor of the building by decreasing dimension f
	void RemoveTopFLoor()
	{
		int i, j, k, index, oldIndex, dimension = f*a*r;
		int *tempArray = new int[dimension]; //temp array to store the existing areas

		for (i = 0; i < dimension; i++)
		{
			tempArray[i] = area[i];
		}

		delete[] area;

		area = new int[(f - 1)*a*r]; //reallocation of the array by decreased floor

		for (i = 0; i < f - 1; i++) //triple loop to access all the dimensions of the building
		{
			for (j = 0; j < a; j++)
			{
				for (k = 0; k < r; k++)
				{
					index = (k*(f - 1)*a) + (j*(f - 1)) + i;  //calculation of new index in which floor is fastest changing
					oldIndex = (k*f*a) + (j*f) + i; //formula to calculate old index in which floor is fastest changing

					area[index] = tempArray[oldIndex];
				}
			}
		}

		delete[] tempArray;
		f--; //decrement floor by 1
	}

	//this function expand each floor by increasing the dimension a
	void ExpandEachFloor(int** newApartments)
	{
		int i, j, k, index, oldIndex, dimension = f*a*r;
		int *tempArray = new int[dimension]; //temp array to store the existing areas

		for (i = 0; i < dimension; i++)
		{
			tempArray[i] = area[i];
		}

		delete[] area;

		area = new int[f*(a+1)*r]; //reallocation of the array by increased apartments

		for (i = 0; i < f; i++) //triple loop to access all the dimensions of the building
		{
			for (j = 0; j < a + 1; j++)
			{
				for (k = 0; k < r; k++)
				{
					index = (k*f*(a+1)) + (j*f) + i; //calculation of new index in which floor is fastest changing

					if (j == a) //condition to increase apartment of each floor
					{
						area[index] = newApartments[i][k];
					}
					else
					{
						oldIndex = (k*f*a) + (j*f) + i; //formula to calculate old index in which floor is fastest changing
						area[index] = tempArray[oldIndex];
					}
				}
			}
		}

		delete[] tempArray;
		a++; //increment apartment by 1
	}

	//this function returns the area of a specific room by using the provided parameters
	int GetRoomArea(int floor,int apartment,int room)
	{
		int index = ((room-1)*f*a) + ((apartment-1)*f) + (floor-1); //formula to calculate index of required room
		return area[index];
	}

	//this function changes the area of a specific room by using the provided parameters
	void SetRoomArea(int floor, int apartment, int room, int newArea)
	{
		int index = ((room - 1)*f*a) + ((apartment - 1)*f) + (floor - 1); //formula to calculate index of required room
		area[index] = newArea;
	}

	/* this function outputs the entire building floor by floor
	each table represents a floor
	each row represents a apartment
	each value represents area of a room */
	void OutputEntireBuilding()
	{
		int i, j, k, index;

		for (i = 0; i < f; i++) //triple loop to access all the dimensions of the building
		{
			cout << "FLOOR " << i + 1 << endl << endl;
			for (j = 0; j < a; j++)
			{
				for (k = 0; k < r; k++)
				{
					index = (k*f*a) + (j*f) + i; //formula to calculate required index
					cout << "| " << area[index] << " ";
				}
				cout << "|" << endl;
			}
			cout << endl << "* * * * * * * * * *" << endl << endl; //line to separate each floor
		}
	}

	//destructor function
	~Building()
	{
		if (area = NULL)
			delete[] area;
	}

};

//this is a helper function to allocate and fill the 2-D array for AddFloor() and ExpandEachFloor() functions
void AllocateAndFill(int** &arr, int x, int y)
{
	int i, j, value = 10;
	arr = new int*[x];

	for (i = 0; i < x; i++)
	{
		arr[i] = new int[y];
		for (j = 0; j < y; j++)
		{
			if (value == 20) //the value of areas in increased floor or apartments can be from 10 to 19
				value = 10;

			arr[i][j] = value;
			value++;
		}
	}
}

//this is a helper function to deallocate the 2-D array for AddFloor() and ExpandEachFloor() functions
void Deallocate(int** &arr,int x)
{
	for (int i = 0; i < x; i++)
	{
		delete[] arr[i];
	}

	delete[] arr;
}

int main()
{
	int f, a, r, choice;
	int x, y, z, value;
	int **buildArray; //2-D array for AddFloor() and ExpandEachFloor() functions

	//take input from user for building dimesnions
	cout << "Enter number of floors: ";
	cin >> f;
	cout << "Enter number of apartments: ";
	cin >> a;
	cout << "Enter number of rooms: ";
	cin >> r;

	Building tower(f, a, r); //class object declaration

	//number choices for the user
	cout << endl;
	cout << "1: Add a floor to the building" << endl;
	cout << "2: Remove the top floor of the building" << endl;
	cout << "3: Expand each floor of the building" << endl;
	cout << "4: Get the area of a specific room" << endl;
	cout << "5: Set the area of a specific room" << endl;
	cout << "6: Output the entire building floor by floor" << endl;
	cout << "0: Exit the program" << endl << endl;
	cout << "Input choice number: ";
	cin >> choice;

	while (choice != 0)
	{
		switch (choice)
		{
		case 0:
			break;
		case 1:
			AllocateAndFill(buildArray, a, r); //allocate and fill the helper 2-D array
			tower.AddFloor(buildArray); //function call to increase floor
			f++;
			Deallocate(buildArray, a); //deallocate the helper 2-D array
			cout << "Floor added to the building!" << endl;
			break;
		case 2:
			tower.RemoveTopFLoor(); //function call to remove floor
			cout << "Top floor has been removed!" << endl;
			f--;
			break;
		case 3:
			AllocateAndFill(buildArray, f, r); //allocate and fill the helper 2-D array
			tower.ExpandEachFloor(buildArray); //function call to expand each floor
			a++;
			Deallocate(buildArray, f); //deallocate the helper 2-D array
			cout << "Each floor has been expanded!" << endl;
			break;
		case 4:
			cout << "Enter the floor number: ";
			cin >> x;
			cout << "Enter the apartment number: ";
			cin >> y;
			cout << "Enter the room number: ";
			cin >> z;
			value = tower.GetRoomArea(x, y, z); //function call to return area of room
			cout << "The area of the room is " << value << endl;
			break;
		case 5:
			cout << "Enter the floor number: ";
			cin >> x;
			cout << "Enter the apartment number: ";
			cin >> y;
			cout << "Enter the room number: ";
			cin >> z;
			cout << "Enter the new area: ";
			cin >> value;
			tower.SetRoomArea(x, y, z, value); //function call set area of room
			cout << "The area has been set!" << endl;
			break;
		case 6:
			cout << endl << "THE BUILDING OUTPUT" << endl << endl;
			tower.OutputEntireBuilding(); //function call to output the building
			break;
		}

		cout << endl << "Input choice number: ";
		cin >> choice;
	}
	
	return 0;
}