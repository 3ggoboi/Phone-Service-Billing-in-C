/*
Write a program that calculates and prints the bill for a cellular telephone company. 
The company offers two types of service: regular and premium. Its rates vary, depending on the type of service. The rates are computed as follows:

Regular service: 500.00 plus first 50 minutes are free. Charges for over 50 minutes are P5.00 per minute.
Premium service: 250.00 plus:
a. For calls made from 6:00 a.m. to 5:59 p.m., the first 75 minutes are free; charges for more than 75 minutes are P2.00 per minute.
b. For calls made from 6:00 p.m. to 5:59 a.m., the first 100 minutes are free; charges for more than 100 minutes are P1.00 per minute.
Your program should prompt the user to enter a service code (type char), and the number of minutes the service was used. (Hint: For the time, you can use military format)


A service code of r or R means regular service; a service code of p or P means premium service. 
Treat any other character as an error. Your program should output type of service, number of minutes the telephone service was used, and the amount due from the user.

For the premium service, the customer may be using the service during the day and the night. 
Therefore, to calculate the bill, you must ask the user to input the number of minutes the service was used during the day and the number of minutes the service was used during the night


TEST CASES [Version 1: User enters the time of the call]

Scenario 1: If the service is REGULAR and the consumed minutes is 100... the cost should be 750.00

Scenario 2: If the service is PREMIUM, call started at 7:00PM, and consumed minutes is 200... the cost should be 350.00

Scenario 3: If the service is PREMIUM, call started at 9:00AM, and consumed minutes is 150... the cost should be 400.00

 
TEST CASES [Version 2: User enters the number of minutes consumed in the day and night, if service is premium]

Scenario 1: If the service is REGULAR and the consumed minutes is 100... the cost should be 750.00

Scenario 2: If the service is PREMIUM, consumed minutes during the night is 200... the cost should be 350.00

Scenario 3: If the service is PREMIUM, consumed minutes during the day is 150... the cost should be 400.00

Scenario 4: If the service is PREMIUM, consumed minutes during the day is 150 and minutes consumed during the night is 200... the cost should be 500.00
*/

// HEADER FILES
#include <stdio.h>
#include <math.h>
#include <ctype.h>

//REGULAR SERVICE CONSTANTS
#define REGULAR_BASEFEE 500.00
#define REGULAR_FREEMIN 50
#define REGULAR_RATEPERMIN 5.0

//PREMIUM SERVICE CONSTANTS
#define PREMIUM_BASEFEE 250.00

//DAY SERVICE
#define PREMIUM_DAYRATE 2.00
#define LIBRE_DAYMINUTES 75

// EVENING SERVICE
#define PREMIUM_NIGHTRATE 1.00
#define LIBRE_NIGHTMINUTES 100



// Function to run the regular service calculations
void run_regular_service(float fMinutes)
{
	float fTotal_bill, fCharge = 0.0;	// initialized all values to 0 so that we won't get garbage values in the bill
	int nExtra_minutes = 0;
	
	if(fMinutes > REGULAR_FREEMIN)	// checking if the free minutes have been exhausted
	{
		nExtra_minutes = fMinutes - REGULAR_FREEMIN;	// calculates how much overtime to charge based on set rate
		fCharge = nExtra_minutes * REGULAR_RATEPERMIN;
	}
	
	// Calculates the total bill
	fTotal_bill = REGULAR_BASEFEE + fCharge;
	
	// Service bill printed out
	printf("\n========================================\n");
	printf("             SERVICE BILL                \n");
	printf("========================================\n");
	printf("Service Type:		REGULAR(R)\n");
	printf("Minutes Used:		%.0f minutes\n", fMinutes);
	printf("Base Fee:		PHP%.2f\n", REGULAR_BASEFEE);
	printf("Overtime Charge:	%d minutes at PHP%.2f/min\n", nExtra_minutes, REGULAR_RATEPERMIN);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("TOTAL AMOUNT DUE: 	PHP%.2f\n", fTotal_bill);
	printf("========================================\n");
}

// Function to run the premium service calculations
void run_premium_service()
{
	float fDay_min = 0, fNight_min = 0, fTotal_minutes = 0;			// Once again, initialized values to 0 
	float fDay_charge = 0.0, fNight_charge = 0.0, fTotal_bill;		// so as to not receive garbage values :(
	int nDay_overtime = 0, nNight_overtime = 0;
	
	// Felt like making it look fancy lol
	printf("\n~-~-~-~-~-~-~- PREMIUM SERVICE MENU -~-~-~-~-~-~-~\n\n");
	printf("Enter minutes used during the DAY (6:00am - 5:59pm): ");       
	if(scanf("%f", &fDay_min) != 1 || fDay_min < 0)
	{
		printf("\n The minutes input is invalid\n");
		return;
	}
	
	printf("Enter minutes used during the EVENING (6:00pm - 5:59am): ");       
	if(scanf("%f", &fNight_min) != 1 || fNight_min < 0)
	{
		printf("\n The minutes input is invalid\n");
		return;
	}
	
	// --- DAY CHARGE COMPUTATION ---
	if(fDay_min > LIBRE_DAYMINUTES)
	{
		nDay_overtime = fDay_min - LIBRE_DAYMINUTES;
		fDay_charge = nDay_overtime * PREMIUM_DAYRATE;
	}
	
	// -- NIGHT CHARGE COMPUTATION ---
	if(fNight_min > LIBRE_NIGHTMINUTES)
	{
		nNight_overtime = fNight_min - LIBRE_NIGHTMINUTES;
		fNight_charge = nNight_overtime * PREMIUM_NIGHTRATE;
	}

	// --- BILL COMPUTATION ---
	fTotal_bill = PREMIUM_BASEFEE + fDay_charge + fNight_charge;
	fTotal_minutes = fDay_min + fNight_min;	
	
	// ---- RESIBO ---
	printf("\n========================================\n");
	printf("             SERVICE BILL                \n");
	printf("========================================\n");
	printf("Service Type:		PREMIUM(P)\n");
	printf("Minutes Used:		%.0f min(s)\n", fTotal_minutes);
	printf("  Day   Minutes:	%.0f min(s)\n", fDay_min);
	printf("  Night Minutes:	%.0f min(s)\n", fNight_min);
	printf("Base Fee:		PHP%.2f\n", PREMIUM_BASEFEE);
	printf("Day Overtime Charge:	%d minutes at PHP%.2f/min\n", nDay_overtime, PREMIUM_DAYRATE);
	printf("Night Overtime Charge:	%d minutes at PHP%.2f/min\n", nNight_overtime, PREMIUM_NIGHTRATE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("TOTAL AMOUNT DUE: 	PHP%.2f\n", fTotal_bill);
	printf("========================================\n");
}

int main()
{
	float fMinutes;
	char cServiceInput;
	
	printf("Which service would you like to avail?\n\n\tType 'r' for our REGULAR service\n\tType 'p' for our PREMIUM service\n\n");
	printf("Input (R/P): ");
	if (scanf(" %c", &cServiceInput) != 1)		//This checks if there is a valid char input
	{
        printf("Input Error...\n");
        return 1;
    }

	cServiceInput = toupper(cServiceInput); 

    //Check if the input is valid based on the two values asked (Either R or P)
    if (cServiceInput != 'R' && cServiceInput != 'P') {
        printf("\nInvalid User Input. Please enter either 'R' or 'P'\n");
        printf("Terminating program...\n");
        return 1;
    }
	
	if(cServiceInput == 'R')
	{
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");;
		printf(">>>You have selected the REGULAR service<<<\n");
        printf("Enter total minutes used: ");       
		if(scanf("%f", &fMinutes) != 1 || fMinutes < 0) 
		{
            printf("\nInvalid User Input for the minutes function :(\n");
			printf("Terminating program due to invalid user input...\n");
            return 1;
        }
        
		run_regular_service(fMinutes);
    }
	else if(cServiceInput == 'P')
	{
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");;
		printf(">>>You have selected the PREMIUM service<<<\n\n");
		run_premium_service();
	}

	
	return 0;
}


/* Dev Notes:
> To completely honest, I used Gemini AI to help point out any syntax errors I wasn't familiar with
> Was not familiar that you could use a scanf function inside an if conditional... that's actually pretty neat ngl
> Took me a long while to figure out how to run checks for invalid inputs
	> I really could have just not done that but I just felt like accounting for it ┐(´ー｀)┌
> Oh yeah, I also used the  <ctype.h> library so that I could make the inputs automatically uppercase
	> I really did not want to make another two additional checks for lowercase characters man...
> Please don't mind me changing "FREE_MINUTES" to "LIBRE_MINUTES", I could feel my brain frying and my head started aching
	> So i did this to make it funny so i could laugh and not go insane </3
	> I just like to have fun pls dont get mad TwT
> Code should work as it should, I made sure any invalid input terminates the program and informs the user of the invalid input
> Yes I tried hard to make it look pretty, and yes it took a lot of uncessary time
	> Will I do this in exams? Definitely not, but does it look nice as an assignment? Very much <333
> Sir Gary if you are reading this I am so sorry you have to read through so much extra code, love ya for teaching us tho :)))
*/