package com.mayinlong.web.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.mayinlong.entity.UserDB;
import com.mayinlong.service.UserService;
import com.mayinlong.utils.MD5;

@WebServlet("/login")
public class LoginServlet extends BaseServlet{

	/**
	 * 
	 */
	private UserService userService =new UserService();
	private static final long serialVersionUID = 1L;
	public void login(HttpServletRequest request,HttpServletResponse response) throws ServletException, IOException {
		String account = request.getParameter("account");
		String password = request.getParameter("password");
		HttpSession session = request.getSession();
		UserDB userDB = userService.login(account,MD5.valueOf(password));
		if (userDB == null) {
			//’À∫≈√‹¬Î¥ÌŒÛ
			request.setAttribute("msg", "’À∫≈√‹¬Î¥ÌŒÛ");
			request.getRequestDispatcher("login.jsp").forward(request, response);
		} else {
			//µ«¬Ω≥…π¶
			session.setAttribute("userDB", userDB);
			request.getRequestDispatcher("index.jsp").forward(request, response);
		}
		
		
	}
	

}
