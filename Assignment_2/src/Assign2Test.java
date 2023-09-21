import java.util.InputMismatchException;
import java.util.Scanner;



/**
 * CET - CS Academic Level 3
 * This class contains the Searching Algorithms and Recursion
 * Student Name: Philogene Villanueva
 * Student Number:  041063813
 * Course: CST8130 - Data Structures
 * @author/Professor: James Mwangi PhD. 
 * 
  */
public class Assign2Test {

	/**
	 * Description: Displays Main menu, ask user to input choice and handles user choice
	 */
	public static void displayMenu() {
		int userInput;
		Scanner input = new Scanner(System.in);
		boolean flag = true;
		boolean buyOrSell = true;
		Inventory invent = new Inventory();

		while (flag) {
			try {

				System.out.println("Please select one of the following");
				System.out.println("1. Add Item to Inventory");
				System.out.println("2. Display Current Inventory");
				System.out.println("3. Buy Item(s)");
				System.out.println("4. Sell Item(s)");
				System.out.println("5. Search for Item");
				System.out.println("6. Save Inventory to File");
				System.out.println("7. Read Inventory from File");
				System.out.println("8. To Exit");
				System.out.print(">");
				userInput = input.nextInt();
				input.nextLine();
				if (userInput >= 1 && userInput <= 8) {

					switch (userInput) {
					case 1:

						invent.addItem(input, false);//call Inventory addItem method to add an Object and it's values
						break;

					case 2:
						invent.toString();//calls tostring method of Inventory class to iterate through List of objects and display
						break;
					case 3:
						buyOrSell = true;//sets buyOrSell variable to true if user choice is 3, Buy
						invent.updateQuantity(input, buyOrSell);//call updateQuantity of Inventory class to update item quantity by buying
						break;

					case 4:
						buyOrSell = false;//sets buyOrSell variable to false if user choice is 4, Sell
						invent.updateQuantity(input, buyOrSell);//call updateQuantity of Inventory class to update item quantity by selling
						break;
					case 5: 
						int ret;
						ret = invent.searchForItem(input);//let's user search for the item via item code
						if(ret == -1) {
							System.out.println("Code not found in Inventory...");
						}
						break;
					
					case 6:
						invent.saveToFile(input);//let's user save all the items inside the current inventory
						break;
						
					case 7: 
						invent.readToFile(input);//let's user read and save data inside a text file
						break; 
						
					case 8:
						flag = false;
						System.out.println("Exiting");//exits program
						break;
					}

				} else {
					System.out.println("...Invalid input, please try again...");//prints invalid input if user inputs out side menu range
				}

			} catch (InputMismatchException e) {//catch invalid inputs by user
				System.out.println("...Invalid input, please try again...");
				input.nextLine();
			}
		}
		input.close();
	}

	/** 
	 * Description: calls display method and will display the menu to the user
	 *
	 */
	public static void main(String[] args) {

		displayMenu();

	}
}
