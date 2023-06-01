/*
 ============================================================================
 Name        : Vehicle_Control_system.c
 Author      : Ahmad Ragab Mohamed
 Description : Vehicle Control System Project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#define WITH_ENGINE_TEMP_CONTROLLER 1
//#define WITH_ENGINE_TEMP_CONTROLLER 0                             /* this will disable or commented any lines of codes related to Engine Termperature Controller */



typedef enum                                                        /* Define a new data type for the state of the devices */
{
	OFF,ON
}State;

/******** Functions Declarations *******/
void PrintBasicOptions(void);                                       /* a function that prompt the user to choose what he wants to do */
void DisplaySensorSetMenu(void);                                    /* a function that prompt the user to choose what he wants to do after the Engine is on */
void DsiplayCurrentVehicleState(State Engine_State,State EngineTempControlerState,State AC_State,float RoomTemperature,int VehicleSpeed,float EngineTemperature); /* display the info of vehicle */
void Turnoff_Function(void);                                        /* a function that implement the case that the user pressed on "Turn off the Vehicle Engine"  option */
void SetTheTrafficLight(void);                                      /* a function that the implement the case that the user wants to set the traffic light with a specific value */
void SetTheRoomTemperature(void);                                   /* a function that the implement the case that the user wants to set the Room Temperature with a specific value */
void SetTheEngineTemperature(void);                                 /* a function that the implement the case that the user wants to set the Engine Temperature with a specific value */

/******** Global Variable Declarations *******/
char ChoiceWhileEngineOn = '\0';                                     /* a variable to store the choice of the user after Engine is ona initialized with "null" */
char choice;                                                         /* a variable to store the choice of the user in the very beginning of the program  */
int QuitProgram = 1;                                                 /* a variable that indicates that the user wants to Quit the program ==> 1 means don't Quit and 0 ==> means Quit*/
const char *Engine[2] = {"OFF","ON"};                                /* array of two strings to use it to print the word "OFF" or "ON" on screen based on the Value of the state of Engine*/
const char *EngineTemperatureControl[2] = {"OFF","ON"};              /* array of two strings to use it to print the word "OFF" or "ON" on screen based on the Value of the state EngineTempController */
const char *AC[2] = {"OFF","ON"};                                    /* array of two strings to use it to print the word "OFF" or "ON" on screen based on the Value of the state of AC */
State Engine_State = ON;                                             /* initial value for Engine State */
State EngineTempControlerState = OFF;                                /* initial value for Engine Temperature Value  */
State AC_State = OFF;                                                /* initial value for AC State */
float RoomTemperature = 35;                                          /* initial Value for Room Temperature and it is a float to fit the upcoming value of (RoomTemperature * (5/4) + 1) formula */
int VehicleSpeed = 50;                                               /* a variable to store the value of vehicle Speed in and initialized with 50 km/hr */
float EngineTemperature = 90;                                        /* initial Value of Engine Temperature it is a float to fit the upcoming value of (EngineTemperature * (5/4) + 1) formula */

int main(void)
{
    setbuf(stdout,NULL);                                             /* a function to remove the buffering in console window */
    printf("Choose what you want to do: \n\n");
    PrintBasicOptions();                                             /* a function that prompt the user to choose what he wants to do */

    do{                                                              /* without this do-while loop, the user can Enter a non valid choice (here we enforce him to enter a valid choice) */
		switch(choice)
		{
				case 'b':                                            /* In Case of the user chose to Turn off the vehicle engine */
						Turnoff_Function();                          /* this Function to handle the situation of Turn off Engine */
						if(QuitProgram == 0)
						{
							return 0;
						}
				break;
				case 'c':                                            /* In case of the user wants to Quit the System */
						 printf("\nState: [Quit the System]\n");
						 return 0;
				break;
				case 'a':                                            /* In case of the user wants to Turn on The Engine */
				break;

				default :                                            /* In case of the user Entered a non valid choice */
							printf("Invalid Input\n");
							PrintBasicOptions();                     /* print out the choices again and prompt the user to Enter a valid choice */
		}
	}while(choice != 'a' && choice != 'c');                          /* this the conditions that assure that the user will Enter a valid choice */

    /******* In case of the user chose to "Turn on Vehicle Engine" *******/
    printf("\nState: [Turn on the vehicle engine]\n");
    DisplaySensorSetMenu();                                          /* a function to display the options and prompt the user to choose */
   do                                                                /* this do-while to enable the user to choose the same choice more than once ==> b more than one or c ==> more than one time*/
   {
 		do
 		{                                                            /* this do-while to Enforce that the user will Enter a valid choice */
 			if (ChoiceWhileEngineOn == 'a')                          /* the user chose to Turn off the Engine */
 			{
 				do                                                   /* doesn't goes out from the loop until the user choose an action other than 'Turn off the Engine' */
 				{
 					  Turnoff_Function();
 					  if(QuitProgram == 0)
 					  {
 						return 0;
 					  }
 				  DisplaySensorSetMenu();
 				}while(ChoiceWhileEngineOn == 'a');
 			}
 			if (ChoiceWhileEngineOn == 'b')                          /* the user chose to set the Traffic Light */
 			{
 				SetTheTrafficLight();                                /* a function to handle the situation if the user chose to set the traffic light */

 			}
 			if(ChoiceWhileEngineOn == 'c')
 			{
 				SetTheRoomTemperature();                             /* a function to handle the situation if the user chose to set the Room Temperature */
 			}
 			else if (ChoiceWhileEngineOn == 'd')
 			{
 				SetTheEngineTemperature();                           /* a function to handle the situation if the user chose to Set the Engine Temperature */

 			}
 			else  if(ChoiceWhileEngineOn != 'a'  && ChoiceWhileEngineOn != 'b' && ChoiceWhileEngineOn != 'c' &&ChoiceWhileEngineOn != 'd')
 			{
 				printf("Invalid Input\n");
 				DisplaySensorSetMenu();                              /* prompt the user to Enter another choice */
 			}
 			else
 			{

 			}
 		}while(ChoiceWhileEngineOn != 'a'  && ChoiceWhileEngineOn != 'b' && ChoiceWhileEngineOn != 'c' &&ChoiceWhileEngineOn != 'd');
    }while(ChoiceWhileEngineOn == 'a' || ChoiceWhileEngineOn == 'b' || ChoiceWhileEngineOn == 'c' || ChoiceWhileEngineOn == 'd');
    return 0;
}


/****************************  Functions Definitions  ***********************************/

/****** a function to print the Set of the choices while being in Turn off mode *****/
void PrintBasicOptions(void)
{
    printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n");
    printf("\nChoose an action: ");
    scanf(" %c", &choice);
}

/****** a function to print the Set of the choices while being in Turn on mode *****/
void DisplaySensorSetMenu(void)
{
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)");
    printf("\nChoose an action: ");
	scanf(" %c",&ChoiceWhileEngineOn);
}


/********* a function to Display the Current Vehicle State **********/
void DsiplayCurrentVehicleState(State Engine_State,State EngineTempControlerState,State AC_State,float RoomTemperature,int VehicleSpeed,float EngineTemperature)
{
	printf("Engine State                        : %s\n",Engine[Engine_State]);
	printf("AC                                  : %s\n",AC[AC_State]);
	printf("Vehicle                             : %d km/hr\n",VehicleSpeed);
	printf("Room Temperature                    : %.2f C\n",RoomTemperature);

	#if WITH_ENGINE_TEMP_CONTROLLER                                  /* this block (#if ... #endif) controls the appearance of  Engine Temperature Controller state on the console */
	printf("Engine Temperature Controller State : %s\n",EngineTemperatureControl[EngineTempControlerState]);
	#endif

	printf("Engine Temperature                  : %.2f C\n\n",EngineTemperature);
	DisplaySensorSetMenu();
}


/**********  a function to deal with the situation if the user chose to "Turn off the Engine"  **********/
void Turnoff_Function(void)
{
	do{                                                               /* this do-while loop to enforce the user to Enter a valid input */
		 do                                                           /* this do-while loop to enforce the user to Enter an input other than "Turn off the Engine" */
		 {
		 	printf("\nState: [Turn off the vehicle engine]\n");
		 	PrintBasicOptions();
		 }while(choice == 'b');
		 if (choice == 'c')                                           /* if the user chose to Quit the program */
		 {
		 	printf("\nState: [Quit the System]\n");
		 	QuitProgram =  0;
		 }
		 else if (choice != 'a')
		 {
		 	printf("Invalid Input\n");

		 }
		 else
		 {

		 }
	}while(choice != 'a' && choice != 'b' && choice != 'c');

}


/* a function to handle the situation if the user chose to set the traffic light */
void SetTheTrafficLight(void)
{
	printf("\nSet The Traffic Light Color (g,o,r || G,O,R): ");
	scanf(" %c",&ChoiceWhileEngineOn);

	if(ChoiceWhileEngineOn == 'g' || ChoiceWhileEngineOn == 'G')
	{
		VehicleSpeed = 100;
		DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
	}
	else if(ChoiceWhileEngineOn == 'o' || ChoiceWhileEngineOn == 'O')
	{
		VehicleSpeed = 30; AC_State = ON; RoomTemperature = (RoomTemperature*(5.0/4) + 1); EngineTempControlerState = ON;
		EngineTemperature = (EngineTemperature*(5.0/4) + 1);
		DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
	}
	else if(ChoiceWhileEngineOn == 'r' || ChoiceWhileEngineOn == 'R')
	{
		VehicleSpeed = 0;
		DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);

	}
	else
	{
		printf("\nInvalid Input\n");
		DisplaySensorSetMenu();

	}
}

/* a function to handle the situation if the user chose to set the Room Temperature */
void SetTheRoomTemperature(void)
{
	int Temperature_State = 0;
	printf("\nSet The Room Temperature : ");
	scanf("%d",&Temperature_State);
	if (VehicleSpeed == 30)                                           /* this a special condition according to Requirement 7.d the displayed will be changed if vehicle speed is 30 km/hr */
	{
		VehicleSpeed = 30; AC_State = ON; RoomTemperature = (RoomTemperature*(5.0/4) + 1); EngineTempControlerState = ON;
		EngineTemperature = (EngineTemperature*(5.0/4) + 1);
		if(Temperature_State < 10)
		{
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
		}
		else if(Temperature_State > 30)
		{
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
		}
		else
		{
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);

		}
	}
	else
	{
		if(Temperature_State < 10)
		{
			RoomTemperature = 20;  AC_State = ON;
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
		}
		else if(Temperature_State > 30)
		{
			RoomTemperature = 20;  AC_State = ON;
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
		}
		else
		{
			AC_State = OFF;
			DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);

		}
	}


}

/* a function to handle the situation if the user chose to set the Engine Temperature */
void SetTheEngineTemperature(void)
{
	int Temperature_State = 0;
	printf("\nSet The Engine Temperature : ");
	scanf("%d",&Temperature_State);

	if(VehicleSpeed == 30)                                        /* this a special condition according to Requirement 7.d the displayed will be changed if vehicle speed is 30 km/hr */
	{
		VehicleSpeed = 30; AC_State = ON; RoomTemperature = (RoomTemperature*(5.0/4) + 1); EngineTempControlerState = ON;
		EngineTemperature = (EngineTemperature*(5.0/4) + 1);
			if(Temperature_State < 100)
			{
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
			}
			else if(Temperature_State > 150)
			{
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
			}
			else
			{
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
			}
	}
	else
	{
		if(Temperature_State < 100)
			{
				EngineTemperature = 125;  EngineTempControlerState = ON;
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
			}
			else if(Temperature_State > 150)
			{
				EngineTemperature = 125;  EngineTempControlerState = ON;
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);
			}
			else
			{
				EngineTempControlerState = OFF;
				DsiplayCurrentVehicleState(Engine_State,EngineTempControlerState,AC_State,RoomTemperature,VehicleSpeed,EngineTemperature);

			}
	}


}

/****************************************************************    THANK YOU FOR YOUR ENDLESS SUPPORT    ******************************************************************************************/



































