package books.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import books.entity.UserDB;
import books.service.UserService;
import books.utils.MD5;

/*
 * 用户登陆
 */
@WebServlet("/login")
public class LoginServlet extends BaseServlet {

	private static final long serialVersionUID = 1L;
	
	private UserService userService=new UserService();
	
	public void login(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException
	{
		String account = request.getParameter("account");
		String password = request.getParameter("password");
		HttpSession session=request.getSession();
		UserDB userDB=userService.login(account, MD5.valueOf(password)); //使用MD5进行加密
		//System.out.println(account);
		//System.out.println(password);
		if(userDB==null)
		{//用户不存在或者密码错误
			request.setAttribute("msg", "账号密码错误");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		}
		else//查出该用户
		{
			session.setAttribute("userDB",userDB);
			request.getRequestDispatcher("index.jsp").forward(request,response);
		}
	}
}
