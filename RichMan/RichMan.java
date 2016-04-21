import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;

class RichMan extends JFrame implements Runnable
{
 ImageIcon[] play_imgs = new ImageIcon[4];
 Player[] player = new Player[4];  
 Player user;
 ArrayList playing = new ArrayList();
 boolean restart=false, is_user_active=true;
 int round;
 
 ClassLoader cl = this.getClass().getClassLoader();
 Toolkit tk = Toolkit.getDefaultToolkit();
 
 PlayInformation play_information = new PlayInformation();
 AudioClip clip = Applet.newAudioClip(cl.getResource("pattern/ting.au"));
 AudioClip back_music = Applet.newAudioClip(cl.getResource("pattern/music.mid"));
	
 JRadioButtonMenuItem music_on = new JRadioButtonMenuItem("開啟", true);
 JRadioButtonMenuItem music_off = new JRadioButtonMenuItem("關閉");

 Icon dice_icon = new ImageIcon(cl.getResource("pattern/dice.gif"));
 JButton dice = new JButton(dice_icon);

 int territory_size=24;
 Territory territory[] = new Territory[territory_size];
 Bank bank;

 public RichMan()
 {
  super("Taiwan RichMan");

  bank= new Bank(this);

  for(int i=0; i<play_imgs.length; i++) 		
   play_imgs[i]= new ImageIcon(cl.getResource("pattern/"+i+".gif"));		

  JPanel game_map_top = new JPanel();
  JPanel game_map_top1 = new JPanel();
  JPanel game_map_down = new JPanel();
  JPanel game_map_down1 = new JPanel();
  JPanel game_map_left = new JPanel();
  JPanel game_map_left1 = new JPanel();
  JPanel game_map_right = new JPanel();
  JPanel game_map_right1 = new JPanel();

  game_map_top.setLayout(new GridLayout(1, 7, 0, 0));
  game_map_down.setLayout(new GridLayout(1, 7, 0, 0));
  game_map_left.setLayout(new GridLayout(5, 1, 0, 0));
  game_map_right.setLayout(new GridLayout(5, 1, 0, 0));

  Vector vector = Script.loadTerritoryData();
  Hashtable table =null;
  String temp_name;
  int temp_price;
  
  for(int i=0; i<territory_size; i++)
  {
   table = (Hashtable) vector.get(i);

   temp_name= (String)table.get("name");
   temp_price =Integer.parseInt((String)table.get("price"));

   territory[i] = new Territory(i, temp_name, temp_price);

   if(i<=6)
    game_map_top.add(territory[i], BorderLayout.CENTER);
   else if(i>=7 && i<=11)
    game_map_right.add(territory[i], BorderLayout.CENTER);
   else if(i>=12 && i<=18)
   {
    game_map_down.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
    game_map_down.add(territory[i], BorderLayout.CENTER);
   }
   else if(i==23)
   {
    for(int z=23; z>=19; z--)
     game_map_left.add(territory[z], BorderLayout.CENTER);
   }
  }

  dice.setEnabled(false);
  dice.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     StartThread();
    }
   }
  );

  Box tt = Box.createHorizontalBox();
  tt.add(dice, BorderLayout.CENTER);
  tt.add(Box.createHorizontalStrut(10));

  Box game_map_center = Box.createVerticalBox();
  game_map_center.add(Box.createVerticalStrut(130));
  game_map_center.add(tt);
  game_map_center.add(Box.createVerticalStrut(30));
  game_map_center.add(play_information, BorderLayout.CENTER);
  game_map_center.add(Box.createVerticalStrut(24));

  game_map_top1.add(game_map_top, BorderLayout.CENTER);
  game_map_down1.add(game_map_down, BorderLayout.CENTER);
  game_map_left1.add(game_map_left, BorderLayout.CENTER);
  game_map_right1.add(game_map_right, BorderLayout.CENTER);

  Box game_map_center1 = Box.createHorizontalBox();

  game_map_center1.add(game_map_left1);
  game_map_center1.add(Box.createHorizontalStrut(105));
  game_map_center1.add(game_map_center);  
  game_map_center1.add(Box.createHorizontalStrut(92));
  game_map_center1.add(game_map_right1);

  JMenuBar menu = new JMenuBar();
  setJMenuBar(menu);

  JMenu game_menu = new JMenu("遊戲");
  menu.add(game_menu);
  JMenuItem start_game = new JMenuItem("重新開始");
  game_menu.add(start_game);
  start_game.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     startGame();
    }
   }
  );

  JMenuItem exit_game = new JMenuItem("離開遊戲");
  game_menu.add(exit_game);
  exit_game.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     System.exit(1);
    }
   }
  );

  JMenu music_menu = new JMenu("BGM");
  music_on.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     if(playing.size()!=0)
      back_music.loop();
    }
   }
  );

  music_off.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     back_music.stop();
    }
   }
  );

  ButtonGroup music_group = new ButtonGroup();
  music_group.add(music_on);
  music_group.add(music_off);
  music_menu.add(music_on);
  music_menu.add(music_off);
  menu.add(music_menu);

  JMenu about_menu = new JMenu("關於");
  JMenuItem about_game = new JMenuItem("遊戲");
  about_game.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     String message="這是一款陽春的大富翁\n"+
                    "Version: 1.0.0.5";
     showMessage("關於遊戲", message);
    }
   }
  );

  JMenuItem author = new JMenuItem("作者");
  author.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     String message="作者: 陶某人";
     showMessage("關於作者", message);
    }
   }
  );

  about_menu.add(about_game);
  about_menu.add(author);
  menu.add(about_menu);

  JPanel main_frame = new JPanel();
  main_frame.setLayout(new BorderLayout(0, -10));

  main_frame.add(game_map_top1, BorderLayout.NORTH);
  main_frame.add(game_map_down1, BorderLayout.SOUTH);
  main_frame.add(game_map_center1, BorderLayout.CENTER);
  
  getContentPane().add(main_frame, BorderLayout.SOUTH);

  setIconImage(tk.getImage(cl.getResource("pattern/dice.gif")));
  setResizable(false);
  setSize(436, 479);
  setVisible(true);
  setLocationRelativeTo(null);
 }

 public static void main(String[] str)
 {
  RichMan application = new RichMan();
  application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 }

 public void updatePlayerInformation()
 {
  play_information.update();
 }

 public Player getUserPlayer()
 {
  return user;
 }

 public void setUserPlayer(Player player)
 {
  user=player;
  bank.setOnBank(player);
 }

 public void showMessage(String title, String message)
 {
  JOptionPane.showMessageDialog(this, message, title, JOptionPane.PLAIN_MESSAGE, dice_icon); 
 }

 public int inputMessage(String title, String message)
 {
  return JOptionPane.showConfirmDialog(this, message, title, JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, dice_icon);                         
 }

 public void showTerritory(Player player)
 {
  ArrayList al= player.getTerritory(); 
  String message="";
  
  for(int i=0; i<al.size(); i++)
  {
   message=message+((Territory)al.get(i)).getTerritoryName()+", "+al.indexOf(al.get(i))+"\n";
  }

  showMessage(player.getPlayerName()+"土地資訊", message);
 }

 public void startGame()
 {
  is_user_active=true;
  round=0;
  playing.clear();

  if(music_on.isSelected())
   back_music.stop();

  final JDialog dialog = new JDialog(this, "選擇人物", true);
  dialog.setSize(160, 100);
  dialog.setResizable(false);

 // dialog.setUndecorated(true);
  dialog.setLocationRelativeTo(null);

  final JRadioButton[] choice = new JRadioButton[4];
  ButtonGroup choice_group = new ButtonGroup();
  JPanel choice_menu = new JPanel(); 
  for(int i=0; i<choice.length; i++)
  {
   choice[i] = new JRadioButton(i+1+"", play_imgs[i]);

   if(i==0)  
    choice[i].setSelected(true); 

   choice_menu.add(choice[i]);
   choice_group.add(choice[i]);
  }
  
  JButton select = new JButton("確定");
  JPanel select_menu = new JPanel(); 
  select_menu.add(select);
  select.addActionListener
  (
   new ActionListener() 
   { 
    public void actionPerformed(ActionEvent event)
    {  
     int x=1;
     Color color=Color.WHITE;

     for(int i=0; i<territory_size; i++)
     {
      territory[i].setInitial();

      if(i<=3)
      {
       switch(i)
       {
        case 0: color=Color.LIGHT_GRAY;
                break;

        case 1: color=Color.RED;
                break;

        case 2: color=Color.YELLOW;
                break;

        case 3: color=Color.GREEN;
                break;
       }

       if(choice[i].isSelected())
       {
        player[0] = new Player("玩家  ", play_imgs[i], 0 ,color);
        setUserPlayer(player[0]);
       }
       else
       {
        String name="電腦"+x;
        player[x] = new Player(name, play_imgs[i], x, color);
        x=x+1;
       }
      }
     }

     dialog.dispose();
     dice.setEnabled(true);

     for(int i=0; i<4; i++)
     {
      player[i].setInitial(); 
      territory[0].setOnTerritory(player[i].getPlayerIcon());
      playing.add(player[i]);
     }

     if(music_on.isSelected())
      back_music.loop();

     play_information.update();
    }
   }
  );

  dialog.getContentPane().add(choice_menu, BorderLayout.NORTH);
  dialog.getContentPane().add(select_menu, BorderLayout.CENTER);
  dialog.show();
 }

 private void runGame()
 {
  round=round+1;
  StartThread();
 }

 private void StartThread()
 {
  new Thread(this).start();
 }

 public void run()
 {
  int x=0; 

  try
  {
   if(is_user_active)
   {
    is_user_active=false;
    dice.setEnabled(false);
    x = (int)(Math.random()*6)+1;
    showMessage("骰點", "              骰子擲出"+x+"點");
    PlayerMove(user, x);
    PlayerCheck(user);    
   }
   else
   {
    for(int i=1; i<playing.size(); i++)
    {
     if(restart)
     {
      restart=false;
      return;
     }   

     Thread.sleep(800);

     x= (int)(Math.random()*6)+1;
      
     PlayerMove((Player)(playing.get(i)), x);
     PlayerCheck((Player)(playing.get(i)));
    }

    Thread.sleep(1000);
    dice.setEnabled(true);
    is_user_active=true;

    if(round%Bank.INTEREST_ROUND == 0)
     bank_interest();
   }
  }
  catch(InterruptedException ex)
  {
  }
 }

 private void PlayerMove(Player player, int moves)
 {
  try
  {
   int before_moves=0, move=0;

   for(int i=1; i<=moves; i++)
   {
    before_moves=player.getPlayerLocation();
    territory[before_moves].setLeaveTerritory(player.getPlayerIcon());

    move=(before_moves+1)%territory_size;
    territory[move].setOnTerritory(player.getPlayerIcon());
    player.setPlayerLocation(move);
    Thread.sleep(500);
   }
  }
  catch(InterruptedException ex)
  {
  }
 }

 private void PlayerCheck(Player check)
 {
  int location=check.getPlayerLocation();

  boolean is_user =check.isUser();

  int territory_price=territory[location].getTerritoryPrice();

  switch(territory[location].getTerritoryState())
  {
   case Territory.Free: if(is_user)
                        {
                         if(check.getMoney()>=territory_price)
                         {
                          int buycheck = inputMessage("購買訊息", "      你要購買這塊地方嗎?");

                          if(buycheck==0)
                           check.buyTerritory(territory[location]);
                         }
                        }
                        else
                        {
                         if( check.getMoney()-(1500+(int)(Math.random()*500)) >= territory_price)
                          check.buyTerritory(territory[location]);
                        }

                        break;

   case Territory.Own: if(territory[location].getTerritoryOwner()!=check)
                        payPassMoney(check, territory[location].getTerritoryPrice()/5);
                       else
                       {
                        if(territory[location].getTerritoryLevel()!=Territory.Top_Level)
                        {
                         if(is_user)
                         {
                          if(check.getMoney()>=territory_price/5)
                          {
                           int buycheck =  inputMessage("土地升級訊息", "      你要升級這塊地方嗎?");

                           if(buycheck==0)
                            territory[location].addTerritoryLevel();
                          }
                         }
                         else
                          if( check.getMoney()-(1500+(int)(Math.random()*500)) >= territory_price/5 )
                           territory[location].addTerritoryLevel();
                        }
                       }

                       break;

   case Territory.Special: switch(location)
                           {
                            case 6: chance(check);
                                    break;

                            case 18: if(is_user)
                                      bank.goBank();
                                     else
                                      bank.goBank(check);                                                                                     break;

                            default: break;
                           }
         
                           break;                     
  }

  play_information.update();

  if(is_user)
   runGame();
 }

 private void payPassMoney(Player player, int money)
 {
  int location=player.getPlayerLocation();
  int deposit=player.getDeposit();

  if(player.getMoney()<money)
  {
   if(deposit>0)
   {
    if(deposit>=money)
     player.setDeposit(-money);
    else
    {
     player.setDeposit(-deposit);

     if(player.getMoney()<money)
      sellTerritory(player, money);
    }
   }
   else
    sellTerritory(player, money);
  }
  
  if(restart)
    return;

  player.subMoney(money);

  if(territory[location].getTerritoryState()!=Territory.Special)
   territory[location].getTerritoryOwner().addMoney(money);
 }

 private void sellTerritory(Player seller, int pay_money)
 {
  int size=seller.getTerritory().size();
  
  if(size==0)
   OutofGame(seller);
  else
  {
   Territory sell=null;

   do
   {
    sell =(Territory)seller.getTerritory().get(0);

    seller.addMoney((sell.getTerritoryPrice())/2);
    seller.removeTerritory(0);
    size=size-1; 

    if(size==0 && seller.getMoney()<pay_money)
     OutofGame(seller);

   }while(seller.getMoney()<pay_money && size>0);
  }
 }

 private void chance(Player player)
 {
  String chance_message[] = new String[5]; 
  int x = (int)(Math.random()*5);

  switch(x)
  {
   case 0: chance_message[0]="得到獎金3000元";
           player.addMoney(3000);
           break;

   case 1: chance_message[1]="投資失敗，損失5000元";
           payPassMoney(player, 5000);
           break;

   case 2: chance_message[2]="沒有任何事發生";
           break;

   case 3: int size=player.getTerritory().size();

           if(size>0)
           {
            size=(int)(Math.random()*size);
            chance_message[3]=((Territory)player.getTerritory().get(size)).getTerritoryName()+"土地被充公";
            player.removeTerritory(size);
           }
           else
           {
            chance_message[3]="遇到流氓，被收保護費2000元";
            payPassMoney(player, 2000);
           }

           break;

   case 4: int money=0;
           int y = (int)(Math.random()*4);

           switch(y)
           {
            case 0: money=200;
                    break;

            case 1: money=1000;
                    break;

            case 2: money=10000;
                    break;

            case 3: money=30000;
                    break;
           }

           chance_message[4]="中樂透，獲得"+money+"元";
           player.addMoney(money);
           break;
  }

  showMessage("機會訊息", player.getPlayerName()+chance_message[x]); 
 }

 private void bank_interest()
 {
  String message="";

  for(int i=0; i<playing.size(); i++)
  {
   Player player=(Player)(playing.get(i));
   message=message+player.getPlayerName()+"得到利息: $"+Bank.calInterest(player)+"  存款總額為: $"+player.getDeposit()+"\n";
  }

  showMessage("銀行計息", message);
  play_information.update();
 }

 private void OutofGame(Player out)
 {
  int location=out.getPlayerLocation();
  territory[location].setLeaveTerritory(out.getPlayerIcon());
  playing.remove(playing.lastIndexOf(out));
  clip.play();

  showMessage("出局訊息", out.getPlayerName()+"出局了!!"); 

  if(out.getPlayerNo()==0 || playing.size()==1)
  {
   showMessage("訊息", "遊戲結束"); 
   restart=true;
   dice.setEnabled(false);
  }
 }

 private class PlayInformation extends JPanel
 {
  public void update()
  {
   repaint();
  }  
 
  public Dimension getPreferredSize() 
  { 
   return new Dimension(93, 67);
  }

  public Dimension getMinimumSize() 
  {
   return getPreferredSize();
  }
   
  public void paintComponent(Graphics g)
  {
   super.paintComponent(g);

   for(int i=0; i<playing.size(); i++)
   {
    Player player=(Player)(playing.get(i));
    String message=player.getPlayerName()+": $"+player.getMoney();
    player.getPlayerIcon().paintIcon(this, g, 3, 4+16*i);
    g.drawString(message, 15, 15+16*i);
   }
  }  
 }

}
