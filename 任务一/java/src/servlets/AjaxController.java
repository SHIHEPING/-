package servlets;

import java.io.IOException;
import java.util.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.*;

import book.bean.BookInfo;

/**
 * 接受客户端后缀为action的请求，并进行处理，并返回响应
 * @author Leiyu
 * @version 1.0
 *
 */
@WebServlet("*.action")
public class AjaxController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public AjaxController() {
		super();
		// TODO Auto-generated constructor stub
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request, response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		
		String actionUrl = request.getServletPath(); //获取客户端的访问URL地址信息
		System.out.println(actionUrl);
		if (actionUrl.equals("/list.action")) { //查询所有图书
			ArrayList<BookInfo> list = BookInfo.getBookList(); // 调用BookInfo的getBookList方法完成
			//使用JSONArray对象将结果构建为json对象并输出到客户端
			JSONArray jsonArray = new JSONArray();
			for (int i = 0; i < list.size(); i++) {
				BookInfo book = list.get(i);
				Map<String, Object> map = new HashMap<String, Object>();
				map.put("id",  book.getId());
				map.put("bookname", book.getBookname());
				map.put("author", book.getAuthor());
				map.put("price", book.getPrice());
				JSONObject BookObj = new JSONObject(map);
				jsonArray.put(BookObj);
			}
			//向客户端返回json结果
			response.getWriter().print(jsonArray.toString());
			
		} else if (actionUrl.equals("/add.action")) { // 增加图书操作
			String name = request.getParameter("bookname");
			String author = request.getParameter("author");
			String price = request.getParameter("price");
			System.out.println(name);
			int r = BookInfo.addBook(name, author, price); // 调用BookInfo的addBook方法完成
			//向客户端返回结果
			response.getWriter().print(r);

		} else if (actionUrl.equals("/edit.action")) { //编辑图书操作
			String id = request.getParameter("id");
			BookInfo bi = BookInfo.getBookById(id); // 调用BookInfo的getBookById方法完成
			//将该对象构建为json数据
			Map<String, Object> map = new HashMap<String, Object>();
			map.put("id",  bi.getId());
			map.put("bookname", bi.getBookname());
			map.put("author", bi.getAuthor());
			map.put("price", bi.getPrice());
			JSONObject BookObj = new JSONObject(map);
			//向客户端返回结果
			response.getWriter().print(BookObj.toString());
			
		} else if (actionUrl.equals("/update.action")) { //更新图书操作
			String id = request.getParameter("id");
			String name = request.getParameter("bookname");
			String author = request.getParameter("author");
			String price = request.getParameter("price");
			int r = BookInfo.updateBook(id, name, author, price);//调用BookInfo的updateBook方法完成
			response.getWriter().print(r);  //向客户端返回结果

		} else if (actionUrl.equals("/delete.action")) { //删除图书操作
			String id = request.getParameter("id");
			int r = BookInfo.deleteBook(id); //调用BookInfo的deleteBook方法完成
			response.getWriter().print(r); //向客户端返回结果
		}
	}

}
