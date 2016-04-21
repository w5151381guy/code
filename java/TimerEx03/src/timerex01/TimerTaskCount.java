/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package timerex01;

import java.util.Date;
import java.util.TimerTask;
import javax.swing.JTextField;

/**
 *
 * @author PAN
 */
public class TimerTaskCount extends TimerTask {

    private String taskName = "";
    private JTextField JTF = null;

    public TimerTaskCount(String inTaskName, JTextField inJTF) {
        this.taskName = inTaskName;
        //JTF = inJTF;
    }
    
    

    @Override
    public void run() {
        JTF.setText(new Date().toString());

    }

}
