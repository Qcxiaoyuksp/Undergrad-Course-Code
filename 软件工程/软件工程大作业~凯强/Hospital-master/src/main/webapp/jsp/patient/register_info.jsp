<%@ page language="java" import="java.util.*" pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
    <head>
        <base href="<%=basePath%>">

        <title>My JSP 'register.jsp' starting page</title>
        <meta http-equiv="pragma" content="no-cache">
        <meta http-equiv="cache-control" content="no-cache">
        <meta http-equiv="expires" content="0">
        <meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
        <meta http-equiv="description" content="This is my page">
        <%--        <link rel="stylesheet" type="text/css" href="styles.css">--%>

        <link href="../../css/register_info.css" type="text/css" rel="stylesheet">
        <link href="../../css/background.css" rel="stylesheet">
        <link href="../../css/readerBlock.css" rel="stylesheet">
        <link href="../../css/menu.css" rel="stylesheet">

        <script type="text/javascript" src="../../js/jquery-3.3.1.min.js"></script>
        <script type="text/javascript">
            function jump() {
                window.location.href = '/register?method=addRegister&doctorStateId=${doctor_state.id}';
                window.confirm('挂号成功! 将返回登录页面!');
                window.location.href = 'login1.jsp';
            }
        </script>

        <%@ include file="../../leftHead.jsp" %>
    </head>

    <body>
        <%@ include file="../../heading.jsp" %>

        <div id="main">

            <%--侧边菜单栏--%>
            <!--侧栏界面设计-->
                <div id="mySidenav" class="sidenav">
                    <a href="javascript:void(0)" class="closebtn" onclick="closeNav()">&times;</a>
                    <a href="/register?method=patientCase&patientId=${sessionScope.patient.id}">病例信息</a>
                    <br/><br/>
                    <a href="/register">预约挂号</a>
                </div>

            <div class="div_menu">
                <%--    <h2>侧边栏实例 - 页面主体向右移动</h2>--%>
                <%--    <p>点击以下菜单图标打开侧边栏，主体内容向右偏移。主体内容添加黑色透明背景</p>--%>
                <script>openNav()</script>
                <span class="menu" onclick="openNav()">&#9776; 菜单栏</span>
            </div>

            <div class="navigation">
                <div class="readerBlock1">
                    当前位置:&nbsp;&nbsp;<a href="/register" id="select1">选择科室</a>->
                    <a href="/register?method=findAllDoctor&departmentId=${departmentId}" id="select2">选择日期和医生</a>->确认挂号
                </div>

                <div class="readerBlock2">欢迎回来&nbsp;: <a
                        href="/book?method=findAllMedicalRecord" class="a">${sessionScope.patient.name}</a>&nbsp;<a
                        href="/logout">注销</a>
                </div>
            </div>

            <center>
                <h2>挂号信息</h2><br/>
                <table class="table" cellspacing="0">
                    <tr>
                        <td>就诊日期:</td>
                        <td>${doctor_state.date}</td>
                    </tr>
                    <br/>

                    <tr>
                        <td>就诊科室:</td>
                        <td>${departmentName}</td>
                    </tr>
                    <br/>

                    <tr>
                        <td>医生姓名:</td>
                        <td>${doctor_state.doctor.name}</td>
                    </tr>
                    <br/>

                    <tr>
                        <td>医生职称:</td>
                        <td>${doctor_state.doctor.title}</td>
                    </tr>
                    <br/>

                    <tr>
                        <td>挂号费用:</td>
                        <td>${doctor_state.fee}</td>
                    </tr>
                    <br/>

                </table>
                <button id="btn" onclick=jump()>
                    确认挂号
                </button>
            </center>


            <%@ include file="../../footer.jsp" %>
    </body>
</html>
