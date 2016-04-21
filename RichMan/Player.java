import java.util.*;
import java.awt.*;
import javax.swing.*;

public class Player
{
 private String name;
 private int no, money, deposit_money, location;
 private ArrayList territory = new ArrayList();
 private ImageIcon icon;
 private Color color;

 public Player(String player_name, ImageIcon img, int player_no , Color c)
 {
  name=player_name;
  icon=img;
  no=player_no;
  color=c;
 } 

 public String getPlayerName()
 {
  return name;
 }

 public ImageIcon getPlayerIcon()
 {
  return icon;
 }

 public Color getPlayerColor()
 {
  return color;
 }
 
 public boolean isUser()
 {
  if(no==0)
   return true;
  else 
   return false;
 }

 public int getPlayerNo()
 {
  return no;
 }

 public int getPlayerLocation()
 {
  return location;
 }

 public void setPlayerLocation(int new_location)
 {
  location=new_location;
 }

 public int getMoney()
 {
  return money;
 }

 public void addMoney(int add)
 {
  money=money+add;
 }
 
 public void subMoney(int sub)
 {
  money=money-sub;
 }

 public ArrayList getTerritory()
 {
  return territory;
 }
  
 public void buyTerritory(Territory add)
 {
  add.setTerritoryOwner(this);
  territory.add(add);
  money=money-add.getTerritoryPrice(); 
 }

 public void removeTerritory(Territory remove)
 {
  territory.remove(remove);
  remove.removeTerritoryOwner(); 
 }

 public void removeTerritory(int index)
 {
  ((Territory)territory.get(index)).removeTerritoryOwner(); 
  territory.remove(index);
 }

 public void setDeposit(int deposit)
 {
  deposit_money=deposit_money+deposit;
  money=money-deposit;
 }

 public void addInterest(int interest)
 {
  deposit_money=deposit_money+interest;
 }

 public int getDeposit()
 {
  return deposit_money;
 }

 public void setInitial() 
 { 
  money=20000; 
  deposit_money=0;
  location=0;
 }

} 
