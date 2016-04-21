import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Bank implements ActionListener
{
 private RichMan game_main;
 private Player player; 

 public final static int INTEREST_ROUND=6; 

 private JButton[] button = new JButton[3];
 private String[] str = {"存款", "提款", "離開"};

 private JDialog dialog;
 private JLabel deposit;

 public Bank(RichMan game)
 {
  game_main=game;
  
  dialog = new JDialog(game_main, "銀行", true);
  dialog.setSize(220, 85);
  dialog.setResizable(false);
  dialog.setLocationRelativeTo(null);

  JPanel bank_menu = new JPanel(); 

  for(int i=0; i<button.length; i++)
  {
   button[i] = new JButton(str[i]);
   button[i].addActionListener(this);

   bank_menu.add(button[i]);
  }

  deposit = new JLabel();

  dialog.getContentPane().add(deposit, BorderLayout.NORTH);
  dialog.getContentPane().add(bank_menu, BorderLayout.CENTER);
 }

 private void showMessage(String title, String message)
 {
  JOptionPane.showMessageDialog(null, message, title, JOptionPane.PLAIN_MESSAGE); 
 }

 public void setOnBank(Player on)
 {
  player=on;
 }

 public static int calInterest(Player player)
 {
  int deposit_money=player.getDeposit();
  int interest = (int)(deposit_money*0.05);
  player.addInterest(interest);
  
  return interest;
 }

 public void actionPerformed(ActionEvent event)
 {
  if(event.getSource().equals(button[0]))
   deposit();
  else if(event.getSource().equals(button[1]))
   drawing();
  else
   dialog.dispose();
 }

 private void deposit()
 {
  if(player.getMoney()>0)
  {
   String money0=(String)JOptionPane.showInputDialog(game_main, "請輸入存款金額", "存款", JOptionPane.PLAIN_MESSAGE);

   if(money0!=null)
   {
    try
    {
     int money=Integer.parseInt(money0);
          
     if(money<=player.getMoney())
     {
      player.setDeposit(money);

      deposit.setText("     你目前的存款: $"+player.getDeposit());
      game_main.updatePlayerInformation();
     }
     else
      showMessage("錯誤訊息", "存款金額不可大於身上擁有金額");
    }
    catch(NumberFormatException ex)
    {
     showMessage("錯誤訊息", "請輸入數字");
    }
   }
  }
  else
   showMessage("錯誤訊息", "你身上現在沒有金額"); 
 }

 private void drawing()
 {
  if(player.getDeposit()>0)
  {
   String money0=(String)JOptionPane.showInputDialog(null, "請輸入提款金額", "提款", JOptionPane.PLAIN_MESSAGE);

   if(money0 != null)
   {
    try
    {
     int money=Integer.parseInt(money0);
          
     if(money<=player.getDeposit())
     {
      player.setDeposit(-money);
      deposit.setText("     你目前的存款: $"+player.getDeposit());
      game_main.updatePlayerInformation();
     }
     else
      showMessage("錯誤訊息", "提款金額不可大於銀行存款金額");
    }
    catch(NumberFormatException ex)
    {
     showMessage("錯誤訊息", "請輸入數字");
    }
   }
  }
  else
   showMessage("錯誤訊息", "你現在在銀行中沒有存款"); 
 }

 // for user player
 public void goBank()
 {
  deposit.setText("     你目前的存款: $"+player.getDeposit());
  dialog.show();
 }

 // for computer player
 public void goBank(Player player)
 {
  int money=player.getMoney();
  int deposit=player.getDeposit();
  int size=player.getTerritory().size();

  if(money>=5000)
  {
   if(size>=4)
    player.setDeposit(money/2);
   else
    return;
  }
  else 
  {
   if(deposit>=5000)
    player.setDeposit(-3000);
   else
    player.setDeposit(-deposit*2/3);
  }

  game_main.updatePlayerInformation();
 }

}