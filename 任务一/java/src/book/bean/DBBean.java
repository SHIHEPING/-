package book.bean;

import java.sql.*;

/**
 * 完成与数据库的连接和数据的访问
 * @author Leiyu
 * @version 1.0
 *
 */
public class DBBean {
	private String driverStr = "com.mysql.jdbc.Driver";
	private String connStr = "jdbc:mysql://45.76.78.208:3306/book?useSSL=false&useUnicode=true&characterEncoding=utf-8";
	private String dbusername = "root";
	private String dbpassword = "TiedaoXinxi";
	private Connection conn = null;
	private Statement stmt = null;

	public DBBean() {
		try {
			Class.forName(driverStr);
			conn = DriverManager.getConnection(connStr, dbusername, dbpassword);
			stmt = conn.createStatement();
		} catch (Exception ex) {
			System.out.println("数据库连接失败！");
		}
	}

	/**
	 * 执行更新操作
	 * @param s
	 * SQL语句
	 * @return
	 * 更新操作的结果
	 */
	public int executeUpdate(String s) {
		int result = 0;
		try {
			result = stmt.executeUpdate(s);
		} catch (Exception ex) {
			System.out.println("更新出现异常！");
		}
		return result;
	}
	
	/**
	 * 执行查询操作
	 * @param s
	 * SQL语句
	 * @return
	 * 查询结果
	 */
	public ResultSet executeQuery(String s) {
		ResultSet rs = null;
		try {
			rs = stmt.executeQuery(s);
		} catch (Exception ex) {
			System.out.println("查询出现异常！");
		}
		return rs;
	}

	/**
	 * 关闭数据库
	 */
	public void close() {
		try {
			stmt.close();
			conn.close();
		} catch (Exception e) {
		}
	}
}
