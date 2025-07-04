package com.mayinlong.web.servlet;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.google.gson.Gson;
import com.mayinlong.entity.UserDB;
import com.mayinlong.service.UserService;
import com.mayinlong.utils.MD5;
import com.mayinlong.utils.PageTool;
import com.mayinlong.utils.PaginationUtils;
import com.mayinlong.utils.ResBean;

@WebServlet("/user")
public class UserSevlet extends BaseServlet{

	/**
	 * 用户
	 */
	private static final long serialVersionUID = 1L;
	private UserService userService = new UserService();
	/**
	 * 
	 * 分页 用户列表
	 * @param request
	 * @param response
	 * @throws ServletException
	 * @throws IOException
	 */
	public void list(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

		
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<UserDB> pageTool = userService.list(currentPage, pageSize);
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), "user?method=list");
		request.setAttribute("pagation", pagation);
		request.setAttribute("uList", pageTool.getRows());
		request.getRequestDispatcher("admin/admin_user.jsp").forward(request, response);
		
	}
	public void addUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException, IllegalAccessException, InvocationTargetException {
//		String account = request.getParameter("account");
//		String password = request.getParameter("password");
//		String name = request.getParameter("name");
//		String phone = request.getParameter("phone");
//		String maxNum = request.getParameter("maxNum");
//		String lendNum = request.getParameter("lendNum");
//		String role = request.getParameter("role");
//		UserDB userDB =new UserDB();
//		userDB.setAccount(account);
//		userDB.setPassword(password);
//		userDB.setPhone(phone);
//		userDB.setName(name);
//		userDB.setMaxNum(Integer.parseInt(maxNum));
//		userDB.setRole(Integer.parseInt(role));
//		userDB.setLendNum(Integer.parseInt(lendNum));
//		System.out.println(userDB);
		UserDB userDB = new UserDB();
		BeanUtils.populate(userDB, request.getParameterMap());
		System.out.println(1);
		System.out.println(request.getParameterMap());
		userDB.setTimes(0);
		userDB.setPassword(MD5.valueOf(userDB.getPassword()));
		System.out.println(userDB);
		userService.addUser(userDB);	    
		response.sendRedirect("user?method=list");

	}
	
	public void checkUser(HttpServletRequest request, HttpServletResponse response) throws IOException {
		String account = request.getParameter("account");
		UserDB userDB = new UserDB();
		userDB.setAccount(account);
		List<UserDB> list = userService.getList(userDB);
		ResBean resBean = new ResBean();
		if (list != null && list.size() > 0) {
			//request.setAttribute("msg", );
			resBean.setCode(400);
			resBean.setMsg("该账号已注册，请更换账号名");
		} else {
			resBean.setCode(200);
			resBean.setMsg("账号可用");
		}
		//将 resBean 转换成 json字符串
		Gson gson = new Gson();
		String json = gson.toJson(resBean);
		response.getWriter().print(json);
	}
	
	
	/**
	 * 管理员修改用户信息
	 * @param request
	 * @param response
	 */
	public void updUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
		UserDB userDB = new UserDB();
		BeanUtils.populate(userDB, request.getParameterMap());
		userService.updUser(userDB);
		response.sendRedirect("user?method=list");
	}
	
	
	/**
	 * 管理员删除用户信息
	 * @param request
	 * @param response
	 */
	public void delUser(HttpServletRequest request, HttpServletResponse response) throws Exception {
		String uid = request.getParameter("uid");
		userService.delUser(Integer.parseInt(uid));
		response.sendRedirect("user?method=list");
	}
	
	
	

}
