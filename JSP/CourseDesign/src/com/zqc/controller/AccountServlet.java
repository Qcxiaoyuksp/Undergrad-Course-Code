package com.zqc.controller;

import com.zqc.dto.SystemAdminDto;
import com.zqc.entity.SystemAdmin;
import com.zqc.service.SystemAdminService;
import com.zqc.service.impl.SystemAdminServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/account")
public class AccountServlet extends HttpServlet {
    private SystemAdminService systemAdminService = new SystemAdminServiceImpl();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        String method = req.getParameter("method");
        switch (method){
            case "login":
                String userID = req.getParameter("userID");
                String password = req.getParameter("password");
                SystemAdminDto systemAdminDto = this.systemAdminService.login(userID, password);
                switch (systemAdminDto.getCode()){
                    case -1:
                        req.setAttribute("userIDError", "工号/学号不存在");
                        req.getRequestDispatcher("login.jsp").forward(req, resp);
                        break;
                    case -2:
                        req.setAttribute("passwordError", "密码错误");
                        req.getRequestDispatcher("login.jsp").forward(req, resp);
                        break;
                    case 0:
                        //跳转到登录成功界面
                        HttpSession session = req.getSession();
                        session.setAttribute("systemAdmin", systemAdminDto.getSystemAdmin());
                        resp.sendRedirect("/systemadmin.jsp");
                        break;
                }
                break;
            case "logout":
                req.getSession().invalidate();
                resp.sendRedirect("/login.jsp");
                break;
            case "register":
                String name = req.getParameter("userFullname");
                String gender = req.getParameter("userGender");
                String nation = req.getParameter("userNation");
                String birth_date = req.getParameter("userBirth");
                String education = req.getParameter("educationLevel");
                String degree = req.getParameter("academicDegree");
                String title = req.getParameter("academicTitle");
                String major = req.getParameter("userSpeciality");
                String graduation_university = req.getParameter("educationSchool");
                String graduation_date = req.getParameter("educationTime");
                String department = req.getParameter("department");
                String address = req.getParameter("address");
                String phone_work = req.getParameter("officePhone");
                String phone_home = req.getParameter("homePhone");
                String email = req.getParameter("email");
                userID = req.getParameter("username");
                password = req.getParameter("password");

                this.systemAdminService.register(new SystemAdmin(userID, password, name, gender, birth_date, nation, department, address, phone_work,phone_home,email,education,degree,title,major,graduation_university,graduation_date));
                req.getRequestDispatcher("login.jsp").forward(req,resp);
                break;
        }

    }
}
