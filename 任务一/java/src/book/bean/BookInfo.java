package book.bean;

import java.sql.*;
import java.util.*;

/**
 * 构造BookInfo对象，对应数据库的BookInfo表
 * 提供了多个静态方法完成BookInfo对象与对应数据库表的所有新增、查询、修改、删除等操作
 * @author Leiyu
 * @version 1.0
 *
 */
public class BookInfo {
	
	private String id;
	private String bookname;
	private String author;
	private String price;
	public String getBookname() {
		return bookname;
	}
	public void setBookname(String bookname) {
		this.bookname = bookname;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getId() {
		return id;
	}
	/**
	 * 从BookInfo表中获取所有的图书信息
	 * @return BookInfo的数组
	 */
	public static ArrayList<BookInfo> getBookList(){
		ArrayList<BookInfo> list=new ArrayList<BookInfo>();
		String sql="select * from bookinfo";
		DBBean jdbc=new DBBean();
		ResultSet rs=jdbc.executeQuery(sql);
        try {
			while(rs.next()){
				BookInfo bi=new BookInfo();
				bi.setId(rs.getString("id"));
				bi.setBookname(rs.getString("bookname"));
				bi.setAuthor(rs.getString("author"));
				bi.setPrice(rs.getString("price"));
				list.add(bi);
			}
			 rs.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
        jdbc.close();
        return list;
	}

	/**
	 * 获取指定id的图书信息
	 * @param id 图书id
	 * @return 一个BookInfo对象
	 */
	public static BookInfo getBookById(String id){
		String sql="select * from bookinfo where id="+id;
		DBBean jdbc=new DBBean();
		ResultSet rs=jdbc.executeQuery(sql);
		BookInfo bi=new BookInfo();
        try {
			if(rs.next()){
				bi.setId(rs.getString("id"));
				bi.setBookname(rs.getString("bookname"));
				bi.setAuthor(rs.getString("author"));
				bi.setPrice(rs.getString("price"));
			}
			 rs.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
        jdbc.close();
        return bi;
	}

	/**
	 * 更新指定id的图书信息
	 * @param id 要更新的图书的id
	 * @param bookname 图书名称
	 * @param author 作者名称
	 * @param price 价格
	 * @return 修改的结果：1代表成功，0代表没有更新
	 */
	public static int updateBook(String id,String bookname,String author,String price){
		int result=0;
		String sql="update bookinfo set bookname='"+bookname+"',author='"+author+"',price="+price+" where id="+id;
		DBBean jdbc=new DBBean();
		result=jdbc.executeUpdate(sql);
		jdbc.close();
		return result;
	}
	
	/**
	 * 删除指定id的图书
	 * @param id 图书id
	 * @return 删除的结果：1代表成功，0代表没有删除
	 */
	public static int deleteBook(String id){
		int result=0;
		String sql="delete from bookinfo where id="+id;
		DBBean jdbc=new DBBean();
		result=jdbc.executeUpdate(sql);
		jdbc.close();
		return result;
	}
	
	/**
	 * 增加一本图书
	 * @param bookname 图书名称
	 * @param author 作者
	 * @param price 价格
	 * @return 新增的结果：1代表成功，0代表没有增加
	 */
	public static int addBook(String bookname,String author,String price){
		int result=0;
		String sql="insert into bookinfo values(null,'"+bookname+"','"+author+"',"+price+")";
		DBBean jdbc=new DBBean();
		result=jdbc.executeUpdate(sql);
		jdbc.close();
		return result;
	}
}
