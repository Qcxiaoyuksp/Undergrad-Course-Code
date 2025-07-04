//package books.servlet.filter;
//
//import java.io.IOException;
//
//import javax.servlet.Filter;
//import javax.servlet.FilterChain;
//import javax.servlet.FilterConfig;
//import javax.servlet.ServletException;
//import javax.servlet.ServletRequest;
//import javax.servlet.ServletResponse;
//import javax.servlet.annotation.WebFilter;
//import javax.servlet.http.HttpServletRequest;
//import javax.servlet.http.HttpServletResponse;
//
//@WebFilter("/*")
//public class LoginFilter implements Filter {
//	
//	@Override
//	public void init(FilterConfig arg0) throws ServletException {
//		// TODO Auto-generated method stub
//		
//	}
//	
//
//	@Override
//	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
//			throws IOException, ServletException {
//		// 强转请求和响应
//		HttpServletRequest req = (HttpServletRequest) request;
//		HttpServletResponse res = (HttpServletResponse) response;
//		//获取请求的路径
//		String uri = req.getRequestURI();
//		//路径判断，部分内容不拦截
//		if (uri.contains("/login") || uri.contains("/static")) {
//			//直接放行
//			chain.doFilter(req, res);
//		} else {
//			//验证是否登陆
//			Object userDB = req.getSession().getAttribute("userDB");
//			if (userDB != null) {
//				//已登录，放行
//				chain.doFilter(req, res);
//			} else {
//				//未登录
//				res.sendRedirect("login.jsp");
//			}
//		}
//	}
//
//	@Override
//	public void destroy() {
//		// TODO Auto-generated method stub
//		
//	}

//}
