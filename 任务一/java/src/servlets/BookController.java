package servlets;

import java.io.IOException;
import java.util.ArrayList;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import book.bean.BookInfo;

/**
 * 用来接收客户端的后缀为do的请求
 * @author Leiyu
 * @version 1.0
 *
 */
@WebServlet("*.do")
public class BookController extends HttpServlet {

	private static final long serialVersionUID = 1L;

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request,response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		request.setCharacterEncoding("utf-8");
		
		String actionUrl=request.getServletPath();		//鑾峰彇鐢ㄦ埛璇锋眰鐨勮矾寰�

		if(actionUrl.equals("/index.do")){			//查询所有图书
			ArrayList<BookInfo> list=BookInfo.getBookList();  // 调用BookInfo的getBookList方法查询所有图书，赋值给list
			request.setAttribute("list", list);					//在request增加属性list，其结果为list对象
			request.getRequestDispatcher("/index.jsp").forward(request, response);//重定向至index.jsp进行显示
		
		}else if(actionUrl.equals("/add.do")){			//新增图书
			String name=request.getParameter("bookname");
			String author=request.getParameter("author");
			String price=request.getParameter("price");
			int r = BookInfo.addBook(name, author, price);	//调用BookInfor的addBook方法完成
			if(r==1)
				request.getRequestDispatcher("success.html").forward(request, response); //成功的话重定向至success.html
			else
				request.getRequestDispatcher("failure.html").forward(request, response); //失败的话重定向至failure.html
		
		}else if(actionUrl.equals("/edit.do")){			//客户端要对指定id的图书进行修改			
			String id=request.getParameter("id");
			BookInfo bi=BookInfo.getBookById(id);		//调用BookInfo的getBookById方法获取图书信息，赋值给bi对象
			request.setAttribute("bi", bi);				//将bi对象增加到request的属性中
			request.getRequestDispatcher("/edit.jsp").forward(request, response);//重定向至edit.jsp进行显示
		
		}else if(actionUrl.equals("/update.do")){	    //用户输入要修改的图书的信息之后需要保存到数据库
			String id=request.getParameter("id");
			String name=request.getParameter("bookname");
			String author=request.getParameter("author");
			String price=request.getParameter("price");
			int r=BookInfo.updateBook(id,name, author, price);//调用BookInfo的updateBook方法实现
			if(r==1)
				request.getRequestDispatcher("/success.html").forward(request, response);//成功的话重定向至success.html
			else
				request.getRequestDispatcher("/failure.html").forward(request, response);//失败的话重定向至failure.html
		
		}else if(actionUrl.equals("/delete.do")){			//用户需要删除指定id的图书
			String id=request.getParameter("id");
			int r=BookInfo.deleteBook(id);			//调用BookInfo的deleteBook方法实现
			if(r==1)
				request.getRequestDispatcher("/success.html").forward(request, response);//成功的话重定向至success.html
			else
				request.getRequestDispatcher("/failure.html").forward(request, response);//失败的话重定向至failure.html
		}
	}

}
