using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

using System.Web.Services.Protocols;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Data.OracleClient;
using System.IO; //Upload Picture File
using Microsoft.VisualBasic.Devices; //需先Add Microsoft.VisualBasic.dll

namespace wsTstTest
{
    /// <summary>
    /// Summary description for wsTstTest
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class wsTstTest : System.Web.Services.WebService
    {
        #region "TST_TEST"

        //動態Oracle SQL語法(強型別)
        [WebMethod(Description = "動態Oracle SQL語法(強型別)")]
        public dsTstTest GetTstTest(string stWhereCommand)
        {
            dsTstTest ds_TstTest = new dsTstTest();
            OracleDataAdapter daSQL = new OracleDataAdapter();
            OracleConnection conn = new OracleConnection();
            try
            {
                string getTNS = this._GetDb("TNS", "ORACLE");
                conn.ConnectionString = getTNS;
                OracleCommand stCMD = new OracleCommand(stWhereCommand, conn);
                daSQL.SelectCommand = stCMD;
                daSQL.Fill(ds_TstTest.Tables["TST_TEST"]);
                return ds_TstTest;
            }
            catch (Exception ex)
            {
                return null;
            }
            finally
            {
                conn.Dispose();
                conn.Close();
            }
        }

        [WebMethod(Description = "TST_TEST檔維護")]
        public string SetTstTest(dsTstTest qDaTaSet)
        {
            dsTstTestTableAdapters.TST_TESTTableAdapter da = new dsTstTestTableAdapters.TST_TESTTableAdapter();
            string mConn = "";
            try
            {
                mConn = this._GetDb("TNS", "ORACLE");
                da.Connection.ConnectionString = mConn;
                da.Update(qDaTaSet);
                return "OK";
            }
            catch (Exception ex)
            {
                string getError = ex.Message.Substring(0, (ex.Message.Length - 1));
                return getError;
            }
        }

        #endregion

        #region "GetQueryCommand"

        //動態Oracle SQL語法(弱型別) - 2
        [WebMethod(Description = "動態Oracle SQL語法(弱型別)")]
        public DataSet GetDynamicSQL(string qSqlCommand)
        {
            DataSet dsSql = new DataSet();
            OracleDataAdapter daSql = new OracleDataAdapter();
            DataTable dtSql = new DataTable();
            OracleConnection Conn = new OracleConnection();
            OracleCommand cmd = new OracleCommand();
            dsSql.Tables.Add(dtSql);
            try
            {
                string getTNS = this._GetDb("TNS", "ORACLE");
                Conn.ConnectionString = getTNS;
                cmd.CommandText = qSqlCommand;
                cmd.Connection = Conn;
                daSql.SelectCommand = cmd;
                daSql.Fill(dsSql.Tables[0]);
                return dsSql;
            }
            catch (Exception ex)
            {
                return null;
            }
        }
        #endregion

        #region "副程式"

        public string _GetDb(string mLabel, string mDb)
        {
            string mResult = string.Empty;
            DataSet ds = new DataSet();
            //--------開啟 xml --------
            ds.ReadXml("C:\\Wearo7_Install\\Domain.xml");
            //--------讀取 DataSet --------
            foreach (DataColumn column in ds.Tables[mLabel].Columns)
            {
                if (column.ColumnName == mDb)
                {
                    mResult = ds.Tables[mLabel].Rows[0][column.ColumnName].ToString();
                }
            }
            return mResult;
        }

        #endregion
    }
}
