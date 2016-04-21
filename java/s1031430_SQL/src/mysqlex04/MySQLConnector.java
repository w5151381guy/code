/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mysqlex04;

import com.mysql.jdbc.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;

/**
 *
 * @author YZU-PAN
 */
public class MySQLConnector {

    //login
    
    private config con = new config(); //configulation object


    String connStr = null;
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    ResultSetMetaData metaData = null;
    StringBuffer ResultSB = new StringBuffer();

    
    
    
    public MySQLConnector(String inHost, String inAcc, String inPW , String inDB) {
        
        con.setDBName(inDB);
        con.setPwStr(inPW);
        con.setUrlstr(inHost);
        con.setUserStr(inAcc);
        
        
 

    }

    public int connectDB() {
        try {
            //conn = (Connection) DriverManager.getConnection("jdbc:mysql://140.138.77.98/javaclass?user=javateam&password=YZUJavateam2015");
            connStr = "jdbc:mysql://" + con.getUrlstr() + "/" + con.getDBName() + "?user=" + con.getUserStr() + "&password=" + con.getPwStr();
            conn = (Connection) DriverManager.getConnection(connStr);
        } catch (SQLException ex) {
            // handle any errors
            System.out.println("SQLException: " + ex.getMessage());
            System.out.println("SQLState: " + ex.getSQLState());
            System.out.println("VendorError: " + ex.getErrorCode());
            return -1;  //若錯誤回傳-1
        }

        return 1;

    }

    public void doQuery(String SQLstr) {
        try {

            String SQL = SQLstr;
           
            //清空result
            ResultSB.delete(0, ResultSB.length());

            stmt = conn.createStatement();
            rs = stmt.executeQuery(SQL);
            metaData = rs.getMetaData(); //取出meta data
            int numCol = metaData.getColumnCount();

            for (int i = 1; i <= numCol; i++) {
                System.out.print("\t" + metaData.getColumnName(i));
                ResultSB.append("\t" + metaData.getColumnName(i));
            }
            System.out.println();
            ResultSB.append("\n");

            //print out detail
            while (rs.next()) {
                for (int i = 1; i <= numCol; i++) {
                    System.out.print("\t" + rs.getObject(i));
                    ResultSB.append("\t" + rs.getObject(i));
                }
                System.out.println();
                ResultSB.append("\n");
                //System.out.println(rs.getString(3) + ", ");

            }

            rs.close();
            stmt.close();

            // Now do something with the ResultSet ....
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

    public StringBuffer getResultString() {
        return this.ResultSB;
    }

    public ResultSetMetaData getMetaData() {
        return this.metaData;
    }

    public ResultSet getResultSet() {
        return this.rs;
    }

}
