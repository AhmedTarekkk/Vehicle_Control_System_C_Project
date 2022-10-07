/*
 * main.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Ahmed Tarek Ahmed
 */

#include <stdio.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

typedef enum //enum to map off to 0 and on to 1
{
	Off,On
}HighLow;

typedef struct //struct for the engine and the room that contain the temperature and the state of the controller/AC
{
	float temp;
	HighLow controller ;
}VehicleStruct;

// using global variables so that any function can modify the values

char system_state, menu,TL_color;
int vehicle_speed = 80;
VehicleStruct Engine = {90,Off} , Room = {27,Off};
HighLow engine = On;

//functions declaration

void menu_function(void);
void modify_speed(int*); // function to try pass by address
void display(void);
void traffic_light(void);
void room_temperature(void);
void engine_temperature(void);

int main(void) {
	setbuf(stdout, NULL);
	do {
		printf("What do you want to do ?\n");
		printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n\n");
		scanf(" %c", &system_state);

		if (system_state == 'c')
		{
			printf("Quit the system\n");
			return 0;
		}

		else if (system_state == 'b')
		{
			printf("Turn Off The Vehicle Engine\n\n");
		}

		else if( system_state == 'a' )
		{
			engine = On; // To Turn on the engine again in case that i turned it off before
			menu_function();
		}
		else
		{
			printf("Invalid Input !\n");
		}

	} while ( !( system_state == 'c' ) );  // 'c' is the only char that will stop the program

	return 0;
}

void menu_function(void)
{
	do {
			printf("a. Turn off the engine\nb. Set the traffic light color\nc. Set the room temperature\n");
			if(WITH_ENGINE_TEMP_CONTROLLER)
			{
				printf("d. Set the engine temperature\n\n");
			}
			scanf(" %c", &menu);
			switch (menu)
			{
				case 'a':
					engine = Off; // turning off the engine
					break;
				case 'b':
					traffic_light();
					break;
				case 'c' :
					room_temperature();
					break;
				case 'd' :
					engine_temperature();
					break;
				}
			modify_speed(&vehicle_speed); //checking the speed by passing its address to modify it in case speed = 30
			display();
		} while (engine);
}

void display(void) // to display all the states after any change
{
	engine ? printf("Engine State: ON\n") : printf("Engine State: OFF\n") ;
	Room.controller ? printf("AC: ON\n") : printf("AC: OFF\n") ;
	printf("Vehicle Speed = %d Km/h\n",vehicle_speed);
	printf("Room Temperature = %0.2f C\n",Room.temp);
	if(WITH_ENGINE_TEMP_CONTROLLER)
	{
		Engine.controller ? printf("Engine Controller State: ON\n") : printf("Engine Controller State: OFF\n") ;
		printf("Engine Temperature = %0.2f C\n\n",Engine.temp);
	}
}

void traffic_light(void)
{
	do
		{
			printf("Enter the traffic light color\nG for green\tO for orange\tR for red\n");
			scanf(" %c",&TL_color);
		}while(!(TL_color=='G' || TL_color=='g' || TL_color=='O' || TL_color=='o' || TL_color=='R' || TL_color=='r'));
		// so i can deny any invalid colors for the traffic light
		switch (TL_color) {
			case 'g':
			case 'G':
				vehicle_speed = 100;
				break;
			case 'o':
			case 'O':
				vehicle_speed = 30;
				break;
			case 'r':
			case 'R':
				vehicle_speed = 0;
				break;
		}
}

void room_temperature(void)
{
	printf("Enter the room temperature\n");
	scanf("%f",&Room.temp);
	if(Room.temp<10 || Room.temp>30)
	{
		Room.controller = On;
		Room.temp = 20;
	}
	else
	{
		Room.controller = Off;
	}
}

void engine_temperature(void)
{
	if(WITH_ENGINE_TEMP_CONTROLLER)
	{
		printf("Enter the engine temperature\n");
		scanf("%f",&Engine.temp);
		if(Engine.temp<100 || Engine.temp>150)
		{
			Engine.controller = On;
			Engine.temp = 125;
		}
		else
		{
			Engine.controller = Off;
		}
	}
}

void modify_speed(int *ptr2speed)
{
	if(*ptr2speed == 30)
		{
			Room.controller = On ;
			Room.temp = Room.temp*((float)5/4)+1 ; // 5/4 should be casted to float so it's value = 1.25 not 1
			if(WITH_ENGINE_TEMP_CONTROLLER)
			{
				Engine.controller = On ;
				Engine.temp = Engine.temp*((float)5/4)+1 ;
			}
		}
}
