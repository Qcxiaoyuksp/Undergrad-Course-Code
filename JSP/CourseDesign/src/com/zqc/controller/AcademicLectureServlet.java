package com.zqc.controller;

import com.zqc.entity.AcademicLecture;
import com.zqc.service.AcademicLectureService;
import com.zqc.service.impl.AcademicLectureServiceImpl;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Time;
import java.util.Date;

@WebServlet("/academicLecture")
public class AcademicLectureServlet extends HttpServlet {

    private AcademicLectureService academicLectureService = new AcademicLectureServiceImpl();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        String method = req.getParameter("method");

        switch (method){
            case "list":
                req.setAttribute("list", this.academicLectureService.list());
                req.getRequestDispatcher("adminmanager.jsp").forward(req, resp);
                break;
            case "search":
                String key = req.getParameter("key");
                String value = req.getParameter("value");
                req.setAttribute("list", this.academicLectureService.search(key, value));
                req.getRequestDispatcher("adminmanager.jsp").forward(req, resp);
                break;
            case "save":
                String title = req.getParameter("title");
                String department_undertake = req.getParameter("department_undertake");
                String speaker = req.getParameter("speaker");
                String department_speaker = req.getParameter("department_speaker");
                String title_speaker = req.getParameter("title_speaker");
                String data_lecture = req.getParameter("data_lecture");
                String time = req.getParameter("time");
                String address = req.getParameter("address");
                this.academicLectureService.save(new AcademicLecture(title, department_undertake, speaker, department_speaker, title_speaker,data_lecture,time,address));
                resp.sendRedirect("/academicLecture?method=list");
                break;
            case "update":
                String idStr = req.getParameter("id");
                Integer id = Integer.parseInt(idStr);
                title = req.getParameter("title");
                department_undertake = req.getParameter("department_undertake");
                speaker = req.getParameter("speaker");
                department_speaker = req.getParameter("department_speaker");
                title_speaker = req.getParameter("title_speaker");
                data_lecture = req.getParameter("data_lecture");
                time = req.getParameter("time");
                address = req.getParameter("address");
                this.academicLectureService.update(new AcademicLecture(id,title, department_undertake, speaker, department_speaker, title_speaker,data_lecture,time,address));
                resp.sendRedirect("/academicLecture?method=list");
                break;
            case "delete":
                idStr = req.getParameter("id");
                id = Integer.parseInt(idStr);
                this.academicLectureService.delete(id);
                resp.sendRedirect("/academicLecture?method=list");
                break;
        }
    }
}
