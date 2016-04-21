/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mysqlex04;

/**
 *
 * @author user
 */
public class config {
    /*
     private String  urlstr = "140.138.77.98";
     private String userStr= "javateam";
     private String pwStr= "YZUJavateam2015";
     */

    private String urlstr;
    private String userStr;
    private String pwStr;
    private String DBName;

    public String getUrlstr() {
        return urlstr;
    }

    public String getUserStr() {
        return userStr;
    }

    public String getPwStr() {
        return pwStr;
    }

    public void setUrlstr(String urlstr) {
        this.urlstr = urlstr;
    }

    public void setUserStr(String userStr) {
        this.userStr = userStr;
    }

    public void setPwStr(String pwStr) {
        this.pwStr = pwStr;
    }

    public String getDBName() {
        return DBName;
    }

    public void setDBName(String DBName) {
        this.DBName = DBName;
    }

}
