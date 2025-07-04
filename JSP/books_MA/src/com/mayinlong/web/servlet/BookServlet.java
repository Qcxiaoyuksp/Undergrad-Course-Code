package com.mayinlong.web.servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.google.gson.Gson;
import com.mayinlong.entity.BookDB;
import com.mayinlong.entity.TypeDB;
import com.mayinlong.entity.UserDB;
import com.mayinlong.service.BookService;
import com.mayinlong.service.TypeService;
import com.mayinlong.utils.PageTool;
import com.mayinlong.utils.PaginationUtils;
import com.mayinlong.utils.ResBean;

@WebServlet("/book")
public class BookServlet extends BaseServlet {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private BookService bookService = new BookService();
	private TypeService typeService = new TypeService();
	
	
public void listByPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	    UserDB userDB = (UserDB) request.getSession().getAttribute("userDB");
	//根据当前登陆的用户获取角色
	    Integer role = userDB.getRole();
	    String word = request.getParameter("word");
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<BookDB> pageTool = bookService.listByPage(currentPage, pageSize,word);
		String path = "book?method=listByPage";
		if (word != null && word != "") {
			path += "&word=" + word;
		}
		
		//生成前端分页按钮
		List<TypeDB> typeList = typeService.list(null, null);
		
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(),path);
		request.setAttribute("typeList", typeList);
		request.setAttribute("pagation", pagation);
		request.setAttribute("word", word);
		request.setAttribute("bList", pageTool.getRows());
		
		//根据role判断跳转的页面
				if (role == 1) {
					//普通用户
					request.getRequestDispatcher("user/select.jsp").forward(request, response);
				} else {
					//管理员
					request.getRequestDispatcher("admin/admin_book.jsp").forward(request, response);
				}
				
		
	}

/**
 * 论文名称校验
 * @param request
 * @param response
 * @throws IOException
 */
public void checkBook(HttpServletRequest request, HttpServletResponse response) throws IOException {
	String bookName = request.getParameter("bookName");
	List<BookDB> list = bookService.list(bookName);
	ResBean resBean = new ResBean();
	if (list != null && list.size() > 0) {
		resBean.setCode(400);
		resBean.setMsg("论文名称已存在");
	} else {
		resBean.setCode(200);
		resBean.setMsg("论文名称可以使用");
	}
	//将 resBean 转换成 json字符串
	Gson gson = new Gson();
	String json = gson.toJson(resBean);
	response.getWriter().print(json);
}

public void addBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
	BookDB bookDB = new BookDB();
	BeanUtils.populate(bookDB, request.getParameterMap());
	bookService.addBook(bookDB);
	response.sendRedirect("book?method=listByPage");
}





/**
 * 管理员修改论文信息
 * @param request
 * @param response
 */
public void updBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
	BookDB bookDB = new BookDB();
	BeanUtils.populate(bookDB, request.getParameterMap());
	bookService.updBook(bookDB);
	response.sendRedirect("book?method=listByPage");
}





/**
 * 管理员删除论文信息
 * @param request
 * @param response
 */
public void delBook(HttpServletRequest request, HttpServletResponse response) throws Exception {
	String bid = request.getParameter("bid");
	bookService.delBook(bid);
	response.sendRedirect("book?method=listByPage");
}
}
