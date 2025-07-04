package books.servlet;


import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;

import com.google.gson.Gson;

import books.entity.UserDB;
import books.service.UserService;
import books.utils.MD5;
import books.utils.PageTool;
import books.utils.PaginationUtils;
import books.utils.ResBean;

@WebServlet("/user")
public class UserServlet extends BaseServlet {

	private static final long serialVersionUID = 1L;
	
	private UserService userService=new UserService();
	
	
	/**
	 * 用户列表  分页
	 * @param request
	 * @param response
	 * @throws IOException 
	 * @throws ServletException 
	 */
	
	public void list(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String currentPage = request.getParameter("pageNum");
		String pageSize = request.getParameter("pageSize");
		PageTool<UserDB> pageTool = userService.list(currentPage, pageSize, null);
		//生成前端分页按钮
		String pagation = PaginationUtils.getPagation(pageTool.getTotalCount(), pageTool.getCurrentPage(), pageTool.getPageSize(), "user?method=list");
		request.setAttribute("pagation", pagation);
		request.setAttribute("uList", pageTool.getRows());
		request.getRequestDispatcher("admin/admin_user.jsp").forward(request, response);
	}
	/*
	public void list(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		List<UserDB> list=userService.list();
		request.setAttribute("ulist", list);
		request.getRequestDispatcher("admin/admin_user.jsp").forward(request, response);
	}
	*/
	
	/**
	 * 添加用户
	 * @param request
	 * @param response
	 * @throws ServletException
	 * @throws IOException
	 * @throws IllegalAccessException
	 * @throws InvocationTargetException
	 */
	public void addUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException, IllegalAccessException, InvocationTargetException {
		
		/*
		 * beanutils:简化过程
		 * String account=request.getParamater("account");
		 * userDB.setAccount(account);....
		 * 
		 * */
		String account=request.getParameter("account");
		String password=request.getParameter("password");
		String name=request.getParameter("name");
		String phone=request.getParameter("phone");
		String maxNum=request.getParameter("maxNum");
		String lendNum=request.getParameter("lendNum");
		String role=request.getParameter("role");
		
		UserDB userDB = new UserDB();
		
		userDB.setAccount(account);
		userDB.setLendNum(Integer.parseInt(lendNum));
		userDB.setMaxNum(Integer.parseInt(maxNum));
		userDB.setName(name);
		userDB.setPassword(password);
		userDB.setPhone(phone);
		userDB.setRole(Integer.parseInt(role));
		
		
		//BeanUtils.populate(userDB, request.getParameterMap());//request.getParameterMap()方法将获得的所有数据放到map集合中
		userDB.setTimes(0); //新用户借阅量0
		userDB.setPassword(MD5.valueOf(userDB.getPassword())); //md5加密密码
		System.out.println(userDB);
		userService.addUser(userDB);
		response.sendRedirect("user?method=list"); //刷新
	}
	
	/**  异步请求
	 * 校验用户账号是否存在
	 * @param request
	 * @param response
	 * @throws IOException 
	 */
	public void checkUser(HttpServletRequest request, HttpServletResponse response) throws IOException {
		String account = request.getParameter("account");
		UserDB userDB = new UserDB();
		userDB.setAccount(account);
		List<UserDB> list = userService.getList(userDB);
		ResBean resBean = new ResBean(); //ResBean  books.utils
		if (list != null && list.size() > 0) {//账号已存在
			//request.setAttribute("msg", );
			resBean.setCode(400);
			resBean.setMsg("账号被占用");
		} else {
			resBean.setCode(200);
			resBean.setMsg("账号可以使用");
		}
		//将 resBean 转换成 json字符串
		Gson gson = new Gson(); //jar包
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
