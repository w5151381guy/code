package figureEX;
public class triangle{

    public triangle(){}

    public void triangleImage(){
      int i=1;
      while(i<=5){
        int j=0;
        while(j<i){
          System.out.print("*");
          j++;
        }
        System.out.printf("%n");
        i++;
      }
    }
}
