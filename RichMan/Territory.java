import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class Territory extends JPanel
{
 private int territory_no, territory_price, territory_level;
 private String territory_name; 
 private Player territory_owner;
 private int territory_state;
 private ArrayList on_territory = new ArrayList();
 private int _paint_loc=20;

 public static final int Free=0;
 public static final int Own=1;
 public static final int Special=2;
 static final int Top_Level=3;

 public Territory(int no, String name, int price)
 {
  super(true); // for DoubleBuffer

  territory_no=no;
  territory_name=name;
  territory_price=price;
  
  if(territory_name.length()==4)
  	  _paint_loc=8;
  
  if(territory_no==0 || territory_no==6 || territory_no==12 || territory_no==18)
   territory_state=Special;
  else
   territory_state=Free;
  
   setBorder(BorderFactory.createEtchedBorder(EtchedBorder.LOWERED));
 }

 public Dimension getPreferredSize() 
 { 
  return new Dimension(60, 60);
 }

 public Dimension getMinimumSize() 
 {
  return getPreferredSize();
 }

 public void setTerritoryOwner(Player owner) 
 { 
  territory_owner=owner; 
  territory_state=Own;
  repaint();
 }

 public Player getTerritoryOwner() 
 { 
  return territory_owner; 
 }

 public void removeTerritoryOwner() 
 { 
  territory_owner=null;
  territory_state=Free;
  territory_level=0;
  repaint();
 }

 public void setOnTerritory(ImageIcon on) 
 { 
  on_territory.add(on);
  repaint(); 
 }

 public void setLeaveTerritory(ImageIcon leave) 
 { 
  on_territory.remove(on_territory.lastIndexOf(leave));
  repaint(); 
 }

 public int getTerritoryNO() 
 {
  return territory_no; 
 }

 public String getTerritoryName() 
 {
  return territory_name; 
 }

 public int getTerritoryPrice() 
 {
  return territory_price+territory_level*500; 
 }

 public int getTerritoryState() 
 {
  return territory_state; 
 }

 public int getTerritoryLevel() 
 {
  return territory_level; 
 }

 public void addTerritoryLevel() 
 {
  territory_owner.subMoney(getTerritoryPrice()/5);
  territory_level=territory_level+1;
  repaint();
 }

 public void setInitial() 
 { 
  territory_owner=null;
  territory_level=0;
  on_territory.clear();
 
  if(territory_no==0 || territory_no==6 || territory_no==12 || territory_no==18)
   territory_state=Special;
  else
   territory_state=Free;

  repaint(); 
 }
   
 public void paintComponent(Graphics g)
 {
  super.paintComponent(g);
  g.drawRect(0, 0, 59, 59);
  
  if(territory_price!=0)
   	g.drawString("$"+territory_price, 23, 55); 
   
  if(!on_territory.isEmpty())
  {
   for(int i=0; i<on_territory.size(); i++)
    ((ImageIcon)(on_territory.get(i))).paintIcon(this, g, 3+15*i, 5);
  }
  

  switch(territory_state)
  {
    case Free:  setBackground(Color.WHITE);
                break;
                
    case Own:   setBackground(territory_owner.getPlayerColor());
   				g.drawString("Lv"+territory_level, 2, 55); 
    			break;
    
    case Special: setBackground(Color.WHITE);
    			  g.setColor(Color.BLUE);
    			  break;
  }

  g.drawString(territory_name, _paint_loc, 35); 
 }  

}