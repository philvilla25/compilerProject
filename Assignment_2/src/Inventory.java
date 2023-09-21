import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.Scanner;
import java.io.File;

/**
 * CET - CS Academic Level 3
 * This class contains the Searching Algorithms and Recursion
 * Student Name: Philogene Villanueva
 * Student Number:  041063813
 * Course: CST8130 - Data Structures
 * @author/Professor: James Mwangi PhD. 
 * 
  */
public class Inventory{

	
	ArrayList<FoodItem> food = new ArrayList<FoodItem>();// List with FoodItem object as parameter
	private int numItems;
	private FoodItem[] inventory;
	
	/*
	 * Default Inventory
	 */
	public Inventory() {
	}

	/**
	 * Description: takes on a scanner parameter to let user input choice from the
	 * options fruit, vegetable or preserve
	 * 
	 * @param scanner
	 * @return
	 */
	public boolean addItem(Scanner scanner, boolean fromFile) {
		boolean status = true;
		String input;

		if (food.size() == 20) {//just checks if arraylist size is 20 and doesn't accept anymore
			return false;
		}

		do {

			try {

				if (fromFile == false) {//checks if item is being added a file or user input

					System.out.print("Do you wish to add a fruit(f), vegetable(v), preserve(p), coffee(c) ?");
				}

				input = scanner.nextLine();
				if (input.contains("f")) {// if user choice is f initialize fruit class
					int match;
					boolean ret = false;
					Fruit fr = new Fruit();// initialize Fruit Object

					ret = fr.addItem(scanner, fromFile);// call fruit class add item method to let user input item
														// values, return
														// true if successful, false if not

					if (ret) {// if return true
						match = alreadyExist(fr.itemCode);// check if item already exist, calls already exist method
															// return 1 if code has match

						if (match >= 0) {// if item exist print item already exist
							System.out.println("Item Code: " + fr.itemCode +" Item Already Exist");
						} else {// else
							food.add(fr);// call arraylist food and instance object of fruit
							if (fromFile == false) {
								break;
							}
						}

					}

				} else if (input.contains("v")) {// if user choice is f initialize fruit class
					Vegetable veg = new Vegetable();// initialize vegetable object
					int matchVeg;
					boolean retVeg;

					retVeg = veg.addItem(scanner, fromFile);// call add item of vegetable method with scanner parameter

					if (retVeg) {// if returns true
						matchVeg = alreadyExist(veg.itemCode);// checks if item code already exist calls alreadyExist
																// method

						if (matchVeg >= 0) {// if returns more than 0 equal to zero then item already exist
							System.out.println("Item Code: " + veg.itemCode +" Item Already Exist");
						} else {
							food.add(veg);// else adds the object instance to Arraylist food
							if (fromFile == false) {
								break;
							}
						}
					}

				} else if (input.contains("p")) {// if user choice is p initialize preserve class
					Preserve pres = new Preserve();// initialize preserve object
					int matchPres;
					boolean presRet;

					presRet = pres.addItem(scanner, fromFile);// call add item of preserve method with scanner parameter

					if (presRet) {
						matchPres = alreadyExist(pres.itemCode);// checks if item code already exist calls alreadyExist
																// method

						if (matchPres >= 0) {// if returns more than 0 equal to zero then item already exist
							System.out.println("Item Code: " + pres.itemCode + " Item Already Exist");
						} else {
							food.add(pres);// else adds the object instance to arraylist food
							if (fromFile == false) {
								break;
							}

						}

					}

				} else if (input.contains("c")) {// if user choice is c initialize coffee class
					Coffee coffee = new Coffee();// initialize coffee object
					int matchPres;
					boolean presRet;

					presRet = coffee.addItem(scanner, fromFile);// call add item of coffee method with scanner parameter
					if (presRet) {
						matchPres = alreadyExist(coffee.itemCode);// checks if item code already exist calls
																	// alreadyExist method

						if (matchPres >= 0) {
							System.out.println("Item Code: "+ coffee.itemCode + " Item Already Exist");// if returns more than 0 equal to zero then item
																		// already exist
						} else {
							food.add(coffee);// else adds the object instance to arraylist food
							if (fromFile == false) {
								break;
							}

						}

					}

				} 

			} catch (InputMismatchException e) {// catches invalid inputs
				System.out.println("Invalid Entry");
				scanner.nextLine();
			}

		} while (scanner.hasNextLine());

		Collections.sort(food);
		
		return status;
	}

	
	@SuppressWarnings("javadoc")
	/**
	 * Description: Iterate ArrayList food using Collection Iterator and prints object
	 * @return returns an emptry string
	 */
	public String toString() {

		System.out.println("Inventory: ");

		Iterator<FoodItem> foodIterate = food.iterator();//calls iterator Class to iterate on all the Objects inside Arraylist food
		while (foodIterate.hasNext()) {
			System.out.println(foodIterate.next());
		}
		return "";
	}

	/**
	 * Description: iterates the whole arraylist to check if itemcode exist
	 * @param itemCode
	 * @return the index of where the itemcode was found inside the List
	 */
	public int alreadyExist(int itemCode) {

		for (int i = 0; i < food.size(); i++) {
			if (food.get(i).getItemCode() == itemCode) {
				return i;//returns index if item code was found
			}
		}

		return -1;//returns -1 if nothing was found
	}
	
	
	/**
	 * Description: ask user for an item code and search for the item inside the current inventory
	 * @param scanner
	 * @return
	 */
	public int searchForItem(Scanner scanner) {
		int itemCode;
		
		try {
		System.out.print("Enter the code for the item: ");
		itemCode = scanner.nextInt();
		
		for (int i = 0; i < food.size(); i++) {
			if (food.get(i).getItemCode() == itemCode) {
				 System.out.println(food.get(i));
				 return 1;
			}
		}
		}catch(InputMismatchException e) {
			System.out.println("Please input an integer");
		}
		return -1;//returns -1 if nothing was found
	}
	

	/**
	 * Description: updateQuantity method accepts the buy or sell feature, and peforms updating the itemquantity value
	 * determines the current item quantity and performs subtraction if user choice is to sell and addition if user choice is to buy
	 * @param scanner
	 * @param buyOrSell
	 * @return boolean true if updating was successful or not
	 */
	public boolean updateQuantity(Scanner scanner, boolean buyOrSell) {
		int itemCode;
		int quantity;
		boolean flag = true;

		if (buyOrSell == true && food.size() > 0) {//checks if user choice is buy or sell and if inventory is empty or not

			while (flag) {
				try {
					System.out.print("Enter the code for the item: ");//ask user to input item code of item to update
					itemCode = scanner.nextInt();

					for (int i = 0; i < food.size(); i++) {

						if (food.get(i).getItemCode() == itemCode) {//checks if item exist

							System.out.print("Enter valid quantity to buy: ");//if item exist ask user for quantity to buy
							quantity = scanner.nextInt();

							if (quantity >= 0) {//checks user input for quantity should be more than zero
								quantity = food.get(i).getItemQuantityinStock() + quantity;//updates item quantity
								food.get(i).setItemQuantityinStock(quantity);//calls FoodItem setter method to set updated item quantity
								flag = false;//exits loop
								return true;//returns true for successful update
							} else {
								System.out.println("Invalid Quantity");//prints if user inputs less than zero 
								scanner.nextLine();
							}
						} else if (i == food.size() - 1 && food.get(i).getItemCode() != itemCode) {//checks if done iterating and item code wasn't found

							System.out.println("Error...could not buy item");
							flag = false;

						}
					}

				} catch (InputMismatchException e) {//catch invalid inputs 
					System.out.println("Invalid Item Code");
					scanner.nextLine();
				}
			}

		} else if (buyOrSell == false && food.size() > 0) {//checks if user choice is buy or sell and if inventory is empty or not
			flag = true;

			while (flag) {
				try {
					System.out.print("Enter the code for the item: ");//ask user to input item code of item to update
					itemCode = scanner.nextInt();

					for (int i = 0; i < food.size(); i++) {

						if (food.get(i).getItemCode() == itemCode) {//checks if item exist

							System.out.print("Enter valid quantity to sell: ");//if item exist ask user for quantity to buy
							quantity = scanner.nextInt();

							if (quantity >= 0 && quantity <= food.get(i).getItemQuantityinStock()) {//checks user input for quantity should be more than zero
																									// and if quantity inputted by user is not more than the current quantity of item
								quantity = food.get(i).getItemQuantityinStock() - quantity;//subtracts the quantity inputted by user with the current item quantity
								food.get(i).setItemQuantityinStock(quantity);//calls setter method to update item quantity of Object
								flag = false;
								return true;

							} else {
								System.out.println("Error...could not sell item");
								scanner.nextLine();
								flag = false;
								break;
							}
						} else if (i == food.size() - 1 && food.get(i).getItemCode() != itemCode) {//checks if done iterating and item code wasn't found

							System.out.println("Error...could not buy item");
							flag = false;

						}
					}

				} catch (InputMismatchException e) {//handles invalid inputs by user 
					System.out.println("Invalid Item Code");
					scanner.nextLine();
				}
			}
		} else {
			if (buyOrSell == true) {
				System.out.println("Error...could not buy item");
			} else
				System.out.println("Error...could not sell item");
		}

		return false;
	}

	/**
	 * Description: saves the current inventory to file created by the user
	 * @param takes on the Scanner
	 * @return void
	 */
	public void saveToFile(Scanner scanner) {
		String textFile;
		
		System.out.print("Name of the file to save to: ");
		textFile = scanner.nextLine();
		String filePath = "C:/AlgonquinSubjects/CST8130_DataStructures/Assignment2/"+textFile;//concatenates user's desired filename to the base file location
		
		try {
		PrintWriter writeOut = new PrintWriter(filePath);//initialize PrintWriter class with the filePath parameter
		
		for (FoodItem item : food) {
			
			if(item.getClass().equals(Fruit.class)) {//checks what's the class 
				writeOut.println("f");//and writes f for fruit
				
			}else if(item.getClass().equals(Vegetable.class)) {//checks what's the class 
				writeOut.println("v");//and writes v for vegetables
			}else if(item.getClass().equals(Preserve.class)) {//checks what's the class 
				writeOut.println("p");//and writes p for preserve
			}else if(item.getClass().equals(Coffee.class)) {//checks what's the class 
				writeOut.println("c");//c for coffee
			}
		    writeOut.println(item.getItemCode());
		    writeOut.println(item.getItemName());
		    writeOut.println(item.getItemQuantityinStock());
		    writeOut.println(item.getItemCost());
		    writeOut.println(item.getItemPrice());
		   
		    if(item.sizeJar != 0) {
		    	writeOut.println(item.getJarSize());	
		    }
		    else if(item.farm != null) {
		    	writeOut.println(item.getFarm());	
		    }
		    
		    writeOut.println();
		}
		
		writeOut.close();
		
		}catch(FileNotFoundException e) {
			System.out.println("File not found");
		}
	}

	
	/**
	 * Description: reads value from a file then store or add the value inside the current inventory arraylist
	 * @return void
	 */
	public void readToFile(Scanner scanner){
		String textFile;
		
		System.out.print("Name of the file to read from : ");
		textFile = scanner.nextLine();
	
		String filePath = "C:/AlgonquinSubjects/CST8130_DataStructures/Assignment2/"+textFile; //concatenates filePath with the inputted text file name from the user
		
		try {
		
		File file = new File(filePath); //initialize file class
		Scanner fileScanner = new Scanner(file);
		addItem(fileScanner, true);//calls method add item to add the values inside the arraylist

		}catch(IOException  e) {
			System.out.println("No file found");
		}
		
	}
}
