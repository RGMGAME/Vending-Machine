/*

Vending Machine Simulator by EZ Connie.
Total hours taken to complete: 13
Total hours wasted on the change calculator: 12

*/



#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

	int input; // input of menus
	int inputfood; //what food the customer picks
	int refillquantity; //the quantity that the admin adds to the machine
	bool exitgame=false; //to exit the program
	bool refilldone=false; //to exit the refill menu
	bool correct_input=false; //checks for correct inputs
	bool admindone=false; //to exit the admin menu
	bool customerdone=false;//to exit the customer menu
	char adminpass[50] = "pass"; //to see if the user is really an admin
	char passguess[50]="/0"; //variable that stores the password guess
	int change; //for change
	int i; //for my fors
	int cap1theory; //these are the theoretical values that the bank will reach after the transaction
	int cap2theory;
	int matchchange=0; //this is the value we give back to the customer, when it reaches the change value
	//we know to give the change

	int nuka=8, nukaprice=1, nukamax=12; // a soft drink,
	// first is the amount the machine has in it, second is the price, and the last is the maximum units the 
	//machine can hold
	int blamco=5, blamcoprice=2, blamcomax=6;// pasta
	int cram=3, cramprice=4, crammax=5; // meat
	int mash=2, mashprice=3, mashmax=6; // potatoes 
	int cap1=35, cap1max=60; //1 value coins in the bank currently and max it can hold
	int cap2=28, cap2max=60; //2 value coins in the bank currently and max it can hold
	int cap1temp=0; //cap1 input before a user picks food, we return this if they cancel the order
	int cap2temp=0; //cap2 input before a user picks food
	int cap1change=0; //for the change calc, how many coins of each value we return
	int cap2change=0;  
	bool nochange=false; //for when we dont have enough money in the bank to give change
	
int refill(){
	while(!refilldone){
		input = 0;
		int input;
		do {
			printf("\nJust type in the code of the item you will put inside me boss!\n\n"
				"1. Nuka Cola (%d/%d)\n2. BlamCo Mac and Cheese (%d/%d)\n3. Cram Meatloaf (%d/%d)\n4. InstaMash (%d/%d)\n"
				"5. 1 cap coins (%d/%d)\n6. 2 cap coins (%d/%d)\n7. Cancel\n", nuka, nukamax, blamco, blamcomax, cram, crammax, mash, mashmax, cap1, cap1max, cap2, cap2max);
			if (scanf("%d", &input) != 1 || input < 1 || input > 7) {
				printf("Invalid input, please enter an integer from 1 to 7.\n");
				while (getchar() != '\n'); // Clears the input buffer	
			}

		} while (input < 1 || input > 7);


		if(input==7){ 
			printf("Cancelled.");
			break;
		}
		//if the food code is good we ask the quantity. negative values to take sth out, positive for refills
		printf("Now put the quantity of the item!\n");
		scanf("%d",&refillquantity);
		while(getchar()!='\n');


		switch (input){//input is the food code
			case 1:
				if(refillquantity>0 && refillquantity+nuka>nukamax)
				//if we want to add but the value after we would add would be more than the maximum amount
				//it can hold, we do not add anything
					printf("I can't hold that many Nuka Colas boss!\n");
				else if (refillquantity<0 && nuka+refillquantity<0)
				//if we want to remove but the ammount after we remove would be negative, in other words,
				//if we try to remove more than what are inside, we do not remove anything
					printf("I don't have that many Nuka Colas boss!\n");
				else
				//if everything is good, we do the math and either remove or add
					nuka+=refillquantity;
				break;
			case 2:
				if(refillquantity>0 && refillquantity+blamco>blamcomax)
					printf("I can't hold that many BlamCo Mac and Cheese's boss!\n");
				else if(refillquantity<0 && refillquantity+blamco<0)
					printf("I don't have that many BlamCo Mac and Cheese's boss!\n");
				else
					blamco+=refillquantity;
				break;
			case 3:
				if(refillquantity>0 && refillquantity+cram>crammax)
					printf("I can't hold that many Cram Meatloafs boss!\n");
				else if(refillquantity<0 && refillquantity+cram<0)
					printf("I don't have that many Cram Meatloafs boss!\n");
				else
					cram+=refillquantity;
				break;
			case 4:
				if(refillquantity>0 && refillquantity+mash>mashmax)
					printf("I can't hold that many InstaMashes boss!\n");
				else if(refillquantity<0 && refillquantity+mash<0)
					printf("I don't have that many InstaMashes boss!\n");
				else
					mash+=refillquantity;
				break;
				
			case 5:
				if(refillquantity>0 && refillquantity+cap1>cap1max)
					printf("I can't hold that many 1-cap coins boss!\n");
				else if(refillquantity<0 && refillquantity+cap1<0)
					printf("I don't have that many 1-cap coins boss!\n");
				else
					cap1+=refillquantity;
				break;
			case 6:
				if(refillquantity>0 && refillquantity+cap2>cap2max)
					printf("I can't hold that many 2-cap coins boss!\n");
				else if(refillquantity<0 && refillquantity+cap2<0)
					printf("I don't have that many 2-cap coins boss!\n");
				else
					cap2+=refillquantity;
				break;

				
		}
		printf("Transaction Complete!\n\n");
		
		
	}
	
	
}
int customer(){
	//oh boy
	system("cls");
	while(!customerdone){
		cap1temp=0; //this is the temporary hold for the coins the customer inputs. if they want to cancel
		//the transaction, the will be returned to them. we set them to 0 before we start because after
		//we use them for the first time, we give them a value. I don't know how much i will write in
		//a comment, that's why i use // and not */, don't judge me.
		cap2temp=0;
		
		printf("Welcome potential customer! Here at RobCo we are dedicated to keeping workers well fed!\nBecause a hungry"
		" worker is thinking of forming unions, and we just can't have that!\nWhat are you having?\n\n");
		//introductory greeting. after that we give the menu. if we are all out of a specific 
		//food, we say it
		if (nuka>0) printf("1. Nuka Cola                              1 cap\n");
		//nuka is the value of nuka colas currently in the machine
		else printf("All out of Nuka Colas! Infinite apologies dear customer!\n");
		if (blamco>0) printf("2. BlamCo Mac and Cheese                  2 caps\n");
		else printf("All out of BlamCo Mac and Cheese! Infinite apologies dear customer!\n");
		if (cram>0) printf("3. Cram Meatloaf                          4 caps\n");
		else printf("All out of Cram Meatloaf! Infinite apologies dear customer!\n");
		if (mash>0) printf("4. InstaMash                              3 caps\n");
		else printf("All out of InstaMash! Infinite apologies dear customer!\n");
		do {
			if (scanf("%d", &inputfood) != 1 || inputfood < 1 || inputfood > 4) {
				printf("Invalid input, please enter an integer from 1 to 4.\n");
				while (getchar() != '\n'); // Clears the input buffer	
			}
		} while (inputfood < 1 || inputfood > 4);

		
		
		
		
		
		if (inputfood==1 && nuka==0){
			printf("Like I said, we are all out of Nuka Colas! Pick something else!\n\n");
			break;
		}
		else if (inputfood==2 && blamco==0){
			printf("Like I said, we are all out of BlamCo Mac and Cheese! Pick something else!\n\n");
			break;
		}
		else if (inputfood==3 && cram==0){
			printf("Like I said, we are all out of Cram Meatloaf! Pick something else!\n\n");
			break;
		}
		else if (inputfood==4 && mash==0){
			printf("Like I said, we are all out of InstaMash! Pick something else!\n\n");
			break;
		}
		//clean the input variable is case something happens
		input=0;
		
		//prompt to add coins
		printf("Insert your hard-earned money! 1 for 1-caps, 2 for 2-caps, 3 when you are done, and 4 to cancel!\n");
		
		while(1){//this keeps asking money until the user has inserted all the money they want, or they 
		//want to cancel the transaction
			
			do {
				if (scanf("%d", &input) != 1 || input < 1 || input > 4) {
					printf("Invalid input, please enter an integer from 1 to 4.\n");
					while (getchar() != '\n'); // Clears the input buffer	
					}
				}while (input < 1 || input > 4);
			/*cap2temp and camp1temp are temporary holders that hold the money until the transaction is
			complete. if the customer changes their mind, the money will be returned to them and no
			food will fall. i also use it to display how much money they have inserted to the machine*/
			if (input==2) cap2temp++;
			else if (input==1) cap1temp++;
			//if the input is 3 we go to change calculation and we give the food, and 4 cancels it
			//so they both break this loop
			else if(input==3 || input==4) break;
			//if they enter a different input we remind them of the prompt 
			//and ask for more dolla
			
			//display of how much they have inserted
			printf("You have inserted %d total value of caps.\n",cap1temp+2*cap2temp);
			//the total value is 1 times the coins worth 1 plus 2 times the coins worth 2
		}
		//he cancels the transaction
		if (input==4){
			printf("Transaction cancelled! Your money have been returned to you! I'm sad to see them go!\n\n");
			break;//this breaks the while(!customerdone) and returns to the main menu
		}
		//below this point, input==3
		
		//checks if the input is enough to buy the product 
		//if you picked the cola and the value of your money are less than the price, you get an error
		//and are sent back in the cap inserting screen
		if (inputfood==1 && cap1temp+2*cap2temp<nukaprice){
			printf("Insufficient funds! Funds you inserted: %d. Nuka Cola Price: %d.\n",cap1temp+2*cap2temp,nukaprice);
			break;
		}
			
		else if(inputfood==2 && cap1temp+2*cap2temp<blamcoprice){
			printf("Insufficient funds! Funds you inserted: %d. BlamCo Price: %d.\n",cap1temp+2*cap2temp,blamcoprice);
			break;
		}
		else if(inputfood==3 && cap1temp+2*cap2temp<cramprice){
			printf("Insufficient funds! Funds you inserted: %d. Cram Price: %d.\n",cap1temp+2*cap2temp,cramprice);
			break;
		}
		else if(inputfood==4 && cap1temp+2*cap2temp<mashprice){
			printf("Insufficient funds! Funds you inserted: %d. Mash Price: %d.\n",cap1temp+2*cap2temp,mashprice);
			break;
		}
		
		//check if the input would overflow the bank
		if (cap1+cap1temp>cap1max){
			//if the caps already in and the caps that would be inserted are more than the maximum
			printf("1-cap overflow. Your money have been returned to you.\n");
			break;
		}
		if (cap2+cap2temp>cap2max){
			printf("2-cap overflow. Your money have been returned to you.\n");
			break;
		}
		// if everything goes according to plan, we start the proccess
		

		
		
		//calculate the change
		if (inputfood==1) {
			change=(cap1temp+2*cap2temp)-nukaprice;
		}	
		else if(inputfood==2){
			change=(cap1temp+2*cap2temp)-blamcoprice;
		}
		else if(inputfood==3){
			change=(cap1temp+2*cap2temp)-cramprice;
		}
		else if(inputfood==4){
			change=(cap1temp+2*cap2temp)-mashprice;
		}
		/*these are the theoretical money we have on the bank, the ones already in and the ones we will add
		after the transaction is completed. we don't add the money to the real bank yet because there is a chance
		we will not have the change and we have to give them their money back. however, we need to be able
		to give them change from their money as well. if they insert a 2cap we cannot tell them I cannot
		give you change because I don't have 2-caps*/
		
		cap1theory=cap1+cap1temp;
		cap2theory=cap2+cap2temp;
		matchchange=0;
		
		/*this next part keeps running until the money we will give is equal to the change. it works like this.
		first we give them 1 cap. if that is the change we break. if that puts the bank in negative we 
		display a message saying we dont have the change. if we need to give more change we take the 1cap
		back and give them a 2cap, so we give them 2 value. is this the change? if no we add another 1cap. 
		so now we give them 3 value. if not the change we take the 1cap and we add a 2cap, so 4 value.
		we add one after every loop and we break when we hit the change*/
		nochange=false; //reset this just in case
		while(matchchange!=change){	
			if (cap1theory>0){//if we have 1caps in the bank we can run the below code that takes 1caps from the bank
				cap1change++;//we give a 1cap
				cap1theory--;//so we remove 1 cap from the bank
				matchchange++;//the amount of money we are planning to give goes up
				if (cap1change<0) {
					nochange=true;
					break;
				} //sometimes this code returns as change -1 1caps and 1 2caps
				if (cap2change<0) {
					nochange=true;
					break;
				} //so i put these lines to stop that
				if (matchchange==change) break;//if we find the change we dont go in the next batch of code
			}
			
			
			if (cap2theory>0){//if we have 2caps in the bank, we run this that gives 2caps, if not we go back up and add 1caps to the change fund
				cap1change--;//we take the 1cap back
				cap1theory++;//we add it to the bank
				
				cap2theory--;//we take a 2cap from the bank
				cap2change++;//we add it to the change we are planning to give
				matchchange++;//the value we are planning to give goes up by -1+2=1
				if (cap1change<0) {
					nochange=true;
					break;
				} 
				if (cap2change<0) {
					nochange=true;
					break;
				}
				if (matchchange==change) break;//if we find the change we dont rerun the loop
			}
			
		}
	
		if(nochange){
			printf("Not enough change in the bank. Contact an administrator. Your money has been returned to you.\n");
			break;
		}
		
		//if the code reaches this then it is all good
		
		//add the client's money in the bank
		cap2+=cap2temp;
		cap1+=cap1temp;
		
		//we lower the food and print confirmation
		if (inputfood==1) {
			nuka--;
			printf("You bought a Nuka Cola.\nPrice: %d\nYou inserted: %d worth of caps.\n",nukaprice,cap1temp+2*cap2temp);
		}	
		else if(inputfood==2){
			blamco--;
			printf("You bought a BlamCo Mac and Cheese.\nPrice: %d\nYou inserted: %d worth of caps.\n",blamcoprice,cap1temp+2*cap2temp);
		}
		else if(inputfood==3){
			cram--;
			printf("You bought a Cram Meatloaf.\nPrice: %d\nYou inserted: %d worth of caps.\n",cramprice,cap1temp+2*cap2temp);
		}
		else if(inputfood==4){
			mash--;
			printf("You bought an InstaMash.\nPrice: %d\nYou inserted: %d worth of caps.\n",mashprice,cap1temp+2*cap2temp);
		}
		//remove the caps we give from the bank
		cap2-=cap2change;
		cap1-=cap1change;
		printf("Your change is %d, given in %d 1-cap coins and in %d 2-cap coins.\nYummy yummy in your tummy! Come again!\n\n\n",change,cap1change,cap2change);
		
		
		break;
	}			
	
}	
int admin(){
	system("cls");
	printf("I knew it was you boss! What would you have me do?");
	while(!admindone){//this stays open as long as admin is working
		printf("\n\n1. Inventory Report.\n2. Refill Inventory.\n3. Run Diagnostics.\n4. Back.\n");
		do {
			if (scanf("%d", &input) != 1 || input < 1 || input > 4) {
				printf("Invalid input, please enter an integer from 1 to 4.\n");
				while (getchar() != '\n'); // Clears the input buffer	
			}
		}while (input < 1 || input > 4);
		switch(input){
			case 1://inventory report
				printf("Inventory Report:\n\nI have %d Nuka Colas.\nI have %d BlamCo Mac and Cheese's.\n"
				"I have %d Cram Meatloafs.\nI have %d InstaMashes.\n\nBank Report:\n\nI have %d 1-cap coins.\n"
				"I have %d 2-cap coins.\n\nBusiness is good boss!\n\n",nuka,blamco,cram,mash,cap1,cap2);
				break;
			case 2://this enters the refill stage
				refilldone=false;//if we enter refill and exit it, refilldone is true, so next time we enter
				//refill, it will do nothing, so we reset it to false before we go in
				refill();
				break;
			case 3://this is just for show
				printf("\n\nSensor Diagnostics:      ||||||");
				sleep(1);
				printf("|||");
				sleep(2);
				printf("||||||");
				sleep(1);
				printf("|||||   OK!\n");
				sleep(1);
				printf("\nSprings Diagnostics:     ||||||||");
				sleep(1);
				printf("|||||");
				sleep(2);
				printf("|||||||   OK!\n");
				sleep(1);
				printf("\nElectronics Diagnostics: |||||||||||||");
				sleep(1);
				printf("|||||||   OK!\n");
				sleep(1);
				printf("\nInventory Diagnostics:   ||||");
				sleep(1);
				printf("|||");
				sleep(2);
				printf("||");
				sleep(1);
				printf("||||||");
				sleep(1);
				printf("|||||   OK!\n");
				sleep(1);
				printf("\nAll systems functional! As expected of me!\n\n");
				break;
			case 4://exits the admin menu
				printf("See ya later boss!\n\n");
				sleep(1);
				admindone=true;
				break;
			default://checks for bad inputs
				printf("That is not a command I recognize, try again!\n\n");
				
		}
		
	}
	system("cls");
	
}	
int main(){

	while(!exitgame){
		printf("Welcome to the Eat'o'tronic 3000! I live to fullfill all the humans' sustenance needs!\n"
		"Are you a customer or an administrator?\n\n");
		printf("1. Customer.\n2. Administrator.\n3. Exit.\n");
		correct_input=false;//this resets the boolean before we enter because when we leave for the first
		//time we set it to true
		while(!correct_input){
			scanf("%d",&input);
			while(getchar()!='\n');
			switch(input){
				case 1://the customer input
					customerdone=false;//resets the bool
					customer();//it goes in
					correct_input=true;//after it is done with the customer it breaks the while with this
					//and goes back up
					break;
				case 2://the admin input
					printf("Welcome Boss! It's not that I don't trust you or anything, but could you press in the\n"
					"admin code? Company policy and all that, you know... Sorry for the inconvenience!\n");
					scanf("%s",&passguess);//there is a password and the admin inputs it
					if(strncmp(passguess,adminpass,50)==0){//if it is good we enter the admin() function
						admindone=false;
						admin();
					}
					else printf("Ooh! So sorry but that is not the right answer boss!\n\n");
					correct_input=true;
					break;
				case 3://exit the machine input
					printf("Hope to see you again soon human!");
					exitgame=true;//breaks the while loop that this whole thing is in
					correct_input=true;//breaks the input loop
					break;
				default:
					printf("That is not a command I recognize, please try 1, 2, or 3!\n");
					//doesnt set correct_input to true, so it will return back up on a bad input
			}
		}
		
		
		
	}
}
