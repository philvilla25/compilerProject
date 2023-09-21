import java.util.Formatter;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * 
 */

/**
 * CET - CS Academic Level 3
 * This class contains the Searching Algorithms and Recursion
 * Student Name: Philogene Villanueva
 * Student Number:  041063813
 * Course: CST8130 - Data Structures
 * @author/Professor: James Mwangi PhD. 
 * 
  */
public class Vegetable extends FoodItem {

	private String farmName;

	/**
	 * Default Constructor
	 */
	public Vegetable() {
		super();
	}

	@Override
	/**
	 * Description: Override method addItem from superclass FoodItem Accepts,
	 * scanner parameter to let user input Vegetable Item values
	 * {@inheritDoc}
	 * @param Scanner scanner
	 * @return boolean value
	 */
	boolean addItem(Scanner scanner, boolean fromFile) {
		boolean added = true;
		boolean qflag = true;

		do {

			if (fromFile == false) {

				try {
					System.out.print("Enter the code for the item: ");// ask user for item code
					this.itemCode = scanner.nextInt();
					scanner.nextLine();

					System.out.print("Enter the name for the item: ");// ask user for item name
					this.itemName = scanner.nextLine();

					while (qflag) {// loops until user enters a correct quantity value
						try {

							System.out.print("Enter the quantity for the item: ");// ask user to enter item quantity
							this.itemQuantityinStock = scanner.nextInt();
							if (this.itemQuantityinStock > 0) {// checks if user inputs more than 0 value or positive
																// number
								qflag = false;// exit loop
							} else {
								System.out.println("Enter Positive Number");
							}

						} catch (InputMismatchException e) {// catch InputMismatch Exception
							System.out.println("Invalid Input");
							scanner.nextLine();
						}
					}
					qflag = true;// reinitialize qflag value

					while (qflag) {// loops until user enters a correct item cost
						try {
							System.out.print("Enter the cost of the item: ");
							this.itemCost = scanner.nextFloat();

							if (this.itemCost > -1) {// checks if user enter more than 0 cost
								qflag = false;
							} else {
								System.out.println("Enter Positive Number");
							}

						} catch (InputMismatchException e) {// catch exception for invalid inputs
							System.out.println("Invalid Input");
							scanner.nextLine();
						}

					}

					qflag = true;
					while (qflag) {// loops until user input correct price
						try {
							System.out.print("Enter the sales price of the item: ");
							this.itemPrice = scanner.nextFloat();
							scanner.nextLine();

							if (this.itemPrice > 0) {
								qflag = false;
							} else {
								System.out.println("Enter Positive Number");
							}

						} catch (InputMismatchException e) {// catch Invalid inputs
							System.out.println("Invalid Input");
							scanner.nextLine();
						}
					}

					System.out.print("Enter the name of the farm supplier: ");
					this.farm = scanner.nextLine();

					added = false;
					return true;
				} catch (InputMismatchException e) {// catch invalid exceptions
					System.out.println("Invalid Input");
					scanner.nextLine();
				}

			} else {

				// System.out.println("Naa kos vegetable" + scanner.nextLine());
				this.itemCode = Integer.parseInt(scanner.nextLine());
				this.itemName = scanner.nextLine();
				this.itemQuantityinStock = Integer.parseInt(scanner.nextLine());
				this.itemCost = Float.parseFloat(scanner.nextLine());
				this.itemPrice = Float.parseFloat(scanner.nextLine());
				this.farm = scanner.nextLine();
				return true;
			}

		} while (scanner.hasNextLine());

		return false;
	}

	/**
	 * Description: Print's values of the item and add farmName
	 * 
	 */
	public String toString() {

		return super.toString() + " Farm Supplier: " + farm;// calls super class FoodItem tostring method to print
															    // the values for an item
	}

	@Override
	/**
	 * Description: formats the output of the values inside the object
	 * {@inheritDoc}
	 * @param writer
	 */
	void outPutItem(Formatter writer) {
		writer.format("Item Code: %s %s %d price $%.2f cost $%.2f Farm Supplier: %s",
		        this.itemCode, this.itemName, this.itemQuantityinStock,
		        this.itemPrice, this.itemCost, farm);
		
		System.out.println(writer.toString());
		writer.close();
	}


}
