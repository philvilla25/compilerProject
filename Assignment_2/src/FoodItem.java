import java.util.Comparator;
import java.util.Formatter;
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
public abstract class FoodItem implements Comparable<FoodItem>{
	
	protected int itemCode;
	protected String itemName;
	protected float itemPrice;
	protected int itemQuantityinStock;	
	protected float itemCost;
	protected String farm;
	protected float sizeJar = 0;
	
	/**
	 * Default Constructor
	 */
	public FoodItem() {}
	
	/**
	 * Description: Parameterized Constructor
	 * @param int itemQuantityinStock, int itemCost, String itemName, float itemPrice
	 *
	 */
	public FoodItem(int itemCode, int itemQuantityinStock, int itemCost, String itemName, float itemPrice) {
		super();
		this.itemCode = itemCode;
		this.itemName = itemName;
		this.itemPrice = itemPrice;
		this.itemQuantityinStock = itemQuantityinStock;
		this.itemCost = itemCost;
	}

	
	/**
	 * Description: returns Item Code value
	 * @return the itemCode
	 */
	public int getItemCode() {
		return itemCode;
	}

	/**
	 * Description: returns item name value
	 * @return the itemName
	 */
	public String getItemName() {
		return itemName;
	}

	/**
	 * Description: returns item price value
	 * @return the itemPrice
	 */
	public float getItemPrice() {
		return itemPrice;
	}

	/**
	 * Description: return item quantity
	 * @return the itemQuantityinStock
	 */
	public int getItemQuantityinStock() {
		return itemQuantityinStock;
	}

	

	/**
	 * Description: return item cost value
	 * @return the itemCost
	 */
	public float getItemCost() {
		return itemCost;
	}

	/**
	 * Description: set's item cost value
	 * @param itemCost the itemCost to set
	 */
	public void setItemCost(float itemCost) {
		this.itemCost = itemCost;
	}

	/**
	 * Description: set's item code value
	 * @param itemCode the itemCode to set
	 */
	public void setItemCode(int itemCode) {
		this.itemCode = itemCode;
	}

	/**
	 * Description: set's item name value
	 * @param itemName the itemName to set
	 */
	public void setItemName(String itemName) {
		this.itemName = itemName;
	}

	/**
	 * Description: set's item price value
	 * @param itemPrice the itemPrice to set
	 */
	public void setItemPrice(float itemPrice) {
		this.itemPrice = itemPrice;
	}

	/**
	 * Description: set's item quantity value
	 * @param itemQuantityinStock the itemQuantityinStock to set
	 */
	public void setItemQuantityinStock(int itemQuantityinStock) {
		this.itemQuantityinStock = itemQuantityinStock;
	}

	/**
	 * Description: set's item cost value
	 * @param itemCost the itemCost to set
	 */
	public void setItemCost(int itemCost) {
		this.itemCost = itemCost;
	}

	/**
	 * Description: print's all the values of the item
	 * 
	 * @return print's values inside array
	 */
	public String toString() {
		
		return "Item Code: " + this.itemCode + " "+ this.itemName + " "+ this.itemQuantityinStock + " " + "price $" + this.itemPrice + " " + "cost $" + this.itemCost;
	}
	
	/**
	 * Description: formats the output of the values inside the object
	 * @param writer
	 */
	abstract void outPutItem(Formatter writer);
		

	/**
	 * Description: abstract method to be implemented by sub class how to add item
	 * @param scanner
	 * @return boolean value
	 * {@inheritDoc}
	 */
	abstract boolean addItem(Scanner scanner, boolean fromFile);
		
		

	/**
	 * Description: updateItem method set's the value of ItemQuantity
	 * takes in the amount to be added(buy) or subtracted(sell)
	 * @param integer amount
	 * @return boolean
	 */
	public boolean updateItem(int amount) {
		
		setItemQuantityinStock(amount);//set's item quantity
		
		return false;
	}
	
	@Override
	/**
	 * Description: implements compareTo method by comparable interface, compares item codes
	 * @return an integer of 0 for true other number for false
	 */
	public int compareTo(FoodItem o) {
		// TODO Auto-generated method stub
		return this.itemCode - o.itemCode;
	}

	/**
	 * Description: gets the value of Farm
	 * @return the farm
	 */
	public String getFarm() {
		return farm;
	}

	/**
	 * Description: set's value of farm variable
	 * @param farm the farm to set
	 */
	public void setFarm(String farm) {
		this.farm = farm;
	}

	/**
	 * Description: gets the jar size 
	 * @return the jarSize
	 */
	public float getJarSize() {
		return sizeJar;
	}

	/**
	 * Description: set's jar size
	 * @param jarSize the jarSize to set
	 */
	public void setJarSize(float jarSize) {
		this.sizeJar = jarSize;
	}
	
}
