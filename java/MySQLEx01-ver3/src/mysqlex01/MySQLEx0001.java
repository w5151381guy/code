/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mysqlex01;

import com.mysql.jdbc.CommunicationsException;
import com.mysql.jdbc.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;

/**
 *
 * @author user
 */
public class MySQLEx0001 {

    private Connection conn = null;
    private Statement stmt = null;
    private ResultSet rs = null;
    private String SQLStr = null; //query SQL string

    private config con = new config(); //configulation object

    /**
     * @param args the command line arguments
     */
    public MySQLEx0001() {

        //建立連線
        //"jdbc:mysql://140.138.77.98/javaclass?user=javateam&password=YZUJavateam2015"
        String connectionStr = "jdbc:mysql://" + con.getUrlstr() + "/javaclass?user=" + con.getUserStr() + "&password=" + con.getPwStr();
        try {
            conn = (Connection) DriverManager.getConnection(connectionStr);
            System.out.println(" Database Connected !");

            //Query 
            SQLStr = "select * from pan_pet limit 100";
            stmt = conn.createStatement(); //建立執行狀態
            rs = stmt.executeQuery(SQLStr); //執行SQL
            ResultSetMetaData metaData = rs.getMetaData(); //取出meta data           
            int numCol = metaData.getColumnCount(); //取出欄位
            System.out.println(" Column Number : " + numCol);

            //Print Out All Column Name           
            for (int i = 1; i <= numCol; i++) {
                System.out.println(" Column Name " + i + " : " + metaData.getColumnName(i));
            }

            System.out.println("\n[ Query Result ]");

            //Print out Column Title
            System.out.print("RowNum.\t");
            for (int i = 1; i <= numCol; i++) {
                System.out.print(metaData.getColumnName(i) + "\t");
            }
            System.out.println();

            //print out query result
            int rowNum = 1;
            while (rs.next()) {

                System.out.print(rowNum + ".\t");
                for (int i = 1; i <= numCol; i++) {
                    System.out.print(rs.getObject(i) + "\t");
                }
                System.out.println();
                rowNum++;
            }
            //close connection
            rs.close();
            stmt.close();
            conn.close();

       } catch (SQLException ex) {
            // handle any errors
            System.out.println("SQLException: " + ex.getMessage());
            System.out.println("SQLState: " + ex.getSQLState());
            System.out.println("VendorError: " + ex.getErrorCode());
        } finally {
            // it is a good idea to release
            // resources in a finally{} block
            // in reverse-order of their creation
            // if they are no-longer needed

            if (rs != null) {
                try {
                    rs.close();
                } catch (SQLException sqlEx) {
                } // ignore

                rs = null;
            }

            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException sqlEx) {
                } // ignore

                stmt = null;
            }
        }

    }

    public static void main(String[] args) {
        // TODO code application logic here

        MySQLEx0001 app = new MySQLEx0001();
    }

}
